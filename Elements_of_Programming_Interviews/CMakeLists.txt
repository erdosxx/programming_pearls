cmake_minimum_required(VERSION 3.3)
project(Elements_of_Programming_Interviews C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
        Chapter_5_Primitive_Types
        Chapter_6_Arrays
        )

add_subdirectory(Chapter_5_Primitive_Types)
add_subdirectory(Chapter_5_Primitive_Types_tests)
add_subdirectory(Chapter_6_Arrays)
add_subdirectory(Chapter_6_Arrays_tests)
