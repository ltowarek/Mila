cmake_minimum_required(VERSION 3.4)
project(bbp_utils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(BBP_UTILS_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "")
set(BBP_UTILS_LIBRARIES bbp_utils_lib CACHE INTERNAL "")
add_library(bbp_utils_lib include/bbp_utils.h include/bbp_utils.cpp)

add_subdirectory(test)
