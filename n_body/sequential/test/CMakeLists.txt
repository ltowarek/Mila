cmake_minimum_required(VERSION 3.3)
project(n_body_sequential_test)

include_directories(${GTEST_INCLUDE_DIRS} ${N_BODY_SEQUENTIAL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} n_body_sequential_test.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${N_BODY_SEQUENTIAL_LIBRARIES})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
