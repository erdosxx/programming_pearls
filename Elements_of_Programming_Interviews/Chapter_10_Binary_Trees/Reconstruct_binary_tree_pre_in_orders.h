#ifndef ALGORITHM_ANALYSIS_RECONSTRUCT_BINARY_TREE_PRE_IN_ORDERS_H
#define ALGORITHM_ANALYSIS_RECONSTRUCT_BINARY_TREE_PRE_IN_ORDERS_H

#include <algorithm>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Binary_tree_prototype.h"
#include "Binary_tree_utils.h"

using std::make_unique;
using std::unique_ptr;
using std::unordered_map;
using std::vector;
using btree::BinaryTreeNode;

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorderHelper(
        const vector<int>&, size_t, size_t, size_t, size_t,
        const unordered_map<int, size_t>&);

// @include
unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
        const vector<int>& preorder, const vector<int>& inorder) {
    unordered_map<int, size_t> node_to_inorder_idx;

    for (size_t i = 0; i < inorder.size(); ++i) {
        node_to_inorder_idx.emplace(inorder[i], i);
    }

    return BinaryTreeFromPreorderInorderHelper(
            preorder, 0, preorder.size(), 0, inorder.size(), node_to_inorder_idx);
}

// Builds the subtree with preorder[preorder_start : preorder_end - 1] and
// inorder[inorder_start : inorder_end - 1].
unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorderHelper(
        const vector<int>& preorder, size_t preorder_start, size_t preorder_end,
        size_t inorder_start, size_t inorder_end,
        const unordered_map<int, size_t>& node_to_inorder_idx) {
    if (preorder_end <= preorder_start || inorder_end <= inorder_start) {
        return nullptr;
    }

    size_t root_inorder_idx = node_to_inorder_idx.at(preorder[preorder_start]);
    size_t left_subtree_size = root_inorder_idx - inorder_start;

    return make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{
            preorder[preorder_start],
            // Recursively builds the left subtree.
            BinaryTreeFromPreorderInorderHelper(
                    preorder, preorder_start + 1,
                    preorder_start + 1 + left_subtree_size, inorder_start,
                    root_inorder_idx, node_to_inorder_idx),
            // Recursively builds the right subtree.
            BinaryTreeFromPreorderInorderHelper(
                    preorder, preorder_start + 1 + left_subtree_size, preorder_end,
                    root_inorder_idx + 1, inorder_end, node_to_inorder_idx)});
}
// @exclude

#endif //ALGORITHM_ANALYSIS_RECONSTRUCT_BINARY_TREE_PRE_IN_ORDERS_H
