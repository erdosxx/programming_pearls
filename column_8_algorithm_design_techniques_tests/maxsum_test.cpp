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

    ASSERT_EQ(0, alg1(array1,10));
    ASSERT_EQ(0, alg2(array1,10));
    ASSERT_EQ(0, alg2b(array1,10));
    ASSERT_EQ(0, alg3(array1,10));
    ASSERT_EQ(0, alg4(array1,10));
    ASSERT_EQ(0, alg4b(array1,10));
    ASSERT_EQ(0, alg4c(array1,10));
}

TEST_F(maxSumFixture, case2_maxsum_Function) {
    int array2[] = {1,1,1,1,1,1,1,1,1,1};

    ASSERT_EQ(10, alg1(array2,10));
    ASSERT_EQ(10, alg2(array2,10));
    ASSERT_EQ(10, alg2b(array2,10));
    ASSERT_EQ(10, alg3(array2,10));
    ASSERT_EQ(10, alg4(array2,10));
    ASSERT_EQ(10, alg4b(array2,10));
    ASSERT_EQ(10, alg4c(array2,10));
}

TEST_F(maxSumFixture, case3_maxsum_Function) {
    int array3[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

    ASSERT_EQ(0, alg1(array3,10));
    ASSERT_EQ(0, alg2(array3,10));
    ASSERT_EQ(0, alg2b(array3,10));
    ASSERT_EQ(0, alg3(array3,10));
    ASSERT_EQ(0, alg4(array3,10));
    ASSERT_EQ(0, alg4b(array3,10));
    ASSERT_EQ(0, alg4c(array3,10));
}

TEST_F(maxSumFixture, case4_maxsum_Function) {
    int array4[] = {31,-41,59,26,-53,58,97,-93,-23,84};

    ASSERT_EQ(187, alg1(array4,10));
    ASSERT_EQ(187, alg2(array4,10));
    ASSERT_EQ(187, alg2b(array4,10));
    ASSERT_EQ(187, alg3(array4,10));
    ASSERT_EQ(187, alg4(array4,10));
    ASSERT_EQ(187, alg4b(array4,10));
    ASSERT_EQ(187, alg4c(array4,10));
}

