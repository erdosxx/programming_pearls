#ifndef ALGORITHM_ANALYSIS_BST_LOWEST_COMMON_ANCESTOR_H
#define ALGORITHM_ANALYSIS_BST_LOWEST_COMMON_ANCESTOR_H

#include <memory>

#include "BST_prototype.h"

using std::make_unique;
using std::unique_ptr;

// @include
// Input nodes are not nonempty and the key at s is less than or equal to that
// at b.
BSTNode<int>* FindLCA(const unique_ptr<BSTNode<int>>& tree,
                      const unique_ptr<BSTNode<int>>& s,
                      const unique_ptr<BSTNode<int>>& b) {
    auto* p = tree.get();
    while (p->data < s->data || p->data > b->data) { // TODO: Is this while can be ommitted?
        // Keep searching since p is outside of [s, b].
        while (p->data < s->data) {
            p = p->right.get();  // LCA must be in p's right child.
        }
        while (p->data > b->data) {
            p = p->left.get();  // LCA must be in p's left child.
        }
    }
    // Now, s->data <= p->data && p->data <= b->data.
    return p;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_BST_LOWEST_COMMON_ANCESTOR_H
