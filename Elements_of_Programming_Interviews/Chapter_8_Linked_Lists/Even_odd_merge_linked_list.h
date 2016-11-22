#ifndef ALGORITHM_ANALYSIS_EVEN_ODD_MERGE_LINKED_LIST_H
#define ALGORITHM_ANALYSIS_EVEN_ODD_MERGE_LINKED_LIST_H
// 8.10 Implement even-odd merge

#include <array>
#include <memory>

#include "Linked_list_prototype.h"

using std::array;
using std::make_shared;
using std::shared_ptr;

namespace even_odd {
    shared_ptr<ListNode<int>> EvenOddMergeOriginal(
            const shared_ptr<ListNode<int>> &L) {
        if (!L) {
            return L;
        }

        auto even_list_head = L;
        auto even_list_iter = even_list_head;

        shared_ptr<ListNode<int>> predecessor_even_list_iter = nullptr;
        auto odd_list_head = L->next;
        auto odd_list_iter = odd_list_head;

        while (even_list_iter && odd_list_iter) {
            even_list_iter->next = odd_list_iter->next;
            predecessor_even_list_iter = even_list_iter;
            even_list_iter = even_list_iter->next;

            if (even_list_iter) {
                odd_list_iter->next = even_list_iter->next;
                odd_list_iter = odd_list_iter->next;
            }
        }

        // Appends odd list to the tail of even list.
        if (even_list_iter) {
            even_list_iter->next = odd_list_head;
        } else {
            predecessor_even_list_iter->next = odd_list_head;
        }
        return even_list_head;
    }

    shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>> &L) {
        if (L == nullptr) {
            return L;
        }

        auto even_dummy_head =
                make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
        auto odd_dummy_head =
                make_shared<ListNode<int>>(ListNode<int>{0, nullptr});

        array<shared_ptr<ListNode<int>>, 2> tails = {even_dummy_head,
                                                     odd_dummy_head};
        int turn = 0;
        for (auto iter = L; iter; iter = iter->next) {
            tails[turn]->next = iter;
            tails[turn] = tails[turn]->next;
            turn ^= 1;  // Alternate between even and odd.
        }

        tails[1]->next = nullptr;
        tails[0]->next = odd_dummy_head->next;
        return even_dummy_head->next;
    }

}

#endif //ALGORITHM_ANALYSIS_EVEN_ODD_MERGE_LINKED_LIST_H
