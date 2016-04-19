#include <iostream>
#include "sort_weiss.h"
#include "UniformRandom.h"
#include <gtest/gtest.h>

using namespace std;

string check_sort_for_a_str(const vector<string> &a) {
    for( int i = 0; i < a.size( ); ++i )
        if( a[i].length( ) != i )
            return "fail: " + to_string(i);
    return "Success"; // success
}

string check_sort_for_int_vec(const vector<int> &a) {
    for( int i = 0; i < a.size( ); ++i )
        if( a[i] != i )
            return "fail: " + to_string(i);
    return "Success"; // success
}

template <typename AnyType>
void permute( vector<AnyType> & a ) {
    static UniformRandom r;

    for( int j = 1; j < a.size( ); ++j )
        swap( a[j], a[r.nextInt(0, j)] );
}

void swap(int x[], int i, int j) {
    int t = x[i];
    x[i] = x[j];
    x[j] = t;
}

class WeissSortAlgorithmFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    enum {NUM_ITEMS=1000};
    // vector<string> a_str(NUM_ITEMS); is wrong.
    // see http://stackoverflow.com/questions/21040977/boost-vector-size-constructor-not-working
    vector<string> a_str_vec;        // This input adds factor of N to running time

    virtual void SetUp() {
        init_string_array();
        init_int_array();
    }

    void init_string_array(){
        for (int i = 1; i < a_str_vec.size(); ++i )  // but we want to test std::move logic
            a_str_vec[i] = a_str_vec[i - 1] + 'a';
    }

    vector<int> int_vec;

    void init_int_array(){
        for (int i=0; i < int_vec.size(); i++) {
            int_vec[i]= i;
        }
    }

public:
    WeissSortAlgorithmFixture() : Test(), a_str_vec(NUM_ITEMS), int_vec(NUM_ITEMS) {
    }

    virtual ~WeissSortAlgorithmFixture() {

    }
};

TEST_F(WeissSortAlgorithmFixture, test_init_string_array_Function) {
    ASSERT_STREQ("", a_str_vec[0].c_str() );
    ASSERT_STREQ("a", a_str_vec[1].c_str() );
    ASSERT_STREQ("aa", a_str_vec[2].c_str() );
    ASSERT_STREQ("aaa", a_str_vec[3].c_str() );
    ASSERT_STREQ("aaaa", a_str_vec[4].c_str() );
}

TEST_F(WeissSortAlgorithmFixture, test_insertionSort_Function) {
    permute(int_vec);
    insertionSort(int_vec);
    ASSERT_EQ(0, int_vec[0]);
    ASSERT_EQ(1, int_vec[1]);
    ASSERT_EQ(500, int_vec[500]);
    ASSERT_EQ(998, int_vec[998]);
    ASSERT_EQ(999, int_vec[999]);
    ASSERT_STREQ("Success", check_sort_for_int_vec(int_vec).c_str());
}

TEST_F(WeissSortAlgorithmFixture, test_insertionSort_param_version_Function) {
    permute(int_vec);
    insertionSort(int_vec, 0, NUM_ITEMS-1);
    ASSERT_EQ(0, int_vec[0]);
    ASSERT_EQ(1, int_vec[1]);
    ASSERT_EQ(500, int_vec[500]);
    ASSERT_EQ(998, int_vec[998]);
    ASSERT_EQ(999, int_vec[999]);
    ASSERT_STREQ("Success", check_sort_for_int_vec(int_vec).c_str());
}

TEST_F(WeissSortAlgorithmFixture, test_shellSort_Function) {
    permute(int_vec);
    shellsort(int_vec);
    ASSERT_EQ(0, int_vec[0]);
    ASSERT_EQ(1, int_vec[1]);
    ASSERT_EQ(500, int_vec[500]);
    ASSERT_EQ(998, int_vec[998]);
    ASSERT_EQ(999, int_vec[999]);
    ASSERT_STREQ("Success", check_sort_for_int_vec(int_vec).c_str());
}

TEST_F(WeissSortAlgorithmFixture, test_heapSort_Function) {
    permute(int_vec);
    heapsort(int_vec);
    ASSERT_EQ(0, int_vec[0]);
    ASSERT_EQ(1, int_vec[1]);
    ASSERT_EQ(500, int_vec[500]);
    ASSERT_EQ(998, int_vec[998]);
    ASSERT_EQ(999, int_vec[999]);
    ASSERT_STREQ("Success", check_sort_for_int_vec(int_vec).c_str());
}

TEST_F(WeissSortAlgorithmFixture, test_mergeSort_Function) {
    permute(a_str_vec);
    mergeSort(a_str_vec);
    //ASSERT_EQ(-1, checkSort(a_str));
    ASSERT_STREQ("Success", check_sort_for_a_str(a_str_vec).c_str());
}

TEST_F(WeissSortAlgorithmFixture, test_QuickSort_Function) {
    permute(int_vec);
    quicksort(int_vec);
    //ASSERT_EQ(-1, checkSort(a_str));
    ASSERT_STREQ("Success", check_sort_for_a_str(a_str_vec).c_str());
}

TEST_F(WeissSortAlgorithmFixture, test_QuickSelect_Function) {
    permute(int_vec);
    quickSelect(int_vec, 500);
    //ASSERT_EQ(-1, checkSort(a_str));
    ASSERT_EQ(499, int_vec[499]);
}
