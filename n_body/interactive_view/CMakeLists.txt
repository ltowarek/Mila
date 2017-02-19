cmake_minimum_required(VERSION 3.4)
project(n_body_interactive_view)


include_directories(${N_BODY_INTERACTIVE_VIEW_INCLUDE_DIRS})
add_library(n_body_interactive_view_lib
    include/n_body_interactive_view.hpp src/n_body_interactive_view.cpp
    include/n_body_interactive_view_profiler.hpp src/n_body_interactive_view_profiler.cpp
    include/n_body_interactive_view_app.hpp src/n_body_interactive_view_app.cpp)
target_link_libraries(${N_BODY_INTERACTIVE_VIEW_LIBRARIES})

add_subdirectory(test)

set_property(TARGET n_body_interactive_view_lib PROPERTY FOLDER "n_body")
