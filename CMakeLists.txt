cmake_minimum_required(VERSION 3.3)
project(Mila)

set(GTEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/deps/googletest)
set(GTEST_INCLUDE_DIRS ${GTEST_ROOT}/include ${GTEST_ROOT})
set(GTEST_LIBRARIES gtest gtest_main)
add_subdirectory(${GTEST_ROOT} EXCLUDE_FROM_ALL)

add_subdirectory(bbp)
add_subdirectory(mean_shift)
add_subdirectory(nbody)
add_subdirectory(sudoku_solver)
add_subdirectory(ocl2json)

