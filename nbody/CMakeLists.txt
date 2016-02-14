cmake_minimum_required(VERSION 3.3)
project(nbody)

add_subdirectory(deps/GLFW EXCLUDE_FROM_ALL)
add_subdirectory(parallel)
add_subdirectory(sequential)
