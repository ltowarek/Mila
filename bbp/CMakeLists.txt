cmake_minimum_required(VERSION 3.4)
project(bbp)

set(BBP_UTILS_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/utils/include)
set(BBP_UTILS_LIBRARIES bbp_utils_lib)
add_subdirectory(utils)

set(BBP_PARALLEL_INCLUDE_DIRS ${UTILS_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/parallel/include ${BBP_UTILS_INCLUDE_DIRS} ${OpenCL_INCLUDE_DIR} ${CLPP_INCLUDE_DIRS})
set(BBP_PARALLEL_LIBRARIES bbp_parallel_lib)
set(KERNEL_FILE ${PROJECT_SOURCE_DIR}/parallel/bbp.cl)
add_subdirectory(parallel)

add_subdirectory(sequential)

set(BBP_FACTORIES_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
set(BBP_FACTORIES_LIBRARIES bbp_factories_lib)
include_directories(${UTILS_INCLUDE_DIRS} ${BBP_PARALLEL_INCLUDE_DIRS})
add_library(bbp_factories_lib
    include/bbp_factories.h include/bbp_factories.cpp)
target_link_libraries(bbp_factories_lib ${UTILS_LIBRARIES} ${BBP_PARALLEL_LIBRARIES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
include_directories(${UTILS_INCLUDE_DIRS})
add_executable(bbp main.cpp)
target_link_libraries(bbp ${UTILS_LIBRARIES})

add_subdirectory(test)
