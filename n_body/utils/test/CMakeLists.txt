cmake_minimum_required(VERSION 3.4)
project(n_body_utils_test)

include_directories(${GTEST_INCLUDE_DIRS} ${N_BODY_UTILS_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} n_body_utils_test.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${N_BODY_UTILS_LIBRARIES})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

set_property(TARGET n_body_utils_test PROPERTY FOLDER "n_body")
