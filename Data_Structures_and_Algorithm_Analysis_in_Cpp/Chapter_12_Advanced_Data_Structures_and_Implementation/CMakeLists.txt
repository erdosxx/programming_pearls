cmake_minimum_required(VERSION 3.3)

project(Ch12_Advanced_Data_Structures)

add_definitions(-std=c++11)

set(HEADER_FILES
        SplayTree.h
        RedBlackTree.h
        Treap.h
        PairingHeap.h
        )

set(SOURCE_FILES
        ../dummy.cpp
        )

add_library(Ch12_Advanced_Data_Structures STATIC ${SOURCE_FILES} ${HEADER_FILES})
