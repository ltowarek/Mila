cmake_minimum_required(VERSION 3.4)
project(ocl2json)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(deps/json11 EXCLUDE_FROM_ALL)
# Remove gcc specific flags from json11
set_target_properties(json11 PROPERTIES COMPILE_OPTIONS -fno-rtti -fno-exceptions -Wall)
set(JSON11_INCLUDE_DIR deps/json11)
set(JSON11_LIBRARIES json11)

find_package(OpenCL REQUIRED)

include_directories(${OpenCL_INCLUDE_DIR} ${JSON11_INCLUDE_DIR})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCL_LIBRARIES} ${JSON11_LIBRARIES})

set_property(TARGET ocl2json PROPERTY FOLDER "ocl2json")
set_property(TARGET json11 PROPERTY FOLDER "ocl2json")

install(TARGETS ocl2json DESTINATION ${CMAKE_BINARY_DIR}/bin)
