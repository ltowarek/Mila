cmake_minimum_required(VERSION 3.4)
project(n_body_sequential)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

find_package(OpenGL REQUIRED)

include_directories(${N_BODY_UTILS_INCLUDE_DIRS})
set(N_BODY_SEQUENTIAL_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include ${N_BODY_UTILS_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
set(N_BODY_SEQUENTIAL_LIBRARIES n_body_sequential_lib ${N_BODY_UTILS_LIBRARIES} glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})
add_library(n_body_sequential_lib include/n_body_sequential.h include/n_body_sequential.cpp
            include/n_body_sequential_profiler.h include/n_body_sequential_profiler.cpp)

add_subdirectory(test)

configure_file(sample_input.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

include_directories(${UTILS_INCLUDE_DIRS} ${N_BODY_SEQUENTIAL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${UTILS_LIBRARIES} ${N_BODY_SEQUENTIAL_LIBRARIES})
