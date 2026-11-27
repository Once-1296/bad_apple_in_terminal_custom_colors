cmake_minimum_required(VERSION 3.25)

# Prevent lilim-setup.cmake from attaching conan_provider.cmake
set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES "" CACHE STRING "" FORCE)
include(cmake/lilim-setup.cmake)

project(bad-apple-terminal
    VERSION 0.1.0
    DESCRIPTION "bad apple in terminal"
    LANGUAGES CXX)

include(cmake/lilim-begin.cmake)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bad-apple-terminal src/main.cpp)

target_include_directories(bad-apple-terminal PRIVATE
    ${LILIM_DEPENDENCIES}
)

# Optional: only needed if libopencv_* are not in default linker search paths
target_link_directories(bad-apple-terminal PRIVATE
    /path/to/opencv/lib
)

target_link_libraries(bad-apple-terminal PRIVATE
    opencv_highgui
    opencv_videoio
    opencv_imgproc
    opencv_core
)

lilim_set_warnings(bad-apple-terminal)

include(cmake/lilim-end.cmake)
