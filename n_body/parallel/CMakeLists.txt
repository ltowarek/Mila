cmake_minimum_required(VERSION 3.3)
project(n_body_parallel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIR})

set(KERNEL_FILE ${PROJECT_SOURCE_DIR}/n_body.cl)
configure_file(${KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

set(N_BODY_PARALLEL_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include ${N_BODY_UTILS_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${OpenCL_INCLUDE_DIR})
set(N_BODY_PARALLEL_LIBRARIES n_body_parallel_lib ${N_BODY_UTILS_LIBRARIES} glfw ${GLFW_LIBRARIES} ${OpenCL_LIBRARIES})
add_library(n_body_parallel_lib include/n_body_parallel.h include/n_body_parallel.cpp
        include/n_body_parallel_profiler.h include/n_body_parallel_profiler.cpp)
target_link_libraries(n_body_parallel_lib ${OpenCL_LIBRARIES})

add_subdirectory(test)

configure_file(sample_input.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

include_directories(${UTILS_INCLUDE_DIRS} ${N_BODY_PARALLEL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${UTILS_LIBRARIES} ${N_BODY_PARALLEL_LIBRARIES})
