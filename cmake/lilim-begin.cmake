# Managed by lilim — rewritten by `lilim add`, `lilim remove` and `lilim sync`.
# Included by CMakeLists.txt before the project's targets.
set(LILIM_CXX_STANDARD 23)   # cxx_standard in lilim.toml
set(CMAKE_CXX_STANDARD ${LILIM_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_CURRENT_LIST_DIR}/Warnings.cmake)

include(${CMAKE_CURRENT_LIST_DIR}/Dependencies.cmake)
