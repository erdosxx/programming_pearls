#ifndef ALGORITHM_ANALYSIS_UNIQUE_BINARY_TREES_ALL_H
#define ALGORITHM_ANALYSIS_UNIQUE_BINARY_TREES_ALL_H
// 16.8 Generate binary trees

#include <algorithm>
#include <vector>

#include "Binary_tree_prototype.h"

using std::make_unique;
using std::vector;

unique_ptr<BinaryTreeNode<int>> Clone(const unique_ptr<BinaryTreeNode<int>>&);

// @include
vector<unique_ptr<BinaryTreeNode<int>>> GenerateAllBinaryTrees(
        int num_nodes) {
    vector<unique_ptr<BinaryTreeNode<int>>> result;
    if (num_nodes == 0) {  // Empty tree, add as an nullptr.
        result.emplace_back(nullptr);
    }

    for (int num_left_tree_nodes = 0; num_left_tree_nodes < num_nodes;
         ++num_left_tree_nodes) {
        int num_right_tree_nodes = num_nodes - 1 - num_left_tree_nodes;
        auto left_subtrees = GenerateAllBinaryTrees(num_left_tree_nodes);
        auto right_subtrees = GenerateAllBinaryTrees(num_right_tree_nodes);

        // Generates all combinations of left_subtrees and right_subtrees.
        for (auto& left : left_subtrees) {
            for (auto& right : right_subtrees) {
                result.emplace_back(make_unique<BinaryTreeNode<int>>(
                        BinaryTreeNode<int>{0, Clone(left), Clone(right)}));
            }
        }
    }
    return result;
}

unique_ptr<BinaryTreeNode<int>> Clone(
        const unique_ptr<BinaryTreeNode<int>>& tree) {
    return tree ? make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{
            0, Clone(tree->left), Clone(tree->right)})
                : nullptr;
}
// @exclude


#endif //ALGORITHM_ANALYSIS_UNIQUE_BINARY_TREES_ALL_H
