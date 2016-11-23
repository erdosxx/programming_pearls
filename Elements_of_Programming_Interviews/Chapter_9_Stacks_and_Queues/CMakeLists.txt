cmake_minimum_required(VERSION 3.3)

project(Ch9_StacksQueues C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        stacks_boot_camp.h
        queues_boot_camp.h
        Stack_with_max.h
        Stack_with_max_improved.h
        RPN.h
        Polish_Notation.h
        valid-parentheses.h
        normalized_pathnames.h
        Postings_list_prototype.h
        Search_postings_list_iterative.h
        Search_postings_list_recursive.h
        View_sunset.h
        Binary_tree_prototype.h
        Binary_tree_level_order.h
        Circular_queue.h
        Queue_from_stacks.h
        Queue_with_max.h
        Queue_with_max_alternative.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

#add_library(Ch9_StacksQueues STATIC ${SOURCE_FILES} ${HEADER_FILES})