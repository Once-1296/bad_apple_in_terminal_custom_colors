# Managed by lilim — rewritten by `lilim add`, `lilim remove` and `lilim sync`.
# Installed automatically when CMake configures (cmake/conan_provider.cmake).
from conan import ConanFile

class BadAppleTerminal(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeConfigDeps"

    def requirements(self):
        self.requires("opencv/4.14.0", force=True)

    def configure(self):
        # Disable GUI (xorg/wayland/gtk/qt) and heavy unused OpenCV codecs/modules
        opencv_off = (
            "with_gtk",
            "with_qt",
            "with_wayland",
            "with_jpeg",
            "with_png",
            "with_tiff",
            "with_jpeg2000",
            "with_webp",
            "with_openexr",
            "with_eigen",
            "with_tesseract",
            "with_gdal",
            "with_quirc",
            "with_protobuf",
            "dnn",
            "calib3d",
            "features2d",
            "flann",
            "gapi",
            "highgui",
            "ml",
            "objdetect",
            "photo",
            "stitching",
            "video",
        )
        for opt in opencv_off:
            setattr(self.options["opencv"], opt, False)

        # Keep ffmpeg minimal so it doesn't pull pulseaudio, x11, vaapi, vdpau, or heavy encoders
        ffmpeg_off = (
            "with_pulse",
            "with_libalsa",
            "with_xcb",
            "with_xlib",
            "with_vaapi",
            "with_vdpau",
            "with_vulkan",
            "with_libx264",
            "with_libx265",
            "with_libsvtav1",
            "with_libaom",
            "with_libfdk_aac",
            "with_libmp3lame",
            "with_libopus",
            "with_libvorbis",
            "with_libvpx",
            "with_libwebp",
            "with_openjpeg",
            "with_openh264",
            "with_dav1d",
            "with_programs",
        )
        for opt in ffmpeg_off:
            setattr(self.options["ffmpeg"], opt, False)
        setattr(self.options["opencv"],"with_dav1d",False)
        setattr(self.options["opencv"],"with_openssl",False)
