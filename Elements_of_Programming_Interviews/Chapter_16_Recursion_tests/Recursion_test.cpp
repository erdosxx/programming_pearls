#include <gtest/gtest.h>
#include <random>
#include <limits>
#include <unordered_set>
#include <cmath>
#include <string>
#include "tower_hanoi.h"
#include "n-queens.h"

using std::istringstream;
using std::stringstream;
using std::default_random_engine;
using std::random_device;
using std::unique_ptr;
using std::numeric_limits;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::is_sorted;
using std::unordered_set;
using std::max;
using std::cout;
using std::endl;
using std::ostream_iterator;
using std::to_string;

class Ch16_Recursion_Fixture : public ::testing::Test {
private:

protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    Ch16_Recursion_Fixture() : Test() {

    }

    virtual ~Ch16_Recursion_Fixture() {
    }
};

TEST_F(Ch16_Recursion_Fixture, tower_hanoi_Function) {
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 10);
    int n = dis(gen);

    //cout << "n = " << n << endl;
    ComputeTowerHanoi(n);

    int num_steps = ComputeTowerHanoi(4);
    ASSERT_EQ(15, num_steps);

    num_steps = ComputeTowerHanoi(1);
    ASSERT_EQ(1, num_steps);

    num_steps = ComputeTowerHanoi(0);
    ASSERT_EQ(0, num_steps);

    num_steps = ComputeTowerHanoi(10);
    ASSERT_EQ(1023, num_steps);
}

TEST_F(Ch16_Recursion_Fixture, n_queens_Function) {
    auto result = NQueens(2);
    ASSERT_EQ(0, result.size());

    result = NQueens(3);
    ASSERT_EQ(0, result.size());

    result = NQueens(4);
    ASSERT_EQ(2, result.size());

    vector<int> place1 = {1, 3, 0, 2};
    vector<int> place2 = {2, 0, 3, 1};
    ASSERT_TRUE(result[0] == place1 || result[0] == place2);
    ASSERT_TRUE(result[1] == place1 || result[1] == place2);
    ASSERT_NE(result[0], result[1]);

    /*
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 15);
    int n = dis(gen);
    //cout << "n = " << n << endl;
    auto result = NQueens(n);
    for (const vector<int>& vec : result) {
        vector<string> text_rep = ToTextRepresentation(vec);
        for (const string& s : text_rep) {
            cout << s << endl;
        }
        cout << endl;
    }
    */
}
