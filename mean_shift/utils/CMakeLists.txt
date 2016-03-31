cmake_minimum_required(VERSION 3.3)
project(mean_shift_utils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(MEAN_SHIFT_UTILS_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "")
set(MEAN_SHIFT_UTILS_LIBRARIES mean_shift_utils_lib CACHE INTERNAL "")
add_library(mean_shift_utils_lib include/mean_shift_utils.h include/mean_shift_utils.cpp)

add_subdirectory(test)
