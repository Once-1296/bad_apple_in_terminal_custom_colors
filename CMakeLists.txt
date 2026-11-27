cmake_minimum_required(VERSION 3.25)

# Prevent lilim-setup.cmake from attaching conan_provider.cmake
include(cmake/lilim-setup.cmake)

project(bad-apple-terminal
    VERSION 0.1.0
    DESCRIPTION "bad apple in terminal"
    LANGUAGES CXX)

include(cmake/lilim-begin.cmake)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bad-apple-terminal src/main.cpp)

target_link_libraries(bad-apple-terminal PRIVATE ${LILIM_DEPENDENCIES})

lilim_set_warnings(bad-apple-terminal)

include(cmake/lilim-end.cmake)
