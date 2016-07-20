#include <gtest/gtest.h>
#include <random>
#include <limits>
#include <unordered_set>
#include <cmath>
#include <string>
#include <bitset>
#include "fibonacci.h"
#include "Max-sum_subarray.h"
#include "Score_combination.h"

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
using std::bitset;

class Ch17_DP_Fixture : public ::testing::Test {
private:

protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    void CheckMaxSum(const vector<int>& A, int max_sum);

    int p_17_1_CheckAnswer(int total_score, const vector<int>& score_ways);

public:
    Ch17_DP_Fixture() : Test() {

    }

    virtual ~Ch17_DP_Fixture() {
    }
};

int Ch17_DP_Fixture::p_17_1_CheckAnswer(int total_score, const vector<int>& score_ways) {
    vector<int> combinations(total_score + 1, 0);
    combinations[0] = 1;  // One way to reach 0.

    for (int score : score_ways) {
        for (int j = score; j <= total_score; ++j) {
            combinations[j] += combinations[j - score];
        }
    }
    return combinations[total_score];
}

void Ch17_DP_Fixture::CheckMaxSum(const vector<int>& A, int max_sum) {
    for (int i = 0; i < A.size(); ++i) {
        int sum = 0;
        for (int j = i; j < A.size(); ++j) {
            sum += A[j];
            ASSERT_LE(sum, max_sum);
        }
    }
}

TEST_F(Ch17_DP_Fixture, Fibonacci_Function) {
    ASSERT_EQ(Fibonacci(10), 55);
    ASSERT_EQ(Fibonacci(0), 0);
    ASSERT_EQ(Fibonacci(1), 1);
    ASSERT_EQ(Fibonacci(16), 987);
    ASSERT_EQ(Fibonacci(40), 102334155);
}

TEST_F(Ch17_DP_Fixture, max_sum_subarray_Function) {
    vector<int> B = {1};
    int max_sum = FindMaximumSubarray(B);
    CheckMaxSum(B, max_sum);
    B = {-5};
    max_sum = FindMaximumSubarray(B);
    CheckMaxSum(B, max_sum);
    B = {0};
    max_sum = FindMaximumSubarray(B);
    CheckMaxSum(B, max_sum);
    B = {0, 0};
    max_sum = FindMaximumSubarray(B);
    CheckMaxSum(B, max_sum);
    B = {0, 0, 0};
    max_sum = FindMaximumSubarray(B);
    CheckMaxSum(B, max_sum);
    B = {0, -5, 0};
    max_sum = FindMaximumSubarray(B);
    CheckMaxSum(B, max_sum);
    B = {-2, -1};
    max_sum = FindMaximumSubarray(B);
    CheckMaxSum(B, max_sum);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        vector<int> A;
        uniform_int_distribution<int> dis(1, 1000);
        A = RandVector<int>(dis(gen));

        int max_sum = FindMaximumSubarray(A);
        CheckMaxSum(A, max_sum);
    }
}

TEST_F(Ch17_DP_Fixture, score_combination_Function) {
    vector<int> individual_play_scores = {2, 3, 7};
    ASSERT_EQ(4, NumCombinationsForFinalScore(12, individual_play_scores));
    ASSERT_EQ(1, NumCombinationsForFinalScore(5, individual_play_scores));
    ASSERT_EQ(3, NumCombinationsForFinalScore(9, individual_play_scores));

    default_random_engine gen((random_device()) ());
    individual_play_scores.clear();
    uniform_int_distribution<int> k_dis(0, 999);

    int k = k_dis(gen);
    uniform_int_distribution<int> size_dis(1, 50);
    individual_play_scores.resize(size_dis(gen));

    for (int i = 0; i < individual_play_scores.size(); ++i) {
        uniform_int_distribution<int> score_dis(1, 1000);
        individual_play_scores[i] = score_dis(gen);
    }

    // cout << NumCombinationsForFinalScore(k, individual_play_scores) << endl;
    ASSERT_EQ(NumCombinationsForFinalScore(k, individual_play_scores),
           p_17_1_CheckAnswer(k, individual_play_scores));
}
