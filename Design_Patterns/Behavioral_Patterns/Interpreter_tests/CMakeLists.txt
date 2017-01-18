cmake_minimum_required(VERSION 3.3)

project(Interpreter)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runInterpreterTests
        interpreter_test.cpp)

target_link_libraries(runInterpreterTests gtest gtest_main)