#include <iostream>
#include "column13.h"
#include <gtest/gtest.h>

using namespace std;

void swap(int x[], int i, int j) {
    int t = x[i];
    x[i] = x[j];
    x[j] = t;
}

class SearchingFixture : public ::testing::Test {
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
    SearchingFixture() : Test() {
    }

    virtual ~SearchingFixture() {

    }
};

TEST_F(SearchingFixture, IntSetSTL_Function) {
    IntSetSTL atest = IntSetSTL(size_ary, 100000);
    atest.insert(10);
    atest.insert(20);
    atest.insert(20);
    atest.insert(30);
    ASSERT_EQ(3, atest.size());
    atest.report(target_array);
    ASSERT_EQ(10, target_array[0]);
    ASSERT_EQ(20, target_array[1]);
    ASSERT_EQ(30, target_array[2]);
}

TEST_F(SearchingFixture, IntSetBitVec_Function) {
    IntSetBitVec atest = IntSetBitVec(size_ary, 100000);
    atest.insert(10);
    atest.insert(20);
    atest.insert(20);
    atest.insert(30);
    ASSERT_EQ(3, atest.size());
    atest.report(target_array);
    ASSERT_EQ(10, target_array[0]);
    ASSERT_EQ(20, target_array[1]);
    ASSERT_EQ(30, target_array[2]);
}

TEST_F(SearchingFixture, IntSetArr_Function) {
    IntSetArr atest = IntSetArr(size_ary, 100000);
    atest.insert(10);
    atest.insert(20);
    atest.insert(20);
    atest.insert(30);
    atest.insert(15);
    ASSERT_EQ(4, atest.size());
    atest.report(target_array);
    ASSERT_EQ(10, target_array[0]);
    ASSERT_EQ(15, target_array[1]);
    ASSERT_EQ(20, target_array[2]);
    ASSERT_EQ(30, target_array[3]);
}

TEST_F(SearchingFixture, IntSetList_Function) {
    IntSetList atest = IntSetList(size_ary, 100000);
    atest.insert_recursive(10);
    ASSERT_EQ(1, atest.size());
    atest.insert_non_recursive(20);
    ASSERT_EQ(2, atest.size());
    atest.insert_non_recursive_with_pointer(20);
    ASSERT_EQ(2, atest.size());
    atest.insert_non_recursive(30);
    ASSERT_EQ(3, atest.size());
    atest.insert_recursive(15);
    ASSERT_EQ(4, atest.size());
    atest.report(target_array);
    ASSERT_EQ(10, target_array[0]);
    ASSERT_EQ(15, target_array[1]);
    ASSERT_EQ(20, target_array[2]);
    ASSERT_EQ(30, target_array[3]);
}

TEST_F(SearchingFixture, IntSetList2_Function) {
    IntSetList_with_allocator atest = IntSetList_with_allocator(size_ary, 100000);
    atest.insert(10);
    ASSERT_EQ(1, atest.size());
    atest.insert(20);
    ASSERT_EQ(2, atest.size());
    atest.insert(20);
    ASSERT_EQ(2, atest.size());
    atest.insert(30);
    ASSERT_EQ(3, atest.size());
    atest.insert(15);
    ASSERT_EQ(4, atest.size());
    atest.report(target_array);
    ASSERT_EQ(10, target_array[0]);
    ASSERT_EQ(15, target_array[1]);
    ASSERT_EQ(20, target_array[2]);
    ASSERT_EQ(30, target_array[3]);
}

TEST_F(SearchingFixture, IntSetBST_Function) {
    IntSetBST atest = IntSetBST(size_ary, 100000);
    atest.insert(10);
    ASSERT_EQ(1, atest.size());
    atest.insert(20);
    ASSERT_EQ(2, atest.size());
    atest.insert(20);
    ASSERT_EQ(2, atest.size());
    atest.insert(30);
    ASSERT_EQ(3, atest.size());
    atest.insert(15);
    ASSERT_EQ(4, atest.size());
    atest.report(target_array);
    ASSERT_EQ(10, target_array[0]);
    ASSERT_EQ(15, target_array[1]);
    ASSERT_EQ(20, target_array[2]);
    ASSERT_EQ(30, target_array[3]);
}

TEST_F(SearchingFixture, IntSetBST2_Function) {
    IntSetBST_with_allocator atest = IntSetBST_with_allocator(size_ary, 100000);
    atest.insert1(10);
    ASSERT_EQ(1, atest.size());
    atest.insert(20);
    ASSERT_EQ(2, atest.size());
    atest.insert1(20);
    ASSERT_EQ(2, atest.size());
    atest.insert(30);
    ASSERT_EQ(3, atest.size());
    atest.insert1(15);
    ASSERT_EQ(4, atest.size());
    atest.report(target_array);
    ASSERT_EQ(10, target_array[0]);
    ASSERT_EQ(15, target_array[1]);
    ASSERT_EQ(20, target_array[2]);
    ASSERT_EQ(30, target_array[3]);
}

TEST_F(SearchingFixture, IntSetBins_Function) {
    IntSetBins atest = IntSetBins(size_ary, 100000);
    atest.insert(10);
    ASSERT_EQ(1, atest.size());
    atest.insert(20);
    ASSERT_EQ(2, atest.size());
    atest.insert(20);
    ASSERT_EQ(2, atest.size());
    atest.insert(30);
    ASSERT_EQ(3, atest.size());
    atest.insert(15);
    ASSERT_EQ(4, atest.size());
    atest.report(target_array);
    ASSERT_EQ(10, target_array[0]);
    ASSERT_EQ(15, target_array[1]);
    ASSERT_EQ(20, target_array[2]);
    ASSERT_EQ(30, target_array[3]);
}

TEST_F(SearchingFixture, IntSetBins2_Function) {
    IntSetBins_with_allocator atest = IntSetBins_with_allocator(size_ary, 100000);
    atest.insert_recursive(10);
    ASSERT_EQ(1, atest.size());
    atest.insert(20);
    ASSERT_EQ(2, atest.size());
    atest.insert_recursive(20);
    ASSERT_EQ(2, atest.size());
    atest.insert(30);
    ASSERT_EQ(3, atest.size());
    atest.insert_recursive(15);
    ASSERT_EQ(4, atest.size());
    atest.report(target_array);
    ASSERT_EQ(10, target_array[0]);
    ASSERT_EQ(15, target_array[1]);
    ASSERT_EQ(20, target_array[2]);
    ASSERT_EQ(30, target_array[3]);
}


