cmake_minimum_required(VERSION 3.4)
project(mean_shift_image_processing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

include_directories(${MEAN_SHIFT_UTILS_INCLUDE_DIRS} ${MEAN_SHIFT_SEQUENTIAL_INCLUDE_DIRS} ${MEAN_SHIFT_PARALLEL_INCLUDE_DIRS})
add_library(mean_shift_image_processing_lib
    include/mean_shift_image_processing.h include/mean_shift_image_processing.cpp
    include/mean_shift_image_processing_profiler.h include/mean_shift_image_processing_profiler.cpp
    include/mean_shift_image_processing_app.h include/mean_shift_image_processing_app.cpp)
target_link_libraries(mean_shift_image_processing_lib ${MEAN_SHIFT_UTILS_LIBRARIES} ${UTILS_LIBRARIES} ${MEAN_SHIFT_SEQUENTIAL_LIBRARIES}
    ${MEAN_SHIFT_PARALLEL_LIBRARIES})

add_subdirectory(test)

set_property(TARGET mean_shift_image_processing_lib PROPERTY FOLDER "mean_shift")
