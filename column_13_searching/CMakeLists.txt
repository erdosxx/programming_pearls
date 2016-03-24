cmake_minimum_required(VERSION 3.3)

project(column_13_searching)

add_definitions(-std=c++11)

set(HEADER_FILES
        column13.h
        )

#set(SOURCE_FILES
#        sortedrand.cpp
#        )

add_library(column_13_searching STATIC ${SOURCE_FILES} ${HEADER_FILES})