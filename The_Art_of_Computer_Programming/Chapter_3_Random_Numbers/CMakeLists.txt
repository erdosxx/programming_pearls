cmake_minimum_required(VERSION 3.3)

project(Ch3_Random_Numbers C CXX)

#for supporting equal(first1, last1, first2, last2) c++14 is required.
add_definitions(-std=c++14)

set(HEADER_FILES
        3_4_2_algorithm_S.h
        3_4_2_Floyd_algorithm.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

add_library(Ch3_Random_Numbers STATIC ${SOURCE_FILES} ${HEADER_FILES})