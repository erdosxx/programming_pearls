cmake_minimum_required(VERSION 3.3)

project(Ch25_Honors_Class C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        GCD1.h
        GCD2.h
        first-missing-positive.h
        Max_difference_k_pairs.h
        Biggest_product_n-1.h
        Biggest_product_n-1_math.h
        Longest_increasing_subarray.h
        Rotate_array_permutation.h
        Rotate_array.h
        rook-attack.h
        justify-text.h
        Zipping_list.h
        Copying_postings_list.h
        longest-valid-parentheses.h
        Sliding_window.h
        binary-tree-postorder-traversal-iterative-alternative.h
        binary-tree-postorder-traversal-iterative.h
        bonus.h
        bonus-improved.h
        Binary_search_unknown_length.h
        Find_kth_element_in_two_sorted_arrays.h
        k-th_largest_element_large_n.h
        Find_element_appears_once.h
        Line_most_points.h
        Shortest_unique_prefix.h
        ../Chapter_8_Linked_Lists/Doubly_linked_list_prototype.h
        Sorted_list_to_BST.h
        BST_to_sorted_doubly_list.h
        BST_prototype_shared_ptr.h
        Merge_two_BSTs.h
        View_from_above.h
        Regular_expression.h
        Add_operators_in_string.h
        Count_inversions.h
        Drawing_skylines.h
        drawing_skylines_alternative.h
        Three_jugs.h
        Maximum_subarray_in_circular_array.h
        Maximum_subarray_in_circular_array_constant_space.h
        Height_determination.h
        Max_submatrix_rectangle.h
        Max_submatrix_rectangle_improved.h
        Max_submatrix_square.h
        Max_submatrix_rectangle_brute_force.h
        Huffman_encoding.h
        trapping-rain-water.h
        Search_a_pair_sorted_array.h
        Search_frequent_items.h
        Longest_subarray_k_improved.h
        Longest_subarray_k.h
        Road_network.h
        Arbitrage.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

add_library(Ch25_Honors_Class STATIC ${SOURCE_FILES} ${HEADER_FILES})