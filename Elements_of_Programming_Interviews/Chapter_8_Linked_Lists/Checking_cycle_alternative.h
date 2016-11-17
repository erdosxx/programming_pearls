#ifndef ALGORITHM_ANALYSIS_CHECKING_CYCLE_ALTERNATIVE_H
#define ALGORITHM_ANALYSIS_CHECKING_CYCLE_ALTERNATIVE_H
// 8.3 Test for cyclicity

#include <memory>

#include "Linked_list_prototype.h"

using std::make_shared;

// See TAOCP II p.7 problem 6.
namespace cycle_alt {
// @include
    shared_ptr<ListNode<int>> HasCycle(const shared_ptr<ListNode<int>> &head) {
        shared_ptr<ListNode<int>> fast = head;
        shared_ptr<ListNode<int>> slow = head;

        while (fast && fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {  // There is a cycle.
                // Tries to find the start of the cycle.
                slow = head;
                // Both pointers advance at the same time.
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;  // slow is the start of cycle.
            }
        }
        return nullptr;  // No cycle.
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_CHECKING_CYCLE_ALTERNATIVE_H
