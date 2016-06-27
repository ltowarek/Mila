cmake_minimum_required(VERSION 3.4)
project(bbp_sequential)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(BBP_SEQUENTIAL_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include ${BBP_UTILS_INCLUDE_DIRS})
set(BBP_SEQUENTIAL_LIBRARIES bbp_sequential_lib ${BBP_UTILS_LIBRARIES})
add_library(bbp_sequential_lib include/bbp_sequential.h include/bbp_sequential.cpp
        include/bbp_sequential_profiler.h include/bbp_sequential_profiler.cpp)

add_subdirectory(test)

include_directories(${UTILS_INCLUDE_DIRS} ${BBP_SEQUENTIAL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${UTILS_LIBRARIES} ${BBP_SEQUENTIAL_LIBRARIES})

