#ifndef ALGORITHM_ANALYSIS_DOUBLY_LINKED_LIST_PROTOTYPE_H
#define ALGORITHM_ANALYSIS_DOUBLY_LINKED_LIST_PROTOTYPE_H

#include <memory>

using std::shared_ptr;

namespace DL {
// @include
    template<typename T>
    struct ListNode {
        T data;
        shared_ptr<DL::ListNode<T>> prev, next;
    };
// @exclude
}

#endif //ALGORITHM_ANALYSIS_DOUBLY_LINKED_LIST_PROTOTYPE_H
