#include <iostream>
#include "column5.h"
#include <gtest/gtest.h>

using namespace std;

void swap(int x[], int i, int j) {
    int t = x[i];
    x[i] = x[j];
    x[j] = t;
}

class SearchAlgorithmFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
        set_value_target_array();
    }

    int size_ary=1000000;
    int* target_array = new int[size_ary];
    int* target_array2 = new int[size_ary];
    int* search_target_array2 = new int[size_ary];

    void set_value_target_array () {
        for(int i=0; i< size_ary; i++) {
            target_array[i] = 10*i;
            target_array2[i] = i;
            search_target_array2[i] = i;
        }
    }

    void scramble(int n) {
        int t;
        int i, j;
        for (i = n-1; i > 0; i--) {
            //j = (RAND_MAX*rand() + rand()) % (i + 1);
            j = rand() % (i + 1);
            swap(search_target_array2, i, j);
        }
    }

public:
    SearchAlgorithmFixture() : Test() {
    }

    virtual ~SearchAlgorithmFixture() {

    }
};

TEST_F(SearchAlgorithmFixture, test_binerysearch1_Function) {
    int test_size = 1000;

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(i, binarysearch1(target_array, test_size, 10*i));
        ASSERT_EQ(-1, binarysearch1(target_array, test_size, 10*i-5));
    }

    ASSERT_EQ(-1, binarysearch1(target_array, test_size, 10*test_size -5));
    ASSERT_EQ(-1, binarysearch1(target_array, test_size, 10*test_size));
}


TEST_F(SearchAlgorithmFixture, test_binerysearch2_Function) {
    int test_size = 1000;

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(i, binarysearch2(target_array, test_size, 10*i));
        ASSERT_EQ(-1, binarysearch2(target_array, test_size, 10*i-5));
    }

    ASSERT_EQ(-1, binarysearch2(target_array, test_size, 10*test_size -5));
    ASSERT_EQ(-1, binarysearch2(target_array, test_size, 10*test_size));
}

TEST_F(SearchAlgorithmFixture, test_binerysearch3_Function) {
    int test_size = 1000;

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(i, binarysearch3(target_array, test_size, 10*i));
        ASSERT_EQ(-1, binarysearch3(target_array, test_size, 10*i-5));
    }

    ASSERT_EQ(-1, binarysearch3(target_array, test_size, 10*test_size -5));
    ASSERT_EQ(-1, binarysearch3(target_array, test_size, 10*test_size));
}

TEST_F(SearchAlgorithmFixture, test_binerysearch4_Function) {
    int test_size = 1000;

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(i, binarysearch4(target_array, test_size, 10*i));
        ASSERT_EQ(-1, binarysearch4(target_array, test_size, 10*i-5));
    }

    ASSERT_EQ(-1, binarysearch4(target_array, test_size, 10*test_size -5));
    ASSERT_EQ(-1, binarysearch4(target_array, test_size, 10*test_size));
}

TEST_F(SearchAlgorithmFixture, test_seqsearch1_Function) {
    int test_size = 1000;

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(i, seqsearch1(target_array, test_size, 10*i));
        ASSERT_EQ(-1, seqsearch1(target_array, test_size, 10*i-5));
    }

    ASSERT_EQ(-1, seqsearch1(target_array, test_size, 10*test_size -5));
    ASSERT_EQ(-1, seqsearch1(target_array, test_size, 10*test_size));
}

TEST_F(SearchAlgorithmFixture, test_seqsearch2_Function) {
    int test_size = 1000;

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(i, seqsearch2(target_array, test_size, 10*i));
        ASSERT_EQ(-1, seqsearch2(target_array, test_size, 10*i-5));
    }

    ASSERT_EQ(-1, seqsearch2(target_array, test_size, 10*test_size -5));
    ASSERT_EQ(-1, seqsearch2(target_array, test_size, 10*test_size));
}

TEST_F(SearchAlgorithmFixture, test_seqsearch3_Function) {
    int test_size = 1000;

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(i, seqsearch3(target_array, test_size, 10*i));
        ASSERT_EQ(-1, seqsearch3(target_array, test_size, 10*i-5));
    }

    ASSERT_EQ(-1, seqsearch3(target_array, test_size, 10*test_size -5));
    ASSERT_EQ(-1, seqsearch3(target_array, test_size, 10*test_size));
}

TEST_F(SearchAlgorithmFixture, test_binerysearch1_with_scramble_Function) {
    int test_size = 10000;
    scramble(test_size);

    for (int i = 0; i < test_size; i++) {
        ASSERT_GT(10000, search_target_array2[i]);
    }

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(search_target_array2[i], binarysearch1(target_array2, test_size, search_target_array2[i]));
    }
}

TEST_F(SearchAlgorithmFixture, test_binerysearch2_with_scramble_Function) {
    int test_size = 10000;
    scramble(test_size);

    for (int i = 0; i < test_size; i++) {
        ASSERT_GT(10000, search_target_array2[i]);
    }

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(search_target_array2[i], binarysearch2(target_array2, test_size, search_target_array2[i]));
    }
}

TEST_F(SearchAlgorithmFixture, test_binerysearch3_with_scramble_Function) {
    int test_size = 10000;
    scramble(test_size);

    for (int i = 0; i < test_size; i++) {
        ASSERT_GT(10000, search_target_array2[i]);
    }

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(search_target_array2[i], binarysearch3(target_array2, test_size, search_target_array2[i]));
    }
}

TEST_F(SearchAlgorithmFixture, test_binerysearch4_with_scramble_Function) {
    int test_size = 10000;
    scramble(test_size);

    for (int i = 0; i < test_size; i++) {
        ASSERT_GT(10000, search_target_array2[i]);
    }

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(search_target_array2[i], binarysearch4(target_array2, test_size, search_target_array2[i]));
    }
}

TEST_F(SearchAlgorithmFixture, test_seqsearch1_with_scramble_Function) {
    int test_size = 10000;
    scramble(test_size);

    for (int i = 0; i < test_size; i++) {
        ASSERT_GT(10000, search_target_array2[i]);
    }

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(search_target_array2[i], seqsearch1(target_array2, test_size, search_target_array2[i]));
    }
}

TEST_F(SearchAlgorithmFixture, test_seqsearch2_with_scramble_Function) {
    int test_size = 10000;
    scramble(test_size);

    for (int i = 0; i < test_size; i++) {
        ASSERT_GT(10000, search_target_array2[i]);
    }

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(search_target_array2[i], seqsearch2(target_array2, test_size, search_target_array2[i]));
    }
}

TEST_F(SearchAlgorithmFixture, test_seqsearch3_with_scramble_Function) {
    int test_size = 10000;
    scramble(test_size);

    for (int i = 0; i < test_size; i++) {
        ASSERT_GT(10000, search_target_array2[i]);
    }

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(search_target_array2[i], seqsearch3(target_array2, test_size, search_target_array2[i]));
    }
}
