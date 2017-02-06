cmake_minimum_required(VERSION 3.4)
project(bbp_sequential)

include_directories(${BBP_SEQUENTIAL_INCLUDE_DIRS})
add_library(bbp_sequential_lib
    include/bbp_sequential.h include/bbp_sequential.cpp
    include/bbp_sequential_profiler.h include/bbp_sequential_profiler.cpp
    include/bbp_sequential_app.h include/bbp_sequential_app.cpp)
target_link_libraries(bbp_sequential_lib ${BBP_UTILS_LIBRARIES} ${UTILS_LIBRARIES})

add_subdirectory(test)

include_directories(${BBP_SEQUENTIAL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${BBP_SEQUENTIAL_LIBRARIES})

set_property(TARGET bbp_sequential_lib PROPERTY FOLDER "bbp")
set_property(TARGET bbp_sequential PROPERTY FOLDER "bbp")
