cmake_minimum_required(VERSION 3.3)

project(Ch25_Honors_Class)

# for supporting equal(first1, last1, first2, last2) c++14 is required.
add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runCh25HonorsClass
        Honors_Class_test.cpp)

target_link_libraries(runCh25HonorsClass gtest gtest_main)