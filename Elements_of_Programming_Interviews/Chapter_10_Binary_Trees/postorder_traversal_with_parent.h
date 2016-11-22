#ifndef ALGORITHM_ANALYSIS_POSTORDER_TRAVERSAL_WITH_PARENT_H
#define ALGORITHM_ANALYSIS_POSTORDER_TRAVERSAL_WITH_PARENT_H
// 10.11.1 Variant Implement an inorder traversal with O(1) space

#include <memory>
#include <vector>

#include "Binary_tree_with_parent_prototype.h"

using std::unique_ptr;
using std::vector;

namespace with_parent {

using btree_with_parent::BinaryTreeNode;

    vector<int> PostorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
        BinaryTreeNode<int> *prev = nullptr;
        BinaryTreeNode<int> *curr = tree.get();
        vector<int> result;

        while (curr != nullptr) {
            BinaryTreeNode<int> *next;

            if (curr->parent == prev) {
                // We came down to curr from prev.
                if (curr->left != nullptr) {  // Keep going left.
                    next = curr->left.get();
                } else {
                    // Done with left, so go right if right is not empty.
                    // Otherwise, go up.
                    next = (curr->right != nullptr) ? curr->right.get() : curr->parent;
                }
            } else if (curr->left.get() == prev) {
                // We came up to curr from its left child.
                result.emplace_back(prev->data);
                // Done with left, so go right if right is not empty. Otherwise, go up.
                next = (curr->right != nullptr) ? curr->right.get() : curr->parent;
            } else {  // Done with both children, so move up.
                result.emplace_back(prev->data);
                next = curr->parent;
            }

            prev = curr;
            curr = next;
        }

        // for root
        result.emplace_back(prev->data);

        return result;
    }
}


#endif //ALGORITHM_ANALYSIS_POSTORDER_TRAVERSAL_WITH_PARENT_H
