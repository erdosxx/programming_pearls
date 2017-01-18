cmake_minimum_required(VERSION 3.3)

project(Command)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runCommandTests
        command_test.cpp)

target_link_libraries(runCommandTests gtest gtest_main)