#ifndef ALGORITHM_ANALYSIS_PATH_SUM_BINARY_TREE_H
#define ALGORITHM_ANALYSIS_PATH_SUM_BINARY_TREE_H

#include <algorithm>
#include <memory>

#include "Binary_tree_prototype.h"

using std::make_unique;
using std::unique_ptr;
using btree::BinaryTreeNode;

bool HasPathSumHelper(const unique_ptr<BinaryTreeNode<int>>&, int, int);

// @include
bool HasPathSum(const unique_ptr<BinaryTreeNode<int>>& tree, int target_sum) {
    return HasPathSumHelper(tree, 0, target_sum);
}

bool HasPathSumHelper(const unique_ptr<BinaryTreeNode<int>>& node,
                      int partial_path_sum, int target_sum) {
    if (node == nullptr) {
        return false;
    }
    partial_path_sum += node->data;
    if (node->left == nullptr && node->right == nullptr) {  // Leaf.
        return partial_path_sum == target_sum;
    }
// Non-leaf.
    return HasPathSumHelper(node->left, partial_path_sum, target_sum) ||
           HasPathSumHelper(node->right, partial_path_sum, target_sum);
}
// @exclude

#endif //ALGORITHM_ANALYSIS_PATH_SUM_BINARY_TREE_H
