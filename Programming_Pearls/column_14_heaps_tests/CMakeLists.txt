cmake_minimum_required(VERSION 3.3)

project(column_14_heaps)

add_definitions(-std=c++11)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runHeapsTests
        heap_test.cpp)

target_link_libraries(runHeapsTests gtest gtest_main)
