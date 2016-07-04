#ifndef ALGORITHM_ANALYSIS_IS_BINARY_TREE_A_BST_H
#define ALGORITHM_ANALYSIS_IS_BINARY_TREE_A_BST_H

#include <limits>
#include <memory>

#include "Binary_tree_prototype.h"

using std::make_unique;
using std::numeric_limits;
using std::unique_ptr;

bool AreKeysInRange(const unique_ptr<BinaryTreeNode<int>>&, int, int);

// @include
bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
    return AreKeysInRange(tree, numeric_limits<int>::min(),
                          numeric_limits<int>::max());
}

bool AreKeysInRange(const unique_ptr<BinaryTreeNode<int>>& tree,
                    int low_range, int high_range) {
    if (tree == nullptr) {
        return true;
    } else if (tree->data < low_range || tree->data > high_range) {
        return false;
    }

    return AreKeysInRange(tree->left, low_range, tree->data) &&
           AreKeysInRange(tree->right, tree->data, high_range);
}
// @exclude

#endif //ALGORITHM_ANALYSIS_IS_BINARY_TREE_A_BST_H
