#ifndef ALGORITHM_ANALYSIS_SUM_ROOT_TO_LEAF_BINARY_TREE_H
#define ALGORITHM_ANALYSIS_SUM_ROOT_TO_LEAF_BINARY_TREE_H

#include <algorithm>
#include <memory>

#include "Binary_tree_prototype.h"

using std::unique_ptr;
using btree::BinaryTreeNode;


int SumRootToLeafHelper(const unique_ptr<BinaryTreeNode<int>>&, int);

// @include
int SumRootToLeaf(const unique_ptr<BinaryTreeNode<int>>& tree) {
    return SumRootToLeafHelper(tree, 0);
}

int SumRootToLeafHelper(const unique_ptr<BinaryTreeNode<int>>& tree,
                        int partial_path_sum) {
    if (tree == nullptr) {
        return 0;
    }

    partial_path_sum = partial_path_sum * 2 + tree->data;
    if (tree->left == nullptr && tree->right == nullptr) {  // Leaf.
        return partial_path_sum;
    }
    // Non-leaf.
    return SumRootToLeafHelper(tree->left, partial_path_sum) +
           SumRootToLeafHelper(tree->right, partial_path_sum);
}
// @exclude

#endif //ALGORITHM_ANALYSIS_SUM_ROOT_TO_LEAF_BINARY_TREE_H
