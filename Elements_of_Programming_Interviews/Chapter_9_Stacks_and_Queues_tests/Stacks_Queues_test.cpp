#include <gtest/gtest.h>
#include <random>
#include <limits>
#include <memory>
#include "stacks_boot_camp.h"
#include "queues_boot_camp.h"
#include "Stack_with_max.h"
#include "Stack_with_max_improved.h"
#include "RPN.h"
#include "Polish_Notation.h"
#include "valid-parentheses.h"
#include "normalized_pathnames.h"
#include "Search_postings_list_iterative.h"
#include "Search_postings_list_recursive.h"
#include "View_sunset.h"
#include "Binary_tree_level_order.h"
#include "Circular_queue.h"
#include "Queue_from_stacks.h"
#include "Queue_with_max.h"
#include "Queue_with_max_alternative.h"

using std::istringstream;
using std::stringstream;
using std::default_random_engine;
using std::random_device;
using std::unique_ptr;
using std::numeric_limits;
using std::make_shared;
using std::shared_ptr;
using std::make_unique;

class StacksQueues_Fixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    StacksQueues_Fixture() : Test() {

    }

    virtual ~StacksQueues_Fixture() {
    }
};

TEST_F(StacksQueues_Fixture, stacks_boot_camp) {
    shared_ptr<ListNode<int>> L4 = make_shared<ListNode<int>>(ListNode<int> {4, nullptr});
    auto L3 = make_shared<ListNode<int>>(ListNode<int> {3, L4});
    auto L2 = make_shared<ListNode<int>>(ListNode<int> {2, L3});
    auto L1 = make_shared<ListNode<int>>(ListNode<int> {1, L2});

    string result;
    result = PrintLinkedListInReverse(&L1);

    ASSERT_EQ(result, "4<-3<-2<-1<-");
}

TEST_F(StacksQueues_Fixture, queues_boot_camp) {
    Queue q_data;
    q_data.Enqueue(0);
    q_data.Enqueue(1);
    q_data.Enqueue(3);
    q_data.Enqueue(2);

    ASSERT_EQ(0, q_data.Front());  //0-1-3-2
    ASSERT_EQ(3, q_data.Max());
    q_data.Dequeue();
    q_data.Dequeue();
    q_data.Dequeue();
    q_data.Dequeue();
    //throw exception.
    ASSERT_THROW(q_data.Dequeue(), length_error);
    ASSERT_THROW(q_data.Front(), length_error);
    ASSERT_THROW(q_data.Max(), length_error);
}

TEST_F(StacksQueues_Fixture, stl_library) {
    ///// stack
    stack<char> s1;  // uses a deque<char> to store elements
    s1.push('a');
    ASSERT_EQ('a', s1.top()); // a
    s1.emplace('b');
    ASSERT_EQ('b', s1.top()); // b-a
    s1.pop();  // a
    ASSERT_EQ('a', s1.top());
    s1.pop(); // empty
    ASSERT_TRUE(s1.empty());

    stack<char,vector<char>> s2; // uses a vector<char> to store elements.
                                // Often, vector is faster than deque and uses less memory.
    s2.push('a');
    ASSERT_EQ('a', s2.top()); // a
    s2.emplace('b');
    ASSERT_EQ('b', s2.top()); // b-a
    s2.pop();  // a
    ASSERT_EQ('a', s2.top());
    s2.pop(); // empty
    ASSERT_TRUE(s2.empty());

    ///// queue
    queue<char> q1;
    q1.push('a');
    ASSERT_EQ(q1.front(), 'a'); // a
    q1.emplace('b');
    ASSERT_EQ(q1.front(), 'a');   // a-b
    ASSERT_EQ(q1.back(), 'b');
    q1.pop();
    ASSERT_EQ(q1.front(), 'b');   // b
    ASSERT_EQ(q1.back(), 'b');

    // unlike stack following does not work
    // queue<char, vector<char>> q2;
    // error: no member named 'pop_front' in 'std::__1::vector<char, std::__1::allocator<char> >'

    ////// deque
    deque<char> dq1;
    dq1.push_back('a');
    ASSERT_EQ(dq1.front(), 'a'); // a
    dq1.emplace_back('b');
    ASSERT_EQ(dq1.front(), 'a'); // a-b
    ASSERT_EQ(dq1.back(), 'b');
    dq1.push_front('z');
    ASSERT_EQ(dq1.front(), 'z'); // z-a-b
    ASSERT_EQ(dq1.back(), 'b');
    dq1.emplace_front('y');
    ASSERT_EQ(dq1.front(), 'y'); // y-z-a-b
    ASSERT_EQ(dq1.back(), 'b');
    dq1.pop_back();
    ASSERT_EQ(dq1.front(), 'y'); // y-z-a
    ASSERT_EQ(dq1.back(), 'a');
    dq1.pop_front();
    ASSERT_EQ(dq1.front(), 'z'); // z-a
    ASSERT_EQ(dq1.back(), 'a');
    ASSERT_EQ(2, dq1.size());
    dq1.pop_front(); // a
    dq1.pop_front(); // empty
    ASSERT_TRUE(dq1.empty());
}
TEST_F(StacksQueues_Fixture, stack_with_max_Function) {
    stack_max::Stack s;
    s.Push(1);
    s.Push(2);
    ASSERT_EQ(2, s.Max());
    s.Pop();  // 2
    ASSERT_EQ(1, s.Max());
    s.Push(3);
    s.Push(2);
    ASSERT_EQ(3, s.Max());
    s.Pop();
    ASSERT_EQ(3, s.Max());
    s.Pop();
    ASSERT_EQ(1, s.Max());
    s.Pop();
    ASSERT_THROW(s.Max(); s.Pop(); s.Pop(); s.Pop(); s.Pop(), length_error );
}

TEST_F(StacksQueues_Fixture, stack_with_max_improved_Function) {
    stack_max_imp::Stack s;
    s.Push(1);
    s.Push(2);
    ASSERT_EQ(2, s.Max());
    s.Pop();  // 2
    ASSERT_EQ(1, s.Max());
    s.Push(3);
    s.Push(2);
    ASSERT_EQ(3, s.Max());
    s.Pop();
    ASSERT_EQ(3, s.Max());
    s.Pop();
    ASSERT_EQ(1, s.Max());
    s.Pop();
    ASSERT_THROW(s.Max(); s.Pop(); s.Pop(); s.Pop(); s.Pop(), length_error );
}

TEST_F(StacksQueues_Fixture, RPN_Function) {
    ASSERT_EQ(0, Eval("2,-10,/"));
    ASSERT_EQ(-5, Eval("-10,2,/"));
    ASSERT_EQ(5, Eval("-10,-2,/"));
    ASSERT_EQ(-5, Eval("5,10,-"));
    ASSERT_EQ(6, Eval("-10,-16,-"));
    ASSERT_EQ(12, Eval("10,2,+"));
    ASSERT_EQ(15, Eval("1,2,+,3,4,*,+"));
    ASSERT_EQ(42, Eval("1,2,3,4,5,+,*,+,+,3,4,*,+"));
    ASSERT_EQ(-6, Eval("1,2,3,4,5,+,*,+,+,3,4,*,+,-7,/"));
}

TEST_F(StacksQueues_Fixture, Polish_Notation) {
    ASSERT_TRUE(isNumber("2342"));
    ASSERT_TRUE(isNumber("-2342"));
    ASSERT_FALSE(isNumber("A"));
    ASSERT_FALSE(isNumber("-A"));
    ASSERT_FALSE(isNumber("-A123"));
    ASSERT_FALSE(isNumber("+"));
    ASSERT_FALSE(isNumber("-"));
    ASSERT_FALSE(isNumber("/"));
    ASSERT_FALSE(isNumber("*"));

    ASSERT_EQ(3, eval_polish_notation("+,1,2"));
    ASSERT_EQ(-1, eval_polish_notation("-,1,2"));
    ASSERT_EQ(2, eval_polish_notation("/,2,1"));
    ASSERT_EQ(2, eval_polish_notation("*,2,1"));
    // b*c + a + (d*e + f)*g
    // 2*3 + 1 + (4*5 + 6)*7 = 189
    ASSERT_EQ(7, eval_polish_notation("+,*,2,3,1"));
    ASSERT_EQ(182, eval_polish_notation("*,+,*,4,5,6,7"));
    ASSERT_EQ(189, eval_polish_notation("+,*,+,*,4,5,6,7,7"));
    ASSERT_EQ(3, eval_polish_notation("+,1,*,1,2"));
    ASSERT_EQ(1, eval_polish_notation("+,1,/,1,2"));
    ASSERT_EQ(189, eval_polish_notation("+,7,182"));
    ASSERT_EQ(189, eval_polish_notation("+,7,*,26,7"));
    ASSERT_EQ(189, eval_polish_notation("+,+,*,2,3,1,*,+,*,4,5,6,7"));
}

TEST_F(StacksQueues_Fixture, valid_parentheses_Function) {
    ASSERT_TRUE(IsWellFormed("()"));
    ASSERT_TRUE(IsWellFormed("()[]{}"));
    ASSERT_TRUE(IsWellFormed("[()[]]{}"));
    ASSERT_TRUE(IsWellFormed("(()[]{()[]{}{}})"));
    ASSERT_FALSE(IsWellFormed("([)]"));
    ASSERT_FALSE(IsWellFormed("["));
    ASSERT_FALSE(IsWellFormed("}"));
    ASSERT_FALSE(IsWellFormed("(()[]{()[]{})({}})"));
}

TEST_F(StacksQueues_Fixture, normalized_pathnames_Function) {
    ASSERT_TRUE(ShortestEquivalentPath("123/456") == string("123/456"));
    ASSERT_TRUE(ShortestEquivalentPath("/123/456") == string("/123/456"));
    ASSERT_TRUE(ShortestEquivalentPath("usr/lib/../bin/gcc") ==
           string("usr/bin/gcc"));
    ASSERT_TRUE(ShortestEquivalentPath("./../") == string(".."));
    ASSERT_TRUE(ShortestEquivalentPath("../../local") == string("../../local"));
    ASSERT_TRUE(ShortestEquivalentPath("./.././../local") == string("../../local"));
    ASSERT_TRUE(ShortestEquivalentPath("/foo/../foo/./../") == string("/"));

//    ASSERT_THROW(ShortestEquivalentPath("/foo.txt"), invalid_argument);
    ASSERT_THROW(ShortestEquivalentPath(""), invalid_argument);
    ASSERT_THROW(ShortestEquivalentPath("/.."), invalid_argument);
//    ASSERT_THROW(ShortestEquivalentPath("/cpp_name/bin/"), invalid_argument);

    ASSERT_TRUE(ShortestEquivalentPath("scripts//./../scripts/awkscripts/././") ==
           string("scripts/awkscripts"));
}

TEST_F(StacksQueues_Fixture, search_postings_list_itr_Function) {
    shared_ptr<PostingListNode> L = nullptr;
    shared_ptr<PostingListNode> curr;
    curr = L;
    // Build a linked list L->1->2->3->4->5->nullptr.
    for (size_t i = 0; i < 5; ++i) {
        shared_ptr<PostingListNode> temp =
                make_shared<PostingListNode>(PostingListNode{postings_itr::UNDIFINED, nullptr, nullptr});
        if (curr) {
            curr->next = temp;
            curr = temp;
        } else {
            curr = L = temp;
        }
    }

    L->jump = nullptr;  // no jump from 1
    L->next->jump = L->next->next->next;  // 2's jump points to 4
    L->next->next->jump = L;  // 3's jump points to 1
    L->next->next->next->jump = nullptr;  // no jump from 4
    L->next->next->next->next->jump =
            L->next->next->next->next;  // 5's jump points to 5
    shared_ptr<PostingListNode> temp = L;
    postings_itr::SetJumpOrder(L);
    // output the jump-first order, it should be 0, 1, 4, 2, 3
    ASSERT_EQ(0, temp->order);
    temp = temp->next;
    ASSERT_EQ(1, temp->order);
    temp = temp->next;
    ASSERT_EQ(4, temp->order);
    temp = temp->next;
    ASSERT_EQ(2, temp->order);
    temp = temp->next;
    ASSERT_EQ(3, temp->order);
}

TEST_F(StacksQueues_Fixture, search_postings_list_rec_Function) {
    shared_ptr<PostingListNode> L = nullptr, curr;
    curr = L;
    // Build a linked list L->1->2->3->4->5->nullptr.
    for (size_t i = 0; i < 5; ++i) {
        shared_ptr<PostingListNode> temp =
                make_shared<PostingListNode>(PostingListNode{postings_rec::UNDIFINED, nullptr, nullptr});
        if (curr) {
            curr->next = temp;
            curr = temp;
        } else {
            curr = L = temp;
        }
    }
    L->jump = nullptr;  // no jump from 1
    L->next->jump = L->next->next->next;  // 2's jump points to 4
    L->next->next->jump = L;  // 3's jump points to 1
    L->next->next->next->jump = nullptr;  // no jump from 4
    L->next->next->next->next->jump =
            L->next->next->next->next;  // 5's jump points to 5
    shared_ptr<PostingListNode> temp = L;
    postings_rec::SetJumpOrder(L);
    // output the jump-first order, it should be 0, 1, 4, 2, 3
    ASSERT_EQ(0, temp->order);
    temp = temp->next;
    ASSERT_EQ(1, temp->order);
    temp = temp->next;
    ASSERT_EQ(4, temp->order);
    temp = temp->next;
    ASSERT_EQ(2, temp->order);
    temp = temp->next;
    ASSERT_EQ(3, temp->order);
}

TEST_F(StacksQueues_Fixture, view_sunset_Function) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());

    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<int> dis(1, 10000);
        int n = dis(gen);

        stringstream ss;
        vector<int> heights;
        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(1, 2 * n);
            int height = dis(gen);
            ss << height << ' ';
            heights.emplace_back(height);
        }

        istringstream sin(ss.str());
        auto res = ExamineBuildingsWithSunset(&sin);
        // cout << res[0] << ' ' << heights[res[0]] << endl;
        for (int i = 1; i < res.size(); ++i) {
            // cout << res[i] << ' ' << heights[res[i]] << endl;
            ASSERT_TRUE(heights[res[i - 1]] < heights[res[i]]);
        }
    }
}

TEST_F(StacksQueues_Fixture, binary_tree_level_order_Function) {
    //      3
    //    2   5
    //  1    4 6
    // 10
    //   13
    //unique_ptr<BinaryTreeNode<int>> tree = make_unique<BinaryTreeNode<int>>(
    //        BinaryTreeNode<int>{3, nullptr, nullptr});

    auto tree = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{3, nullptr, nullptr});
    tree->left = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{2, nullptr, nullptr});
    tree->left->left = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{1, nullptr, nullptr});
    tree->left->left->left = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{10, nullptr, nullptr});
    tree->left->left->left->right = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{13, nullptr, nullptr});
    tree->right = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{5, nullptr, nullptr});
    tree->right->left = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{4, nullptr, nullptr});
    tree->right->right = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{6, nullptr, nullptr});
    // should output 3
    //               2 5
    //               1 4 6
    //               10
    //               13
    auto result = BinaryTreeDepthOrder(tree);
    vector<vector<int>> golden_res = {{3}, {2, 5}, {1, 4, 6}, {10}, {13}};
    ASSERT_TRUE(equal(golden_res.begin(), golden_res.end(), result.begin(),
                 result.end()));
}

TEST_F(StacksQueues_Fixture, circular_queue_Function) {
    circular_queue::Queue q(8);
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    q.Enqueue(4);
    q.Enqueue(5);
    q.Enqueue(6);
    q.Enqueue(7);
    q.Enqueue(8);
    // Now head = 0 and tail = 0

    ASSERT_EQ(1, q.Dequeue());
    ASSERT_EQ(2, q.Dequeue());
    ASSERT_EQ(3, q.Dequeue());
    // Now head = 3 and tail = 0

    q.Enqueue(11);
    q.Enqueue(12);
    q.Enqueue(13);
    // Ok till here. Now head = 3 and tail = 3

    q.Enqueue(14);  // now the vector (data) is resized; but the head and tail.
    // (or elements) does not change accordingly.
    q.Enqueue(15);
    q.Enqueue(16);
    q.Enqueue(17);
    q.Enqueue(18);
    // The elements starting from head=3 are over-written!

    ASSERT_EQ(4, q.Dequeue());
    ASSERT_EQ(5, q.Dequeue());
    ASSERT_EQ(6, q.Dequeue());
    ASSERT_EQ(7, q.Dequeue());
    ASSERT_EQ(8, q.Dequeue());
    ASSERT_EQ(11, q.Dequeue());
    ASSERT_EQ(12, q.Dequeue());

    circular_queue::Queue q1(8);
    q1.Enqueue(1);
    q1.Enqueue(2);
    q1.Enqueue(3);
    ASSERT_EQ(1, q1.Dequeue());
    q1.Enqueue(4);
    ASSERT_EQ(2, q1.Dequeue());
    ASSERT_EQ(3, q1.Dequeue());
    ASSERT_EQ(4, q1.Dequeue());
    ASSERT_THROW(q1.Dequeue(),length_error);

    // test resize().
    q1.Enqueue(4);
    q1.Enqueue(4);
    q1.Enqueue(4);
    q1.Enqueue(4);
    q1.Enqueue(4);
    q1.Enqueue(4);
    q1.Enqueue(4);
    q1.Enqueue(4);
    q1.Enqueue(4);
    ASSERT_EQ(9, q1.size());
}

TEST_F(StacksQueues_Fixture, queue_from_stacks_Function) {
    queue_from_stack::Queue Q;
    Q.Enqueue(1);
    Q.Enqueue(2);
    ASSERT_EQ(1, Q.Dequeue());
    ASSERT_EQ(2, Q.Dequeue());
    Q.Enqueue(3);
    ASSERT_EQ(3, Q.Dequeue());
    ASSERT_THROW(Q.Dequeue(), length_error);

    Q.Enqueue(-1);
    Q.Enqueue(123);
    Q.Enqueue(numeric_limits<int>::max());
    Q.Enqueue(numeric_limits<int>::min());
    Q.Enqueue(0);
    ASSERT_EQ(-1, Q.Dequeue());
    Q.Enqueue(0);
    ASSERT_EQ(123, Q.Dequeue());
    ASSERT_EQ(numeric_limits<int>::max(), Q.Dequeue());
    ASSERT_EQ(numeric_limits<int>::min(), Q.Dequeue());
    ASSERT_EQ(0, Q.Dequeue());
    ASSERT_EQ(0, Q.Dequeue());
    ASSERT_THROW(Q.Dequeue(), length_error);
}

TEST_F(StacksQueues_Fixture, queue_with_max_Function) {
    original::QueueWithMax Q;
    Q.Enqueue(11);
    Q.Enqueue(2);
    ASSERT_EQ(11, Q.Max());
    ASSERT_EQ(11, Q.Dequeue());
    ASSERT_EQ(2, Q.Max());
    ASSERT_EQ(2, Q.Dequeue());
    Q.Enqueue(3);
    ASSERT_EQ(3, Q.Max());
    ASSERT_EQ(3, Q.Dequeue());

    Q.Enqueue(numeric_limits<int>::max() - 1);
    Q.Enqueue(numeric_limits<int>::max());
    Q.Enqueue(-2);
    Q.Enqueue(-1);
    Q.Enqueue(-1);
    Q.Enqueue(numeric_limits<int>::min());
    ASSERT_EQ(numeric_limits<int>::max(), Q.Max());
    ASSERT_EQ(numeric_limits<int>::max() - 1, Q.Dequeue());
    ASSERT_EQ(numeric_limits<int>::max(), Q.Max());
    ASSERT_EQ(numeric_limits<int>::max(), Q.Dequeue());
    ASSERT_EQ(-1, Q.Max());
    ASSERT_EQ(-2, Q.Dequeue());
    ASSERT_EQ(-1, Q.Max());
    ASSERT_EQ(-1, Q.Dequeue());
    ASSERT_EQ(-1, Q.Dequeue());
    ASSERT_EQ(numeric_limits<int>::min(), Q.Max());
    ASSERT_EQ(numeric_limits<int>::min(), Q.Dequeue());
    ASSERT_THROW(Q.Max(), length_error);

    original::QueueWithMax Q1;
    Q1.Enqueue(1);
    Q1.Enqueue(2);
    ASSERT_EQ(2, Q1.Max());
    ASSERT_EQ(1, Q1.Dequeue());
    ASSERT_EQ(2, Q1.Max());
    ASSERT_EQ(2, Q1.Dequeue());
    Q1.Enqueue(3);
    ASSERT_EQ(3, Q1.Max());
    ASSERT_EQ(3, Q1.Dequeue());
    ASSERT_THROW(Q1.Max(), length_error);
    ASSERT_THROW(Q1.Dequeue(), length_error);
}

TEST_F(StacksQueues_Fixture, queue_with_max_alt_Function) {
    QueueWithMaxAlternative::QueueWithMax<int> Q;
    Q.Enqueue(11);
    Q.Enqueue(2);
    ASSERT_EQ(11, Q.Max());
    ASSERT_EQ(11, Q.Dequeue());
    ASSERT_EQ(2, Q.Max());
    ASSERT_EQ(2, Q.Dequeue());
    Q.Enqueue(3);
    ASSERT_EQ(3, Q.Max());
    ASSERT_EQ(3, Q.Dequeue());
    Q.Enqueue(numeric_limits<int>::max() - 1);
    Q.Enqueue(numeric_limits<int>::max());
    Q.Enqueue(-2);
    Q.Enqueue(-1);
    Q.Enqueue(-1);
    Q.Enqueue(numeric_limits<int>::min());
    ASSERT_EQ(numeric_limits<int>::max(), Q.Max());
    ASSERT_EQ(numeric_limits<int>::max() - 1, Q.Dequeue());
    ASSERT_EQ(numeric_limits<int>::max(), Q.Max());
    ASSERT_EQ(numeric_limits<int>::max(), Q.Dequeue());
    ASSERT_EQ(-1, Q.Max());
    ASSERT_EQ(-2, Q.Dequeue());
    ASSERT_EQ(-1, Q.Max());
    ASSERT_EQ(-1, Q.Dequeue());
    ASSERT_EQ(-1, Q.Dequeue());
    ASSERT_EQ(numeric_limits<int>::min(), Q.Max());
    ASSERT_EQ(numeric_limits<int>::min(), Q.Dequeue());
    ASSERT_THROW(Q.Max(), length_error);

    QueueWithMaxAlternative::QueueWithMax<int> Q1;
    Q1.Enqueue(1);
    Q1.Enqueue(2);
    ASSERT_EQ(2, Q1.Max());
    ASSERT_EQ(1, Q1.Dequeue());
    ASSERT_EQ(2, Q1.Max());
    ASSERT_EQ(2, Q1.Dequeue());
    Q1.Enqueue(3);
    ASSERT_EQ(3, Q1.Max());
    ASSERT_EQ(3, Q1.Dequeue());
    ASSERT_THROW(Q1.Max(), length_error);
    ASSERT_THROW(Q1.Dequeue(), length_error);
}
