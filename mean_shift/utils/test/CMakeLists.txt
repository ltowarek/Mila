cmake_minimum_required(VERSION 3.4)
project(mean_shift_utils_test)

include_directories(${GTEST_INCLUDE_DIRS} ${MEAN_SHIFT_UTILS_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} mean_shift_utils_test.cpp ${LODEPNG_INCLUDE_DIRS}/lodepng.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${MEAN_SHIFT_UTILS_LIBRARIES})

file(COPY test_image.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

set_property(TARGET mean_shift_utils_test PROPERTY FOLDER "mean_shift")
