cmake_minimum_required(VERSION 3.3)

project(Ch10_BinaryTrees C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        Binary_tree_prototype.h
        Balanced_binary_tree.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

add_library(Ch10_BinaryTrees STATIC ${SOURCE_FILES} ${HEADER_FILES})