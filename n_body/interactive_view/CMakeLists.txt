cmake_minimum_required(VERSION 3.4)
project(n_body_interactive_view)

find_package(OpenGL REQUIRED)

include_directories(${N_BODY_INTERACTIVE_VIEW_INCLUDE_DIRS})
add_library(n_body_interactive_view_lib
    include/n_body_interactive_view.h include/n_body_interactive_view.cpp
    include/n_body_interactive_view_profiler.h include/n_body_interactive_view_profiler.cpp
    include/n_body_interactive_view_app.h include/n_body_interactive_view_app.cpp)
target_link_libraries(n_body_interactive_view_lib ${N_BODY_UTILS_LIBRARIES} ${UTILS_LIBRARIES} ${N_BODY_SEQUENTIAL_LIBRARIES} ${N_BODY_PARALLEL_LIBRARIES} ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})

add_subdirectory(test)

set_property(TARGET n_body_interactive_view_lib PROPERTY FOLDER "n_body")
