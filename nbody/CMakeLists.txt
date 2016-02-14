cmake_minimum_required(VERSION 3.3)
project(nbody)

add_subdirectory(deps/GLFW EXCLUDE_FROM_ALL)
set(GLFW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/GLFW/include)

add_subdirectory(parallel)
add_subdirectory(sequential)
