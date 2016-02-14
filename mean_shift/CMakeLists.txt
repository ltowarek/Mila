cmake_minimum_required(VERSION 3.3)
project(mean_shift)

add_subdirectory(deps/zlib EXCLUDE_FROM_ALL)
file(COPY deps/zlib/zlib.h DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/deps/zlib)
set(ZLIB_ROOT ${CMAKE_CURRENT_BINARY_DIR}/deps/zlib)
find_package(ZLIB REQUIRED)
message(WARNING ${ZLIB_INCLUDE_DIR})
message(WARNING ${ZLIB_LIBRARIES})

add_subdirectory(deps/png EXCLUDE_FROM_ALL)
set(PNG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/png ${CMAKE_CURRENT_BINARY_DIR}/deps/png)
set(PNG_INCLUDE_DIR ${PNG_INCLUDE_DIRS})
set(PNG_LIBRARIES png)

add_subdirectory(parallel)
add_subdirectory(sequential)
