cmake_minimum_required(VERSION 3.4)
project(mean_shift_image_processing)

include_directories(${MEAN_SHIFT_IMAGE_PROCESSING_INCLUDE_DIRS})
add_library(mean_shift_image_processing_lib
    include/mean_shift_image_processing.h include/mean_shift_image_processing.cpp
    include/mean_shift_image_processing_profiler.h include/mean_shift_image_processing_profiler.cpp
    include/mean_shift_image_processing_app.h include/mean_shift_image_processing_app.cpp)
target_link_libraries(${MEAN_SHIFT_IMAGE_PROCESSING_LIBRARIES})

add_subdirectory(test)

set_property(TARGET mean_shift_image_processing_lib PROPERTY FOLDER "mean_shift")
