cmake_minimum_required(VERSION 3.3)
project(bbp_parallel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIR})

set(BBP_PARALLEL_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
set(BBP_PARALLEL_LIBRARIES bbp_parallel_lib)
add_library(bbp_parallel_lib include/bbp_parallel.h include/bbp_parallel.cpp)
target_link_libraries(bbp_parallel_lib ${OpenCL_LIBRARIES})

add_subdirectory(test)

file(COPY bbp.cl DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCL_LIBRARIES})
