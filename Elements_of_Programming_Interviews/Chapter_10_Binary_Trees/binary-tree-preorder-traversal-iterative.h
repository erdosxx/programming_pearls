#ifndef ALGORITHM_ANALYSIS_BINARY_TREE_PREORDER_TRAVERSAL_ITERATIVE_H
#define ALGORITHM_ANALYSIS_BINARY_TREE_PREORDER_TRAVERSAL_ITERATIVE_H

#include <algorithm>
#include <memory>
#include <stack>
#include <vector>

#include "Binary_tree_prototype.h"
#include "Binary_tree_utils.h"

using std::stack;
using std::unique_ptr;
using std::vector;

// @include
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
// @exclude

#endif //ALGORITHM_ANALYSIS_BINARY_TREE_PREORDER_TRAVERSAL_ITERATIVE_H
