cmake_minimum_required(VERSION 3.4)
project(n_body_parallel)

configure_file(${N_BODY_KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

include_directories(${N_BODY_PARALLEL_INCLUDE_DIRS})
add_library(n_body_parallel_lib
    include/n_body_parallel.hpp src/n_body_parallel.cpp
    include/n_body_parallel_profiler.hpp src/n_body_parallel_profiler.cpp
    include/n_body_parallel_app.hpp src/n_body_parallel_app.cpp)
target_link_libraries(${N_BODY_PARALLEL_LIBRARIES})

add_subdirectory(test)

set_property(TARGET n_body_parallel_lib PROPERTY FOLDER "n_body")
