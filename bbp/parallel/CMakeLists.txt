cmake_minimum_required(VERSION 3.4)
project(bbp_parallel)

configure_file(${BBP_KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

include_directories(${BBP_PARALLEL_INCLUDE_DIRS})
add_library(bbp_parallel_lib
            include/bbp_parallel.hpp src/bbp_parallel.cpp
            include/bbp_parallel_profiler.hpp src/bbp_parallel_profiler.cpp
            include/bbp_parallel_app.hpp src/bbp_parallel_app.cpp)
target_link_libraries(${BBP_PARALLEL_LIBRARIES})

add_subdirectory(test)

set_property(TARGET bbp_parallel_lib PROPERTY FOLDER "bbp")
