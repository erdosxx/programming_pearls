#ifndef ALGORITHM_ANALYSIS_BST_SORTED_ORDER_H
#define ALGORITHM_ANALYSIS_BST_SORTED_ORDER_H
//10.7 Implement an inorder traversal without recursion

#include <memory>
#include <stack>
#include <vector>

#include "BST_prototype.h"

using std::stack;
using std::unique_ptr;
using std::vector;
using node_ptr= unique_ptr<BSTNode<int>>;

// @include
vector<int> BSTInSortedOrder(const unique_ptr<BSTNode<int>>& tree) {
    stack<const BSTNode<int> *> s;
    // pointer to const BSTNode<int>
    const auto * curr = tree.get();
    vector<int> result;

    while (!s.empty() || curr) {
        if (curr) {
            s.push(curr);
            // Going left.
            curr = curr->left.get();
        } else {
            // Going up.
            curr = s.top();
            s.pop();
            result.emplace_back(curr->data);
            // Going right.
            curr = curr->right.get();
        }
    }
    return result;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_BST_SORTED_ORDER_H
