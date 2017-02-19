cmake_minimum_required(VERSION 3.4)
project(mean_shift_parallel)

configure_file(${MEAN_SHIFT_KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

include_directories(${MEAN_SHIFT_PARALLEL_INCLUDE_DIRS})
add_library(mean_shift_parallel_lib
            include/mean_shift_parallel.hpp src/mean_shift_parallel.cpp
            include/mean_shift_parallel_profiler.hpp src/mean_shift_parallel_profiler.cpp
            include/mean_shift_parallel_app.hpp src/mean_shift_parallel_app.cpp)
target_link_libraries(${MEAN_SHIFT_PARALLEL_LIBRARIES})

add_subdirectory(test)

set_property(TARGET mean_shift_parallel_lib PROPERTY FOLDER "mean_shift")
