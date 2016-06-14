cmake_minimum_required(VERSION 3.3)

project(Ch10_BinaryTrees)

# for supporting equal(first1, last1, first2, last2) c++14 is required.
add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runBinaryTreesTests
        Binary_Trees_test.cpp)

target_link_libraries(runBinaryTreesTests gtest gtest_main)