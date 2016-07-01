#ifndef ALGORITHM_ANALYSIS_POPULATING_NEXT_RIGHT_POINTERS_ANY_BINARY_TREE_H
#define ALGORITHM_ANALYSIS_POPULATING_NEXT_RIGHT_POINTERS_ANY_BINARY_TREE_H

#include <memory>

using std::make_unique;
using std::unique_ptr;

namespace right_any_btree {
    template<typename T>
    struct BinaryTreeNode {
        T data;
        unique_ptr<BinaryTreeNode<T>> left, right;
        BinaryTreeNode<T> *next;  // populate this field.
    };

// @include
    void populate_next_pointer(BinaryTreeNode<int> *node) {
        while (node) {
            BinaryTreeNode<int> *next_level_start = nullptr;
            BinaryTreeNode<int> *prev = nullptr;

            while (node) {
                if (!next_level_start) {
                    next_level_start = node->left ? node->left.get() : node->right.get();
                }

                if (node->left) {
                    if (prev) {
                        prev->next = node->left.get();
                    }
                    prev = node->left.get();
                }

                if (node->right) {
                    if (prev) {
                        prev->next = node->right.get();
                    }
                    prev = node->right.get();
                }

                node = node->next;
            }
            node = next_level_start;
        }
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_POPULATING_NEXT_RIGHT_POINTERS_ANY_BINARY_TREE_H
