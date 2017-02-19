cmake_minimum_required(VERSION 3.4)
project(mean_shift_sequential)

include_directories(${MEAN_SHIFT_UTILS_INCLUDE_DIRS})
add_library(mean_shift_sequential_lib
    include/mean_shift_sequential.hpp src/mean_shift_sequential.cpp
    include/mean_shift_sequential_profiler.hpp src/mean_shift_sequential_profiler.cpp
    include/mean_shift_sequential_app.hpp src/mean_shift_sequential_app.cpp)
target_link_libraries(mean_shift_sequential_lib ${UTILS_LIBRARIES})

add_subdirectory(test)

include_directories(${MEAN_SHIFT_SEQUENTIAL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${MEAN_SHIFT_SEQUENTIAL_LIBRARIES})

set_property(TARGET mean_shift_sequential_lib PROPERTY FOLDER "mean_shift")
set_property(TARGET mean_shift_sequential PROPERTY FOLDER "mean_shift")
