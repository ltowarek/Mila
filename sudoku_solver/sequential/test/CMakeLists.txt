cmake_minimum_required(VERSION 3.4)
project(sudoku_solver_sequential_test)

include_directories(${GTEST_INCLUDE_DIRS} ${SUDOKU_SOLVER_SEQUENTIAL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} sudoku_solver_sequential_test.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${SUDOKU_SOLVER_SEQUENTIAL_LIBRARIES})

file(COPY test_file.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY test_file_reference.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
