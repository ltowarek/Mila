cmake_minimum_required(VERSION 3.4)
project(bbp_sequential)

include_directories(${BBP_SEQUENTIAL_INCLUDE_DIRS})
add_library(bbp_sequential_lib
    include/bbp_sequential.hpp src/bbp_sequential.cpp
    include/bbp_sequential_profiler.hpp src/bbp_sequential_profiler.cpp
    include/bbp_sequential_app.hpp src/bbp_sequential_app.cpp)
target_link_libraries(bbp_sequential_lib ${BBP_UTILS_LIBRARIES} ${UTILS_LIBRARIES})

add_subdirectory(test)

set_property(TARGET bbp_sequential_lib PROPERTY FOLDER "bbp")
