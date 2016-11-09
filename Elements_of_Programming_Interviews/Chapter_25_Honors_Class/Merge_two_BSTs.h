#ifndef ALGORITHM_ANALYSIS_MERGE_TWO_BSTS_H
#define ALGORITHM_ANALYSIS_MERGE_TWO_BSTS_H
// 25.24 Merge two BSTs

#include <memory>

#include "BST_prototype_shared_ptr.h"

using std::make_shared;
using std::shared_ptr;

shared_ptr<BSTNode<int>> BSTToDoublyListHelper(
        const shared_ptr<BSTNode<int>>&);

shared_ptr<BSTNode<int>> MergeTwoSortedLists(shared_ptr<BSTNode<int>>,
shared_ptr<BSTNode<int>>);

void AppendNode(shared_ptr<BSTNode<int>>*, shared_ptr<BSTNode<int>>*);

// Build a BST from the (s + 1)-th to the e-th node in L.
shared_ptr<BSTNode<int>> BuildBSTFromSortedDoublyListHelper(
        shared_ptr<BSTNode<int>>* L, int s, int e) {
    shared_ptr<BSTNode<int>> curr = nullptr;
    if (s < e) {
        int m = s + ((e - s) / 2);
        auto temp = BuildBSTFromSortedDoublyListHelper(L, s, m);
        curr = *L;
        curr->left = temp;
        *L = (*L)->right;
        curr->right = BuildBSTFromSortedDoublyListHelper(L, m + 1, e);
    }
    return curr;
}

shared_ptr<BSTNode<int>> BuildBSTFromSortedDoublyList(
        shared_ptr<BSTNode<int>> L, int n) {
    return BuildBSTFromSortedDoublyListHelper(&L, 0, n);
}

shared_ptr<BSTNode<int>> BSTToDoublyList(const shared_ptr<BSTNode<int>>& n) {
    auto res = BSTToDoublyListHelper(n);
    res->left->right = nullptr;  // breaks the link from tail to head.
    res->left = nullptr;  // breaks the link from head to tail.
    return res;
}

// Transform a BST into a circular sorted doubly linked list in-place,
// return the head of the list.
shared_ptr<BSTNode<int>> BSTToDoublyListHelper(
        const shared_ptr<BSTNode<int>>& n) {
    // Empty subtree.
    if (!n) {
        return nullptr;
    }

    // Recursively build the list from left and right subtrees.
    auto l_head(BSTToDoublyListHelper(n->left));
    auto r_head(BSTToDoublyListHelper(n->right));

    shared_ptr<BSTNode<int>> l_tail = nullptr;

    // Append n to the list from left subtree.
    if (l_head) {
        l_tail = l_head->left;
        l_tail->right = n;
        n->left = l_tail;
        l_tail = n;
    } else {
        l_head = l_tail = n;
    }

    shared_ptr<BSTNode<int>> r_tail = nullptr;

    // Append the list from right subtree to n.
    if (r_head) {
        r_tail = r_head->left;
        l_tail->right = r_head;
        r_head->left = l_tail;
    } else {
        r_tail = l_tail;
    }
    r_tail->right = l_head;
    l_head->left = r_tail;

    return l_head;
}

// Count the list length till end.
int CountLength(shared_ptr<BSTNode<int>> L) {
    int len = 0;
    while (L) {
        ++len;
        L = L->right;
    }
    return len;
}

// @include
shared_ptr<BSTNode<int>> MergeTwoBSTs(shared_ptr<BSTNode<int>> A,
                                      shared_ptr<BSTNode<int>> B) {
    A = BSTToDoublyList(A);
    B = BSTToDoublyList(B);

    int A_length = CountLength(A);
    int B_length = CountLength(B);

    return BuildBSTFromSortedDoublyList(MergeTwoSortedLists(A, B),
                                        A_length + B_length);
}
// @exclude

// Merges two sorted doubly linked lists, returns the head of merged list.
shared_ptr<BSTNode<int>> MergeTwoSortedLists(shared_ptr<BSTNode<int>> A,
                                             shared_ptr<BSTNode<int>> B) {
    shared_ptr<BSTNode<int>> sorted_head(new BSTNode<int>);
    shared_ptr<BSTNode<int>> tail = sorted_head;

    while (A && B) {
        AppendNode(A->data < B->data ? &A : &B, &tail);
    }

    if (A) {
        // Appends the remaining of A.
        AppendNode(&A, &tail);
    } else if (B) {
        // Appends the remaining of B.
        AppendNode(&B, &tail);
    }
    return sorted_head->right;
}

// tail -> node
void AppendNode(shared_ptr<BSTNode<int>>* node,
                shared_ptr<BSTNode<int>>* tail) {
    (*tail)->right = *node;
    *tail = *node;  // Resets tail to the last node.
    *node = (*node)->right; // Move node target to next
}

#endif //ALGORITHM_ANALYSIS_MERGE_TWO_BSTS_H
