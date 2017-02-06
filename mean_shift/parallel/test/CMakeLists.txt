cmake_minimum_required(VERSION 3.4)
project(mean_shift_parallel_test)

configure_file(${KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

include_directories(${GTEST_INCLUDE_DIRS} ${MEAN_SHIFT_PARALLEL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} mean_shift_parallel_test.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${MEAN_SHIFT_PARALLEL_LIBRARIES})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

set_property(TARGET mean_shift_parallel_test PROPERTY FOLDER "mean_shift")
