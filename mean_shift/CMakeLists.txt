cmake_minimum_required(VERSION 3.3)
project(mean_shift)

add_subdirectory(deps/zlib)
set(ZLIB_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/zlib ${CMAKE_CURRENT_BINARY_DIR}/deps/zlib)
set(ZLIB_INCLUDE_DIR ${ZLIB_INCLUDE_DIRS})
set(ZLIB_LIBRARIES zlib)

add_subdirectory(deps/png)
set(PNG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/png ${CMAKE_CURRENT_BINARY_DIR}/deps/png)
set(PNG_INCLUDE_DIR ${PNG_INCLUDE_DIRS})
set(PNG_LIBRARIES png)

add_subdirectory(parallel)
add_subdirectory(sequential)
