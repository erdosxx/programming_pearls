#ifndef ALGORITHM_ANALYSIS_BINARY_TREE_WITH_PARENT_PROTOTYPE_H
#define ALGORITHM_ANALYSIS_BINARY_TREE_WITH_PARENT_PROTOTYPE_H

#include <memory>

using std::unique_ptr;

namespace btree_with_parent {
// @include
    template<typename T>
    struct BinaryTreeNode {
        T data;
        unique_ptr<BinaryTreeNode<T>> left, right;
        BinaryTreeNode<T> *parent;
    };
// @exclude
}

#endif //ALGORITHM_ANALYSIS_BINARY_TREE_WITH_PARENT_PROTOTYPE_H
