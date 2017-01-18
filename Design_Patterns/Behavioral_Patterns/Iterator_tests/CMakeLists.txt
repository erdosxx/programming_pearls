cmake_minimum_required(VERSION 3.3)

project(Iterator)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runIteratorTests
        iterator_test.cpp)

target_link_libraries(runIteratorTests gtest gtest_main)