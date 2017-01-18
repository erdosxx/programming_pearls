cmake_minimum_required(VERSION 3.3)

project(Decorator)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runDecoratorTests
        decorator_test.cpp)

target_link_libraries(runDecoratorTests gtest gtest_main)