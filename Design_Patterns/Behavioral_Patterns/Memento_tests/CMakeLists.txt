cmake_minimum_required(VERSION 3.3)

project(Memento)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runMementoTests
        memento_test.cpp)

target_link_libraries(runMementoTests gtest gtest_main)