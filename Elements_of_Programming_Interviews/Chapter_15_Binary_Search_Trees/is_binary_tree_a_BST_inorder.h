#ifndef ALGORITHM_ANALYSIS_IS_BINARY_TREE_A_BST_INORDER_H
#define ALGORITHM_ANALYSIS_IS_BINARY_TREE_A_BST_INORDER_H

#include <memory>
#include <limits>

using std::unique_ptr;

namespace inorder {
    bool IsBinaryTreeBST_Helper (const unique_ptr<BinaryTreeNode<int>>& tree, int* prev_data, bool* is_true_before) {
        if(! *is_true_before ) {
            return *is_true_before;
        }

        if (tree == nullptr) {
            return *is_true_before;
        }

        IsBinaryTreeBST_Helper(tree->left, prev_data, is_true_before);

        const BinaryTreeNode<int>& node = *tree.get();

        if (*prev_data > node.data) {
            *is_true_before = false;
            return *is_true_before;
        }

        *prev_data = node.data;

        IsBinaryTreeBST_Helper(tree->right, prev_data, is_true_before);

        return *is_true_before;
    }

    bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>> &tree) {
        int prev_data = numeric_limits<int>::min();
        bool is_true_before = true;

        return IsBinaryTreeBST_Helper(tree, &prev_data, &is_true_before);
    }
}
#endif //ALGORITHM_ANALYSIS_IS_BINARY_TREE_A_BST_INORDER_H
