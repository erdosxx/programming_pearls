#ifndef ALGORITHM_ANALYSIS_K_TH_NODE_BINARY_TREE_H
#define ALGORITHM_ANALYSIS_K_TH_NODE_BINARY_TREE_H
// 10.9 Compute the kth node in an inorder traversal

#include <memory>

using std::make_unique;
using std::unique_ptr;

namespace kthNode {
    template<typename T>
    struct BinaryTreeNode {
        T data;
        unique_ptr<BinaryTreeNode<T>> left, right;
        int size;
    };

// @include
    const BinaryTreeNode<int> *FindKthNodeBinaryTree(
            const unique_ptr<BinaryTreeNode<int>> &tree, int k) {
        const auto *iter = tree.get();

        while (iter != nullptr) {
            int left_size = iter->left ? iter->left->size : 0;

            if (left_size + 1 < k) {  // k-th node must be in right subtree of iter.
                k -= (left_size + 1);
                iter = iter->right.get();
            } else if (left_size == k - 1) {  // k-th is iter itself.
                return iter;
            } else {  // k-th node must be in left subtree of iter.
                iter = iter->left.get();
            }
        }
        // If k is between 1 and the tree size, this line is unreachable.
        return nullptr;
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_K_TH_NODE_BINARY_TREE_H
