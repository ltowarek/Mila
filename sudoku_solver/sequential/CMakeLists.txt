cmake_minimum_required(VERSION 3.4)
project(sudoku_solver_sequential)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${SUDOKU_SOLVER_UTILS_INCLUDE_DIRS})
set(SUDOKU_SOLVER_SEQUENTIAL_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include ${SUDOKU_SOLVER_UTILS_INCLUDE_DIRS})
set(SUDOKU_SOLVER_SEQUENTIAL_LIBRARIES ${SUDOKU_SOLVER_UTILS_LIBRARIES} sudoku_solver_sequential_lib)
add_library(sudoku_solver_sequential_lib include/sudoku_solver_sequential.h include/sudoku_solver_sequential.cpp
            include/sudoku_solver_sequential_profiler.h include/sudoku_solver_sequential_profiler.cpp)
target_link_libraries(sudoku_solver_sequential_lib ${SUDOKU_SOLVER_UTILS_LIBRARIES})

add_subdirectory(test)

include_directories(${UTILS_INCLUDE_DIRS} ${SUDOKU_SOLVER_SEQUENTIAL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${UTILS_LIBRARIES} ${SUDOKU_SOLVER_SEQUENTIAL_LIBRARIES})

