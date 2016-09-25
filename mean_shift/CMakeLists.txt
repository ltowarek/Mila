cmake_minimum_required(VERSION 3.4)
project(mean_shift)

set(LODEPNG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/lodepng)

set(MEAN_SHIFT_UTILS_INCLUDE_DIRS ${UTILS_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/utils/include ${LODEPNG_INCLUDE_DIRS})
set(MEAN_SHIFT_UTILS_LIBRARIES mean_shift_utils_lib)
add_subdirectory(utils)

set(MEAN_SHIFT_PARALLEL_INCLUDE_DIRS ${UTILS_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/parallel/include ${MEAN_SHIFT_UTILS_INCLUDE_DIRS})
set(MEAN_SHIFT_PARALLEL_LIBRARIES mean_shift_parallel_lib)
add_subdirectory(parallel)

set(MEAN_SHIFT_SEQUENTIAL_INCLUDE_DIRS ${UTILS_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/sequential/include ${MEAN_SHIFT_UTILS_INCLUDE_DIRS})
set(MEAN_SHIFT_SEQUENTIAL_LIBRARIES mean_shift_sequential_lib)
add_subdirectory(sequential)
