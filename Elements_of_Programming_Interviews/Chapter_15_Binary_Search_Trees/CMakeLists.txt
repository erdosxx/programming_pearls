cmake_minimum_required(VERSION 3.3)

project(Ch15_BST C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        binary_search_trees_boot_camp.h
        BST_prototype.h
        Binary_tree_prototype.h
        is_binary_tree_a_BST.h
        is_binary_tree_a_BST_BFS.h
        is_binary_tree_a_BST_inorder.h
        Search_BST_first_larger_k.h
        Find_k_largest_BST.h
        BST_lowest_common_ancestor.h
        Rebuild_BST_preorder.h
        Rebuild_BST_preorder_better.h
        Minimum_distance_3_sorted_arrays.h
        generating-a-b-sqrt2-improved.h
        Generating_a_b_sqrt2.h
        Build_BST_from_sorted_array.h
        insertion-deletion-BST.h
        Descendant_and_ancestor.h
        range-lookup-BST.h
        AddingCredits.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

#add_library(Ch15_BST STATIC ${SOURCE_FILES} ${HEADER_FILES})