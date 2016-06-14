#ifndef ALGORITHM_ANALYSIS_LINKED_LIST_PROTOTYPE_H
#define ALGORITHM_ANALYSIS_LINKED_LIST_PROTOTYPE_H

#include <memory>

using std::shared_ptr;

// @include
template <typename T>
struct ListNode {
    T data;
    shared_ptr<ListNode<T>> next;
};
// @exclude

#endif //ALGORITHM_ANALYSIS_LINKED_LIST_PROTOTYPE_H
