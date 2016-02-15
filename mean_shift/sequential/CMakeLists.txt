cmake_minimum_required(VERSION 3.3)
project(mean_shift_sequential)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${LODEPNG_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp ${LODEPNG_INCLUDE_DIRS}/lodepng.cpp)
