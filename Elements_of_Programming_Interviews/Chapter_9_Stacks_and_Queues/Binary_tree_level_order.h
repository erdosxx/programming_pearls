#ifndef ALGORITHM_ANALYSIS_BINARY_TREE_LEVEL_ORDER_H
#define ALGORITHM_ANALYSIS_BINARY_TREE_LEVEL_ORDER_H
// 9.7 Compute binary tree nodes in order of increasing depth

#include <queue>
#include <memory>
#include <vector>

#include "Binary_tree_prototype.h"

using std::move;
using std::queue;
using std::unique_ptr;
using std::vector;

// @include
vector<vector<int>> BinaryTreeDepthOrder(
        const unique_ptr<BinaryTreeNode<int>>& tree) {
    queue<BinaryTreeNode<int>*> processing_queue;
    processing_queue.emplace(tree.get()); // get: Returns the stored pointer

    int num_nodes_to_process_at_current_level = processing_queue.size();
    vector<vector<int>> final_result;
    vector<int> one_level_result;

    while (!processing_queue.empty()) {
        auto curr = processing_queue.front();
        processing_queue.pop();
        --num_nodes_to_process_at_current_level;

        if (curr) {
            one_level_result.emplace_back(curr->data);
            // Defer the null checks to the null test above.
            processing_queue.emplace(curr->left.get());
            processing_queue.emplace(curr->right.get());
        }

        // Done with the nodes at the current depth.
        if (num_nodes_to_process_at_current_level == 0) {
            num_nodes_to_process_at_current_level = processing_queue.size();
            if (!one_level_result.empty()) {
                final_result.emplace_back(move(one_level_result));
            }
        }
    }
    return final_result;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_BINARY_TREE_LEVEL_ORDER_H
