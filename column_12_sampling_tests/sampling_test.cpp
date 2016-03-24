#include <iostream>
#include "column12.h"
#include <gtest/gtest.h>

using namespace std;

void swap(int x[], int i, int j) {
    int t = x[i];
    x[i] = x[j];
    x[j] = t;
}

class SamplingFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    int size_ary=100000;
    int* target_array = new int[size_ary];

    int check_increate_array_without_duplicate(int* x, int n) {
        for(int i=1; i < n; i++){
            if (x[i] - x[i-1] <= 0)
                return 0;  // test fail
        }
        return 1; // test pass
    }

public:
    SamplingFixture() : Test() {
    }

    virtual ~SamplingFixture() {

    }
};

TEST_F(SamplingFixture, genknuth_Function) {
    int sample_size = 99000;
    genknuth(target_array, sample_size, size_ary);
    ASSERT_EQ(1, check_increate_array_without_duplicate(target_array, sample_size));
}

TEST_F(SamplingFixture, gensets_Function) {
    int sample_size = 99000;
    gensets(target_array, sample_size, size_ary);
    ASSERT_EQ(1, check_increate_array_without_duplicate(target_array, sample_size));
}

TEST_F(SamplingFixture, genshuf_Function) {
    int sample_size = 99000;
    genshuf(target_array, sample_size, size_ary);
    ASSERT_EQ(1, check_increate_array_without_duplicate(target_array, sample_size));
}

TEST_F(SamplingFixture, genfloyd_Function) {
    int sample_size = 99000;
    genfloyd(target_array, sample_size, size_ary);
    ASSERT_EQ(1, check_increate_array_without_duplicate(target_array, sample_size));
}
