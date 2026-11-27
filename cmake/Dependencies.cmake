# Managed by lilim — rewritten by `lilim add`, `lilim remove` and `lilim sync`.
# Packages come from Conan (conanfile.py, installed during configure by cmake/conan_provider.cmake).

find_package(OpenCV CONFIG REQUIRED)

# Libraries linked by the project's targets.
set(LILIM_DEPENDENCIES OpenCV::OpenCV)
