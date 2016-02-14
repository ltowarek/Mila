cmake_minimum_required(VERSION 3.3)
project(mean_shift_parallel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenCL REQUIRED)

file(COPY mean_shift.cl DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(${PNG_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS} ${OpenCL_INCLUDE_DIR})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES} ${PNG_LIBRARIES} ${OpenCL_LIBRARIES})
