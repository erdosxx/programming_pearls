cmake_minimum_required(VERSION 3.3)

project(Ch4_Trees)

add_definitions(-std=c++11)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runTreeTests
        tree_test.cpp)


target_link_libraries(runTreeTests gtest gtest_main)
