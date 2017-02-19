cmake_minimum_required(VERSION 3.4)
project(n_body_utils)

add_library(n_body_utils_lib include/n_body_utils.hpp src/n_body_utils.cpp include/n_body.hpp src/n_body.cpp)

add_subdirectory(test)

set_property(TARGET n_body_utils_lib PROPERTY FOLDER "n_body")
