cmake_minimum_required(VERSION 3.3)

project(column_13_searching)

add_definitions(-std=c++11)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runSearchingTests
        searching_test.cpp)

target_link_libraries(runSearchingTests gtest gtest_main)
