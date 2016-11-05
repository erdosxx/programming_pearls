cmake_minimum_required(VERSION 3.3)
project(The_Art_of_Computer_Programming C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(
        Chapter_3_Random_Numbers
        )

add_subdirectory(Chapter_3_Random_Numbers)
add_subdirectory(Chapter_3_Random_Numbers_tests)
