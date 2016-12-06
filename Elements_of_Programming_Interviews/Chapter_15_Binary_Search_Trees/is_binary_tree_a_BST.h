#ifndef ALGORITHM_ANALYSIS_IS_BINARY_TREE_A_BST_H
#define ALGORITHM_ANALYSIS_IS_BINARY_TREE_A_BST_H
// 15.1 Test if a binary tree satisfies the BST property

#include <limits>
#include <memory>

#include "Binary_tree_prototype.h"

using std::numeric_limits;
using std::unique_ptr;

bool AreKeysInRange(const unique_ptr<BinaryTreeNode<int>>& tree,
                    int low_range, int high_range) {
    if (tree == nullptr) {
        return true;
    //} else if (tree->data < low_range || tree->data > high_range) {
    } else if ( !(low_range <= tree->data && tree->data <= high_range) ) {
        return false;
    }

    return AreKeysInRange(tree->left, low_range, tree->data) &&
           AreKeysInRange(tree->right, tree->data, high_range);
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
    return AreKeysInRange(tree, numeric_limits<int>::min(),
                          numeric_limits<int>::max());
}

#endif //ALGORITHM_ANALYSIS_IS_BINARY_TREE_A_BST_H
