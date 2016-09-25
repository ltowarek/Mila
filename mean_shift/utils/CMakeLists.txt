cmake_minimum_required(VERSION 3.4)
project(mean_shift_utils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

include_directories(${MEAN_SHIFT_UTILS_INCLUDE_DIRS})
add_library(mean_shift_utils_lib
    ${LODEPNG_INCLUDE_DIRS}/lodepng.cpp
    include/mean_shift_utils.h include/mean_shift_utils.cpp
    include/mean_shift.h include/mean_shift.cpp
    include/mean_shift_image_processing.h include/mean_shift_image_processing.cpp)

add_subdirectory(test)
