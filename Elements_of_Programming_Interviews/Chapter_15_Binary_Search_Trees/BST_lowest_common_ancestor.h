#ifndef ALGORITHM_ANALYSIS_BST_LOWEST_COMMON_ANCESTOR_H
#define ALGORITHM_ANALYSIS_BST_LOWEST_COMMON_ANCESTOR_H
// 15.4 Compute the LCA in a BST

#include <memory>

#include "BST_prototype.h"

using std::unique_ptr;

// @include
// Input nodes are not nonempty and the key at node1 is less than or equal to that
// at node2.
BSTNode<int>* FindLCA(const unique_ptr<BSTNode<int>>& tree,
                      const unique_ptr<BSTNode<int>>& small,
                      const unique_ptr<BSTNode<int>>& big) {
    BSTNode<int>* p = tree.get();

    // Stop when small->data <= p->data <= big->data
    // while (p->data < small->data || p->data > big->data) {
    while (!(small->data <= p->data && p->data <= big->data)) {
        // Keep searching since p is outside of [s, b].
        while (p->data < small->data) {
            p = p->right.get();  // LCA must be in p's right child.
        }

        while (p->data > big->data) {
            p = p->left.get();  // LCA must be in p's left child.
        }
    }

    return p;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_BST_LOWEST_COMMON_ANCESTOR_H
