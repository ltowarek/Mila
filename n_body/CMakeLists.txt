cmake_minimum_required(VERSION 3.4)
project(n_body)

add_subdirectory(deps/glfw EXCLUDE_FROM_ALL)
set(GLFW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/include)

add_subdirectory(utils)
add_subdirectory(parallel)
add_subdirectory(sequential)
