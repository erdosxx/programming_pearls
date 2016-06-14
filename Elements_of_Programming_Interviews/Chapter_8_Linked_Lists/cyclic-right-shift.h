#ifndef ALGORITHM_ANALYSIS_CYCLIC_RIGHT_SHIFT_H
#define ALGORITHM_ANALYSIS_CYCLIC_RIGHT_SHIFT_H

#include <memory>

#include "Linked_list_prototype.h"

using std::make_shared;
using std::shared_ptr;

// @include
shared_ptr<ListNode<int>> CyclicallyRightShiftList(
        shared_ptr<ListNode<int>> L, int k) {
    if (L == nullptr) {
        return L;
    }

    // Computes the length of L and the tail.
    auto tail = L;
    int n = 1;
    while (tail->next) {
        ++n;
        tail = tail->next;
    }

    k %= n;
    if (k == 0) {
        return L;
    }

    tail->next = L;  // Makes a cycle by connecting the tail to the head.
    int steps_to_new_head = n - k;
    auto new_tail = tail;
    while (steps_to_new_head--) {
        new_tail = new_tail->next;
    }

    auto new_head = new_tail->next;
    new_tail->next = nullptr;
    return new_head;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_CYCLIC_RIGHT_SHIFT_H
