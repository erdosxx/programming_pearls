cmake_minimum_required(VERSION 3.3)

project(Builder)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runBuilderTests
        builder_test.cpp)

target_link_libraries(runBuilderTests gtest gtest_main)