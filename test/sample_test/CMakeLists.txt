cmake_minimum_required(VERSION 3.3)
project(sample_test)

include_directories(${GTEST_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} sample_test.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES})
