#ifndef ALGORITHM_ANALYSIS_POPULATING_NEXT_RIGHT_POINTERS_H
#define ALGORITHM_ANALYSIS_POPULATING_NEXT_RIGHT_POINTERS_H
// 10.16 Compute the right sibling tree

#include <memory>

using std::make_unique;
using std::unique_ptr;

namespace right_sibling {
    template<typename T>
    struct BinaryTreeNode {
        T data;
        unique_ptr<BinaryTreeNode<T>> left, right;
        BinaryTreeNode<T> *next;  // Populates this field.
    };

    void PopulateLowerLevelNextField(BinaryTreeNode<int> *);

    void ConstructRightSibling(BinaryTreeNode<int> *tree) {
        auto left_start = tree;

        while (left_start && left_start->left) {
            PopulateLowerLevelNextField(left_start);
            left_start = left_start->left.get();
        }
    }

    void PopulateLowerLevelNextField(BinaryTreeNode<int> *start_node) {
        auto iter = start_node;

        while (iter) {
            // Populate left child's next field.
            iter->left->next = iter->right.get();
            // Populate right child's next field if iter is not the last node of this
            // level.
            if (iter->next) {
                iter->right->next = iter->next->left.get();
            }
            iter = iter->next;
        }
    }
}

#endif //ALGORITHM_ANALYSIS_POPULATING_NEXT_RIGHT_POINTERS_H
