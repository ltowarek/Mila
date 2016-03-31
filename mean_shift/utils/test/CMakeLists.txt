cmake_minimum_required(VERSION 3.3)
project(mean_shift_utils_test)

include_directories(${GTEST_INCLUDE_DIRS} ${MEAN_SHIFT_UTILS_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} mean_shift_utils_test.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${BBP_UTILS_LIBRARIES})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
