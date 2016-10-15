#ifndef ALGORITHM_ANALYSIS_BST_TO_SORTED_DOUBLY_LIST_H
#define ALGORITHM_ANALYSIS_BST_TO_SORTED_DOUBLY_LIST_H

#include <memory>

#include "BST_prototype_shared_ptr.h"

using std::make_shared;
using std::shared_ptr;

// @include
struct HeadAndTail {
    shared_ptr<BSTNode<int>> head, tail;
};

HeadAndTail BSTToDoublyLinkedListHelper(const shared_ptr<BSTNode<int>>&);

shared_ptr<BSTNode<int>> BSTToDoublyLinkedList(
        const shared_ptr<BSTNode<int>>& tree) {
    return BSTToDoublyLinkedListHelper(tree).head;
}

// Transforms a BST into a sorted doubly linked list in-place,
// and return the head and tail of the list.
HeadAndTail BSTToDoublyLinkedListHelper(
        const shared_ptr<BSTNode<int>>& tree) {
    // Empty subtree.
    if (!tree) {
        return {nullptr, nullptr};
    }

    // Recursively builds the list from left and right subtrees.
    HeadAndTail left = BSTToDoublyLinkedListHelper(tree->left);
    HeadAndTail right = BSTToDoublyLinkedListHelper(tree->right);

    // Appends tree to the list from left subtree.
    if (left.tail) {
        left.tail->right = tree;
    }
    tree->left = left.tail;

    // Appends the list from right subtree to tree.
    tree->right = right.head;
    if (right.head) {
        right.head->left = tree;
    }

    return {left.head ? left.head : tree, right.tail ? right.tail : tree};
}
// @exclude

#endif //ALGORITHM_ANALYSIS_BST_TO_SORTED_DOUBLY_LIST_H
