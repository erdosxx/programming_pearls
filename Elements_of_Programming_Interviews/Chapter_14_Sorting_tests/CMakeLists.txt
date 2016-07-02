cmake_minimum_required(VERSION 3.3)

project(Ch14_Sorting)

# for supporting equal(first1, last1, first2, last2) c++14 is required.
add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runCh14Sorting
        Sorting_test.cpp)

target_link_libraries(runCh14Sorting gtest gtest_main)