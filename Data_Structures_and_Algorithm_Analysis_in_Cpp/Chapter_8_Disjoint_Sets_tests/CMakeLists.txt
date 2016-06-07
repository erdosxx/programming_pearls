cmake_minimum_required(VERSION 3.3)

project(Ch8_Disjoint_Sets)

add_definitions(-std=c++11)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runDisjointSetsTests
        disjoint_sets_test.cpp
        )


target_link_libraries(runDisjointSetsTests gtest gtest_main)