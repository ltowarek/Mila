cmake_minimum_required(VERSION 3.4)
project(n_body)

option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_INSTALL OFF)
add_subdirectory(deps/glfw EXCLUDE_FROM_ALL)

add_subdirectory(utils)
add_subdirectory(sequential)
add_subdirectory(parallel)
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

configure_file(${N_BODY_KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
include_directories(${UTILS_INCLUDE_DIRS} ${N_BODY_FACTORIES_INCLUDE_DIRS})
add_executable(n_body main.cpp)
target_link_libraries(n_body ${UTILS_LIBRARIES} ${N_BODY_FACTORIES_LIBRARIES})

add_subdirectory(test)

set_property(TARGET n_body_factories_lib PROPERTY FOLDER "n_body")
set_property(TARGET n_body PROPERTY FOLDER "n_body")
set_property(TARGET glfw PROPERTY FOLDER "n_body")
