cmake_minimum_required(VERSION 3.3)

project(Visitor)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runVisitorTests
        visitor_test.cpp)

target_link_libraries(runVisitorTests gtest gtest_main)