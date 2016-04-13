cmake_minimum_required(VERSION 3.3)
project(sudoku_solver_utils_test)

include_directories(${GTEST_INCLUDE_DIRS} ${SUDOKU_SOLVER_UTILS_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} sudoku_solver_utils_test.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${SUDOKU_SOLVER_UTILS_LIBRARIES})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
