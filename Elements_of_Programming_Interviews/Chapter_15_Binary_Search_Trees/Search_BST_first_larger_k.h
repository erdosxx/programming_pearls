#ifndef ALGORITHM_ANALYSIS_SEARCH_BST_FIRST_LARGER_K_H
#define ALGORITHM_ANALYSIS_SEARCH_BST_FIRST_LARGER_K_H
// 15.2 Find the first key greater than a given timestamp in a BST

#include "BST_prototype.h"

using std::unique_ptr;

// @include
BSTNode<int>* FindFirstGreaterThanK(const unique_ptr<BSTNode<int>>& tree, int k) {
    BSTNode<int> *subtree = tree.get();
    BSTNode<int> *first_so_far = nullptr;

    while (subtree) {
        if (subtree->data > k) {
            first_so_far = subtree;
            subtree = subtree->left.get();
        } else {  // Root and all keys in left subtree are <= k, so skip them.
            subtree = subtree->right.get();
        }
    }
    return first_so_far;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_SEARCH_BST_FIRST_LARGER_K_H
