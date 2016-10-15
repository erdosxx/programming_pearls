#ifndef ALGORITHM_ANALYSIS_SORTED_LIST_TO_BST_H
#define ALGORITHM_ANALYSIS_SORTED_LIST_TO_BST_H

#include <cassert>
#include <iostream>
#include <memory>

#include "Doubly_linked_list_prototype.h"

using std::make_shared;
using std::cout;
using std::endl;

shared_ptr<DL::ListNode<int>> BuildBSTFromSortedDoublyListHelper(
        shared_ptr<DL::ListNode<int>>*, const int, const int);

// @include
// Returns the root of the corresponding BST. The prev and next fields of the
// list nodes are used as the BST nodes left and right fields, respectively.
// The length of the list is given.
shared_ptr<DL::ListNode<int>> BuildBSTFromSortedDoublyList(
        shared_ptr<DL::ListNode<int>> L, const int length) {
    return BuildBSTFromSortedDoublyListHelper(&L, 0, length);
}

// Builds a BST from the (start + 1)-th to the end-th node, inclusive, in L,
// and returns the root.
shared_ptr<DL::ListNode<int>> BuildBSTFromSortedDoublyListHelper(
        shared_ptr<DL::ListNode<int>>* L_ref, const int start, const int end) {
    if (start >= end) {
        return nullptr;
    }

    int mid = start + ((end - start) / 2);
    auto left = BuildBSTFromSortedDoublyListHelper(L_ref, start, mid);
    // The last function call sets L_ref to the successor of the maximum node in
    // the tree rooted at left.
    auto curr = *L_ref;
    *L_ref = (*L_ref)->next;
    curr->prev = left;
    curr->next = BuildBSTFromSortedDoublyListHelper(L_ref, mid + 1, end);
    return curr;
}
// @exclude

template <typename T>
void InorderTraversal(const shared_ptr<DL::ListNode<T>>& node, const T& pre,
                      int depth) {
    if (node) {
        InorderTraversal(node->prev, pre, depth + 1);
        assert(pre <= node->data);
        cout << node->data << ' ' << "; depth = " << depth << endl;
        InorderTraversal(node->next, node->data, depth + 1);
    }
}

#endif //ALGORITHM_ANALYSIS_SORTED_LIST_TO_BST_H
