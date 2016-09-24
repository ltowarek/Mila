cmake_minimum_required(VERSION 3.4)
project(mean_shift_utils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

include_directories(${LODEPNG_INCLUDE_DIRS})
set(MEAN_SHIFT_UTILS_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include ${LODEPNG_INCLUDE_DIRS} CACHE INTERNAL "")
set(MEAN_SHIFT_UTILS_LIBRARIES mean_shift_utils_lib CACHE INTERNAL "")
add_library(mean_shift_utils_lib
    ${LODEPNG_INCLUDE_DIRS}/lodepng.cpp
    include/mean_shift_utils.h include/mean_shift_utils.cpp
    include/mean_shift.h include/mean_shift.cpp)

add_subdirectory(test)
