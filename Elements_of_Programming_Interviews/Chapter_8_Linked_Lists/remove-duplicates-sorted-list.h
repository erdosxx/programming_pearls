#ifndef ALGORITHM_ANALYSIS_REMOVE_DUPLICATES_SORTED_LIST_H
#define ALGORITHM_ANALYSIS_REMOVE_DUPLICATES_SORTED_LIST_H

#include <memory>

#include "Linked_list_prototype.h"

using std::make_shared;
using std::shared_ptr;

// @include
shared_ptr<ListNode<int>> RemoveDuplicates(
        const shared_ptr<ListNode<int>>& L) {
    auto iter = L;
    while (iter) {
        // Uses next_distinct to find the next distinct value.
        auto next_distinct = iter->next;
        while (next_distinct && next_distinct->data == iter->data) {
            next_distinct = next_distinct->next;
        }
        iter->next = next_distinct;
        iter = next_distinct;
    }
    return L;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_REMOVE_DUPLICATES_SORTED_LIST_H
