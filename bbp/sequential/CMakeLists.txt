cmake_minimum_required(VERSION 3.4)
project(bbp_sequential)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

include_directories(${BBP_SEQUENTIAL_INCLUDE_DIRS})
add_library(bbp_sequential_lib
    include/bbp_sequential.h include/bbp_sequential.cpp
    include/bbp_sequential_profiler.h include/bbp_sequential_profiler.cpp)
target_link_libraries(bbp_sequential_lib ${BBP_UTILS_LIBRARIES} ${UTILS_LIBRARIES})

add_subdirectory(test)

include_directories(${BBP_SEQUENTIAL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${BBP_SEQUENTIAL_LIBRARIES})

