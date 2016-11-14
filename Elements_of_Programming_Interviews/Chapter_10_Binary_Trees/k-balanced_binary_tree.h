#ifndef ALGORITHM_ANALYSIS_K_BALANCED_BINARY_TREE_H
#define ALGORITHM_ANALYSIS_K_BALANCED_BINARY_TREE_H
// 10.1.2 Variant Test if a binary tree is height-balanced

#include <cstdlib>
#include <memory>
#include <utility>

#include "Binary_tree_prototype.h"

using std::unique_ptr;
using btree::BinaryTreeNode;

struct TreeWithSize;
TreeWithSize FindKUnbalancedNodeHelper(const unique_ptr<BinaryTreeNode<int>>&,
                                       int);

struct TreeWithSize {
    BinaryTreeNode<int>* root;
    int size;
};

BinaryTreeNode<int>* FindKUnbalancedNode(
        const unique_ptr<BinaryTreeNode<int>>& tree, int k) {
    return FindKUnbalancedNodeHelper(tree, k).root;
}

// If there is any k-unbalanced node in tree, the root field is a k-unbalanced
// node; otherwise, it is null.  If the root is not null, the size field is
// the
// number of nodes in tree.
TreeWithSize FindKUnbalancedNodeHelper(
        const unique_ptr<BinaryTreeNode<int>>& tree, int k) {
    if (tree == nullptr) {
        return {nullptr, 0};  // Base case.
    }

    // Early return if left subtree is not k-balanced.
    TreeWithSize left_result = FindKUnbalancedNodeHelper(tree->left, k);
    if (left_result.root != nullptr) {
        return {left_result.root, 0};
    }
    // Early return if right subtree is not k-balanced.
    TreeWithSize right_result = FindKUnbalancedNodeHelper(tree->right, k);
    if (right_result.root != nullptr) {
        return {right_result.root, 0};
    }

    int node_num = left_result.size + right_result.size + 1;
    if (abs(left_result.size - right_result.size) > k) {
        // tree is not k-balanced but its children are k-balanced.
        return {tree.get(), node_num};
    }
    return {nullptr, node_num};
}
// @exclude

#endif //ALGORITHM_ANALYSIS_K_BALANCED_BINARY_TREE_H
