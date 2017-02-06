cmake_minimum_required(VERSION 3.4)
project(mean_shift_parallel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIR})

configure_file(${KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

include_directories(${MEAN_SHIFT_UTILS_INCLUDE_DIRS})
add_library(mean_shift_parallel_lib
    include/mean_shift_parallel.h include/mean_shift_parallel.cpp
    include/mean_shift_parallel_profiler.h include/mean_shift_parallel_profiler.cpp
    include/mean_shift_parallel_app.h include/mean_shift_parallel_app.cpp)
target_link_libraries(mean_shift_parallel_lib ${UTILS_LIBRARIES} ${OpenCL_LIBRARIES})

add_subdirectory(test)

include_directories(${MEAN_SHIFT_PARALLEL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${MEAN_SHIFT_PARALLEL_LIBRARIES})

set_property(TARGET mean_shift_parallel_lib PROPERTY FOLDER "mean_shift")
set_property(TARGET mean_shift_parallel PROPERTY FOLDER "mean_shift")
