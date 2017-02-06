cmake_minimum_required(VERSION 3.4)
project(n_body)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(GLFW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/include)
set(GLFW_LIBRARIES glfw)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_INSTALL OFF)
add_subdirectory(deps/glfw EXCLUDE_FROM_ALL)

set(N_BODY_UTILS_INCLUDE_DIRS ${UTILS_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/utils/include ${LODEPNG_INCLUDE_DIRS})
set(N_BODY_UTILS_LIBRARIES n_body_utils_lib)
add_subdirectory(utils)

set(N_BODY_SEQUENTIAL_INCLUDE_DIRS ${UTILS_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/sequential/include ${N_BODY_UTILS_INCLUDE_DIRS})
set(N_BODY_SEQUENTIAL_LIBRARIES n_body_sequential_lib ${N_BODY_UTILS_LIBRARIES} ${UTILS_LIBRARIES})
add_subdirectory(sequential)

set(N_BODY_PARALLEL_INCLUDE_DIRS ${UTILS_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/parallel/include ${N_BODY_UTILS_INCLUDE_DIRS} ${OpenCL_INCLUDE_DIR} ${CLPP_INCLUDE_DIRS})
set(N_BODY_PARALLEL_LIBRARIES n_body_parallel_lib ${N_BODY_UTILS_LIBRARIES} ${UTILS_LIBRARIES} ${OpenCL_LIBRARIES})
set(KERNEL_FILE ${PROJECT_SOURCE_DIR}/parallel/n_body.cl)
add_subdirectory(parallel)

set(N_BODY_INTERACTIVE_VIEW_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/interactive_view/include ${UTILS_INCLUDE_DIRS} ${N_BODY_UTILS_INCLUDE_DIRS} ${N_BODY_SEQUENTIAL_INCLUDE_DIRS} ${N_BODY_PARALLEL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
set(N_BODY_INTERACTIVE_VIEW_LIBRARIES n_body_interactive_view_lib ${UTILS_LIBRARIES} ${N_BODY_SEQUENTIAL_LIBRARIES} ${N_BODY_PARALLEL_LIBRARIES} ${N_BODY_UTILS_LIBRARIES} ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})
add_subdirectory(interactive_view)

set(N_BODY_FACTORIES_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
set(N_BODY_FACTORIES_LIBRARIES n_body_factories_lib)
include_directories(${UTILS_INCLUDE_DIRS}
    ${N_BODY_PARALLEL_INCLUDE_DIRS}
    ${N_BODY_SEQUENTIAL_INCLUDE_DIRS}
    ${N_BODY_INTERACTIVE_VIEW_INCLUDE_DIRS}
    ${N_BODY_UTILS_INCLUDE_DIRS})
add_library(n_body_factories_lib
    include/n_body_factories.h include/n_body_factories.cpp)
target_link_libraries(n_body_factories_lib
    ${UTILS_LIBRARIES}
    ${N_BODY_PARALLEL_LIBRARIES}
    ${N_BODY_SEQUENTIAL_LIBRARIES}
    ${N_BODY_INTERACTIVE_VIEW_LIBRARIES}
    ${N_BODY_UTILS_LIBRARIES})

configure_file(${KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
include_directories(${UTILS_INCLUDE_DIRS} ${N_BODY_FACTORIES_INCLUDE_DIRS})
add_executable(n_body main.cpp)
target_link_libraries(n_body ${UTILS_LIBRARIES} ${N_BODY_FACTORIES_LIBRARIES})

add_subdirectory(test)

set_property(TARGET n_body_factories_lib PROPERTY FOLDER "n_body")
set_property(TARGET n_body PROPERTY FOLDER "n_body")
set_property(TARGET glfw PROPERTY FOLDER "n_body")
