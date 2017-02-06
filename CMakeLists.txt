cmake_minimum_required(VERSION 3.4)
project(Mila)

set(MILA_VERSION_MAJOR 0)
set(MILA_VERSION_MINOR 4)
set(MILA_VERSION_PATCH 0)
configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/include/version.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/include/version.h"
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(CheckCXXCompilerFlag)

check_cxx_compiler_flag(/fp:strict HAS_FP_STRICT)
if (HAS_FP_STRICT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:strict")
endif()

check_cxx_compiler_flag(-msse2 HAS_MSSE2)
if (HAS_MSSE2)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2")
endif()

check_cxx_compiler_flag(-mfpmath HAS_MFPMATH)
if (HAS_MFPMATH)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfpmath=sse")
endif()

check_cxx_compiler_flag(-std=gnu++11 HAS_CPP11)
if (HAS_CPP11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
endif()

set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll")
set(GTEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/deps/googletest)
set(GTEST_INCLUDE_DIRS ${GTEST_ROOT}/include ${GTEST_ROOT})
set(GTEST_LIBRARIES gtest gtest_main)
add_subdirectory(${GTEST_ROOT} EXCLUDE_FROM_ALL)

set(CLPP_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/clpp)

set(UTILS_INCLUDE_DIRS ${OpenCL_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/utils/include ${CLPP_INCLUDE_DIRS} CACHE INTERNAL "")
set(UTILS_LIBRARIES utils_lib ${OpenCL_LIBRARIES} CACHE INTERNAL "")
add_subdirectory(utils)

enable_testing()
configure_file(CTestCustom.cmake ${CMAKE_BINARY_DIR})

add_subdirectory(bbp)
add_subdirectory(mean_shift)
add_subdirectory(n_body)
add_subdirectory(ocl2json)

set_property(TARGET gtest PROPERTY FOLDER "deps")
set_property(TARGET gtest_main PROPERTY FOLDER "deps")
