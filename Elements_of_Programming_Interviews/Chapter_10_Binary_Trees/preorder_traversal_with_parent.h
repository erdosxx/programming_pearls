#ifndef ALGORITHM_ANALYSIS_PREORDER_TRAVERSAL_WITH_PARENT_H
#define ALGORITHM_ANALYSIS_PREORDER_TRAVERSAL_WITH_PARENT_H
// 10.11.1 Variant Implement an inorder traversal with O(1) space

#include <memory>
#include <vector>

#include "Binary_tree_with_parent_prototype.h"

using std::unique_ptr;
using std::vector;

namespace with_parent {
    using btree_with_parent::BinaryTreeNode;

    vector<int> PreorderTraversal(const unique_ptr<BinaryTreeNode<int>> &tree) {
        BinaryTreeNode<int>* prev = nullptr;
        BinaryTreeNode<int>* curr = tree.get();
        vector<int> result;

        while (curr != nullptr) {
            BinaryTreeNode<int>* next;

            if (curr->parent == prev) {
                // We came down to curr from prev.
                result.emplace_back(curr->data);

                if (curr->left != nullptr) {  // Keep going left.
                    next = curr->left.get();
                } else {
                    // Done with left, so go right if right is not empty.
                    // Otherwise, go up.
                    next = (curr->right != nullptr) ? curr->right.get() : curr->parent;
                }
            } else if (curr->left.get() == prev) {
                // We came up to curr from its left child.
                // Done with left, so go right if right is not empty. Otherwise, go up.
                next = (curr->right != nullptr) ? curr->right.get() : curr->parent;
            } else {  // Done with both children, so move up.
                next = curr->parent;
            }

            prev = curr;
            curr = next;
        }
        return result;
    }
}

#endif //ALGORITHM_ANALYSIS_PREORDER_TRAVERSAL_WITH_PARENT_H
