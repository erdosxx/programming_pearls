#ifndef ALGORITHM_ANALYSIS_SYMMETRIC_BINARY_TREE_H
#define ALGORITHM_ANALYSIS_SYMMETRIC_BINARY_TREE_H
// 10.2 Test if a binary tree is symmetric

#include <cassert>
#include <iostream>
#include <memory>

#include "Binary_tree_prototype.h"

using std::unique_ptr;
using btree::BinaryTreeNode;
using btree_ptr= unique_ptr<BinaryTreeNode<int>>;

bool CheckSymmetric(const btree_ptr & subtree_0,
                    const btree_ptr & subtree_1) {
    if (subtree_0 == nullptr && subtree_1 == nullptr) {
        return true;
    } else if (subtree_0 != nullptr && subtree_1 != nullptr) {
        return subtree_0->data == subtree_1->data &&
               CheckSymmetric(subtree_0->left, subtree_1->right) &&
               CheckSymmetric(subtree_0->right, subtree_1->left);
    }
    // One subtree is empty, and the other is not.
    return false;
}

bool IsSymmetric(const btree_ptr & tree) {
    return tree == nullptr || CheckSymmetric(tree->left, tree->right);
}

#endif //ALGORITHM_ANALYSIS_SYMMETRIC_BINARY_TREE_H
