cmake_minimum_required(VERSION 3.3)

project(Ch7_Sorting)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runSortingTests
        sorting_test.cpp)


target_link_libraries(runSortingTests gtest gtest_main)