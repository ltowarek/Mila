cmake_minimum_required(VERSION 3.4)
project(n_body_interactive_view_test)

configure_file(reference_mouse_positions.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(reference_particles.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${KERNEL_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

include_directories(${GTEST_INCLUDE_DIRS} ${N_BODY_INTERACTIVE_VIEW_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} n_body_interactive_view_test.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${N_BODY_INTERACTIVE_VIEW_LIBRARIES})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

set_property(TARGET n_body_interactive_view_test PROPERTY FOLDER "n_body")
