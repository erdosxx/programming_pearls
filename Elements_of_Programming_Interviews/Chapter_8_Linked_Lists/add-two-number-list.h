#ifndef ALGORITHM_ANALYSIS_ADD_TWO_NUMBER_LIST_H
#define ALGORITHM_ANALYSIS_ADD_TWO_NUMBER_LIST_H
// 8.13 Add list-based integers

#include <memory>

#include "Linked_list_prototype.h"

using std::make_shared;
using std::shared_ptr;

// @include
shared_ptr<ListNode<int>> AddTwoNumbers(shared_ptr<ListNode<int>> L1,
                                        shared_ptr<ListNode<int>> L2) {
    shared_ptr<ListNode<int>> dummy_head(new ListNode<int>);
    auto place_iter = dummy_head;
    int carry = 0;
    while (L1 || L2) {
        int sum = carry;
        if (L1) {
            sum += L1->data;
            L1 = L1->next;
        }
        if (L2) {
            sum += L2->data;
            L2 = L2->next;
        }
        place_iter->next =
                make_shared<ListNode<int>>(ListNode<int>{sum % 10, nullptr});
        carry = sum / 10;
        place_iter = place_iter->next;
    }
    // carry cannot exceed 1, so we never need to add more than one node.
    if (carry) {
        place_iter->next =
                make_shared<ListNode<int>>(ListNode<int>{carry, nullptr});
    }
    return dummy_head->next;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_ADD_TWO_NUMBER_LIST_H
