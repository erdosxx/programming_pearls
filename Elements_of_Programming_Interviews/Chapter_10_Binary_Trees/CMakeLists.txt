cmake_minimum_required(VERSION 3.3)

project(Ch10_BinaryTrees C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        Binary_tree_prototype.h
        tree_traversal.h
        Balanced_binary_tree.h
        largest_complete_subtree.h
        k-balanced_binary_tree.h
        k-balanced_binary_tree_erdos.h
        Symmetric_binary_tree.h
        Lowest_common_ancestor_no_parent.h
        Binary_tree_with_parent_prototype.h
        Lowest_common_ancestor.h
        sum-root-to-leaf-binary-tree.h
        path-sum-binary-tree.h
        BST_prototype.h
        BST_sorted_order.h
        Binary_tree_utils.h
        binary-tree-preorder-traversal-iterative.h
        k-th_node_binary_tree.h
        Successor.h
        Inorder_traversal_with_parent.h
        Reconstruct_binary_tree_pre_in_orders.h
        Reconstruct_preorder_with_null.h
        Connect_leaves_binary_tree.h
        Exterior_binary_tree.h
        populating-next-right-pointers.h
        populating-next-right-pointers-any-binary-tree.h
        Binary_tree_lock.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

add_library(Ch10_BinaryTrees STATIC ${SOURCE_FILES} ${HEADER_FILES})