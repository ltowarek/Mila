cmake_minimum_required(VERSION 3.4)
project(bbp_parallel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(KERNEL_FILE ${PROJECT_SOURCE_DIR}/bbp.cl)
configure_file(${KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIR})

set(BBP_PARALLEL_INCLUDE_DIRS ${UTILS_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include ${BBP_UTILS_INCLUDE_DIRS} ${OpenCL_INCLUDE_DIR} ${CLPP_INCLUDE_DIRS})
set(BBP_PARALLEL_LIBRARIES bbp_parallel_lib ${BBP_UTILS_LIBRARIES} ${OpenCL_LIBRARIES})
add_library(bbp_parallel_lib
    include/bbp_parallel.h include/bbp_parallel.cpp
    include/bbp_parallel_profiler.h include/bbp_parallel_profiler.cpp
    include/bbp_parallel_app.h include/bbp_parallel_app.cpp)
target_link_libraries(bbp_parallel_lib ${UTILS_LIBRARIES} ${OpenCL_LIBRARIES})

add_subdirectory(test)

include_directories(${BBP_PARALLEL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${BBP_PARALLEL_LIBRARIES})
