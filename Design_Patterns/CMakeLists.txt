cmake_minimum_required(VERSION 3.3)
project(Design_Patterns C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_subdirectory(Behavioral_Patterns)
add_subdirectory(Creational_Patterns)
add_subdirectory(Structural_Patterns)
