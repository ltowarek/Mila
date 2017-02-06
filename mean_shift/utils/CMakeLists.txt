cmake_minimum_required(VERSION 3.4)
project(mean_shift_utils)

include_directories(${MEAN_SHIFT_UTILS_INCLUDE_DIRS})
add_library(mean_shift_utils_lib
    ${LODEPNG_INCLUDE_DIRS}/lodepng.cpp
    include/mean_shift_utils.h include/mean_shift_utils.cpp
    include/mean_shift.h include/mean_shift.cpp)

add_subdirectory(test)

set_property(TARGET mean_shift_utils_lib PROPERTY FOLDER "mean_shift")
