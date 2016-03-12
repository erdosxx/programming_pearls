cmake_minimum_required(VERSION 3.3)

project(column_5_small_matter_of_programming)

add_definitions(-std=c++11)

set(HEADER_FILES
        column5.h
        )

#set(SOURCE_FILES
#        search.c.c
#        )

add_library(column_5_small_matter_of_programming STATIC ${SOURCE_FILES} ${HEADER_FILES})