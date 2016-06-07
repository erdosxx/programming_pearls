#include <gtest/gtest.h>
#include "LeftistHeap.h"
#include "BinaryHeap.h"
#include "BinomialQueue.h"
#include <queue>
#include <functional>
#include <iostream>

class PriorityQueuesAlgorithmFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    const int minItem = 10000; // same number of digits
    const int maxItem = 99999;
    BinaryHeap<string> bh;

    const int numItems = 10000;
    LeftistHeap<int> lh;
    LeftistHeap<int> lh1;
    LeftistHeap<int> lh2;

    int bq_numItems = 100000;
    BinomialQueue<int> bq;
    BinomialQueue<int> bq1;
    BinomialQueue<int> bq2;

    priority_queue<int> maxPQ;
    priority_queue<int, vector<int>, greater<int> > minPQ;

public:
    PriorityQueuesAlgorithmFixture() : Test() {

    }

    virtual ~PriorityQueuesAlgorithmFixture() {
        bh.makeEmpty();
        lh.makeEmpty();
        lh1.makeEmpty();
        lh2.makeEmpty();
        bq.makeEmpty();
        bq1.makeEmpty();
        bq2.makeEmpty();
        maxPQ.empty();
        minPQ.empty();
    }
};

TEST_F(PriorityQueuesAlgorithmFixture, binary_heap_Function) {
    for(int i = 37; i != 0; i = ( i + 37 ) % maxItem ) {
        // should use to_string in C++11
        ostringstream sout;
        sout << "hello" << i;
        if( i >= minItem ) {
            string s = sout.str();
            bh.insert( s );
        }
    }

    string x;
    for(int i = minItem; i < maxItem; ++i ) {
        ostringstream sout;
        sout << "hello" << i;

        bh.deleteMin( x );

        ASSERT_EQ(x, sout.str());
    }
}

TEST_F(PriorityQueuesAlgorithmFixture, binomial_queue_Function) {
    for(int i = 37; i != 0; i = ( i + 37 ) % bq_numItems )
        if( i % 2 == 0 )
            bq1.insert( i );
        else
            bq.insert( i );

    bq.merge( bq1 );
    bq2 = bq;

    for(int i = 1; i < bq_numItems; ++i ) {
        int x;
        bq2.deleteMin( x );
        ASSERT_EQ(x, i);
    }

    ASSERT_TRUE(bq1.isEmpty());
}

TEST_F(PriorityQueuesAlgorithmFixture, leftiest_heap_Function) {

    for(int i = 37; i != 0; i = ( i + 37 ) % numItems )
        if( i % 2 == 0 )
            lh1.insert( i );
        else
            lh.insert( i );

    lh.merge( lh1 );

    lh2 = lh;

    for(int i = 1; i < numItems; ++i ) {
        int x;
        lh2.deleteMin( x );

        ASSERT_EQ(x, i);
    }

    ASSERT_TRUE(lh1.isEmpty());
}

TEST_F(PriorityQueuesAlgorithmFixture, STL_heap_Function) {
    minPQ.push(4);
    minPQ.push(3);
    minPQ.push(5);
    ASSERT_EQ(3, minPQ.top());
    minPQ.pop();
    ASSERT_EQ(4, minPQ.top());
    minPQ.pop();
    ASSERT_EQ(5, minPQ.top());
    minPQ.pop();

    maxPQ.push(4);
    maxPQ.push(3);
    maxPQ.push(5);
    ASSERT_EQ(5, maxPQ.top());
    maxPQ.pop();
    ASSERT_EQ(4, maxPQ.top());
    maxPQ.pop();
    ASSERT_EQ(3, maxPQ.top());
    maxPQ.pop();
}

TEST_F(PriorityQueuesAlgorithmFixture, arithmetic_Function) {
    int i = 2;
    int j = 1;
    i -= j + 1;
    ASSERT_EQ(0, i);
    int k = (1 << 2) -1; // 2^2 -1
    ASSERT_EQ(3, k);
}
