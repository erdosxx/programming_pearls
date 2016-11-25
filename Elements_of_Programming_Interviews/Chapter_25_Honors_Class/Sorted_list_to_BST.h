#ifndef ALGORITHM_ANALYSIS_SORTED_LIST_TO_BST_H
#define ALGORITHM_ANALYSIS_SORTED_LIST_TO_BST_H
// 25.22 Convert a sorted doubly linked list into a BST

#include <memory>

#include "Doubly_linked_list_prototype.h"

// Builds a BST from the (start + 1)-th to the end-th node, inclusive, in L,
// and returns the root.
shared_ptr<DL::ListNode<int>> BuildBSTFromSortedDoublyListHelper(
        shared_ptr<DL::ListNode<int>>* L_ptr, const int& start, const int& end) {
    if (start >= end) {
        return nullptr;
    }

    int mid = start + ((end - start) / 2);
    auto left = BuildBSTFromSortedDoublyListHelper(L_ptr, start, mid);
    // The last function call sets L_ptr to the successor of the maximum node in
    // the tree rooted at left.
    auto curr = *L_ptr;
    *L_ptr = (*L_ptr)->next;
    curr->prev = left;
    curr->next = BuildBSTFromSortedDoublyListHelper(L_ptr, mid + 1, end);
    return curr;
}

// Returns the root of the corresponding BST. The prev and next fields of the
// list nodes are used as the BST nodes left and right fields, respectively.
// The length of the list is given.
shared_ptr<DL::ListNode<int>> BuildBSTFromSortedDoublyList(
        shared_ptr<DL::ListNode<int>> L, const int& length) {
    return BuildBSTFromSortedDoublyListHelper(&L, 0, length);
}

#endif //ALGORITHM_ANALYSIS_SORTED_LIST_TO_BST_H
