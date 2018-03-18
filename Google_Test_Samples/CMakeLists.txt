cmake_minimum_required(VERSION 3.3)

project(Google_Test_Samples)

# for supporting equal(first1, last1, first2, last2) c++14 is required.
add_definitions(-std=c++17)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(sample1_unittest sample1_unittest.cc sample1.cc)
add_executable(sample2_unittest sample2_unittest.cc sample2.cc)
add_executable(sample3_unittest sample3_unittest.cc)
add_executable(sample4_unittest sample4_unittest.cc sample4.cc)
add_executable(sample5_unittest sample5_unittest.cc sample1.cc)
add_executable(sample6_unittest sample6_unittest.cc)
add_executable(sample7_unittest sample7_unittest.cc)
add_executable(sample8_unittest sample8_unittest.cc)
add_executable(sample9_unittest sample9_unittest.cc)
add_executable(sample10_unittest sample10_unittest.cc)
add_executable(mock_turtle_test mock_turtle_test.cpp)

target_link_libraries(sample1_unittest gtest gmock gtest_main)
target_link_libraries(sample2_unittest gtest gmock gtest_main)
target_link_libraries(sample3_unittest gtest gmock gtest_main)
target_link_libraries(sample4_unittest gtest gmock gtest_main)
target_link_libraries(sample5_unittest gtest gmock gtest_main)
target_link_libraries(sample6_unittest gtest gmock gtest_main)
target_link_libraries(sample7_unittest gtest gmock gtest_main)
target_link_libraries(sample8_unittest gtest gmock gtest_main)
target_link_libraries(sample10_unittest gtest gmock gtest_main)
target_link_libraries(mock_turtle_test gmock gtest gtest_main)

set(HEADER_FILES
        sample1.h
        sample2.h
        sample3-inl.h
        sample4.h
        prime_tables.h
        turtle.h
        mock_turtle.h
        painter.h
        )

set(SOURCE_FILES
        sample1.cc
        sample1_unittest.cc
        sample2.cc
        sample2_unittest.cc
        sample3_unittest.cc
        sample4.cc
        sample4_unittest.cc
        sample5_unittest.cc
        sample6_unittest.cc
        sample7_unittest.cc
        sample8_unittest.cc
        sample9_unittest.cc
        sample10_unittest.cc
        )

add_library(Google_Test_Samples STATIC ${SOURCE_FILES} ${HEADER_FILES})
