cmake_minimum_required(VERSION 3.4)
project(sudoku_solver_parallel_test)

configure_file(${KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

include_directories(${GTEST_INCLUDE_DIRS} ${SUDOKU_SOLVER_PARALLEL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} sudoku_solver_parallel_test.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${SUDOKU_SOLVER_PARALLEL_LIBRARIES})

file(COPY test_file.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY test_file_reference.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
