cmake_minimum_required(VERSION 3.4)
project(utils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIR} ${UTILS_INCLUDE_DIRS})
add_library(utils_lib
        include/utils.h include/utils.cpp
        include/version.h include/version.cpp
        include/statistics.h include/statistics.cpp
        include/logger.h include/logger.cpp
        include/profiler.h include/profiler.cpp
        include/ocl_app.h include/ocl_app.cpp
        include/ocl_app_profiler.h include/ocl_app_profiler.cpp)

add_subdirectory(test)
