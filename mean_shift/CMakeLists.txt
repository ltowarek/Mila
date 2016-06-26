cmake_minimum_required(VERSION 3.3)
project(mean_shift)

set(LODEPNG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/lodepng)

add_subdirectory(utils)
add_subdirectory(parallel)
add_subdirectory(sequential)
