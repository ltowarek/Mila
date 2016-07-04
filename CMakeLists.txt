cmake_minimum_required(VERSION 3.4)
project(Mila)

set(MILA_VERSION_MAJOR 0)
set(MILA_VERSION_MINOR 3)
set(MILA_VERSION_PATCH 0)
configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/include/version.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/include/version.h"
)

set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll")
set(GTEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/deps/googletest)
set(GTEST_INCLUDE_DIRS ${GTEST_ROOT}/include ${GTEST_ROOT})
set(GTEST_LIBRARIES gtest gtest_main)
add_subdirectory(${GTEST_ROOT} EXCLUDE_FROM_ALL)

set(CLPP_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/clpp)

set(UTILS_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/utils/include CACHE INTERNAL "")
set(UTILS_LIBRARIES utils_lib CACHE INTERNAL "")
add_subdirectory(utils)

enable_testing()
configure_file(CTestCustom.cmake ${CMAKE_BINARY_DIR})

add_subdirectory(bbp)
add_subdirectory(mean_shift)
add_subdirectory(n_body)
add_subdirectory(sudoku_solver)
add_subdirectory(ocl2json)
