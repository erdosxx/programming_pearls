cmake_minimum_required(VERSION 3.3)
project(The_Algorithm_Design_Manual C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
        Chapter_5_Graph_Traversal
        )

add_subdirectory(Chapter_5_Graph_Traversal)
add_subdirectory(Chapter_5_Graph_Traversal_tests)
