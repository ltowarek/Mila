cmake_minimum_required(VERSION 3.4)
project(bbp_sequential_test)

include_directories(${GTEST_INCLUDE_DIRS} ${BBP_SEQUENTIAL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} sequential_bbp_test.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${BBP_SEQUENTIAL_LIBRARIES})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

set_property(TARGET bbp_sequential_test PROPERTY FOLDER "bbp")
