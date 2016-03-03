cmake_minimum_required(VERSION 3.3)

project(column_1_cracking_the_oyster_tests)

add_definitions(-std=c++11)

#set(HEADER_FILES
#        sort.h
#        )

set(SOURCE_FILES
        testsort.cpp
        )

add_library(column_1_cracking_the_oyster_tests STATIC ${SOURCE_FILES} ${HEADER_FILES})