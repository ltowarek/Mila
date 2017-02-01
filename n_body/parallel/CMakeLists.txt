cmake_minimum_required(VERSION 3.4)
project(n_body_parallel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIR})

configure_file(${KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

include_directories(${UTILS_INCLUDE_DIRS} ${N_BODY_UTILS_INCLUDE_DIRS})
add_library(n_body_parallel_lib
    include/n_body_parallel.h include/n_body_parallel.cpp
    include/n_body_parallel_profiler.h include/n_body_parallel_profiler.cpp
    include/n_body_parallel_app.h include/n_body_parallel_app.cpp)
target_link_libraries(n_body_parallel_lib ${UTILS_LIBRARIES} ${N_BODY_UTILS_LIBRARIES} ${OpenCL_LIBRARIES})

add_subdirectory(test)

include_directories(${N_BODY_PARALLEL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${N_BODY_PARALLEL_LIBRARIES})
