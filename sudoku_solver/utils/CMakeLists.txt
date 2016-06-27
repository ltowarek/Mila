cmake_minimum_required(VERSION 3.4)
project(sudoku_solver_utils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SUDOKU_SOLVER_UTILS_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "")
set(SUDOKU_SOLVER_UTILS_LIBRARIES sudoku_solver_utils_lib CACHE INTERNAL "")
add_library(sudoku_solver_utils_lib include/sudoku_solver_utils.h include/sudoku_solver_utils.cpp)

add_subdirectory(test)
