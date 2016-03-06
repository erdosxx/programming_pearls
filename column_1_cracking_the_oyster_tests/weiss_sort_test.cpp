#include <iostream>
#include "sort_weiss.h"
#include <vector>
#include <string>
#include "UniformRandom.h"
#include <gtest/gtest.h>

using namespace std;

string checkSort( const vector<string> & a ) {
    for( int i = 0; i < a.size( ); ++i )
        if( a[i].length( ) != i )
            return "fail: " + to_string(i);
    return "success"; // success
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

    int max_val =10000000;
    const int BITSPERWORD=32;
    int size_internal_ary= 1 + max_val/BITSPERWORD;

    int*internal_array = new int[size_internal_ary];

    const int NUM_ITEMS = 1000;
    // vector<string> a_str(NUM_ITEMS); is wrong.
    // see http://stackoverflow.com/questions/21040977/boost-vector-size-constructor-not-working
    vector<string> a_str;        // This input adds factor of N to running time

    virtual void SetUp() {
        set_value_target_array();
        shuffle_array(100000);
        init_string_array();
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

    void init_string_array(){
        for ( int i = 1; i < a_str.size(); ++i )  // but we want to test std::move logic
            a_str[i] = a_str[i - 1] + 'a';
    }

public:
    WeissSortAlgorithmFixture() : Test(), a_str(NUM_ITEMS) {
    }

    virtual ~WeissSortAlgorithmFixture() {

    }
};

TEST_F(WeissSortAlgorithmFixture, test_init_string_array_Function) {
    ASSERT_STREQ("", a_str[0].c_str() );
    ASSERT_STREQ("a", a_str[1].c_str() );
    ASSERT_STREQ("aa", a_str[2].c_str() );
    ASSERT_STREQ("aaa", a_str[3].c_str() );
    ASSERT_STREQ("aaaa", a_str[4].c_str() );
}

TEST_F(WeissSortAlgorithmFixture, test_mergeSort_Function) {
    permute(a_str);
    mergeSort(a_str);
    //ASSERT_EQ(-1, checkSort(a_str));
    ASSERT_STREQ("success", checkSort(a_str).c_str());
}
