#ifndef ALGORITHM_ANALYSIS_BST_PROTOTYPE_H
#define ALGORITHM_ANALYSIS_BST_PROTOTYPE_H

#include <memory>

using std::unique_ptr;

// @include
template <typename T>
struct BSTNode {
    T data;
    unique_ptr<BSTNode<T>> left, right;
};
// @exclude

#endif //ALGORITHM_ANALYSIS_BST_PROTOTYPE_H
