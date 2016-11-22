#ifndef ALGORITHM_ANALYSIS_BINARY_TREE_PREORDER_TRAVERSAL_ITERATIVE_H
#define ALGORITHM_ANALYSIS_BINARY_TREE_PREORDER_TRAVERSAL_ITERATIVE_H
// 10.8 Implement a preorder traversal without recursion

#include <algorithm>
#include <memory>
#include <stack>
#include <vector>

#include "Binary_tree_prototype.h"

using std::stack;
using std::unique_ptr;
using std::vector;

vector<int> PreorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
    stack<BinaryTreeNode<int>*> path;
    path.emplace(tree.get());
    vector<int> result;

    while (!path.empty()) {
        auto curr = path.top();
        path.pop();
        if (curr != nullptr) {
            result.emplace_back(curr->data);
            path.emplace(curr->right.get());
            path.emplace(curr->left.get());
        }
    }
    return result;
}

#endif //ALGORITHM_ANALYSIS_BINARY_TREE_PREORDER_TRAVERSAL_ITERATIVE_H
