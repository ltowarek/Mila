cmake_minimum_required(VERSION 3.4)
project(n_body)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(GLFW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/include)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_INSTALL OFF)
add_subdirectory(deps/glfw EXCLUDE_FROM_ALL)

set(N_BODY_UTILS_INCLUDE_DIRS ${UTILS_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/utils/include ${LODEPNG_INCLUDE_DIRS})
set(N_BODY_UTILS_LIBRARIES n_body_utils_lib)
add_subdirectory(utils)

set(N_BODY_SEQUENTIAL_INCLUDE_DIRS ${UTILS_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/sequential/include ${N_BODY_UTILS_INCLUDE_DIRS})
set(N_BODY_SEQUENTIAL_LIBRARIES n_body_sequential_lib ${N_BODY_UTILS_LIBRARIES})
add_subdirectory(sequential)

add_subdirectory(parallel)

add_subdirectory(test)
