cmake_minimum_required(VERSION 3.4)
project(utils)

include_directories(${UTILS_INCLUDE_DIRS})
add_library(utils_lib
    include/utils.hpp src/utils.cpp
    include/version.hpp src/version.cpp
    include/statistics.hpp src/statistics.cpp
    include/logger.hpp src/logger.cpp
    include/profiler.hpp src/profiler.cpp
    include/ocl_app.hpp src/ocl_app.cpp
    include/ocl_app_profiler.hpp src/ocl_app_profiler.cpp
    include/plugin.hpp src/plugin.cpp)
target_link_libraries(${UTILS_LIBRARIES})

add_subdirectory(test)

set_property(TARGET utils_lib PROPERTY FOLDER "utils")
