cmake_minimum_required(VERSION 3.4)
project(bbp_parallel)

configure_file(${BBP_KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIR})

include_directories(${BBP_PARALLEL_INCLUDE_DIRS})
add_library(bbp_parallel_lib
    include/bbp_parallel.hpp src/bbp_parallel.cpp
    include/bbp_parallel_profiler.hpp src/bbp_parallel_profiler.cpp
    include/bbp_parallel_app.hpp src/bbp_parallel_app.cpp)
target_link_libraries(bbp_parallel_lib ${UTILS_LIBRARIES} ${OpenCL_LIBRARIES} ${BBP_UTILS_LIBRARIES})

add_subdirectory(test)

set_property(TARGET bbp_parallel_lib PROPERTY FOLDER "bbp")
