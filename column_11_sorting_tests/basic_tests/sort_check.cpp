#include <gtest/gtest.h>
#include "sort.h"

class sortAlgorithmFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
        set_value_target_array();
        shuffle_array(1000);
    }

    int size_ary=1000;
    int* target_array = new int[size_ary];

    void set_value_target_array () {
        for(int i=0; i< size_ary; i++) {
            target_array[i] = 1000 - i;
        }
    };

    void shuffle_array (int times) {
        for (int i = 0; i < times; i++) {
            int idx1 = rand() % size_ary;
            int idx2 = rand() % size_ary;
            swap(target_array, idx1, idx2);
        }
    }


public:
    sortAlgorithmFixture() : Test() {

    }

    virtual ~sortAlgorithmFixture() {

    }
};

TEST_F(sortAlgorithmFixture, test_insertionSort) {
    isort1(target_array, size_ary);
    EXPECT_EQ(1, target_array[0]);
    EXPECT_EQ(2, target_array[1]);
    EXPECT_EQ(501, target_array[500]);
    EXPECT_EQ(701, target_array[700]);
    EXPECT_EQ(999, target_array[998]);
    EXPECT_EQ(1000, target_array[999]);
}
