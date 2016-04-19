cmake_minimum_required(VERSION 3.3)

project(column_1_cracking_the_oyster_tests)

add_definitions(-std=c++11)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runBitSortTests
        bit_sort_test.cpp)


add_executable(runWeissSortTests
        weiss_sort_test.cpp)

target_link_libraries(runBitSortTests gtest gtest_main)
target_link_libraries(runWeissSortTests gtest gtest_main)
#target_link_libraries(runBitSortTests column_1_cracking_the_oyster)
