cmake_minimum_required(VERSION 3.3)

project(Ch8_LinkedLists C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        Linked_list_prototype.h
        Merge_sorted_lists.h
        reverse_linked_list_from_s_to_f.h
        Checking_cycle.h
        Checking_cycle_alternative.h
        Overlapping_lists_no_cycle.h
        Overlapping_lists.h
        Deletion_list.h
        Remove_kth_last_list.h
        remove-duplicates-sorted-list.h
        cyclic-right-shift.h
        Even_odd_merge_linked_list.h
        Palindrome_linked_list.h
        Reverse_linked_list_iterative.h
        list-pivoting.h
        add-two-number-list.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

add_library(Ch8_LinkedLists STATIC ${SOURCE_FILES} ${HEADER_FILES})