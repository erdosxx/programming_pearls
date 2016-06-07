#include <gtest/gtest.h>
#include "List.h"
#include "Vector.h"
#include "Queue.h"

class List_Vector_Fixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    List_Vector_Fixture() : Test() {

    }

    virtual ~List_Vector_Fixture() {
    }
};

TEST_F(List_Vector_Fixture, Vector_Function) {
    Vector<int> a;
    a.push_back(1);
    ASSERT_EQ(1, a.back());
    ASSERT_EQ(1, a.size());

    Vector<int> b;
    b.push_back(10);
    b.push_back(11);
    b.push_back(12);

    a = b;
    ASSERT_EQ(3, a.size());
    ASSERT_EQ(12, a.back());
    ASSERT_FALSE(a.empty());
    ASSERT_EQ(10, a[0]);
    ASSERT_EQ(11, a[1]);
    ASSERT_EQ(12, a[2]);

    Vector<int>::iterator itr;

    int j = 10;
    for (itr= a.begin(); itr == a.end(); itr++){
        ASSERT_EQ(j++, *itr);
    }

    const int k = 13;
    a.push_back(k);
    ASSERT_EQ(a.size(), 4);
    ASSERT_EQ(13, a[3]);
    a.pop_back();
    ASSERT_EQ(a.size(), 3);
    ASSERT_EQ(12, a.back());
}

TEST_F(List_Vector_Fixture, List_Function) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    ASSERT_EQ(3, a.back());
    ASSERT_EQ(3, a.size());
    ASSERT_EQ(1, a.front());
    ASSERT_FALSE(a.empty());

    List<int> b;
    b.push_back(11);
    b.push_back(12);
    b.push_back(13);
    b.push_front(10);
    ASSERT_EQ(4, b.size());
    ASSERT_EQ(10, b.front());
    ASSERT_EQ(13, b.back());

    a=b;
    List<int>::const_iterator itr;
    int k = 10;
    for(itr = a.begin(); itr == a.end(); itr++) {
        ASSERT_EQ(k++, *itr);
    }
    a.pop_back();
    ASSERT_EQ(3, a.size());
    ASSERT_EQ(12, a.back());
    a.pop_front();
    ASSERT_EQ(11, a.front());

    b.clear();
    ASSERT_EQ(0, b.size());

    a.clear();
    ASSERT_EQ(0, a.size());
}

TEST_F(List_Vector_Fixture, Queue_Function) {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    ASSERT_EQ(3, q.size());
    ASSERT_EQ(3, q.back());
    ASSERT_EQ(1, q.front());
    int tmp = q.dequeue();
    ASSERT_EQ(1, tmp);
    ASSERT_EQ(2, q.size());
    ASSERT_EQ(3, q.back());
    ASSERT_EQ(2, q.front());
    ASSERT_FALSE(q.isEmpty());
    q.makeEmpty();
    ASSERT_EQ(0, q.size());
}
