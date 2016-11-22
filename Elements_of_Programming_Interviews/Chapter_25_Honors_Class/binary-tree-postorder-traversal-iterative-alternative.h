#ifndef ALGORITHM_ANALYSIS_BINARY_TREE_POSTORDER_TRAVERSAL_ITERATIVE_ALTERNATIVE_H
#define ALGORITHM_ANALYSIS_BINARY_TREE_POSTORDER_TRAVERSAL_ITERATIVE_ALTERNATIVE_H
// 25.13 Implement a postorder traversal without recursion

#include <algorithm>
#include <memory>
#include <stack>
#include <vector>

#include "Binary_tree_prototype.h"

using std::stack;
using std::unique_ptr;
using std::vector;

namespace alt {
    vector<int> InvertedPreorderTraversal(const unique_ptr<BinaryTreeNode<int>>&);

    vector<int> PostorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
        vector<int> sequence = InvertedPreorderTraversal(tree);
        reverse(sequence.begin(), sequence.end());
        return sequence;
    }

    // See 10.8 page 145
    vector<int> InvertedPreorderTraversal(
            const unique_ptr<BinaryTreeNode<int>>& tree) {
        stack<BinaryTreeNode<int> *> path;
        path.emplace(tree.get());
        vector<int> result;

        while (!path.empty()) {
            auto *curr = path.top();
            path.pop();

            if (curr != nullptr) {
                result.emplace_back(curr->data);
                path.emplace(curr->left.get());
                path.emplace(curr->right.get());
            }
        }
        return result;
    }
}

#endif //ALGORITHM_ANALYSIS_BINARY_TREE_POSTORDER_TRAVERSAL_ITERATIVE_ALTERNATIVE_H
