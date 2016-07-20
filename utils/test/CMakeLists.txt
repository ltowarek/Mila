cmake_minimum_required(VERSION 3.4)
project(utils_test)

include_directories(${GTEST_INCLUDE_DIRS} ${UTILS_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} utils_test.cpp version_test.cpp statistics_test.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${UTILS_LIBRARIES})

file(COPY test.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
