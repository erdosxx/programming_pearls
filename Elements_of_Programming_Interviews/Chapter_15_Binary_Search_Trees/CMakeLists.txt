cmake_minimum_required(VERSION 3.3)

project(Ch15_BST C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        BST_prototype.h
        Binary_tree_prototype.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

add_library(Ch15_BST STATIC ${SOURCE_FILES} ${HEADER_FILES})