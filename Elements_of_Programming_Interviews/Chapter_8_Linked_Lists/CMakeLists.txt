cmake_minimum_required(VERSION 3.3)

project(Ch8_LinkedLists C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        linked_list_boot_camp.h
        Linked_list_prototype.h
        Doubly_linked_list_prototype.h
        Merge_sorted_lists.h
        Merge_sorted_doubly_linked_lists.h
        reverse_linked_list_from_s_to_f.h
        Reverse_linked_list_iterative.h
        Reverse_linked_list_recursive.h
        reverse-list-in-k-group.h
        reverse-list-in-k-group-erdos.h
        Checking_cycle.h
        Checking_cycle_alternative.h
        Overlapping_lists_no_cycle.h
        Overlapping_lists.h
        Deletion_list.h
        Remove_kth_last_list.h
        remove-duplicates-sorted-list.h
        cyclic-right-shift.h
        Even_odd_merge_linked_list.h
        Even_odd_merge_linked_list_erdos.h
        Palindrome_linked_list.h
        list-pivoting.h
        add-two-number-list.h
        )

set(SOURCE_FILES
        ../dummy.cpp
        )

add_library(Ch8_LinkedLists STATIC ${SOURCE_FILES} ${HEADER_FILES})