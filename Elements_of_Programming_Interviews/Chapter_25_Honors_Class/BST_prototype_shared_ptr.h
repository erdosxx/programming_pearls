#ifndef ALGORITHM_ANALYSIS_BST_PROTOTYPE_SHARED_PTR_H
#define ALGORITHM_ANALYSIS_BST_PROTOTYPE_SHARED_PTR_H

#include <memory>

using std::shared_ptr;

// @include
template <typename T>
struct BSTNode {
    T data;
    shared_ptr<BSTNode<T>> left, right;
};
// @exclude

#endif //ALGORITHM_ANALYSIS_BST_PROTOTYPE_SHARED_PTR_H
