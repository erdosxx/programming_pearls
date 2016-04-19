cmake_minimum_required(VERSION 3.3)

project(column_15_strings_of_pearls)

add_definitions(-std=c++11)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runStringsTests
        strings_test.cpp)

target_link_libraries(runStringsTests gtest gtest_main)
