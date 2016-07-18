cmake_minimum_required(VERSION 3.4)
project(utils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_library(utils_lib include/utils.h include/utils.cpp include/version.h include/version.cpp include/statistics.h include/statistics.cpp)

add_subdirectory(test)
