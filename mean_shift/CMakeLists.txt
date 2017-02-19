cmake_minimum_required(VERSION 3.4)
project(mean_shift)


add_subdirectory(utils)
add_subdirectory(parallel)
add_subdirectory(sequential)
add_subdirectory(image_processing)

set(MEAN_SHIFT_FACTORIES_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
set(MEAN_SHIFT_FACTORIES_LIBRARIES mean_shift_factories_lib)
include_directories(${UTILS_INCLUDE_DIRS}
    ${MEAN_SHIFT_PARALLEL_INCLUDE_DIRS}
    ${MEAN_SHIFT_SEQUENTIAL_INCLUDE_DIRS}
    ${MEAN_SHIFT_IMAGE_PROCESSING_INCLUDE_DIRS}
    ${MEAN_SHIFT_UTILS_INCLUDE_DIRS})
add_library(mean_shift_factories_lib
    include/mean_shift_factories.h include/mean_shift_factories.cpp)
target_link_libraries(mean_shift_factories_lib
    ${UTILS_LIBRARIES}
    ${MEAN_SHIFT_PARALLEL_LIBRARIES}
    ${MEAN_SHIFT_SEQUENTIAL_LIBRARIES}
    ${MEAN_SHIFT_IMAGE_PROCESSING_LIBRARIES}
    ${MEAN_SHIFT_UTILS_LIBRARIES})

configure_file(${MEAN_SHIFT_KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
include_directories(${UTILS_INCLUDE_DIRS} ${MEAN_SHIFT_FACTORIES_INCLUDE_DIRS})
add_executable(mean_shift main.cpp)
target_link_libraries(mean_shift ${UTILS_LIBRARIES} ${MEAN_SHIFT_FACTORIES_LIBRARIES})

add_subdirectory(test)

set_property(TARGET mean_shift_factories_lib PROPERTY FOLDER "mean_shift")
set_property(TARGET mean_shift PROPERTY FOLDER "mean_shift")
