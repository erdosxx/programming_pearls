cmake_minimum_required(VERSION 3.3)

project(Ch17_DP C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        fibonacci.h
        Max-sum_subarray.h
        Score_combination.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

add_library(Ch17_DP STATIC ${SOURCE_FILES} ${HEADER_FILES})