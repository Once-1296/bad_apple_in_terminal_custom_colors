# Managed by lilim — rewritten by `lilim add`, `lilim remove` and `lilim sync`.
# Included by CMakeLists.txt before the project's targets.
set(LILIM_CXX_STANDARD 23)   # cxx_standard in lilim.toml
set(CMAKE_CXX_STANDARD ${LILIM_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_CURRENT_LIST_DIR}/Warnings.cmake)
if(NOT CMAKE_PROJECT_TOP_LEVEL_INCLUDES MATCHES "conan_provider" AND NOT CMAKE_TOOLCHAIN_FILE MATCHES "conan_toolchain")
    # projects from before lilim 1.3 don't include lilim-setup.cmake yet
    message(WARNING "Conan isn't set up for this configure, so dependencies won't be found. "
        "Configure with a preset (cmake --preset debug), or add this line before project() in CMakeLists.txt:\n"
        "  include(cmake/lilim-setup.cmake)")
endif()

include(${CMAKE_CURRENT_LIST_DIR}/Dependencies.cmake)
