#include <gtest/gtest.h>
#include "column1.h"

void swap(int x[], int i, int j) {
    int t = x[i];
    x[i] = x[j];
    x[j] = t;
}

class bitSortAlgorithmFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    int max_val =10000000;
    const int BITSPERWORD=32;
    int size_internal_ary= 1 + max_val/BITSPERWORD;

    int*internal_array = new int[size_internal_ary];

    virtual void SetUp() {
        set_value_target_array();
        shuffle_array(100000);
    }

    int size_ary=1000000;
    int* target_array = new int[size_ary];

    void set_value_target_array () {
        for(int i=0; i< size_ary; i++) {
            target_array[i] = max_val - (i + 1);
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
    bitSortAlgorithmFixture() : Test() {

    }

    virtual ~bitSortAlgorithmFixture() {

    }
};

TEST_F(bitSortAlgorithmFixture, test_setFunction) {
    set(internal_array, 0);
    set(internal_array, 1);
    set(internal_array, 2);
    set(internal_array, 3);
    set(internal_array, 4);
    set(internal_array, 5);
    // 111111 = 63
    set(internal_array, 32);
    set(internal_array, 33);
    // 11 = 3

    EXPECT_EQ(63, internal_array[0]);
    EXPECT_EQ(3, internal_array[1]);
}

TEST_F(bitSortAlgorithmFixture, test_clrFunction) {
    set(internal_array, 0);
    set(internal_array, 1);
    set(internal_array, 2);
    set(internal_array, 3);
    set(internal_array, 4);
    set(internal_array, 5);
    // 111111 = 63
    set(internal_array, 32);
    set(internal_array, 33);
    // 11 = 3
    clr(internal_array, 3);
    clr(internal_array, 33);
    // 110111 = 55
    // 01 = 1

    EXPECT_EQ(55, internal_array[0]);
    EXPECT_EQ(1, internal_array[1]);
}

TEST_F(bitSortAlgorithmFixture, test_tstFunction) {
    set(internal_array, 0);
    set(internal_array, 1);
    set(internal_array, 2);
    set(internal_array, 3);
    set(internal_array, 4);
    set(internal_array, 5);
    // 111111 = 63
    set(internal_array, 32);
    set(internal_array, 33);
    // 11 = 3
    clr(internal_array, 3);
    clr(internal_array, 33);

    EXPECT_EQ(2, tst(internal_array, 1));
    EXPECT_EQ(0, tst(internal_array, 3));
    EXPECT_EQ(32, tst(internal_array, 5));
}

TEST_F(bitSortAlgorithmFixture, test_bitCountSort) {
    EXPECT_EQ(9999999, target_array[0]);
    EXPECT_EQ(9999998, target_array[1]);
    EXPECT_EQ(9999997, target_array[2]);
    count_bit_sort(target_array,size_ary,max_val);
    EXPECT_EQ(9000000, target_array[0]);
    EXPECT_EQ(9000001, target_array[1]);
    EXPECT_EQ(9999998, target_array[999998]);
    EXPECT_EQ(9999999, target_array[999999]);
}
