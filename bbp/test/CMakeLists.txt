cmake_minimum_required(VERSION 3.4)
project(bbp_test)

configure_file(${BBP_KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

include_directories(${GTEST_INCLUDE_DIRS} ${BBP_PARALLEL_INCLUDE_DIRS} ${BBP_FACTORIES_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} bbp_test.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${BBP_PARALLEL_LIBRARIES} ${BBP_FACTORIES_LIBRARIES})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

set_property(TARGET bbp_test PROPERTY FOLDER "bbp")
