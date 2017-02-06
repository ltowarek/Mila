cmake_minimum_required(VERSION 3.4)
project(mean_shift_image_processing_test)

configure_file(test_image.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(test_image_reference.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

include_directories(${GTEST_INCLUDE_DIRS} ${MEAN_SHIFT_IMAGE_PROCESSING_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} mean_shift_image_processing_test.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${MEAN_SHIFT_IMAGE_PROCESSING_LIBRARIES})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

set_property(TARGET mean_shift_image_processing_test PROPERTY FOLDER "mean_shift")
