cmake_minimum_required(VERSION 3.3)

project(Ch9_Graph_Algorithms)

add_definitions(-std=c++11)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runGraphAlgorithmsTests
        graph_algorithms_test.cpp)


target_link_libraries(runGraphAlgorithmsTests gtest gtest_main)