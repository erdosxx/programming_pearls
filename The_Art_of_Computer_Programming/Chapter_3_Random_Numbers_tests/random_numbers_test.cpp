#include <gtest/gtest.h>
#include "3_4_2_algorithm_S.h"
#include "3_4_2_Floyd_algorithm.h"

using std::vector;
using std::for_each;
using std::cout;
using std::endl;
using std::move;

using std::default_random_engine;
using std::uniform_int_distribution;

class Random_Numbers_Fixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    Random_Numbers_Fixture() : Test() {

    }

    virtual ~Random_Numbers_Fixture() {
    }
};

TEST_F(Random_Numbers_Fixture, 3_4_2_algorithm_S_Function) {
    int N=10;
    vector<int> A(N);

    // A = 0, 1, 2, 3, ..., n-1
    iota(A.begin(), A.end(),0);

    int n = 8;
    vector<int> result(n);
    result = move(selection_sampling(n, &A));
    auto iter = unique(result.begin(), result.end());
    ASSERT_TRUE(iter == result.end()); // no duplicate.

    /*
    cout << endl;
    for(int i=0; i < n; i++) {
        cout << result[i] <<":";
    }
    cout << endl;
     */
}

TEST_F(Random_Numbers_Fixture, 3_4_2_Floyd_algorithm) {
    int N = 10;
    vector<int> A(N);
    iota(A.begin(), A.end(), 10);
    int n = 8;

    vector<int> result(n);
    result = move(floyd_sampling(n, &A));

    cout << endl;
    for(int i=0; i < n; i++) {
        cout << result[i] <<":";
    }
    cout << endl;

    sort(result.begin(), result.end());
    auto iter = unique(result.begin(), result.end());

    ASSERT_TRUE(iter == result.end());
}

