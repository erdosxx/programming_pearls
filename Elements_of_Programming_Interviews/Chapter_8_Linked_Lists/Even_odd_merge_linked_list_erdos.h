#ifndef ALGORITHM_ANALYSIS_EVEN_ODD_MERGE_LINKED_LIST_ERDOS_H
#define ALGORITHM_ANALYSIS_EVEN_ODD_MERGE_LINKED_LIST_ERDOS_H
// 8.10 Implement even-odd merge

#include <memory>
#include "Linked_list_prototype.h"

using std::shared_ptr;
using n_ptr_type = shared_ptr<ListNode<int>>;


n_ptr_type EvenOddMerge_erdos(const n_ptr_type &L) {
    if (!L) {
        return L;
    }

    n_ptr_type curr_even = L;
    n_ptr_type odd_tail = L->next;

    if (!odd_tail || !odd_tail->next) { // only one or two elements
        return L;
    }

    n_ptr_type next_even = odd_tail->next;

    while (next_even && odd_tail) {
        odd_tail->next = next_even->next;
        next_even->next = curr_even->next;
        curr_even->next = next_even;

        curr_even = curr_even->next;
        odd_tail = odd_tail->next;
        if (odd_tail) {
            next_even = odd_tail->next;
        }
    }

    return L;
}

#endif //ALGORITHM_ANALYSIS_EVEN_ODD_MERGE_LINKED_LIST_ERDOS_H
