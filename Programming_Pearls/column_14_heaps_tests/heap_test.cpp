#include "min_priqueue.h"
#include <gtest/gtest.h>

void swap(int* x, int i, int j) {
    int t = x[i];
    x[i] = x[j];
    x[j] = t;
}

class HeapOperationFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
        set_value_target_array();
        shuffle_array(100000);
        insert_to_priqueue();
    }

    int size_ary=100000;
    int* target_array = new int[size_ary];

    min_priqueue<int> pq;

    void set_value_target_array () {
        for(int i=0; i< size_ary; i++) {
            target_array[i] = 100000 - i;
        }
    };

    void shuffle_array (int times) {
        for (int i = 0; i < times; i++) {
            int idx1 = rand() % size_ary;
            int idx2 = rand() % size_ary;
            swap(target_array, idx1, idx2);
        }
    }

    void insert_to_priqueue(){
        for(int i=0; i< size_ary; i++) {
            pq.insert(target_array[i]);
        }
    }
public:
    HeapOperationFixture() : Test(), pq(size_ary) {
    }

    virtual ~HeapOperationFixture() {

    }
};

TEST_F(HeapOperationFixture, test_heapsort_Function) {
    pqsort(target_array,size_ary);
    ASSERT_EQ(1, target_array[0]);
    ASSERT_EQ(500, target_array[499]);
    ASSERT_EQ(1500, target_array[1499]);
    ASSERT_EQ(100000, target_array[99999]);
}


TEST_F(HeapOperationFixture, test_priqueue_Function) {
    ASSERT_EQ(1, pq.extractmin());
    ASSERT_EQ(2, pq.extractmin());
    ASSERT_EQ(3, pq.extractmin());
    ASSERT_EQ(4, pq.extractmin());
}

