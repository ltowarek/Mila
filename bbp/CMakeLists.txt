cmake_minimum_required(VERSION 3.3)
project(bbp)

set(CLPP_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/clpp)

add_subdirectory(utils)
add_subdirectory(parallel)
add_subdirectory(sequential)
