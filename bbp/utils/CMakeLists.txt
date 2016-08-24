cmake_minimum_required(VERSION 3.4)
project(bbp_utils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
add_library(bbp_utils_lib
    include/bbp_utils.h include/bbp_utils.cpp
    include/bbp.h include/bbp.cpp)

add_subdirectory(test)
