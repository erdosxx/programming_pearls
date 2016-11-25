#include <gtest/gtest.h>
#include <random>
#include <list>
#include <forward_list>
#include <iterator>
#include "linked_list_boot_camp.h"
#include "Merge_sorted_lists.h"
#include "Merge_sorted_doubly_linked_lists.h"
#include "reverse_linked_list_from_s_to_f.h"
#include "Reverse_linked_list_iterative.h"
#include "Reverse_linked_list_recursive.h"
#include "reverse-list-in-k-group.h"
#include "reverse-list-in-k-group-erdos.h"
#include "Checking_cycle.h"
#include "Checking_cycle_alternative.h"
#include "Overlapping_lists_no_cycle.h"
#include "Overlapping_lists.h"
#include "Deletion_list.h"
#include "Remove_kth_last_list.h"
#include "remove-duplicates-sorted-list.h"
#include "cyclic-right-shift.h"
#include "Even_odd_merge_linked_list.h"
#include "Even_odd_merge_linked_list_erdos.h"
#include "Palindrome_linked_list.h"
#include "list-pivoting.h"
#include "add-two-number-list.h"

using even_odd::EvenOddMerge;
using even_odd::EvenOddMergeOriginal;
using std::default_random_engine;
using std::random_device;
using std::uniform_int_distribution;
using std::list;
using std::forward_list;
using std::advance;
using std::next;
using std::prev;

class LinkedLists_Fixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    shared_ptr<ListNode<int>> p_8_10_CreateList(int n);
    bool p_8_10_CheckAnswer(const shared_ptr<ListNode<int>> &L, int n);

public:
    LinkedLists_Fixture() : Test() {

    }

    virtual ~LinkedLists_Fixture() {
    }
};

shared_ptr<ListNode<int>> LinkedLists_Fixture::p_8_10_CreateList(int n) {
    shared_ptr<ListNode<int>> head = nullptr;
    for (int i = n - 1; i >= 0; --i) {
        auto curr = make_shared<ListNode<int>>(ListNode<int>{i, nullptr});
        curr->next = head;
        head = curr;
    }
    return head;
}

bool LinkedLists_Fixture::p_8_10_CheckAnswer(const shared_ptr<ListNode<int>> &L, int n) {
    int x = 0;
    int count = 0;

    auto iter = L;
    while (iter) {
        ++count;
        if (x != iter->data)
            return false;
        x += 2;
        if (x >= n) {
            x = 1;
        }
        // cout << iter->data << endl;
        iter = iter->next;
    }
    return count == n;
}

TEST_F(LinkedLists_Fixture, linked_list_boot_camp) {
    shared_ptr<ListNode<int>> a3 = make_shared<ListNode<int>>(ListNode<int>{3, nullptr});
    shared_ptr<ListNode<int>> a2 = make_shared<ListNode<int>>(ListNode<int>{2, a3});
    shared_ptr<ListNode<int>> a1 = make_shared<ListNode<int>>(ListNode<int>{1, a2});

    shared_ptr<ListNode<int>> target_ptr = SearchList(a1, 2);
    ASSERT_EQ(target_ptr->data, 2);

    shared_ptr<ListNode<int>> new_node = make_shared<ListNode<int>>(ListNode<int>{10, nullptr});
    InsertAfter(a2, new_node);
    ASSERT_EQ(a2->next->data, 10);
    ASSERT_EQ(a2->next->next->data, 3);

    // Delete node
    shared_ptr<ListNode<int>> null_node = nullptr;
    DeleteAfter(null_node);
    ASSERT_TRUE(null_node == nullptr);

    DeleteAfter(a2);
    ASSERT_TRUE(a2->next->data == 3);
    DeleteAfter(a3);
    ASSERT_TRUE(a3->next == nullptr);
}

TEST_F(LinkedLists_Fixture, stl_library) {
    list<int> int_list{0,1,2,3,4,5};
    int_list.push_back(-1);
    ASSERT_EQ(*int_list.begin(), 0);

    // See C++PL, p.960
    // q = next(p) <=> q = p + 1
    list<int>::iterator list_iter = int_list.begin();
    list_iter = next(list_iter);
    ASSERT_EQ(*list_iter, 1);

    // q = next(p,n) <=>  q = p + n
    list_iter = next(list_iter, 2);
    ASSERT_EQ(*list_iter, 3);

    list_iter = int_list.begin();
    // advance(p,n) <=> p += n;
    advance(list_iter, 3);
    ASSERT_EQ(*list_iter, 3);

    // q = prev(p,n)  <= > q = p - n
    list_iter = prev(list_iter, 2);
    ASSERT_EQ(*list_iter, 1);

    list_iter = prev(list_iter);
    ASSERT_EQ(*list_iter, 0);

    // emplace_front, emplace_back
    int_list.emplace_front(-1);
    ASSERT_EQ(*(int_list.cbegin()), -1);
    int_list.emplace_back(6);
    ASSERT_EQ(*(prev(int_list.cend())), 6);

    // pop_front, pop_back
    int_list = {0,1,2,3,4,5};
    list_iter = int_list.begin();
    ASSERT_EQ(int_list.size(), 6);

    int_list.pop_front();
    list_iter = int_list.begin();
    // not work: list_iter = int_list.cbegin();
    ASSERT_EQ(int_list.size(), 5);
    ASSERT_EQ(*list_iter, 1);

    int_list.pop_back();
    ASSERT_EQ(int_list.size(), 4);
    list_iter = prev(int_list.end());
    ASSERT_EQ(*list_iter, 4);

    int_list={2,3,2,3,5};
    list_iter = int_list.begin();
    // lst.remove(v): remove all elements of lst with value v.
    int_list.remove(3);  // {2,2,5}
    ASSERT_EQ(int_list.size(), 3);
    ASSERT_EQ(*list_iter, 2);
    list_iter = next(list_iter);
    ASSERT_EQ(*list_iter, 2);
    list_iter = next(list_iter);
    ASSERT_EQ(*list_iter, 5);

    // lst.splice(p, lst2) :
    //   Insert the elements of list2 before p;
    //   lst2 becomes empty
    list<int> lst1 {1,2,3};
    list<int> lst2 {5,6,7};
    auto p = lst1.begin();
    p++; // p points to 2

    auto q = lst2.begin();
    q++; // q points to 6

    lst1.splice(p, lst2); // lst1 is now {1,5,6,7,2,3}; lst2 is now {}
    auto lst_iter = lst1.begin();
    ASSERT_EQ(*lst_iter, 1);
    lst_iter++;
    ASSERT_EQ(*lst_iter,5);
    lst_iter++;
    ASSERT_EQ(*lst_iter,6);
    lst_iter++;
    ASSERT_EQ(*lst_iter,7);
    lst_iter++;
    ASSERT_EQ(*lst_iter,2);
    lst_iter++;
    ASSERT_EQ(*lst_iter,3);

    ASSERT_EQ(lst2.size(), 0);

    // p still points to 2 and q still points to 6
    ASSERT_EQ(*p, 2);
    ASSERT_EQ(*q, 6);


    // lst.splice(p, lst2, p2) :
    //   Insert the element pointed to by p2 in lst2 before p;
    //   the element pointed to by p2 is removed from lst2
    list<int> lst1_1 {1,2,3};
    list<int> lst2_1 {5,6,7};
    auto p_1 = lst1_1.begin();
    p_1++; // p points to 2

    auto q_1 = lst2_1.begin();
    q_1++; // q points to 6

    lst1_1.splice(p_1, lst2_1, q_1); // {1,6,2,3}
    lst_iter = lst1_1.begin();

    ASSERT_EQ(*lst_iter, 1);
    lst_iter++;
    ASSERT_EQ(*lst_iter, 6);
    lst_iter++;
    ASSERT_EQ(*lst_iter, 2);
    lst_iter++;
    ASSERT_EQ(*lst_iter, 3);
    lst_iter++;
    ASSERT_EQ(lst1_1.size(), 4);
    ASSERT_EQ(lst2_1.size(), 2);

    // p still points to 2 and q still points to 6
    ASSERT_EQ(*p_1, 2);
    ASSERT_EQ(*q_1, 6);

    // lst.splice(p,lst2,b,e) :
    //   Insert the elements [b,e) from lst2 before p;
    //   the elements [b,e) are removed from lst2
    list<int> lst1_2 {1,2,3};
    list<int> lst2_2 {5,6,7,8};
    auto p_2 = lst1_2.begin();
    p_2++; // p points to 2

    auto q_2 = lst2_2.begin();
    q_2++; // q points to 6

    lst1_2.splice(p_2, lst2_2, q_2, next(q_2,2)); // {1,6,7,2,3}
    lst_iter = lst1_2.begin();

    ASSERT_EQ(*lst_iter, 1);
    lst_iter++;
    ASSERT_EQ(*lst_iter, 6);
    lst_iter++;
    ASSERT_EQ(*lst_iter, 7);
    lst_iter++;
    ASSERT_EQ(*lst_iter, 2);
    lst_iter++;
    ASSERT_EQ(*lst_iter, 3);
    lst_iter++;

    ASSERT_EQ(lst1_2.size(), 5);
    ASSERT_EQ(lst2_2.size(), 2);

    // p still points to 2 and q still points to 6
    ASSERT_EQ(*p_1, 2);
    ASSERT_EQ(*q_1, 6);

    // lst.unique(): remove adjacent duplicate elements of lst.
    int_list={2,2,5};
    int_list.unique(); // {2,5}
    ASSERT_EQ(int_list.size(), 2);

    // reverse:
    int_list={1,2,3};
    int_list.reverse(); // {3,2,1}
    // not work: reverse(int_list);
    list_iter = int_list.begin();
    ASSERT_EQ(*list_iter, 3);
    list_iter = next(list_iter);
    ASSERT_EQ(*list_iter, 2);
    list_iter = next(list_iter);
    ASSERT_EQ(*list_iter, 1);

    // sort
    int_list={3,2,5,4};
    int_list.sort(); // {2,3,4,5}
    list_iter = int_list.begin();
    ASSERT_EQ(*list_iter, 2);
    list_iter = next(list_iter);
    ASSERT_EQ(*list_iter, 3);
    list_iter = next(list_iter);
    ASSERT_EQ(*list_iter, 4);
    list_iter = next(list_iter);
    ASSERT_EQ(*list_iter, 5);

    ///// forward_list
    forward_list<int> fwd_lst {1,2,3};
    forward_list<int>::iterator fwd_iter = fwd_lst.begin();
    ASSERT_EQ(1, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(2, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(3, *fwd_iter);

    // advance, next
    fwd_iter = fwd_lst.begin();
    advance(fwd_iter,1);
    ASSERT_EQ(2, *fwd_iter);
    fwd_iter = next(fwd_iter);
    ASSERT_EQ(3, *fwd_iter);

    // push_front, emplace_front
    fwd_lst = {1,2,3};
    fwd_lst.push_front(0);
    fwd_iter = fwd_lst.begin();
    ASSERT_EQ(0, *fwd_iter);

    fwd_lst.emplace_front(-1);
    fwd_iter = fwd_lst.begin();
    ASSERT_EQ(-1, *fwd_iter);  // {-1,0,1,2,3}

    // pop_front
    fwd_lst.pop_front();
    fwd_iter = fwd_lst.begin();
    ASSERT_EQ(0, *fwd_iter);  // {0,1,2,3}

    // p2 = lst.insert_after(p,x) : Insert x after p; p2 points to the new element
    // p2 = lst.emplace_after(p,args) : Emplace element constructed from args after p;
    //                              p2 points to the new element
    fwd_lst = {0,1,2,3,4,5};
    fwd_iter = fwd_lst.begin();
    advance(fwd_iter,2);    // point to 2
    fwd_iter = fwd_lst.insert_after(fwd_iter, -2); // {0,1,2,-2,3,4,5}
    ASSERT_EQ(-2, *fwd_iter); // now point to new element -2
    fwd_iter = fwd_lst.begin();
    ASSERT_EQ(0, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(1, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(2, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(-2, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(3, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(4, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(5, *fwd_iter);
    fwd_iter++;

    fwd_lst = {0,1,2,3,4,5};
    fwd_iter = fwd_lst.begin();
    advance(fwd_iter,2);    // point to 2
    fwd_iter = fwd_lst.emplace_after(fwd_iter, -2); // {0,1,2,-2,3,4,5}
    ASSERT_EQ(-2, *fwd_iter); // now point to new element -2
    fwd_iter = fwd_lst.begin();
    ASSERT_EQ(0, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(1, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(2, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(-2, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(3, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(4, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(5, *fwd_iter);
    fwd_iter++;


    fwd_lst = {0,1};
    fwd_iter = fwd_lst.begin();
    fwd_iter++;
    fwd_lst.insert_after(fwd_iter, 2); //{0,1,2}

    fwd_iter = fwd_lst.begin();
    ASSERT_EQ(0, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(1, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(2, *fwd_iter);

    // p2 = lst.erase_after(p)
    // Erase the element after p;
    // p2 points to the element after p or lst.end()

    fwd_lst = {0,1,2,3};
    fwd_iter = fwd_lst.begin();
    fwd_iter++;  // point ot 1
    fwd_iter = fwd_lst.erase_after(fwd_iter); // {0,1,3}
    ASSERT_EQ(3, *fwd_iter); // point to 3
    fwd_iter = fwd_lst.begin();
    ASSERT_EQ(0, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(1, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(3, *fwd_iter);

    // lst.splice_after(p, lst2) : Splice in lst2 after p
    fwd_lst = {0,1,2};
    fwd_iter = fwd_lst.begin();
    fwd_iter++;  // point to 1
    forward_list<int> fwd_lst2 {10,11,12};
    fwd_lst.splice_after(fwd_iter, fwd_lst2); // {0,1,10,11,12,2}

    fwd_iter = fwd_lst.begin();
    ASSERT_EQ(0, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(1, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(10, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(11, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(12, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(2, *fwd_iter);

    // lst.splice_after(p, lst2, p2) : Splice in p2 after p; remove p2 from lst2
    fwd_lst = {0,1,2};
    fwd_iter = fwd_lst.begin();
    fwd_iter++;  // point to 1
    fwd_lst2 = {10,11,12};
    auto fwd_iter2 = fwd_lst2.begin();
    fwd_iter2++; // point to 11
    fwd_lst.splice_after(fwd_iter, fwd_lst2, fwd_iter2); // fwd_lst: {0,1,12,2}, fwd_lst2 = {10,11}

    fwd_iter = fwd_lst.begin();
    ASSERT_EQ(0, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(1, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(12, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(2, *fwd_iter);
    fwd_iter++;
    ASSERT_TRUE(fwd_iter==fwd_lst.end());

    fwd_iter2 = fwd_lst2.begin();
    ASSERT_EQ(10, *fwd_iter2);
    fwd_iter2++;
    ASSERT_EQ(11, *fwd_iter2);
    fwd_iter2++;
    ASSERT_TRUE(fwd_iter2==fwd_lst2.end());

     // lst.splice_after(p, lst2, b, e) : Splice in [b,e) after p; remove [b,e) from lst2
    fwd_lst = {0,1,2};
    fwd_iter = fwd_lst.begin();
    fwd_iter++;  // point to 1
    fwd_lst2 = {10,11,12,14};
    auto fwd_iterB = next(fwd_lst2.begin(),1); // point to 11
    auto fwd_iterE = next(fwd_lst2.begin(),3); // point to 14

    fwd_lst.splice_after(fwd_iter, fwd_lst2, fwd_iterB, fwd_iterE); // fwd_lst: {0,1,12,2}, fwd_lst2 = {10,11,14}

    fwd_iter = fwd_lst.begin();
    ASSERT_EQ(0, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(1, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(12, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(2, *fwd_iter);
    fwd_iter++;
    ASSERT_TRUE(fwd_iter==fwd_lst.end());

    fwd_iter2 = fwd_lst2.begin();
    ASSERT_EQ(10, *fwd_iter2);
    fwd_iter2++;
    ASSERT_EQ(11, *fwd_iter2);
    fwd_iter2++;
    ASSERT_EQ(14, *fwd_iter2);
    fwd_iter2++;
    ASSERT_TRUE(fwd_iter2==fwd_lst2.end());

    // reverse
    fwd_lst = {0,1,2};
    // not work: reverse(fwd_lst)
    fwd_lst.reverse(); // {2,1,0}
    fwd_iter = fwd_lst.begin();

    ASSERT_EQ(2, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(1, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(0, *fwd_iter);

    // sort
    fwd_lst = {2,1,0};
    fwd_lst.sort();  // {0,1,2}
    //not work: sort(fwd_lst);
    fwd_iter = fwd_lst.begin();

    ASSERT_EQ(0, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(1, *fwd_iter);
    fwd_iter++;
    ASSERT_EQ(2, *fwd_iter);
}

TEST_F(LinkedLists_Fixture, merge_sorted_lists_Function) {
    // 1 -> 3 -> 5
    shared_ptr<ListNode<int>> a3 = make_shared<ListNode<int>>(ListNode<int>{5, nullptr});
    shared_ptr<ListNode<int>> a2 = make_shared<ListNode<int>>(ListNode<int>{3, a3});
    shared_ptr<ListNode<int>> a1 = make_shared<ListNode<int>>(ListNode<int>{1, a2});

    // 2 -> 4 -> 6
    shared_ptr<ListNode<int>> b3 = make_shared<ListNode<int>>(ListNode<int>{6, nullptr});
    shared_ptr<ListNode<int>> b2 = make_shared<ListNode<int>>(ListNode<int>{4, b3});
    shared_ptr<ListNode<int>> b1 = make_shared<ListNode<int>>(ListNode<int>{2, b2});

    shared_ptr<ListNode<int>> L3 = nullptr;

    L3 = MergeTwoSortedLists(a1, b1);

    // L3 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6
    ASSERT_TRUE(L3->data == 1 && L3->next->data == 2 && L3->next->next->data == 3 &&
    L3->next->next->next->data == 4 && L3->next->next->next->next->data == 5 &&
    L3->next->next->next->next->next->data == 6);
}

TEST_F(LinkedLists_Fixture, merge_sorted_doubly_linked_lists) {
    // 1 <-> 3 <-> 5
    shared_ptr<DL::ListNode<int>> a3 (new DL::ListNode<int>{5, nullptr, nullptr});
    shared_ptr<DL::ListNode<int>> a2 (new DL::ListNode<int>{3, nullptr, a3});
    shared_ptr<DL::ListNode<int>> a1 (new DL::ListNode<int>{1, nullptr, a2});
    a2->prev = a1;
    a3->prev = a2;

    // 2 <-> 4 <-> 6
    shared_ptr<DL::ListNode<int>> b3 (new DL::ListNode<int>{6, nullptr, nullptr});
    shared_ptr<DL::ListNode<int>> b2 (new DL::ListNode<int>{4, nullptr, b3});
    shared_ptr<DL::ListNode<int>> b1 (new DL::ListNode<int>{2, nullptr, b2});
    b2->prev = b1;
    b3->prev = b2;

    shared_ptr<DL::ListNode<int>> L3 = nullptr;

    // L3 -> 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6
    L3 = MergeTwoSortedDoublyLists(a1, b1);
    ASSERT_TRUE(L3->data == 1 && L3->next->data == 2 && L3->next->next->data == 3 &&
                L3->next->next->next->data == 4 && L3->next->next->next->next->data == 5 &&
                L3->next->next->next->next->next->data == 6);
    //ASSERT_TRUE(b3->data == 6 && b3->prev->data == 5 && b3->prev->prev->data == 4 &&
                //b3->prev->prev->prev->data == 3 && b3->prev->prev->prev->prev->data == 2 &&
                //b3->prev->prev->prev->prev->prev->data == 1);
    ASSERT_EQ(6, b3->data);
    ASSERT_EQ(5, b3->prev->data);
    ASSERT_EQ(4, b3->prev->prev->data);
    ASSERT_EQ(3, b3->prev->prev->prev->data);
    ASSERT_EQ(2, b3->prev->prev->prev->prev->data);
    ASSERT_EQ(1, b3->prev->prev->prev->prev->prev->data);
}

TEST_F(LinkedLists_Fixture, reverse_linked_list_s_to_t_Function) {
    // input: nullptr
    // output: nullptr
    shared_ptr<ListNode<int>> L = nullptr;
    auto result = ReverseSublist(L, 1, 1);
    ASSERT_TRUE(result == nullptr);

    // input: 1
    // output: 1
    L = make_shared<ListNode<int>>(ListNode<int>{1, nullptr});
    result = ReverseSublist(L, 1, 1);
    ASSERT_TRUE(result == L);

    // input: 1 -> 2 -> 3
    // output: 2 -> 1 -> 3
    //L = make_shared<ListNode<int>>(ListNode<int>{
    //        1, make_shared<ListNode<int>>(ListNode<int>{
    //                2, make_shared<ListNode<int>>(ListNode<int>{3, nullptr})})});
    shared_ptr<ListNode<int>> next_ptr2 = make_shared<ListNode<int>>(ListNode<int> {3, nullptr});
    shared_ptr<ListNode<int>> next_ptr = make_shared<ListNode<int>>(ListNode<int> {2, next_ptr2});
    L = make_shared<ListNode<int>>(ListNode<int>{1, next_ptr});

    result = ReverseSublist(L, 1, 2);
    ASSERT_TRUE(result->data == 2 && result->next->data == 1 &&
           result->next->next->data == 3 && !result->next->next->next);

    // input: 1 -> 2 -> 3
    // output: 3 -> 2 -> 1
    next_ptr2 = make_shared<ListNode<int>>(ListNode<int> {3, nullptr});
    next_ptr = make_shared<ListNode<int>>(ListNode<int> {2, next_ptr2});
    L = make_shared<ListNode<int>>(ListNode<int> {1, next_ptr});

    result = ReverseSublist(L, 0, 2);
    ASSERT_TRUE(result->data == 3 && result->next->data == 2 &&
           result->next->next->data == 1 && !result->next->next->next);

    // input: 1 -> 2 -> 3
    // output: 3 -> 2 -> 1
    next_ptr2 = make_shared<ListNode<int>>(ListNode<int> {3, nullptr});
    next_ptr = make_shared<ListNode<int>>(ListNode<int> {2, next_ptr2});
    L = make_shared<ListNode<int>>(ListNode<int> {1, next_ptr});

    result = ReverseSublist(L, 1, 3);
    ASSERT_TRUE(result->data == 3 && result->next->data == 2 &&
           result->next->next->data == 1 && !result->next->next->next);

    // input: 1 -> 2 -> 3
    // output: 1 -> 2 -> 3
    next_ptr2 = make_shared<ListNode<int>>(ListNode<int> {3, nullptr});
    next_ptr = make_shared<ListNode<int>>(ListNode<int> {2, next_ptr2});
    L = make_shared<ListNode<int>>(ListNode<int> {1, next_ptr});

    result = ReverseSublist(L, 3, 3);
    ASSERT_TRUE(result->data == 1 && result->next->data == 2 &&
           result->next->next->data == 3 && !result->next->next->next);

    // input: 1 -> 2 -> 3
    // output: 1 -> 3 -> 2
    result = ReverseSublist(L, 2, 3);
    ASSERT_TRUE(result->data == 1 && result->next->data == 3 &&
           result->next->next->data == 2 && !result->next->next->next);

    // input: 3 -> 5
    // output: 5 -> 3
    // L = make_shared<ListNode<int>>(ListNode<int>{
    //        3, make_shared<ListNode<int>>(ListNode<int>{5, nullptr})});
    next_ptr = make_shared<ListNode<int>>(ListNode<int> {5, nullptr});
    L = make_shared<ListNode<int>>(ListNode<int> {3, next_ptr});

    result = ReverseSublist(L, 1, 2);
    ASSERT_TRUE(result->data == 5 && result->next->data == 3 && !result->next->next);
}

TEST_F(LinkedLists_Fixture, reverse_list_iterative) {
    shared_ptr<ListNode<int>> L = nullptr;
    auto result = ReverseLinkedList(L);
    ASSERT_TRUE(result == nullptr);

    L = make_shared<ListNode<int>>(ListNode<int> {1, nullptr});
    result = ReverseLinkedList(L);
    ASSERT_TRUE(result->data == 1 && result->next == nullptr);

    auto L4 = make_shared<ListNode<int>>(ListNode<int> {4, nullptr});
    auto L3 = make_shared<ListNode<int>>(ListNode<int> {3, L4});
    auto L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    auto L1 = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = ReverseLinkedList(L1);
    ASSERT_TRUE(result->data == 4 && result->next->data == 3 &&
           result->next->next->data == 2 && result->next->next->next->data == 1 &&
           result->next->next->next->next == nullptr);
}

TEST_F(LinkedLists_Fixture, reverse_list_iterative_knuth) {
    shared_ptr<ListNode<int>> L = nullptr;
    auto result = ReverseLinkedList_knuth(L);
    ASSERT_TRUE(result == nullptr);

    L = make_shared<ListNode<int>>(ListNode<int> {1, nullptr});
    result = ReverseLinkedList_knuth(L);
    ASSERT_TRUE(result->data == 1 && result->next == nullptr);

    auto L4 = make_shared<ListNode<int>>(ListNode<int> {4, nullptr});
    auto L3 = make_shared<ListNode<int>>(ListNode<int> {3, L4});
    auto L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    auto L1 = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = ReverseLinkedList_knuth(L1);
    ASSERT_TRUE(result->data == 4 && result->next->data == 3 &&
           result->next->next->data == 2 && result->next->next->next->data == 1 &&
           result->next->next->next->next == nullptr);
}

TEST_F(LinkedLists_Fixture, reverse_list_recursive) {
    shared_ptr<ListNode<int>> L = nullptr;
    auto result = rec::ReverseLinkedList(L);
    ASSERT_TRUE(result == nullptr);

    L = make_shared<ListNode<int>>(ListNode<int> {1, nullptr});
    result = rec::ReverseLinkedList(L);
    ASSERT_TRUE(result->data == 1 && result->next == nullptr);

    auto L4 = make_shared<ListNode<int>>(ListNode<int> {4, nullptr});
    auto L3 = make_shared<ListNode<int>>(ListNode<int> {3, L4});
    auto L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    auto L1 = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = rec::ReverseLinkedList(L1);
    ASSERT_TRUE(result->data == 4 && result->next->data == 3 &&
           result->next->next->data == 2 && result->next->next->next->data == 1 &&
           result->next->next->next->next == nullptr);
}

TEST_F(LinkedLists_Fixture, check_k_elements_exist_Function) {
    shared_ptr<ListNode<int>> L = nullptr;
    ASSERT_FALSE(check_k_elements_exist(L, 1));

    // 1 -> 2
    // head
    auto L2 = make_shared<ListNode<int>>(ListNode<int> {2, nullptr});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    ASSERT_TRUE(check_k_elements_exist(L,1));

    // 1 -> 2
    // head
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, nullptr});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    ASSERT_FALSE(check_k_elements_exist(L,2));

    // 1 -> 2
    // head
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, nullptr});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    ASSERT_FALSE(check_k_elements_exist(L,0));

    // 1 -> 2
    // head
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, nullptr});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    ASSERT_FALSE(check_k_elements_exist(L,3));

    // 1 -> 2 -> 3 -> 4
    // head
    auto L4 = make_shared<ListNode<int>>(ListNode<int> {2, nullptr});
    auto L3 = make_shared<ListNode<int>>(ListNode<int> {2, L4});
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    ASSERT_FALSE(check_k_elements_exist(L,4));

    // 1 -> 2 -> 3 -> 4
    // head
    L4 = make_shared<ListNode<int>>(ListNode<int> {2, nullptr});
    L3 = make_shared<ListNode<int>>(ListNode<int> {2, L4});
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    ASSERT_TRUE(check_k_elements_exist(L,3));

    // 1 -> 2 -> 3 -> 4
    L4 = make_shared<ListNode<int>>(ListNode<int> {4, nullptr});
    L3 = make_shared<ListNode<int>>(ListNode<int> {3, L4});
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    ASSERT_TRUE(check_k_elements_exist(L, 2));
}

TEST_F(LinkedLists_Fixture, reverse_list_first_k_Function) {
    // nullptr
    // nullptr
    shared_ptr<ListNode<int>> L = nullptr;
    auto result = reverse_list_first_k(L, 0);
    ASSERT_TRUE(result == nullptr);

    // 1
    // nullptr
    L = make_shared<ListNode<int>>(ListNode<int> {1, nullptr});
    result = reverse_list_first_k(L, 1);
    ASSERT_TRUE(result == nullptr);

    // 1 -> 2
    // 1 -> 2
    //      |result
    auto L2 = make_shared<ListNode<int>>(ListNode<int> {2, nullptr});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = reverse_list_first_k(L, 1);
    ASSERT_TRUE(result != nullptr && result->data == 2 && result->next == nullptr);

    // 1 -> 2
    // nullptr : not enough elements
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, nullptr});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = reverse_list_first_k(L, 2);
    ASSERT_TRUE(result == nullptr);

    // 1 -> 2 -> 3
    // 1 -> 3 -> 2
    //           |result
    auto L3 = make_shared<ListNode<int>>(ListNode<int> {3, nullptr});
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = reverse_list_first_k(L, 2);
    ASSERT_TRUE(result != nullptr && result->data == 2 && result->next == nullptr);

    // 1 -> 2 -> 3 -> 4
    // 1 -> 3 -> 2 -> 4
    //           |result
    auto L4 = make_shared<ListNode<int>>(ListNode<int> {4, nullptr});
    L3 = make_shared<ListNode<int>>(ListNode<int> {3, L4});
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = reverse_list_first_k(L, 2);
    ASSERT_TRUE(result != nullptr && result->data == 2 && result->next->data == 4 &&
            result->next->next == nullptr);
    ASSERT_TRUE(L->next->data == 3 && L->next->next->data == 2 &&
                L->next->next->next->data == 4 && L->next->next->next->next == nullptr);

    // 1 -> 2 -> 3 -> 4
    // 1 -> 4 -> 3 -> 2
    //                |result
    L4 = make_shared<ListNode<int>>(ListNode<int> {4, nullptr});
    L3 = make_shared<ListNode<int>>(ListNode<int> {3, L4});
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = reverse_list_first_k(L, 3);
    ASSERT_TRUE(result != nullptr && result->data == 2 && result->next == nullptr);
    ASSERT_TRUE(L->next->data == 4 && L->next->next->data == 3 &&
                L->next->next->next->data == 2 && L->next->next->next->next == nullptr);
}

TEST_F(LinkedLists_Fixture, reverse_list_in_k_group_erdos_Function) {
    // nullptr
    // nullptr
    shared_ptr<ListNode<int>> L = nullptr;
    auto result = reverse_list_in_k_group(L, 0);
    ASSERT_TRUE(result == nullptr);

    // 1
    // nullptr
    L = make_shared<ListNode<int>>(ListNode<int> {1, nullptr});
    result = reverse_list_in_k_group(L, 1);
    ASSERT_TRUE(result != nullptr && result->data == 1 && result->next == nullptr);

    // 1 -> 2
    // 1 -> 2
    auto L2 = make_shared<ListNode<int>>(ListNode<int> {2, nullptr});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = reverse_list_in_k_group(L, 1);
    ASSERT_TRUE(result != nullptr && result->data == 1 && result->next->data == 2
            && result->next->next == nullptr);

    // 1 -> 2
    // 2 -> 1
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, nullptr});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = reverse_list_in_k_group(L, 2);
    ASSERT_TRUE(result != nullptr && result->data == 2 &&
            result->next->data == 1 && result->next->next == nullptr);

    // 1 -> 2 -> 3
    // 2 -> 1 -> 3
    auto L3 = make_shared<ListNode<int>>(ListNode<int> {3, nullptr});
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = reverse_list_in_k_group(L, 2);
    ASSERT_TRUE(result != nullptr && result->data == 2 && result->next->data == 1 &&
                result->next->next->data == 3 && result->next->next->next == nullptr);

    // 1 -> 2 -> 3
    // 3 -> 2 -> 1
    L3 = make_shared<ListNode<int>>(ListNode<int> {3, nullptr});
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = reverse_list_in_k_group(L, 3);
    ASSERT_TRUE(result != nullptr && result->data == 3 && result->next->data == 2 &&
                result->next->next->data == 1 && result->next->next->next == nullptr);

    // 1 -> 2 -> 3 -> 4
    // 2 -> 1 -> 4 -> 3
    auto L4 = make_shared<ListNode<int>>(ListNode<int> {4, nullptr});
    L3 = make_shared<ListNode<int>>(ListNode<int> {3, L4});
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = reverse_list_in_k_group(L, 2);
    ASSERT_TRUE(result != nullptr && result->data == 2 && result->next->data == 1 &&
            result->next->next->data == 4 && result->next->next->next->data == 3 &&
            result->next->next->next->next == nullptr);

    // 1 -> 2 -> 3 -> 4
    // 3 -> 2 -> 1 -> 4
    L4 = make_shared<ListNode<int>>(ListNode<int> {4, nullptr});
    L3 = make_shared<ListNode<int>>(ListNode<int> {3, L4});
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = reverse_list_in_k_group(L, 3);
    ASSERT_TRUE(result != nullptr && result->data == 3 && result->next->data == 2 &&
            result->next->next->data == 1 && result->next->next->next->data == 4 &&
            result->next->next->next->next == nullptr);

    // 1 -> 2 -> 3 -> 4 -> 5
    // 3 -> 2 -> 1 -> 4 -> 5
    auto L5 = make_shared<ListNode<int>>(ListNode<int> {5, nullptr});
    L4 = make_shared<ListNode<int>>(ListNode<int> {4, L5});
    L3 = make_shared<ListNode<int>>(ListNode<int> {3, L4});
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = reverse_list_in_k_group(L, 3);
    ASSERT_TRUE(result != nullptr && result->data == 3 && result->next->data == 2 &&
            result->next->next->data == 1 && result->next->next->next->data == 4 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next == nullptr);

    // 1 -> 2 -> 3 -> 4 -> 5 -> 6
    // 3 -> 2 -> 1 -> 6 -> 5 -> 4
    auto L6 = make_shared<ListNode<int>>(ListNode<int> {6, nullptr});
    L5 = make_shared<ListNode<int>>(ListNode<int> {5, L6});
    L4 = make_shared<ListNode<int>>(ListNode<int> {4, L5});
    L3 = make_shared<ListNode<int>>(ListNode<int> {3, L4});
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = reverse_list_in_k_group(L, 3);
    ASSERT_TRUE(result != nullptr &&
            result->data == 3 &&
            result->next->data == 2 &&
            result->next->next->data == 1 &&
            result->next->next->next->data == 6  &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 4 &&
            result->next->next->next->next->next->next == nullptr
    );
}

TEST_F(LinkedLists_Fixture, reverse_list_in_k_group_Function) {
    // nullptr
    // nullptr
    shared_ptr<ListNode<int>> L = nullptr;
    auto result = ReverseK(L, 0);
    ASSERT_TRUE(result == nullptr);

    // 1
    // nullptr
    L = make_shared<ListNode<int>>(ListNode<int> {1, nullptr});
    result = ReverseK(L, 1);
    ASSERT_TRUE(result != nullptr && result->data == 1 && result->next == nullptr);

    // 1 -> 2
    // 1 -> 2
    auto L2 = make_shared<ListNode<int>>(ListNode<int> {2, nullptr});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = ReverseK(L, 1);
    ASSERT_TRUE(result != nullptr && result->data == 1 && result->next->data == 2
            && result->next->next == nullptr);

    // 1 -> 2
    // 2 -> 1
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, nullptr});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = ReverseK(L, 2);
    ASSERT_TRUE(result != nullptr && result->data == 2 &&
            result->next->data == 1 && result->next->next == nullptr);

    // 1 -> 2 -> 3
    // 2 -> 1 -> 3
    auto L3 = make_shared<ListNode<int>>(ListNode<int> {3, nullptr});
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = ReverseK(L, 2);
    ASSERT_TRUE(result != nullptr && result->data == 2 && result->next->data == 1 &&
                result->next->next->data == 3 && result->next->next->next == nullptr);

    // 1 -> 2 -> 3
    // 3 -> 2 -> 1
    L3 = make_shared<ListNode<int>>(ListNode<int> {3, nullptr});
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = ReverseK(L, 3);
    ASSERT_TRUE(result != nullptr && result->data == 3 && result->next->data == 2 &&
                result->next->next->data == 1 && result->next->next->next == nullptr);

    // 1 -> 2 -> 3 -> 4
    // 2 -> 1 -> 4 -> 3
    auto L4 = make_shared<ListNode<int>>(ListNode<int> {4, nullptr});
    L3 = make_shared<ListNode<int>>(ListNode<int> {3, L4});
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = ReverseK(L, 2);
    ASSERT_TRUE(result != nullptr && result->data == 2 && result->next->data == 1 &&
            result->next->next->data == 4 && result->next->next->next->data == 3 &&
            result->next->next->next->next == nullptr);

    // 1 -> 2 -> 3 -> 4
    // 3 -> 2 -> 1 -> 4
    L4 = make_shared<ListNode<int>>(ListNode<int> {4, nullptr});
    L3 = make_shared<ListNode<int>>(ListNode<int> {3, L4});
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = ReverseK(L, 3);
    ASSERT_TRUE(result != nullptr && result->data == 3 && result->next->data == 2 &&
            result->next->next->data == 1 && result->next->next->next->data == 4 &&
            result->next->next->next->next == nullptr);

    // 1 -> 2 -> 3 -> 4 -> 5
    // 3 -> 2 -> 1 -> 4 -> 5
    auto L5 = make_shared<ListNode<int>>(ListNode<int> {5, nullptr});
    L4 = make_shared<ListNode<int>>(ListNode<int> {4, L5});
    L3 = make_shared<ListNode<int>>(ListNode<int> {3, L4});
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = ReverseK(L, 3);
    ASSERT_TRUE(result != nullptr && result->data == 3 && result->next->data == 2 &&
            result->next->next->data == 1 && result->next->next->next->data == 4 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next == nullptr);

    // 1 -> 2 -> 3 -> 4 -> 5 -> 6
    // 3 -> 2 -> 1 -> 6 -> 5 -> 4
    auto L6 = make_shared<ListNode<int>>(ListNode<int> {6, nullptr});
    L5 = make_shared<ListNode<int>>(ListNode<int> {5, L6});
    L4 = make_shared<ListNode<int>>(ListNode<int> {4, L5});
    L3 = make_shared<ListNode<int>>(ListNode<int> {3, L4});
    L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    L = make_shared<ListNode<int>>(ListNode<int> {1, L2});
    result = ReverseK(L, 3);
    ASSERT_TRUE(result != nullptr &&
            result->data == 3 &&
            result->next->data == 2 &&
            result->next->next->data == 1 &&
            result->next->next->next->data == 6  &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 4 &&
            result->next->next->next->next->next->next == nullptr
    );
}

TEST_F(LinkedLists_Fixture, cycle_Function) {
    // 1 -> 2 -> 3
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
    // 1 -> 2 <-> 3
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
    // L -> 1 -> 2 -> 3
    shared_ptr<ListNode<int>> L;
    L = make_shared<ListNode<int>>(ListNode<int>{
            1, make_shared<ListNode<int>>(ListNode<int>{
                    2, make_shared<ListNode<int>>(ListNode<int>{3, nullptr})})});
    L = RemoveKthLast(L, 2);
    // L -> 1 -> 3
    ASSERT_TRUE(L->data == 1 && L->next->data == 3 && L->next->next == nullptr);
    L = RemoveKthLast(L, 2);
    // L -> 3
    ASSERT_TRUE(L->data == 3 && L->next == nullptr);
    L = RemoveKthLast(L, 1);
    // L
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
    // 0
    auto L = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
    auto result = EvenOddMerge(L);
    ASSERT_TRUE(result->data == 0);

    // 0 -> 1
    L->next = make_shared<ListNode<int>>(ListNode<int>{1, nullptr});
    result = EvenOddMerge(L);
    ASSERT_TRUE(result->data == 0);
    ASSERT_TRUE(result->next->data == 1);

    // 0 -> 1 -> 2
    L->next->next = make_shared<ListNode<int>>(ListNode<int>{2, nullptr});
    result = EvenOddMerge(L);
    ASSERT_TRUE(result->data == 0);
    ASSERT_TRUE(result->next->data == 2);
    ASSERT_TRUE(result->next->next->data == 1);

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 1000);
    int n = dis(gen);
    shared_ptr<ListNode<int>> head = p_8_10_CreateList(n);
    ASSERT_TRUE(p_8_10_CheckAnswer(EvenOddMerge(head), n));
    shared_ptr<ListNode<int>> another_head = p_8_10_CreateList(n);
    ASSERT_TRUE(p_8_10_CheckAnswer(EvenOddMergeOriginal(another_head), n));
}

TEST_F(LinkedLists_Fixture, even_odd_merge_erdos) {
    // 0
    auto L = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
    auto result = EvenOddMerge_erdos(L);
    ASSERT_TRUE(result->data == 0);

    // 0 -> 1
    L->next = make_shared<ListNode<int>>(ListNode<int>{1, nullptr});
    result = EvenOddMerge_erdos(L);
    ASSERT_TRUE(result->data == 0);
    ASSERT_TRUE(result->next->data == 1);

    // 0 -> 1 -> 2
    L->next->next = make_shared<ListNode<int>>(ListNode<int>{2, nullptr});
    result = EvenOddMerge_erdos(L);
    ASSERT_TRUE(result->data == 0);
    ASSERT_TRUE(result->next->data == 2);
    ASSERT_TRUE(result->next->next->data == 1);

    for (int i = 0; i < 1000; ++i) {
        random_device rd;
        default_random_engine gen(rd());
        //default_random_engine gen((random_device()) ());
        uniform_int_distribution<int> dis(1, 1000);
        int n = dis(gen);
        shared_ptr<ListNode<int>> head = p_8_10_CreateList(n);
        ASSERT_TRUE(p_8_10_CheckAnswer(EvenOddMerge_erdos(head), n));
    }
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
