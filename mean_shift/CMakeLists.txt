cmake_minimum_required(VERSION 3.3)
project(mean_shift)

find_package(PNG REQUIRED)

add_subdirectory(parallel)
add_subdirectory(sequential)
