cmake_minimum_required(VERSION 3.3)
project(nbody_sequential)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${GLFW_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
