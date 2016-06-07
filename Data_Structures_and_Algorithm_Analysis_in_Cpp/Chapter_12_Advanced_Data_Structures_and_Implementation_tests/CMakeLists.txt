cmake_minimum_required(VERSION 3.3)

project(Ch12_Advanced_Data_Structures)

add_definitions(-std=c++11)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runAdvancedTreeTests
        adv_tree_test.cpp)

target_link_libraries(runAdvancedTreeTests gtest gtest_main)
