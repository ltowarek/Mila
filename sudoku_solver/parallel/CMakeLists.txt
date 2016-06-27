cmake_minimum_required(VERSION 3.4)
project(sudoku_solver_parallel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIR})

set(KERNEL_FILE ${PROJECT_SOURCE_DIR}/sudoku_solver.cl)
configure_file(${KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

set(SUDOKU_SOLVER_PARALLEL_INCLUDE_DIRS ${UTILS_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include ${SUDOKU_SOLVER_UTILS_INCLUDE_DIRS} ${OpenCL_INCLUDE_DIR} ${CLPP_INCLUDE_DIRS})
set(SUDOKU_SOLVER_PARALLEL_LIBRARIES ${SUDOKU_SOLVER_UTILS_LIBRARIES} ${OpenCL_LIBRARIES} sudoku_solver_parallel_lib)
add_library(sudoku_solver_parallel_lib include/sudoku_solver_parallel.h include/sudoku_solver_parallel.cpp include/sudoku_solver_parallel_profiler.cpp include/sudoku_solver_parallel_profiler.h)
target_link_libraries(sudoku_solver_parallel_lib ${UTILS_LIBRARIES} ${OpenCL_LIBRARIES} ${SUDOKU_SOLVER_UTILS_LIBRARIES})

add_subdirectory(test)

include_directories(${SUDOKU_SOLVER_PARALLEL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${SUDOKU_SOLVER_PARALLEL_LIBRARIES})
