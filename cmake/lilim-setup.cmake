# Managed by lilim — rewritten by `lilim add`, `lilim remove` and `lilim sync`.
# Included by CMakeLists.txt before project(), so a configure without a preset (an IDE's
# own build profile, or a plain `cmake -B build`) gets dependencies the way the presets do.
if(NOT CMAKE_PROJECT_TOP_LEVEL_INCLUDES)
    set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES "${CMAKE_CURRENT_LIST_DIR}/conan_provider.cmake")
endif()
