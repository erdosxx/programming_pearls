#include <iostream>
#include "column8.h"
#include <gtest/gtest.h>

using namespace std;

void swap(int x[], int i, int j) {
    int t = x[i];
    x[i] = x[j];
    x[j] = t;
}

class maxSumFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    maxSumFixture() : Test() {
    }

    virtual ~maxSumFixture() {

    }
};

TEST_F(maxSumFixture, case1_maxsum_Function) {
    int array1[] = {0,0,0,0,0,0,0,0,0,0};

    ASSERT_EQ(0, maxsum_simple(array1, 10));
    ASSERT_EQ(0, maxsum_simple2(array1, 10));
    ASSERT_EQ(0, maxsum_cumarr(array1, 10));
    ASSERT_EQ(0, maxsum_divide_n_conquer(array1, 10));
    ASSERT_EQ(0, maxsum_fast(array1, 10));
    ASSERT_EQ(0, maxsum_fast2(array1, 10));
    ASSERT_EQ(0, maxsum_fast3(array1, 10));
    ASSERT_EQ(0, maxsum_dnc_linear(array1, 10));
}

TEST_F(maxSumFixture, case2_maxsum_Function) {
    int array2[] = {1,1,1,1,1,1,1,1,1,1};

    ASSERT_EQ(10, maxsum_simple(array2, 10));
    ASSERT_EQ(10, maxsum_simple2(array2, 10));
    ASSERT_EQ(10, maxsum_cumarr(array2, 10));
    ASSERT_EQ(10, maxsum_divide_n_conquer(array2, 10));
    ASSERT_EQ(10, maxsum_fast(array2, 10));
    ASSERT_EQ(10, maxsum_fast2(array2, 10));
    ASSERT_EQ(10, maxsum_fast3(array2, 10));
    ASSERT_EQ(10, maxsum_dnc_linear(array2, 10));
}

TEST_F(maxSumFixture, case3_maxsum_Function) {
    int array3[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

    ASSERT_EQ(0, maxsum_simple(array3, 10));
    ASSERT_EQ(0, maxsum_simple2(array3, 10));
    ASSERT_EQ(0, maxsum_cumarr(array3, 10));
    ASSERT_EQ(0, maxsum_divide_n_conquer(array3, 10));
    ASSERT_EQ(0, maxsum_fast(array3, 10));
    ASSERT_EQ(0, maxsum_fast2(array3, 10));
    ASSERT_EQ(0, maxsum_fast3(array3, 10));
    ASSERT_EQ(0, maxsum_dnc_linear(array3, 10));
}

TEST_F(maxSumFixture, case4_maxsum_Function) {
    int array4[] = {31,-41,59,26,-53,58,97,-93,-23,84};

    ASSERT_EQ(187, maxsum_simple(array4, 10));
    ASSERT_EQ(187, maxsum_simple2(array4, 10));
    ASSERT_EQ(187, maxsum_cumarr(array4, 10));
    ASSERT_EQ(187, maxsum_divide_n_conquer(array4, 10));
    ASSERT_EQ(187, maxsum_fast(array4, 10));
    ASSERT_EQ(187, maxsum_fast2(array4, 10));
    ASSERT_EQ(187, maxsum_fast3(array4, 10));
    ASSERT_EQ(187, maxsum_dnc_linear(array4, 10));
}

