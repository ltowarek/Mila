cmake_minimum_required(VERSION 3.4)
project(n_body_sequential)

include_directories(${UTILS_INCLUDE_DIRS} ${N_BODY_UTILS_INCLUDE_DIRS})
add_library(n_body_sequential_lib
    include/n_body_sequential.hpp src/n_body_sequential.cpp
    include/n_body_sequential_profiler.hpp src/n_body_sequential_profiler.cpp
    include/n_body_sequential_app.hpp src/n_body_sequential_app.cpp)
target_link_libraries(n_body_sequential_lib ${UTILS_LIBRARIES} ${N_BODY_UTILS_LIBRARIES})

add_subdirectory(test)

include_directories(${N_BODY_SEQUENTIAL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${N_BODY_SEQUENTIAL_LIBRARIES})

set_property(TARGET n_body_sequential_lib PROPERTY FOLDER "n_body")
set_property(TARGET n_body_sequential PROPERTY FOLDER "n_body")
