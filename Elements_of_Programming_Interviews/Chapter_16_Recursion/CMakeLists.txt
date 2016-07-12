cmake_minimum_required(VERSION 3.3)

project(Ch16_Recursion C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        tower_hanoi.h
        n-queens.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

add_library(Ch16_Recursion STATIC ${SOURCE_FILES} ${HEADER_FILES})