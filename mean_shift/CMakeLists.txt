cmake_minimum_required(VERSION 3.4)
project(mean_shift)

set(LODEPNG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/lodepng)

set(MEAN_SHIFT_UTILS_INCLUDE_DIRS ${UTILS_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/utils/include ${LODEPNG_INCLUDE_DIRS})
set(MEAN_SHIFT_UTILS_LIBRARIES mean_shift_utils_lib)
add_subdirectory(utils)

set(MEAN_SHIFT_PARALLEL_INCLUDE_DIRS ${UTILS_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/parallel/include ${MEAN_SHIFT_UTILS_INCLUDE_DIRS})
set(MEAN_SHIFT_PARALLEL_LIBRARIES mean_shift_parallel_lib ${MEAN_SHIFT_UTILS_LIBRARIES})
set(KERNEL_FILE ${PROJECT_SOURCE_DIR}/parallel/mean_shift.cl)
add_subdirectory(parallel)

set(MEAN_SHIFT_SEQUENTIAL_INCLUDE_DIRS ${UTILS_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/sequential/include ${MEAN_SHIFT_UTILS_INCLUDE_DIRS})
set(MEAN_SHIFT_SEQUENTIAL_LIBRARIES mean_shift_sequential_lib ${MEAN_SHIFT_UTILS_LIBRARIES})
add_subdirectory(sequential)

set(MEAN_SHIFT_FACTORIES_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
set(MEAN_SHIFT_FACTORIES_LIBRARIES mean_shift_factories_lib)
include_directories(${UTILS_INCLUDE_DIRS} ${MEAN_SHIFT_PARALLEL_INCLUDE_DIRS} ${MEAN_SHIFT_SEQUENTIAL_INCLUDE_DIRS} ${MEAN_SHIFT_UTILS_INCLUDE_DIRS})
add_library(mean_shift_factories_lib
    include/mean_shift_factories.h include/mean_shift_factories.cpp)
target_link_libraries(mean_shift_factories_lib
    ${UTILS_LIBRARIES}
    ${MEAN_SHIFT_PARALLEL_LIBRARIES}
    ${MEAN_SHIFT_SEQUENTIAL_LIBRARIES}
    ${MEAN_SHIFT_UTILS_LIBRARIES})

configure_file(${KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
include_directories(${UTILS_INCLUDE_DIRS} ${MEAN_SHIFT_FACTORIES_INCLUDE_DIRS})
add_executable(mean_shift main.cpp)
target_link_libraries(mean_shift ${UTILS_LIBRARIES} ${MEAN_SHIFT_FACTORIES_LIBRARIES})

add_subdirectory(test)
