#ifndef ALGORITHM_ANALYSIS_BINARY_TREE_LEVEL_ORDER_BOTTOM_UP_H
#define ALGORITHM_ANALYSIS_BINARY_TREE_LEVEL_ORDER_BOTTOM_UP_H
// 9.7.2 Variant Compute binary tree nodes in order of increasing depth

#include <memory>
#include <queue>
#include <vector>

#include "Binary_tree_prototype.h"

using std::queue;
using std::unique_ptr;
using std::vector;

vector<vector<int>> bottom_up_level_order(
        const unique_ptr<BinaryTreeNode<int>>& root) {
    vector<vector<int>> final_result;
    vector<int> one_level_result;
    queue<BinaryTreeNode<int>*> curr_level;
    queue<BinaryTreeNode<int>*> next_level;
    curr_level.emplace(root.get());

    while (!curr_level.empty()) {
        auto curr_node = curr_level.front();
        curr_level.pop();

        if (curr_node) {
            one_level_result.emplace_back(curr_node->data);
            next_level.emplace(curr_node->left.get());
            next_level.emplace(curr_node->right.get());
        }

        if (curr_level.empty() && !one_level_result.empty()) {
            final_result.emplace_back(move(one_level_result));
            curr_level.swap(next_level);
        }
    }
    reverse(final_result.begin(), final_result.end());
    return final_result;
}

#endif //ALGORITHM_ANALYSIS_BINARY_TREE_LEVEL_ORDER_BOTTOM_UP_H
