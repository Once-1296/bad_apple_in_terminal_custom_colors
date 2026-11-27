#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <csignal>
#include <iostream>
#include <opencv5/opencv2/opencv.hpp>
#include <optional>
#include <print>
#include <string>
#include <string_view>
#include <sys/ioctl.h>
#include <thread>
#include <unistd.h>

namespace {

std::atomic<bool> g_running{true};

void handleSigint(int)
{
    g_running = false;
}

struct Rgb
{
    int r{0};
    int g{0};
    int b{0};

    bool operator==(const Rgb&) const = default;
    bool operator!=(const Rgb&) const = default;
};

std::optional<Rgb> parseHexColor(std::string_view s)
{
    if (!s.empty() && s.front() == '#') {
        s.remove_prefix(1);
    }
    if (s.size() != 6) {
        return std::nullopt;
    }
    int val = 0;
    auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), val, 16);
    if (ec != std::errc{} || ptr != s.data() + s.size()) {
        return std::nullopt;
    }
    return Rgb{
        .r = (val >> 16) & 0xFF,
        .g = (val >> 8) & 0xFF,
        .b = val & 0xFF,
    };
}

void appendFg(std::string& out, Rgb c)
{
    out += "\033[38;2;" + std::to_string(c.r) + ";" + std::to_string(c.g) + ";" + std::to_string(c.b) + "m";
}

void appendBg(std::string& out, Rgb c)
{
    out += "\033[48;2;" + std::to_string(c.r) + ";" + std::to_string(c.g) + ";" + std::to_string(c.b) + "m";
}

} // namespace

int main(int argc, char* argv[])
{
    std::string videoPath;
    int argIdx = 1;

    if (argc >= 2 && std::string_view{argv[1]} != "--") {
        videoPath = argv[1];
        argIdx = 2;
    }
#ifdef BAD_APPLE_DEFAULT_VIDEO
    else if (std::string_view{BAD_APPLE_DEFAULT_VIDEO}.size() > 0) {
        videoPath = BAD_APPLE_DEFAULT_VIDEO;
    }
#endif
    else {
        std::println("Usage: bad_apple_terminal <path_to_video> [dark_hex light_hex]");
        return 1;
    }

    Rgb darkColor{0, 0, 0};
    Rgb lightColor{255, 255, 255};

    if (argc - argIdx >= 2) {
        auto parsedDark = parseHexColor(argv[argIdx]);
        auto parsedLight = parseHexColor(argv[argIdx + 1]);
        if (!parsedDark || !parsedLight) {
            std::cerr << "Error: Colors must be 6-digit hex RGB (e.g. ff0000 00ff00).\n";
            return 1;
        }
        darkColor = *parsedDark;
        lightColor = *parsedLight;
    }

    std::signal(SIGINT, handleSigint);

    cv::VideoCapture cap(videoPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file: " << videoPath << "\n";
        return -1;
    }

    struct winsize w{};
    int termCols = 100;
    int termRows = 35;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        if (w.ws_col > 0)
            termCols = w.ws_col;
        if (w.ws_row > 0)
            termRows = w.ws_row;
    }

    int srcW = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int srcH = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    int maxW = (srcW > 0) ? std::min(termCols, srcW) : termCols;
    int maxH = (srcH > 0) ? std::min(termRows * 2, srcH) : (termRows * 2);

    int renderWidth = std::max(1, maxW);
    int renderHeight = std::max(2, (maxH / 2) * 2);
    int charRows = renderHeight / 2;

    double fps = cap.get(cv::CAP_PROP_FPS);
    if (fps <= 0.0) {
        fps = 30.0;
    }
    auto frameDuration = std::chrono::microseconds(static_cast<long long>(1'000'000.0 / fps));

    std::cout << "\033[?1049h\033[2J\033[?25l" << std::flush;

    cv::Mat frame, resized;
    std::string output;
    output.reserve(static_cast<std::size_t>(renderWidth) * static_cast<std::size_t>(charRows) * 24);

    auto nextFrameTime = std::chrono::steady_clock::now();

    while (g_running) {
        if (!cap.read(frame) || frame.empty()) {
            break;
        }

        cv::resize(frame, resized, cv::Size(renderWidth, renderHeight), 0, 0, cv::INTER_AREA);

        output = "\033[H";
        std::optional<Rgb> lastFg;
        std::optional<Rgb> lastBg;

        for (int r = 0; r < renderHeight; r += 2) {
            for (int c = 0; c < renderWidth; ++c) {
                cv::Vec3b topPx = resized.at<cv::Vec3b>(r, c);
                cv::Vec3b botPx = resized.at<cv::Vec3b>(r + 1, c);

                bool topWhite = (static_cast<int>(topPx[0]) + topPx[1] + topPx[2]) > 381;
                bool botWhite = (static_cast<int>(botPx[0]) + botPx[1] + botPx[2]) > 381;

                Rgb fg = topWhite ? lightColor : darkColor;
                Rgb bg = botWhite ? lightColor : darkColor;

                bool fgChanged = (!lastFg || *lastFg != fg);
                bool bgChanged = (!lastBg || *lastBg != bg);

                if (fgChanged && bgChanged) {
                    appendFg(output, fg);
                    appendBg(output, bg);
                    lastFg = fg;
                    lastBg = bg;
                } else if (fgChanged) {
                    appendFg(output, fg);
                    lastFg = fg;
                } else if (bgChanged) {
                    appendBg(output, bg);
                    lastBg = bg;
                }

                output += "▀";
            }

            output += "\033[0m";
            lastFg.reset();
            lastBg.reset();
            if (r + 2 < renderHeight) {
                output += '\n';
            }
        }

        std::cout << output << std::flush;

        nextFrameTime += frameDuration;
        std::this_thread::sleep_until(nextFrameTime);
    }

    std::cout << "\033[0m\033[?25h\033[?1049l" << std::flush;
    cap.release();

    return 0;
}
