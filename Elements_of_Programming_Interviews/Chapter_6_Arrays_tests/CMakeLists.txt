cmake_minimum_required(VERSION 3.3)

project(Ch6_Arrays)

# for supporting equal(first1, last1, first2, last2) c++14 is required.
add_definitions(-std=c++17)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runArraysTests arrays_test.cpp)

add_executable(permute_the_elements_of_an_array_6_9_test
        permute_the_elements_of_an_array_6_9_test.cpp)

add_executable(introduction_to_google_test introduction_to_google_test.cpp)

target_link_libraries(runArraysTests gtest gtest_main)
target_link_libraries(permute_the_elements_of_an_array_6_9_test gtest gmock gtest_main)
target_link_libraries(introduction_to_google_test gtest gmock gtest_main)
