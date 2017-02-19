cmake_minimum_required(VERSION 3.4)
project(bbp)

add_subdirectory(utils)
add_subdirectory(parallel)
add_subdirectory(sequential)

set(BBP_FACTORIES_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
set(BBP_FACTORIES_LIBRARIES bbp_factories_lib)
include_directories(${UTILS_INCLUDE_DIRS} ${BBP_PARALLEL_INCLUDE_DIRS} ${BBP_SEQUENTIAL_INCLUDE_DIRS})
add_library(bbp_factories_lib
    include/bbp_factories.h include/bbp_factories.cpp)
target_link_libraries(bbp_factories_lib ${UTILS_LIBRARIES} ${BBP_PARALLEL_LIBRARIES} ${BBP_SEQUENTIAL_LIBRARIES})

configure_file(${BBP_KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
include_directories(${UTILS_INCLUDE_DIRS} ${BBP_FACTORIES_INCLUDE_DIRS})
add_executable(bbp main.cpp)
target_link_libraries(bbp ${UTILS_LIBRARIES} ${BBP_FACTORIES_LIBRARIES})

add_subdirectory(test)

set_property(TARGET bbp PROPERTY FOLDER "bbp")
set_property(TARGET bbp_factories_lib PROPERTY FOLDER "bbp")
