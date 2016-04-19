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
        set_value_target_array_same();
    }

    int size_ary=1000000;
    int* target_array = new int[size_ary];
    int* target_array2 = new int[size_ary];
    int* search_target_array2 = new int[size_ary];

    int size_ary_same= 100;
    int* target_array_same = new int[size_ary_same];

    void set_value_target_array_same () {
        for(int i=0; i< size_ary_same; i++) {
            target_array_same[i] = i/25;
        }
    }

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

TEST_F(SearchAlgorithmFixture, test_binarysearch1_Function) {
    int test_size = 1000;

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(i, binarysearch1(target_array, test_size, 10*i));
        ASSERT_EQ(-1, binarysearch1(target_array, test_size, 10*i-5));
    }

    ASSERT_EQ(-1, binarysearch1(target_array, test_size, 10*test_size -5));
    ASSERT_EQ(-1, binarysearch1(target_array, test_size, 10*test_size));
}


TEST_F(SearchAlgorithmFixture, test_binarysearch2_Function) {
    int test_size = 1000;

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(i, binarysearch2(target_array, test_size, 10*i));
        ASSERT_EQ(-1, binarysearch2(target_array, test_size, 10*i-5));
    }

    ASSERT_EQ(-1, binarysearch2(target_array, test_size, 10*test_size -5));
    ASSERT_EQ(-1, binarysearch2(target_array, test_size, 10*test_size));
}

TEST_F(SearchAlgorithmFixture, test_binary_search_first_Function) {
    int test_size = 1000;

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(i, binary_search_first(target_array, test_size, 10 * i));
        ASSERT_EQ(-1, binary_search_first(target_array, test_size, 10 * i - 5));
    }

    ASSERT_EQ(-1, binary_search_first(target_array, test_size, 10 * test_size - 5));
    ASSERT_EQ(-1, binary_search_first(target_array, test_size, 10 * test_size));

    ASSERT_EQ(0, binary_search_first(target_array_same, size_ary_same, 0));
    ASSERT_EQ(25, binary_search_first(target_array_same, size_ary_same, 1));
    ASSERT_EQ(50, binary_search_first(target_array_same, size_ary_same, 2));
    ASSERT_EQ(75, binary_search_first(target_array_same, size_ary_same, 3));
}

TEST_F(SearchAlgorithmFixture, test_binary_search_last_Function) {
    int test_size = 1000;

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(i, binary_search_last(target_array, test_size, 10 * i));
        ASSERT_EQ(-1, binary_search_last(target_array, test_size, 10 * i - 5));
    }

    ASSERT_EQ(-1, binary_search_last(target_array, test_size, 10 * test_size - 5));
    ASSERT_EQ(-1, binary_search_last(target_array, test_size, 10 * test_size));

    ASSERT_EQ(24, binary_search_last(target_array_same, size_ary_same, 0));
    ASSERT_EQ(49, binary_search_last(target_array_same, size_ary_same, 1));
    ASSERT_EQ(74, binary_search_last(target_array_same, size_ary_same, 2));
    ASSERT_EQ(99, binary_search_last(target_array_same, size_ary_same, 3));
}

TEST_F(SearchAlgorithmFixture, test_binarysearch4_Function) {
    int test_size = 1000;

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(i, binarysearch4(target_array, test_size, 10*i));
        ASSERT_EQ(-1, binarysearch4(target_array, test_size, 10*i-5));
    }

    ASSERT_EQ(-1, binarysearch4(target_array, test_size, 10*test_size -5));
    ASSERT_EQ(-1, binarysearch4(target_array, test_size, 10*test_size));
}

TEST_F(SearchAlgorithmFixture, test_seqsearch_simple_Function) {
    int test_size = 1000;

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(i, seqsearch_simple(target_array, test_size, 10 * i));
        ASSERT_EQ(-1, seqsearch_simple(target_array, test_size, 10 * i - 5));
    }

    ASSERT_EQ(-1, seqsearch_simple(target_array, test_size, 10 * test_size - 5));
    ASSERT_EQ(-1, seqsearch_simple(target_array, test_size, 10 * test_size));
}

TEST_F(SearchAlgorithmFixture, test_seqsearch_sentinel_Function) {
    int test_size = 1000;

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(i, seqsearch_sentinel(target_array, test_size, 10 * i));
        ASSERT_EQ(-1, seqsearch_sentinel(target_array, test_size, 10 * i - 5));
    }

    ASSERT_EQ(-1, seqsearch_sentinel(target_array, test_size, 10 * test_size - 5));
    ASSERT_EQ(-1, seqsearch_sentinel(target_array, test_size, 10 * test_size));
}

TEST_F(SearchAlgorithmFixture, test_seqsearch_loop_unrolling_Function) {
    int test_size = 1000;

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(i, seqsearch_loop_unrolling(target_array, test_size, 10 * i));
        ASSERT_EQ(-1, seqsearch_loop_unrolling(target_array, test_size, 10 * i - 5));
    }

    ASSERT_EQ(-1, seqsearch_loop_unrolling(target_array, test_size, 10 * test_size - 5));
    ASSERT_EQ(-1, seqsearch_loop_unrolling(target_array, test_size, 10 * test_size));
}

TEST_F(SearchAlgorithmFixture, test_binarysearch1_with_scramble_Function) {
    int test_size = 10000;
    scramble(test_size);

    for (int i = 0; i < test_size; i++) {
        ASSERT_GT(10000, search_target_array2[i]);
    }

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(search_target_array2[i], binarysearch1(target_array2, test_size, search_target_array2[i]));
    }
}

TEST_F(SearchAlgorithmFixture, test_binarysearch2_with_scramble_Function) {
    int test_size = 10000;
    scramble(test_size);

    for (int i = 0; i < test_size; i++) {
        ASSERT_GT(10000, search_target_array2[i]);
    }

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(search_target_array2[i], binarysearch2(target_array2, test_size, search_target_array2[i]));
    }
}

TEST_F(SearchAlgorithmFixture, test_binarysearch3_with_scramble_Function) {
    int test_size = 10000;
    scramble(test_size);

    for (int i = 0; i < test_size; i++) {
        ASSERT_GT(10000, search_target_array2[i]);
    }

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(search_target_array2[i], binary_search_first(target_array2, test_size, search_target_array2[i]));
    }
}

TEST_F(SearchAlgorithmFixture, test_binarysearch4_with_scramble_Function) {
    int test_size = 10000;
    scramble(test_size);

    for (int i = 0; i < test_size; i++) {
        ASSERT_GT(10000, search_target_array2[i]);
    }

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(search_target_array2[i], binarysearch4(target_array2, test_size, search_target_array2[i]));
    }
}

TEST_F(SearchAlgorithmFixture, test_seqsearch_simple_with_scramble_Function) {
    int test_size = 10000;
    scramble(test_size);

    for (int i = 0; i < test_size; i++) {
        ASSERT_GT(10000, search_target_array2[i]);
    }

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(search_target_array2[i], seqsearch_simple(target_array2, test_size, search_target_array2[i]));
    }
}

TEST_F(SearchAlgorithmFixture, test_seqsearch_sentinel_with_scramble_Function) {
    int test_size = 10000;
    scramble(test_size);

    for (int i = 0; i < test_size; i++) {
        ASSERT_GT(10000, search_target_array2[i]);
    }

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(search_target_array2[i], seqsearch_sentinel(target_array2, test_size, search_target_array2[i]));
    }
}

TEST_F(SearchAlgorithmFixture, test_seqsearch_loop_unrolling_with_scramble_Function) {
    int test_size = 10000;
    scramble(test_size);

    for (int i = 0; i < test_size; i++) {
        ASSERT_GT(10000, search_target_array2[i]);
    }

    for (int i = 0; i < test_size; i++) {
        ASSERT_EQ(search_target_array2[i], seqsearch_loop_unrolling(target_array2, test_size, search_target_array2[i]));
    }
}
