#include <gtest/gtest.h>
#include <random>
#include "Merge_sorted_lists.h"
#include "reverse_linked_list_from_s_to_f.h"
#include "Checking_cycle.h"
#include "Checking_cycle_alternative.h"
#include "Overlapping_lists_no_cycle.h"
#include "Overlapping_lists.h"
#include "Deletion_list.h"
#include "Remove_kth_last_list.h"
#include "remove-duplicates-sorted-list.h"
#include "cyclic-right-shift.h"
#include "Even_odd_merge_linked_list.h"
#include "Palindrome_linked_list.h"
#include "list-pivoting.h"
#include "add-two-number-list.h"

using even_odd::EvenOddMerge;
using even_odd::EvenOddMergeOriginal;
using std::default_random_engine;
using std::random_device;
using std::uniform_int_distribution;

class LinkedLists_Fixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    LinkedLists_Fixture() : Test() {

    }

    virtual ~LinkedLists_Fixture() {
    }
};

TEST_F(LinkedLists_Fixture, merge_sorted_lists_Function) {
    shared_ptr<ListNode<int>> a3 = make_shared<ListNode<int>>(ListNode<int>{5, nullptr});
    shared_ptr<ListNode<int>> a2 = make_shared<ListNode<int>>(ListNode<int>{3, a3});
    shared_ptr<ListNode<int>> a1 = make_shared<ListNode<int>>(ListNode<int>{1, a2});

    shared_ptr<ListNode<int>> b3 = make_shared<ListNode<int>>(ListNode<int>{6, nullptr});
    shared_ptr<ListNode<int>> b2 = make_shared<ListNode<int>>(ListNode<int>{4, b3});
    shared_ptr<ListNode<int>> b1 = make_shared<ListNode<int>>(ListNode<int>{2, b2});

    shared_ptr<ListNode<int>> L3 = nullptr;

    L3 = MergeTwoSortedLists(a1, b1);

    ASSERT_TRUE(L3->data == 1 && L3->next->data == 2 && L3->next->next->data == 3 &&
    L3->next->next->next->data == 4 && L3->next->next->next->next->data == 5 &&
    L3->next->next->next->next->next->data == 6);
}

TEST_F(LinkedLists_Fixture, reverse_linked_list_Function) {
    shared_ptr<ListNode<int>> L = nullptr;
    auto result = ReverseSublist(L, 0, 0);
    ASSERT_TRUE(result == nullptr);

    L = make_shared<ListNode<int>>(ListNode<int>{1, nullptr});
    result = ReverseSublist(L, 0, 0);
    ASSERT_TRUE(result == L);

    L = make_shared<ListNode<int>>(ListNode<int>{
            1, make_shared<ListNode<int>>(ListNode<int>{
                    2, make_shared<ListNode<int>>(ListNode<int>{3, nullptr})})});
    result = ReverseSublist(L, 0, 1);
    ASSERT_TRUE(result->data == 2 && result->next->data == 1 &&
           result->next->next->data == 3);

    L = make_shared<ListNode<int>>(ListNode<int>{
            1, make_shared<ListNode<int>>(ListNode<int>{
                    2, make_shared<ListNode<int>>(ListNode<int>{3, nullptr})})});
    result = ReverseSublist(L, 0, 2);
    ASSERT_TRUE(result->data == 3 && result->next->data == 2 &&
           result->next->next->data == 1);

    L = make_shared<ListNode<int>>(ListNode<int>{
            1, make_shared<ListNode<int>>(ListNode<int>{
                    2, make_shared<ListNode<int>>(ListNode<int>{3, nullptr})})});
    result = ReverseSublist(L, 3, 3);
    ASSERT_TRUE(result->data == 1 && result->next->data == 2 &&
           result->next->next->data == 3 && !result->next->next->next);

    result = ReverseSublist(L, 2, 3);
    ASSERT_TRUE(result->data == 1 && result->next->data == 3 &&
           result->next->next->data == 2 && !result->next->next->next);

    L = make_shared<ListNode<int>>(ListNode<int>{
            3, make_shared<ListNode<int>>(ListNode<int>{5, nullptr})});
    result = ReverseSublist(L, 1, 2);
    ASSERT_TRUE(result->data == 5 && result->next->data == 3 && !result->next->next);
}

TEST_F(LinkedLists_Fixture, cycle_Function) {
    shared_ptr<ListNode<int>> L3 =
            make_shared<ListNode<int>>(ListNode<int>{3, nullptr});
    shared_ptr<ListNode<int>> L2 =
            make_shared<ListNode<int>>(ListNode<int>{2, L3});
    shared_ptr<ListNode<int>> L1 =
            make_shared<ListNode<int>>(ListNode<int>{1, L2});

    // should output "L1 does not have cycle."
    ASSERT_TRUE(cycle::HasCycle(L1) == nullptr);
    ASSERT_TRUE(cycle_alt::HasCycle(L1) == nullptr);

    // make it a cycle
    L3->next = L2;
    // should output "L1 has cycle, located at node has value 2"
    ASSERT_TRUE(cycle::HasCycle(L1) != nullptr);
    ASSERT_TRUE(cycle_alt::HasCycle(L1) != nullptr);
    ASSERT_EQ(2, cycle::HasCycle(L1)->data);
    ASSERT_EQ(2, cycle_alt::HasCycle(L1)->data);
}

TEST_F(LinkedLists_Fixture, Overlapping_lists_Function) {
    shared_ptr<ListNode<int>> L1, L2;
    // L1: 1->2->3->4->5->6-
    //              ^  ^    |
    //              |  |____|
    // L2: 7->8-----
    L1 = make_shared<ListNode<int>>(ListNode<int>{
            1, make_shared<ListNode<int>>(ListNode<int>{
                    2, make_shared<ListNode<int>>(ListNode<int>{
                            3, make_shared<ListNode<int>>(ListNode<int>{
                                    4, make_shared<ListNode<int>>(ListNode<int>{
                                            5, make_shared<ListNode<int>>(
                                                    ListNode<int>{6, nullptr})})})})})});
    L1->next->next->next->next->next->next = L1->next->next->next->next;

    L2 = make_shared<ListNode<int>>(ListNode<int>{
            7, make_shared<ListNode<int>>(ListNode<int>{8, nullptr})});
    L2->next->next = L1->next->next->next;
    ASSERT_EQ(4, OverlappingLists(L1, L2)->data);

    // L1: 1->2->3->4->5->6-
    //           ^     ^    |
    //           |     |____|
    // L2: 7->8---
    L2->next->next = L1->next->next;
    ASSERT_EQ(3, OverlappingLists(L1, L2)->data);

    //shared_ptr<ListNode<int>> L1, L2;

    // L1: 1->2->3->null
    L1 = make_shared<ListNode<int>>(ListNode<int>{
            1, make_shared<ListNode<int>>(ListNode<int>{
                    2, make_shared<ListNode<int>>(ListNode<int>{3, nullptr})})});
    L2 = L1->next->next;
    ASSERT_EQ(3, OverlappingLists(L1, L2)->data);
    // L2: 4->5->null
    L2 = make_shared<ListNode<int>>(ListNode<int>{
            4, make_shared<ListNode<int>>(ListNode<int>{5, nullptr})});
    ASSERT_TRUE(OverlappingLists(L1, L2) == nullptr);
    L1->next->next->next = L1;
    ASSERT_TRUE(OverlappingLists(L1, L2) == nullptr);
    L2->next->next = L2;
    ASSERT_TRUE(OverlappingLists(L1, L2) == nullptr);
    L2->next->next = L1;
    ASSERT_TRUE(OverlappingLists(L1, L2) != nullptr);
}

TEST_F(LinkedLists_Fixture, deletion_list_Function) {
    shared_ptr<ListNode<int>> L;
    L = make_shared<ListNode<int>>(ListNode<int>{
            1, make_shared<ListNode<int>>(ListNode<int>{
                    2, make_shared<ListNode<int>>(ListNode<int>{3, nullptr})})});
    DeletionFromList(L);
    ASSERT_TRUE(L->data == 2 && L->next->data == 3);
}

TEST_F(LinkedLists_Fixture, Remove_kth_last_list_Function) {
    shared_ptr<ListNode<int>> L;
    L = make_shared<ListNode<int>>(ListNode<int>{
            1, make_shared<ListNode<int>>(ListNode<int>{
                    2, make_shared<ListNode<int>>(ListNode<int>{3, nullptr})})});
    L = RemoveKthLast(L, 2);
    ASSERT_TRUE(L->data == 1 && L->next->data == 3 && L->next->next == nullptr);
    L = RemoveKthLast(L, 2);
    ASSERT_TRUE(L->data == 3 && L->next == nullptr);
    L = RemoveKthLast(L, 1);
    ASSERT_TRUE(L == nullptr);
}

TEST_F(LinkedLists_Fixture, remove_duplicates_sorted_list_Function) {
    shared_ptr<ListNode<int>> L = nullptr;
    auto result = RemoveDuplicates(L);
    ASSERT_TRUE(result == nullptr);

    L = make_shared<ListNode<int>>(ListNode<int>{123, nullptr});
    result = RemoveDuplicates(L);
    ASSERT_TRUE(result == L);

    L->next = make_shared<ListNode<int>>(ListNode<int>{123, nullptr});
    result = RemoveDuplicates(L);
    ASSERT_TRUE(result->next == nullptr);

    // Creating an invalid input, 123 -> 124 -> 123, algo will not detect dups!
    L->next = make_shared<ListNode<int>>(ListNode<int>{124, nullptr});
    L->next->next = make_shared<ListNode<int>>(ListNode<int>{123, nullptr});
    result = RemoveDuplicates(L);
    ASSERT_TRUE(result->data == 123 && result->next->data == 124 &&
           result->next->next->data == 123);

    L = make_shared<ListNode<int>>(ListNode<int>{
            2, make_shared<ListNode<int>>(ListNode<int>{
                    2, make_shared<ListNode<int>>(ListNode<int>{
                            2, make_shared<ListNode<int>>(ListNode<int>{
                                    2, make_shared<ListNode<int>>(
                                            ListNode<int>{2, nullptr})})})})});
    shared_ptr<ListNode<int>> pre = nullptr;
    result = RemoveDuplicates(L);

    int count = 0;
    // check difference between previous and next data.
    while (result) {
        ++count;
        if (pre) {
            ASSERT_TRUE(pre->data != result->data);
        }
        pre = result;
        result = result->next;
    }
    ASSERT_TRUE(count == 1);
}

TEST_F(LinkedLists_Fixture, cyclic_right_shift_Function) {
    shared_ptr<ListNode<int>> L;
    L = make_shared<ListNode<int>>(ListNode<int>{1, nullptr});
    auto result = CyclicallyRightShiftList(L, 2);
    ASSERT_TRUE(result == L);

    L->next = make_shared<ListNode<int>>(ListNode<int>{2, nullptr});
    result = CyclicallyRightShiftList(L, 2);
    ASSERT_TRUE(result == L);

    result = CyclicallyRightShiftList(L, 3);
    ASSERT_TRUE(result->next == L);

    L = make_shared<ListNode<int>>(ListNode<int>{
            1, make_shared<ListNode<int>>(ListNode<int>{
                    2, make_shared<ListNode<int>>(ListNode<int>{3, nullptr})})});
    result = CyclicallyRightShiftList(L, 2);
    ASSERT_TRUE(result->data == 2 && result->next->data == 3 &&
           result->next->next->data == 1 && !result->next->next->next);
}

TEST_F(LinkedLists_Fixture, even_odd_merge_Function) {
    auto L = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
    auto result = EvenOddMerge(L);
    ASSERT_TRUE(result->data == 0);

    L->next = make_shared<ListNode<int>>(ListNode<int>{1, nullptr});
    result = EvenOddMerge(L);
    ASSERT_TRUE(result->data == 0);
    ASSERT_TRUE(result->next->data == 1);

    L->next->next = make_shared<ListNode<int>>(ListNode<int>{2, nullptr});
    result = EvenOddMerge(L);
    ASSERT_TRUE(result->data == 0);
    ASSERT_TRUE(result->next->data == 2);
    ASSERT_TRUE(result->next->next->data == 1);

    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 1000);
    int n = dis(gen);
    shared_ptr<ListNode<int>> head = even_odd::CreateList(n);
    ASSERT_TRUE(even_odd::CheckAnswer(EvenOddMerge(head), n));
    shared_ptr<ListNode<int>> another_head = even_odd::CreateList(n);
    ASSERT_TRUE(even_odd::CheckAnswer(EvenOddMergeOriginal(another_head), n));
}

TEST_F(LinkedLists_Fixture, Palindrome_Funtion) {
    ASSERT_TRUE(IsLinkedListAPalindrome(nullptr) == true);
    ASSERT_TRUE(IsLinkedListAPalindrome(
            make_shared<ListNode<int>>(ListNode<int>{1, nullptr})) == true);
    ASSERT_TRUE(IsLinkedListAPalindrome(make_shared<ListNode<int>>(ListNode<int>{
            1, make_shared<ListNode<int>>(ListNode<int>{1, nullptr})})) ==
           true);
    ASSERT_TRUE(IsLinkedListAPalindrome(make_shared<ListNode<int>>(ListNode<int>{
            1, make_shared<ListNode<int>>(ListNode<int>{2, nullptr})})) ==
           false);
    ASSERT_TRUE(IsLinkedListAPalindrome(make_shared<ListNode<int>>(ListNode<int>{
            1, make_shared<ListNode<int>>(ListNode<int>{
                    3, make_shared<ListNode<int>>(ListNode<int>{
                            2, make_shared<ListNode<int>>(
                                    ListNode<int>{1, nullptr})})})})) == false);

    shared_ptr<ListNode<int>> head = nullptr;
    // A link list is a palindrome.
    for (int i = 6; i >= 1; --i) {
        shared_ptr<ListNode<int>> curr =
                make_shared<ListNode<int>>(ListNode<int>{1, head});
        head = curr;
    }
    ASSERT_TRUE(IsLinkedListAPalindrome(head) == true);

    // Still a palindrome linked list.
    head = shared_ptr<ListNode<int>>(nullptr);
    for (int i = 5; i >= 1; --i) {
        shared_ptr<ListNode<int>> curr =
                make_shared<ListNode<int>>(ListNode<int>{1, head});
        head = curr;
    }
    head->next->next->data = 3;
    ASSERT_TRUE(IsLinkedListAPalindrome(head) == true);

    // Not a palindrome linked list.
    head = nullptr;
    for (int i = 5; i >= 1; --i) {
        shared_ptr<ListNode<int>> curr =
                make_shared<ListNode<int>>(ListNode<int>{i, head});
        head = curr;
    }
    ASSERT_TRUE(IsLinkedListAPalindrome(head) == false);
    ASSERT_TRUE(IsLinkedListAPalindrome(nullptr) == true);
}

TEST_F(LinkedLists_Fixture, list_pivoting_Function) {
    shared_ptr<ListNode<int>> L =
            make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
    auto result = ListPivoting(L, 0);
    ASSERT_TRUE(result == L);
    result = ListPivoting(L, 1);
    ASSERT_TRUE(result == L);
    result = ListPivoting(L, -1);
    ASSERT_TRUE(result == L);

    L = make_shared<ListNode<int>>(ListNode<int>{
            2, make_shared<ListNode<int>>(ListNode<int>{0, nullptr})});
    result = ListPivoting(L, -1);
    ASSERT_TRUE(result->data == 2 && result->next->data == 0);

    L = make_shared<ListNode<int>>(ListNode<int>{
            2, make_shared<ListNode<int>>(ListNode<int>{0, nullptr})});
    result = ListPivoting(L, 1);
    ASSERT_TRUE(result->data == 0 && result->next->data == 2);

    L = make_shared<ListNode<int>>(ListNode<int>{
            2, make_shared<ListNode<int>>(ListNode<int>{
                    0, make_shared<ListNode<int>>(ListNode<int>{-2, nullptr})})});
    result = ListPivoting(L, 1);
    ASSERT_TRUE(result->data == 0 && result->next->data == -2 &&
           result->next->next->data == 2);

    L = make_shared<ListNode<int>>(ListNode<int>{
            1, make_shared<ListNode<int>>(ListNode<int>{
                    4, make_shared<ListNode<int>>(ListNode<int>{
                            3, make_shared<ListNode<int>>(ListNode<int>{
                                    2, make_shared<ListNode<int>>(
                                            ListNode<int>{5, nullptr})})})})});
    int x = 4;
    result = ListPivoting(L, x);
    bool before_x = true;

    while (result) {
        if (result->data >= x) {
            before_x = false;
        }
        if (before_x) {
            ASSERT_TRUE(result->data < x);
        } else {
            ASSERT_TRUE(result->data >= x);
        }
        result = result->next;
    }
}

TEST_F(LinkedLists_Fixture, add_two_number_Function) {
    shared_ptr<ListNode<int>> L;
    L = make_shared<ListNode<int>>(ListNode<int>{
            2, make_shared<ListNode<int>>(ListNode<int>{
                    4, make_shared<ListNode<int>>(ListNode<int>{3, nullptr})})});
    shared_ptr<ListNode<int>> R;
    R = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
    auto S = AddTwoNumbers(L, R);
    ASSERT_TRUE(S->data == 2 && S->next->data == 4 && S->next->next->data == 3);

    L = make_shared<ListNode<int>>(ListNode<int>{
            3, make_shared<ListNode<int>>(ListNode<int>{
                    4, make_shared<ListNode<int>>(ListNode<int>{2, nullptr})})});
    R = make_shared<ListNode<int>>(ListNode<int>{
            7, make_shared<ListNode<int>>(ListNode<int>{
                    5, make_shared<ListNode<int>>(ListNode<int>{7, nullptr})})});
    S = AddTwoNumbers(L, R);
    ASSERT_TRUE(S->data == 0 && S->next->data == 0 && S->next->next->data == 0 &&
           S->next->next->next->data == 1);

    L = make_shared<ListNode<int>>(ListNode<int>{1, nullptr});
    R = make_shared<ListNode<int>>(ListNode<int>{1, nullptr});
    S = AddTwoNumbers(L, R);
    ASSERT_TRUE(S->data == 2 && S->next == nullptr);

    L = make_shared<ListNode<int>>(ListNode<int>{5, nullptr});
    R = make_shared<ListNode<int>>(ListNode<int>{5, nullptr});
    S = AddTwoNumbers(L, R);
    ASSERT_TRUE(S->data == 0 && S->next->data == 1 && S->next->next == nullptr);

    L = make_shared<ListNode<int>>(ListNode<int>{
            2, make_shared<ListNode<int>>(ListNode<int>{
                    4, make_shared<ListNode<int>>(ListNode<int>{3, nullptr})})});
    R = make_shared<ListNode<int>>(ListNode<int>{
            5, make_shared<ListNode<int>>(ListNode<int>{
                    6, make_shared<ListNode<int>>(ListNode<int>{7, nullptr})})});
    S = AddTwoNumbers(L, R);
    ASSERT_TRUE(S->data == 7 && S->next->data == 0 && S->next->next->data == 1 &&
           S->next->next->next->data == 1);

    L = make_shared<ListNode<int>>(ListNode<int>{
            9, make_shared<ListNode<int>>(ListNode<int>{9, nullptr})});
    R = make_shared<ListNode<int>>(ListNode<int>{9, nullptr});
    S = AddTwoNumbers(L, R);
    ASSERT_TRUE(S->data == 8 && S->next->data == 0 && S->next->next->data == 1);
}
