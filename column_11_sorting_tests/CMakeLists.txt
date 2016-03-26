cmake_minimum_required(VERSION 3.3)

project(column_11_sorting)

add_definitions(-std=c++11)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runSortAlgorithmTests
         sort_check.cpp)

target_link_libraries(runSortAlgorithmTests gtest gtest_main)
