#ifndef ALGORITHM_ANALYSIS_CHECKING_CYCLE_H
#define ALGORITHM_ANALYSIS_CHECKING_CYCLE_H

#include <memory>

#include "Linked_list_prototype.h"

// See TAOCP II p.7 problem 6.
namespace cycle {

// @include
    shared_ptr<ListNode<int>> HasCycle(const shared_ptr<ListNode<int>> &head) {
        shared_ptr<ListNode<int>> fast = head;
        shared_ptr<ListNode<int>> slow = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                // There is a cycle, so now let's calculate the cycle length.
                int cycle_len = 0;
                do {
                    ++cycle_len;
                    fast = fast->next;
                } while (slow != fast);

                // Finds the start of the cycle.
                auto cycle_len_advanced_iter = head;
                while (cycle_len--) {
                    cycle_len_advanced_iter = cycle_len_advanced_iter->next;
                }

                auto iter = head;
                // Both iterators advance in tandem.
                while (iter != cycle_len_advanced_iter) {
                    iter = iter->next;
                    cycle_len_advanced_iter = cycle_len_advanced_iter->next;
                }
                return iter;  // iter is the start of cycle.
            }
        }
        return nullptr;  // No cycle.
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_CHECKING_CYCLE_H
