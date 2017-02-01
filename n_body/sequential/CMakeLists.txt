cmake_minimum_required(VERSION 3.4)
project(n_body_sequential)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

include_directories(${UTILS_INCLUDE_DIRS} ${N_BODY_UTILS_INCLUDE_DIRS})
add_library(n_body_sequential_lib
    include/n_body_sequential.h include/n_body_sequential.cpp
    include/n_body_sequential_profiler.h include/n_body_sequential_profiler.cpp
    include/n_body_sequential_app.h include/n_body_parallel_app.cpp)
target_link_libraries(n_body_sequential_lib ${UTILS_LIBRARIES} ${N_BODY_UTILS_LIBRARIES})

add_subdirectory(test)

include_directories(${N_BODY_SEQUENTIAL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${N_BODY_SEQUENTIAL_LIBRARIES})
