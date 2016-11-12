#ifndef ALGORITHM_ANALYSIS_OVERLAPPING_LISTS_H
#define ALGORITHM_ANALYSIS_OVERLAPPING_LISTS_H
// 8.5 Test for overlapping lists - lists may have cycles

#include <memory>

#include "Checking_cycle.h"
#include "Linked_list_prototype.h"
#include "Overlapping_lists_no_cycle.h"

using std::make_shared;
using std::shared_ptr;

int Distance(shared_ptr<ListNode<int>> a, shared_ptr<ListNode<int>> b);

// @include
shared_ptr<ListNode<int>> OverlappingLists(shared_ptr<ListNode<int>> L1,
                                           shared_ptr<ListNode<int>> L2) {
    // Store the start of cycle if any.
    auto root1 = cycle::HasCycle(L1);
    auto root2 = cycle::HasCycle(L2);

    if (!root1 && !root2) {
        // Both lists don't have cycles.
        return OverlappingNoCycleLists(L1, L2);
    } else if ((root1 && !root2) || (!root1 && root2)) {
        // One list has cycle, and one list has no cycle.
        return nullptr;
    }
    // Both lists have cycles.
    auto temp = root2;
    do {
        temp = temp->next;
    } while (temp != root1 && temp != root2);

    // L1 and L2 do not end in the same cycle.
    if (temp != root1) {
        return nullptr;  // Cycles are disjoint.
    }

    // L1 and L2 end in the same cycle, locate the overlapping node if they
    // first overlap before cycle starts.
    int stem1_length = Distance(L1, root1);
    int stem2_length = Distance(L2, root2);
    AdvanceListByK(abs(stem1_length - stem2_length),
                   stem1_length > stem2_length ? &L1 : &L2);
    while (L1 != L2 && L1 != root1 && L2 != root2) {
        L1 = L1->next, L2 = L2->next;
    }

    // If L1 == L2 before reaching root1, it means the overlap first occurs
    // before the cycle starts; otherwise, the first overlapping node is not
    // unique, so we can return any node on the cycle.
    return L1 == L2 ? L1 : root1;
}

// Calculates the distance between a and b.
int Distance(shared_ptr<ListNode<int>> a, shared_ptr<ListNode<int>> b) {
    int dis = 0;
    while (a != b) {
        a = a->next;
        ++dis;
    }
    return dis;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_OVERLAPPING_LISTS_H
