cmake_minimum_required(VERSION 3.3)

project(column_8_algorithm_design_techniques)

add_definitions(-std=c++11)

set(HEADER_FILES
        column8.h
        )

#set(SOURCE_FILES
#        search.c.c
#        )

add_library(column_8_algorithm_design_techniques STATIC ${SOURCE_FILES} ${HEADER_FILES})