cmake_minimum_required(VERSION 3.4)
project(bbp_utils)

add_library(bbp_utils_lib
    include/bbp_utils.hpp src/bbp_utils.cpp
    include/bbp.hpp src/bbp.cpp)

add_subdirectory(test)

set_property(TARGET bbp_utils_lib PROPERTY FOLDER "bbp")
