cmake_minimum_required(VERSION 3.4)
project(n_body_utils)

set(N_BODY_UTILS_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "")
set(N_BODY_UTILS_LIBRARIES n_body_utils_lib CACHE INTERNAL "")
add_library(n_body_utils_lib include/n_body_utils.h include/n_body_utils.cpp include/n_body.h include/n_body.cpp)

add_subdirectory(test)

set_property(TARGET n_body_utils_lib PROPERTY FOLDER "n_body")
