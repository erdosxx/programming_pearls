#ifndef ALGORITHM_ANALYSIS_BALANCED_BINARY_TREE_H
#define ALGORITHM_ANALYSIS_BALANCED_BINARY_TREE_H
//10.1 Test if a binary tree is height-balanced

#include <algorithm>
#include <memory>
#include <utility>

#include "Binary_tree_prototype.h"

using std::max;
using std::unique_ptr;
using btree::BinaryTreeNode;

struct BalancedStatusWithHeight {
    bool balanced;
    int height;
};

// First timestamp of the return timestamp indicates if tree is balanced, and if
// balanced the second timestamp of the return timestamp is the height of tree.
BalancedStatusWithHeight CheckBalanced(
        const unique_ptr<BinaryTreeNode<int>>& tree) {
    if (tree == nullptr) {
        return {true, -1};  // Base case.
    }

    auto left_result = CheckBalanced(tree->left);
    if (!left_result.balanced) {
        return {false, 0};  // Left subtree is not balanced.
    }

    auto right_result = CheckBalanced(tree->right);
    if (!right_result.balanced) {
        return {false, 0};  // Right subtree is not balanced.
    }

    bool is_balanced = abs(left_result.height - right_result.height) <= 1;
    int height = max(left_result.height, right_result.height) + 1;
    return {is_balanced, height};
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
    return CheckBalanced(tree).balanced;
}

#endif //ALGORITHM_ANALYSIS_BALANCED_BINARY_TREE_H
