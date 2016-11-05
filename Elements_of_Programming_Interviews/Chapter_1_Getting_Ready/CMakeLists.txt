cmake_minimum_required(VERSION 3.3)

project(Ch1_Getting_Ready C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

add_library(Ch1_Getting_Ready STATIC ${SOURCE_FILES} ${HEADER_FILES})