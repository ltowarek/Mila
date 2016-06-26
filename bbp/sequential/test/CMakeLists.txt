cmake_minimum_required(VERSION 3.3)
project(bbp_sequential_test)

include_directories(${GTEST_INCLUDE_DIRS} ${BBP_SEQUENTIAL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} test.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${BBP_SEQUENTIAL_LIBRARIES})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
