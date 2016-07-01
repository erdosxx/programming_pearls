#ifndef ALGORITHM_ANALYSIS_BINARY_TREE_PROTOTYPE_H
#define ALGORITHM_ANALYSIS_BINARY_TREE_PROTOTYPE_H

#include <memory>

using std::unique_ptr;

namespace btree {
// @include
    template<typename T>
    struct BinaryTreeNode {
        T data;
        unique_ptr<BinaryTreeNode<T>> left, right;
    };
// @exclude
}

#endif //ALGORITHM_ANALYSIS_BINARY_TREE_PROTOTYPE_H
