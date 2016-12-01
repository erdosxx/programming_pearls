#ifndef ALGORITHM_ANALYSIS_CONVERT_RIGHT_CHILD_TO_NEXT_SIBLING_H
#define ALGORITHM_ANALYSIS_CONVERT_RIGHT_CHILD_TO_NEXT_SIBLING_H
// 10.16.1 Variant Compute the right sibling tree

#include <vector>
#include <queue>
#include <memory>

using std::vector;
using std::queue;
using std::shared_ptr;

namespace right_child {
    template<typename T>
    struct BinaryTreeNode {
        T data;
        shared_ptr<BinaryTreeNode<T>> left, right;
    };

    void convert_right_child_to_next_sibling(shared_ptr<BinaryTreeNode<int>>* tree_ptr) {
        queue<shared_ptr<BinaryTreeNode<int>>*> processing_queue;
        processing_queue.emplace(tree_ptr);

        int num_nodes_to_process_at_current_level = processing_queue.size();
        vector<vector<shared_ptr<BinaryTreeNode<int>>*>> final_result;
        vector<shared_ptr<BinaryTreeNode<int>>*> one_level_result;

        while (!processing_queue.empty()) {
            auto curr = processing_queue.front();
            processing_queue.pop();
            --num_nodes_to_process_at_current_level;

            if (curr) {
                one_level_result.emplace_back(curr);
                // Defer the null checks to the null test above.
                if ((*curr)->left) {
                    processing_queue.emplace(&(*curr)->left);
                }
                if ((*curr)->right) {
                    processing_queue.emplace(&(*curr)->right);
                }
            }

            // Done with the nodes at the current depth.
            if (num_nodes_to_process_at_current_level == 0) {
                num_nodes_to_process_at_current_level = processing_queue.size();
                if (!one_level_result.empty()) {
                    final_result.emplace_back(move(one_level_result));
                }
            }
        }

        for (int i = final_result.size() -1; i >= 0; --i) {
            for (int j = 1; j < final_result[i].size(); ++j) {
                (*final_result[i][j-1])->right = (*final_result[i][j]);
            }
            (*final_result[i][final_result[i].size()-1])->right = nullptr;
        }
    }
}

#endif //ALGORITHM_ANALYSIS_CONVERT_RIGHT_CHILD_TO_NEXT_SIBLING_H
