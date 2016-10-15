#ifndef ALGORITHM_ANALYSIS_BINARY_TREE_POSTORDER_TRAVERSAL_ITERATIVE_H
#define ALGORITHM_ANALYSIS_BINARY_TREE_POSTORDER_TRAVERSAL_ITERATIVE_H

#include <algorithm>
#include <memory>
#include <stack>
#include <vector>

#include "Binary_tree_prototype.h"
#include "Binary_tree_utils.h"

using std::make_unique;
using std::stack;
using std::unique_ptr;
using std::vector;

// @include
// We use stack and previous node pointer to simulate postorder traversal.
vector<int> PostorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
    if (tree == nullptr) {  // Empty tree.
        return {};
    }

    stack<BinaryTreeNode<int>*> path;
    BinaryTreeNode<int>* prev = nullptr;
    path.emplace(tree.get());
    vector<int> postorder_sequence;

    while (!path.empty()) {
        auto curr = path.top();

        if (prev == nullptr || prev->left.get() == curr ||
            prev->right.get() == curr) { // We came down to curr from prev.
            if (curr->left != nullptr) {  // Traverse left.
                path.emplace(curr->left.get());
            } else if (curr->right != nullptr) {  // Traverse right.
                path.emplace(curr->right.get());
            } else {  // Leaf node, so visit current node.
                postorder_sequence.emplace_back(curr->data);
                path.pop();
            }
        } else if (curr->left.get() == prev) { // Done with left, so now traverse right.
            if (curr->right != nullptr) {
                path.emplace(curr->right.get());
            } else {  // No right child, so visit curr.
                postorder_sequence.emplace_back(curr->data);
                path.pop();
            }
        } else { // Finished traversing left and right, so visit curr.
            postorder_sequence.emplace_back(curr->data);
            path.pop();
        }
        prev = curr;
    }
    return postorder_sequence;
}
// @exclude


#endif //ALGORITHM_ANALYSIS_BINARY_TREE_POSTORDER_TRAVERSAL_ITERATIVE_H
