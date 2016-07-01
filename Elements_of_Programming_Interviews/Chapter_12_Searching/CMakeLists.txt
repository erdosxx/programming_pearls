cmake_minimum_required(VERSION 3.3)

project(Ch12_Searching C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        Bentleybsearch.h
        Binary_search_first_k.h
        Binary_search_Ai=i.h
        Binary_search_circular_array.h
        Binary_search_circular_array_with_duplicates.h
        square-root-int.h
        Square_root.h
        Matrix_search.h
        Finding_min_max.h
        order_statistic.h
        Missing_element.h
        Find_missing_and_duplicate_XOR.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

add_library(Ch12_Searching STATIC ${SOURCE_FILES} ${HEADER_FILES})