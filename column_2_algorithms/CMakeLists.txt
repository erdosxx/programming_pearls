cmake_minimum_required(VERSION 3.3)

project(column_2_algorithms)

add_definitions(-std=c++11)

set(HEADER_FILES
        column2.h
        )

#set(SOURCE_FILES
#        gcd.c myrotate-2.cpp rotate.c sign.c squash.c
#        )

add_library(column_2_algorithms STATIC ${SOURCE_FILES} ${HEADER_FILES})