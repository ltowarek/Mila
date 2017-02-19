cmake_minimum_required(VERSION 3.4)
project(plugin_manager)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${PLUGIN_MANAGER_INCLUDE_DIRS})
add_library(${PROJECT_NAME} include/plugin_manager.hpp src/plugin_manager.cpp)
target_link_libraries(${PROJECT_NAME} ${UTILS_LIBRARIES})

set_property(TARGET plugin_manager PROPERTY FOLDER "plugin_manager")
