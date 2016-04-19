cmake_minimum_required(VERSION 3.3)

project(Ch5_Graph_Traversal)

add_definitions(-std=c++11)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runGraphTests
        graph_test.cpp)


target_link_libraries(runGraphTests gtest gtest_main)
