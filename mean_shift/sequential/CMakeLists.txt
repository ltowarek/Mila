cmake_minimum_required(VERSION 3.3)
project(mean_shift_sequential)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${PNG_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES} ${PNG_LIBRARIES})
