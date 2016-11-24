cmake_minimum_required(VERSION 3.3)

project(column_15_strings_of_pearls)

add_definitions(-std=c++11)

set(HEADER_FILES
        column15.h
        )

set(SOURCE_FILES
        ../dummy.cpp
        )

add_library(column_15_strings_of_pearls STATIC ${SOURCE_FILES} ${HEADER_FILES})