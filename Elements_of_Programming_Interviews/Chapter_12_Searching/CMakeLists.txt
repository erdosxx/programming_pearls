cmake_minimum_required(VERSION 3.3)

project(Ch12_Searching C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        Bentleybsearch.h
        student_search.h
        Binary_search_first_k.h
        Binary_search_first_larger_k.h
        Binary_search_upper_lower_k.h
        Binary_search_local_minimum.h
        prefix_search.h
        Binary_search_Ai=i.h
        Binary_search_circular_array.h
        Binary_search_circular_array_with_duplicates.h
        Binary_search_ascending_descending_array.h
        Binary_search_k_circular_array.h
        square-root-int.h
        Square_root.h
        DivisionFloat.h
        Matrix_search.h
        Finding_min_max.h
        order_statistic.h
        Missing_element.h
        Find_missing_and_duplicate_XOR.h
        min_index_distance.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

#add_library(Ch12_Searching STATIC ${SOURCE_FILES} ${HEADER_FILES})