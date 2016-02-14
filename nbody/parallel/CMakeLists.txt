cmake_minimum_required(VERSION 3.3)
project(nbody_parallel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIR} ${GLFW_INCLUDE_DIRS})

file(COPY nbody.cl DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCL_LIBRARIES} glfw ${GLFW_LIBRARIES})

