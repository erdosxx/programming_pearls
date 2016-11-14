#ifndef ALGORITHM_ANALYSIS_K_BALANCED_BINARY_TREE_ERDOS_H
#define ALGORITHM_ANALYSIS_K_BALANCED_BINARY_TREE_ERDOS_H
// 10.1.2 Variant Test if a binary tree is height-balanced

#include <algorithm>
#include <cstdlib>
#include <memory>
#include "Binary_tree_prototype.h"

using std::max;
using std::unique_ptr;
using btree::BinaryTreeNode;
using uniq_node_ptr = unique_ptr<BinaryTreeNode<int>>;

enum {DONT_KNOW=0};

struct k_subtree_stat {
    int size;
    bool isBalanced;
};

k_subtree_stat k_balanced_subtree(const uniq_node_ptr& tree, const int& k, const uniq_node_ptr*& up_node) {
    if (up_node != nullptr) { // already have a solution, so do not need to proceed.
        return {DONT_KNOW, false};
    }

    if (tree == nullptr) {
        return {0, true};
    }

    k_subtree_stat left_result = k_balanced_subtree(tree->left, k, up_node);
    if (left_result.isBalanced == false) {
        return {DONT_KNOW, false};
    }

    k_subtree_stat right_result = k_balanced_subtree(tree->right, k, up_node);
    if (right_result.isBalanced == false) {
        return {DONT_KNOW, false};
    }

    int diff_size = abs(left_result.size - right_result.size);

    if (diff_size < k) {
        return {left_result.size + right_result.size +1, true};
    } else { // diff_bal >= k
        up_node = &tree;
        return {left_result.size + right_result.size +1, false};
    }
}

const uniq_node_ptr* upper_k_balanced_subtree(const uniq_node_ptr& tree, const int& k) {
    const uniq_node_ptr* upper_k_bal_node_ptr = nullptr;
    k_balanced_subtree(tree, k, upper_k_bal_node_ptr);

    return upper_k_bal_node_ptr;
}


#endif //ALGORITHM_ANALYSIS_K_BALANCED_BINARY_TREE_ERDOS_H
