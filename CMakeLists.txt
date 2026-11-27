cmake_minimum_required(VERSION 3.25)
include(cmake/lilim-setup.cmake)   # managed by lilim: dependencies without a preset too

project(bad-apple-terminal
    VERSION 0.1.0
    DESCRIPTION "bad apple in terminal"
    LANGUAGES CXX)

include(cmake/lilim-begin.cmake)   # managed by lilim: C++ standard, warnings, dependencies

add_executable(bad-apple-terminal src/main.cpp)
target_link_libraries(bad-apple-terminal PRIVATE ${LILIM_DEPENDENCIES})
lilim_set_warnings(bad-apple-terminal)

include(cmake/lilim-end.cmake)     # managed by lilim: tests, benchmarks, docs, packaging
