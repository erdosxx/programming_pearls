#include <gtest/gtest.h>
#include "sort.h"

class sortAlgorithmFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
        set_value_target_array();
        shuffle_array(100000);
    }

    int size_ary=100000;
    int* target_array = new int[size_ary];

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


public:
    sortAlgorithmFixture() : Test() {

    }

    virtual ~sortAlgorithmFixture() {

    }
};

TEST_F(sortAlgorithmFixture, test_insertion1Sort) {
    insertionSort(target_array, size_ary);
    EXPECT_EQ(1, target_array[0]);
    EXPECT_EQ(2, target_array[1]);
    EXPECT_EQ(501, target_array[500]);
    EXPECT_EQ(701, target_array[700]);
    EXPECT_EQ(999, target_array[998]);
    EXPECT_EQ(1000, target_array[999]);
}

TEST_F(sortAlgorithmFixture, test_insertion2Sort) {
    isort2(target_array, size_ary);
    EXPECT_EQ(1, target_array[0]);
    EXPECT_EQ(2, target_array[1]);
    EXPECT_EQ(501, target_array[500]);
    EXPECT_EQ(701, target_array[700]);
    EXPECT_EQ(999, target_array[998]);
    EXPECT_EQ(1000, target_array[999]);
}

TEST_F(sortAlgorithmFixture, test_insertion3Sort) {
    isort3(target_array, size_ary);
    EXPECT_EQ(1, target_array[0]);
    EXPECT_EQ(2, target_array[1]);
    EXPECT_EQ(501, target_array[500]);
    EXPECT_EQ(701, target_array[700]);
    EXPECT_EQ(999, target_array[998]);
    EXPECT_EQ(1000, target_array[999]);
}

TEST_F(sortAlgorithmFixture, test_quick1Sort) {
    qsort1(target_array, 0, size_ary-1);
    EXPECT_EQ(1, target_array[0]);
    EXPECT_EQ(2, target_array[1]);
    EXPECT_EQ(501, target_array[500]);
    EXPECT_EQ(701, target_array[700]);
    EXPECT_EQ(999, target_array[998]);
    EXPECT_EQ(10000, target_array[9999]);
    EXPECT_EQ(100000, target_array[99999]);
}

TEST_F(sortAlgorithmFixture, test_quick2Sort) {
    qsort2(target_array, 0, size_ary-1);
    EXPECT_EQ(1, target_array[0]);
    EXPECT_EQ(2, target_array[1]);
    EXPECT_EQ(501, target_array[500]);
    EXPECT_EQ(701, target_array[700]);
    EXPECT_EQ(999, target_array[998]);
    EXPECT_EQ(10000, target_array[9999]);
    EXPECT_EQ(100000, target_array[99999]);
}

TEST_F(sortAlgorithmFixture, test_quick3Sort) {
    qsort3(target_array, 0, size_ary-1);
    EXPECT_EQ(1, target_array[0]);
    EXPECT_EQ(2, target_array[1]);
    EXPECT_EQ(501, target_array[500]);
    EXPECT_EQ(701, target_array[700]);
    EXPECT_EQ(999, target_array[998]);
    EXPECT_EQ(10000, target_array[9999]);
    EXPECT_EQ(100000, target_array[99999]);
}

TEST_F(sortAlgorithmFixture, test_quick4Sort) {
    qsort4(target_array, 0, size_ary-1, 50);
    isort3(target_array, size_ary);
    EXPECT_EQ(1, target_array[0]);
    EXPECT_EQ(2, target_array[1]);
    EXPECT_EQ(501, target_array[500]);
    EXPECT_EQ(701, target_array[700]);
    EXPECT_EQ(999, target_array[998]);
    EXPECT_EQ(10000, target_array[9999]);
    EXPECT_EQ(100000, target_array[99999]);
}
