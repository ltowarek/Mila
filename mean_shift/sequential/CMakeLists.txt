cmake_minimum_required(VERSION 3.4)
project(mean_shift_sequential)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

include_directories(${MEAN_SHIFT_UTILS_INCLUDE_DIRS})
set(MEAN_SHIFT_SEQUENTIAL_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include ${MEAN_SHIFT_UTILS_INCLUDE_DIRS})
set(MEAN_SHIFT_SEQUENTIAL_LIBRARIES mean_shift_sequential_lib ${MEAN_SHIFT_UTILS_LIBRARIES})
add_library(mean_shift_sequential_lib include/mean_shift_sequential.h include/mean_shift_sequential.cpp
        include/mean_shift_sequential_profiler.h include/mean_shift_sequential_profiler.cpp)

add_subdirectory(test)

include_directories(${UTILS_INCLUDE_DIRS} ${MEAN_SHIFT_SEQUENTIAL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${UTILS_LIBRARIES} ${MEAN_SHIFT_SEQUENTIAL_LIBRARIES})
