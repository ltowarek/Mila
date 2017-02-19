cmake_minimum_required(VERSION 3.4)
project(mean_shift_sequential)

include_directories(${MEAN_SHIFT_SEQUENTIAL_INCLUDE_DIRS})
add_library(mean_shift_sequential_lib
    include/mean_shift_sequential.hpp src/mean_shift_sequential.cpp
    include/mean_shift_sequential_profiler.hpp src/mean_shift_sequential_profiler.cpp
    include/mean_shift_sequential_app.hpp src/mean_shift_sequential_app.cpp)
target_link_libraries(${MEAN_SHIFT_SEQUENTIAL_LIBRARIES})

add_subdirectory(test)

set_property(TARGET mean_shift_sequential_lib PROPERTY FOLDER "mean_shift")
