# bad-apple-terminal

bad apple in terminal

https://archive.org/details/bad-apple-full-version-w-video-lyrics-in-romaji-translation-in-english
video taken from here

## Build

Requirements: CMake 3.25+, Ninja, a C++23 compiler and [Conan 2](https://conan.io) (`pipx install conan`).
Dependencies are installed automatically when CMake configures.

```sh
cmake --preset debug
cmake --build --preset debug

```

Use the `release` preset for an optimised build. On Windows, run these from a
*Developer PowerShell for VS* so the MSVC tools are on `PATH`.

## to run
```sh
cmake --preset release
cmake --build --preset release
# ./release_exe <path_to_file> [color_for_dark_pixels] [color_for_light_pixels]
# color is in hex form, so like ffffff is white, 000000 is black
./build/release/bad-apple-terminal Bad\ Apple\!\!\ -\ Full\ Version\ w_video\ \[Lyrics\ in\ Romaji,\ Translation\ in\ English\].mp4 1e0c0f d4d3ca
```
pls dont resize terminal window after it starts, it causes UB and u cannot exit without killing terminal or spamming CTRL C.

## CI

Builds and tests on linux-gcc, linux-clang, windows-msvc with gitlab
(`.gitlab-ci.yml`).

## Dependencies

None yet — add one with `lilim add dep <name>`.

_Generated with [lilim](https://gitlab.com/ayushsshukla/lilim)._
