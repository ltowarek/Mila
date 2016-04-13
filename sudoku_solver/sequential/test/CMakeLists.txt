cmake_minimum_required(VERSION 3.3)
project(sudoku_solver_sequential_test)

include_directories(${GTEST_INCLUDE_DIRS} ${SUDOKU_SOLVER_SEQUENTIAL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} sudoku_solver_sequential_test.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${SUDOKU_SOLVER_SEQUENTIAL_LIBRARIES})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
