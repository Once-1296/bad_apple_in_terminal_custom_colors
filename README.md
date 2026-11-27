# bad-apple-terminal

bad apple in terminal

## Build

Requirements: CMake 3.25+, Ninja, a C++23 compiler and [Conan 2](https://conan.io) (`pipx install conan`).
Dependencies are installed automatically when CMake configures.

```sh
cmake --preset debug
cmake --build --preset debug
```

Use the `release` preset for an optimised build. On Windows, run these from a
*Developer PowerShell for VS* so the MSVC tools are on `PATH`.

## CI

Builds and tests on linux-gcc, linux-clang, windows-msvc with gitlab
(`.gitlab-ci.yml`).

## Dependencies

None yet — add one with `lilim add dep <name>`.

_Generated with [lilim](https://gitlab.com/ayushsshukla/lilim)._
