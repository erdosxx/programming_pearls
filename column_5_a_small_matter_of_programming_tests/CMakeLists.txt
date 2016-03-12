cmake_minimum_required(VERSION 3.3)

project(column_9_code_tuning)

add_definitions(-std=c++11)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runSearchTests
        search_test.cpp)

target_link_libraries(runSearchTests gtest gtest_main)
