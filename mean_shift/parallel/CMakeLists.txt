cmake_minimum_required(VERSION 3.3)
project(mean_shift_parallel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIR})

set(KERNEL_FILE ${PROJECT_SOURCE_DIR}/mean_shift.cl)
configure_file(${KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

set(MEAN_SHIFT_PARALLEL_INCLUDE_DIRS ${UTILS_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include ${MEAN_SHIFT_UTILS_INCLUDE_DIRS} ${OpenCL_INCLUDE_DIR} ${CLPP_INCLUDE_DIRS})
set(MEAN_SHIFT_PARALLEL_LIBRARIES mean_shift_parallel_lib ${MEAN_SHIFT_UTILS_LIBRARIES} ${OpenCL_LIBRARIES})
add_library(mean_shift_parallel_lib include/mean_shift_parallel.h include/mean_shift_parallel.cpp include/mean_shift_parallel_profiler.cpp include/mean_shift_parallel_profiler.h)
target_link_libraries(mean_shift_parallel_lib ${UTILS_LIBRARIES} ${OpenCL_LIBRARIES})

add_subdirectory(test)

include_directories(${MEAN_SHIFT_PARALLEL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${MEAN_SHIFT_PARALLEL_LIBRARIES})
