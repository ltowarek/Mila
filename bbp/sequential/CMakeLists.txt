cmake_minimum_required(VERSION 3.3)
project(bbp_sequential)


set(BBP_SEQUENTIAL_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
set(BBP_SEQUENTIAL_LIBRARIES bbp_sequential_lib)
add_library(bbp_sequential_lib include/bbp_sequential.h include/bbp_sequential.cpp)

add_subdirectory(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${BBP_SEQUENTIAL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${BBP_SEQUENTIAL_LIBRARIES})

