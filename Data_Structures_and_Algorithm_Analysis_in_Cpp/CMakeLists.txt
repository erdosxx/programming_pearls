cmake_minimum_required(VERSION 3.3)
project(Data_Structures_and_Algorithm_Analysis_in_Cpp C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
        Chapter_4_Trees
        )

add_subdirectory(Chapter_4_Trees)
add_subdirectory(Chapter_4_Trees_tests)
