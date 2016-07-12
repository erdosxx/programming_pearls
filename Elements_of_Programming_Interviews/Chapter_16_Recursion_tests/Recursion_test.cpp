#include <gtest/gtest.h>
#include <random>
#include <limits>
#include <unordered_set>
#include <cmath>
#include <string>
#include "tower_hanoi.h"
#include "n-queens.h"
#include "permutations.h"
#include "permutations-alternative.h"
#include "Power_set.h"
#include "Power_set_alternative.h"
#include "combinations.h"

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

TEST_F(Ch16_Recursion_Fixture, permutations_Function) {
    vector<int> A = {1, 2, 3};
    auto result = Permutations(A);
    ASSERT_EQ(result.size(), 6);
    vector<vector<int>> golden_result = {{1, 2, 3}, {1, 3, 2}, {2, 1, 3},
                                         {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};
    for (size_t i = 0; i < 6; ++i) {
        ASSERT_TRUE(equal(result[i].begin(), result[i].end(), golden_result[i].begin(),
                     golden_result[i].end()));
    }

    /*
    default_random_engine gen((random_device())());
    uniform_int_distribution<size_t> dis(1, 10);
    size_t n = dis(gen);

    vector<int> A(n);
    iota(A.begin(), A.end(), 0);
    auto result = Permutations(A);
    cout << "n = " << n << endl;
    for (const vector<int>& vec : result) {
        for (int a : vec) {
            cout << a << " ";
        }
        cout << endl;
    }
     */
}

TEST_F(Ch16_Recursion_Fixture, permutations_alt_Function) {
    vector<int> A = {0, 1, 2};
    auto result = alt::Permutations(A);
    ASSERT_EQ(result.size(), 6);
    vector<vector<int>> golden_result = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2},
                                         {1, 2, 0}, {2, 1, 0}, {2, 0, 1}};
    for (int i = 0; i < 6; ++i) {
        ASSERT_TRUE(equal(result[i].begin(), result[i].end(), golden_result[i].begin(),
                     golden_result[i].end()));
    }

    /*
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 10);
    size_t n = dis(gen);

    vector<int> A(n);
    iota(A.begin(), A.end(), 0);
    auto result = Permutations(A);
    cout << "n = " << n << endl;
    for (const auto &vec : result) {
        for (int a : vec) {
            cout << a << " ";
        }
        cout << endl;
    }
     */
}

TEST_F(Ch16_Recursion_Fixture, Power_set_Function) {
    vector<vector<int>> golden_result = {{},  {0},    {1},    {0, 1},
                                         {2}, {0, 2}, {1, 2}, {0, 1, 2}};
    auto result = GeneratePowerSet({0, 1, 2});
    ASSERT_TRUE(equal(result.begin(), result.end(), golden_result.begin(),
                 golden_result.end()));

    /*
    vector<int> S;
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 10);
    S.resize(dis(gen));
    iota(S.begin(), S.end(), 0);

    auto power_set = GeneratePowerSet(S);
    for (const vector<int>& one_set : power_set) {
        copy(one_set.begin(), one_set.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
     */
}

TEST_F(Ch16_Recursion_Fixture, Power_set_alt_Function) {
    vector<vector<int>> golden_result = {{0, 1, 2}, {0, 1}, {0, 2}, {0},
                                         {1, 2},    {1},    {2},    {}};
    auto result = alt::GeneratePowerSet({0, 1, 2});
    ASSERT_TRUE(equal(result.begin(), result.end(), golden_result.begin(),
                 golden_result.end()));

    /*
    vector<int> S;
    if (argc >= 2) {
        for (int i = 1; i < argc; ++i) {
            S.emplace_back(atoi(argv[i]));
        }
    } else {
        default_random_engine gen((random_device())());
        uniform_int_distribution<int> dis(1, 10);
        S.resize(dis(gen));
        iota(S.begin(), S.end(), 0);
    }
    auto power_set = GeneratePowerSet(S);
    for (const vector<int>& one_set : power_set) {
        copy(one_set.begin(), one_set.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
     */
}

TEST_F(Ch16_Recursion_Fixture, combinations_Function) {
    auto result = Combinations(4, 2);
    vector<vector<int>> golden_result = {{1, 2}, {1, 3}, {1, 4},
                                         {2, 3}, {2, 4}, {3, 4}};
    ASSERT_TRUE(equal(result.begin(), result.end(), golden_result.begin(),
                 golden_result.end()));

    /*
    default_random_engine gen((random_device())());
    int n, k;
    if (argc == 3) {
        n = stoi(argv[1]), k = stoi(argv[2]);
    } else {
        uniform_int_distribution<int> n_dis(1, 10);
        n = n_dis(gen);
        uniform_int_distribution<int> k_dis(0, n);
        k = k_dis(gen);
    }
    auto result = Combinations(n, k);
    cout << "n = " << n << ", k = " << k << endl;
    for (const vector<int>& vec : result) {
        for (int a : vec) {
            cout << a << " ";
        }
        cout << endl;
    }
     */
}
