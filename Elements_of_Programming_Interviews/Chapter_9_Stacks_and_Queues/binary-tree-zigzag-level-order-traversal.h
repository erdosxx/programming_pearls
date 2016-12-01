#ifndef ALGORITHM_ANALYSIS_BINARY_TREE_ZIGZAG_LEVEL_ORDER_TRAVERSAL_H
#define ALGORITHM_ANALYSIS_BINARY_TREE_ZIGZAG_LEVEL_ORDER_TRAVERSAL_H
// 9.7.1 Variant Compute binary tree nodes in order of increasing depth

#include <memory>
#include <stack>
#include <vector>

#include "Binary_tree_prototype.h"

using std::stack;
using std::unique_ptr;
using std::vector;

vector<vector<int>> binary_tree_zigzag_level_order(
        const unique_ptr<BinaryTreeNode<int>> &root) {
    vector<vector<int>> final_result;
    vector<int> current_level_result;

    stack<BinaryTreeNode<int>*> curr_level;
    stack<BinaryTreeNode<int>*> next_level;
    bool left_to_right = true;
    curr_level.emplace(root.get());

    while (!curr_level.empty()) {
        auto curr_node = curr_level.top();
        curr_level.pop();

        if (curr_node) {
            //cout << curr_node->data << " ";
            current_level_result.emplace_back(curr_node->data);

            if (left_to_right) {
                next_level.emplace(curr_node->left.get());
                next_level.emplace(curr_node->right.get());
            } else {
                next_level.emplace(curr_node->right.get());
                next_level.emplace(curr_node->left.get());
            }
        }

        if (curr_level.empty() && !next_level.empty()) {
            if (!current_level_result.empty()) {
                final_result.emplace_back(move(current_level_result));
            }

            // Toggles left_to_right.
            left_to_right = !left_to_right;
            // following is equivalent of swap(curr_level, next_level);
            curr_level.swap(next_level);
        }
    }

    return final_result;
}


#endif //ALGORITHM_ANALYSIS_BINARY_TREE_ZIGZAG_LEVEL_ORDER_TRAVERSAL_H
