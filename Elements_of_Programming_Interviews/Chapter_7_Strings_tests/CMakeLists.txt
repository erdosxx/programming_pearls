cmake_minimum_required(VERSION 3.3)

project(Ch7_Strings)

# for supporting equal(first1, last1, first2, last2) c++14 is required.
add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runElementsStringsTests
        Strings_test.cpp)

target_link_libraries(runElementsStringsTests gtest gtest_main)