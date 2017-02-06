cmake_minimum_required(VERSION 3.4)
project(bbp_parallel_test)

configure_file(${KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

include_directories(${GTEST_INCLUDE_DIRS} ${BBP_PARALLEL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} parallel_bbp_test.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${BBP_PARALLEL_LIBRARIES})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

set_property(TARGET bbp_parallel_test PROPERTY FOLDER "bbp")
