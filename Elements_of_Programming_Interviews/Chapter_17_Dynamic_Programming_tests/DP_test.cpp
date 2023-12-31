#include <gtest/gtest.h>
#include <random>
#include <limits>
#include <unordered_set>
#include <cmath>
#include <string>
#include "fibonacci.h"
#include "Max-sum_subarray.h"
#include "Score_combination.h"
#include "Score_combination_alternative.h"
#include "Score_permutation.h"
#include "Score_permutation_two_team.h"
#include "Lead_changes.h"
#include "Levenshtein_distance.h"
#include "Number_ways.h"
#include "Computing_binomial_coefficients.h"
#include "String_in_matrix.h"
#include "0-1_knapsack.h"
#include "Word_breaking.h"
#include "triangle.h"
#include "Picking_up_coins.h"
#include "number-steps.h"
#include "Pretty_printing.h"
#include "Longest_nondecreasing_subsequence_n2.h"
#include "Longest_nondecreasing_subsequence_nlogn.h"
#include "fibonacci_rakuten.h"

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
using std::boolalpha;

class Ch17_DP_Fixture : public ::testing::Test {
private:

protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    void CheckMaxSum(const vector<int>& A, int max_sum);

    int p_17_1_CheckAnswer(int total_score, const vector<int>& score_ways);

    int p_17_2_CheckAnswer(string A, string B);
    string RandString(int len);

    int p_17_3_CheckAns(int n, int k);

    int p_17_4_CheckAns(int n, int k);

    vector<vector<int>> p_17_5_RandMatrix(int n);

    void p_17_7_CheckAns(const string& s, vector<string>& ans);

    string p_17_7_RandString(int len);

public:
    Ch17_DP_Fixture() : Test() {

    }

    virtual ~Ch17_DP_Fixture() {
    }
};

string Ch17_DP_Fixture::p_17_7_RandString(int len) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    string ret;
    while (len--) {
        uniform_int_distribution<int> dis('a', 'z');
        ret += dis(gen);
    }
    return ret;
}

// Verify the strings in ans can be assembled into s.
void Ch17_DP_Fixture::p_17_7_CheckAns(const string& s, vector<string>& ans) {
    string temp;
    // cout << s << endl;
    for (int i = 0; i < ans.size(); ++i) {
        // cout << ans[i] << ' ';
        temp += ans[i];
    }
    // cout << endl;
    ASSERT_TRUE(!ans.size() || !s.compare(temp));
}

vector<vector<int>> Ch17_DP_Fixture::p_17_5_RandMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            uniform_int_distribution<int> dis(0, n - 1);
            matrix[i][j] = dis(gen);
        }
    }
    return matrix;
}

int Ch17_DP_Fixture::p_17_4_CheckAns(int n, int k) {
    vector<int> number;
    for (int i = 0; i < k; ++i) {
        number.emplace_back(n - i);
    }

    vector<int> temp;
    for (int i = 2; i <= k; ++i) {
        bool find = false;
        for (int& a : number) {
            if ((a % i) == 0) {
                a /= i;
                find = true;
                break;
            }
        }
        if (find == false) {
            temp.emplace_back(i);
        }
    }

    int res = 1;
    for (int a : number) {
        res *= a;
    }

    for (int a : temp) {
        res /= a;
    }

    return res;
}

int Ch17_DP_Fixture::p_17_3_CheckAns(int n, int k) {
    vector<vector<int>> table(n + 1, vector<int>(k + 1));
    // Basic case: C(i, 0) = 1.
    for (int i = 0; i <= n; ++i) {
        table[i][0] = 1;
    }
    // Basic case: C(i, i) = 1.
    for (int i = 1; i <= k; ++i) {
        table[i][i] = 1;
    }
    // C(i, j) = C(i - 1, j) + C(i - 1, j - 1).
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j < i && j <= k; ++j) {
            table[i][j] = table[i - 1][j] + table[i - 1][j - 1];
        }
    }
    return table[n][k];
}

int Ch17_DP_Fixture::p_17_2_CheckAnswer(string A, string B) {
    // Try to reduce the space usage.
    if (A.size() < B.size()) {
        swap(A, B);
    }

    // use O(min(A,B)) space.
    vector<int> D(B.size() + 1);
    // Initialization.
    iota(D.begin(), D.end(), 0);

    // update D as late row
    for (int i = 1; i <= A.size(); ++i) {
        int pre_i_1_j_1 = D[0];  // Stores the timestamp of D[i - 1][j - 1].
        // in the table, the data in first column is i.
        D[0] = i;

        for (int j = 1; j <= B.size(); ++j) {
            int pre_i_1_j = D[j];  // Stores the timestamp of D[i -1][j].
            //  (i-1, j-1)    (i-1, j) = D[j]
            //            \      |
            //              \    \/
            //   D[j-1]  -->  D'[j]
            //
            D[j] =    //D'[j]
                    A[i - 1] == B[j - 1]
                    ? pre_i_1_j_1
                    : 1 + min({pre_i_1_j_1, D[j - 1], pre_i_1_j});
            // Previous D[i - 1][j] will become the next D[i - 1][j - 1].
            pre_i_1_j_1 = pre_i_1_j;
        }
    }
    return D.back();
}

string Ch17_DP_Fixture::RandString(int len) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis('a', 'z');
    string ret;
    while (len--) {
        ret += dis(gen);
    }
    return ret;
}

// Solution for Variant of 17.1.1
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

TEST_F(Ch17_DP_Fixture, Fibonacci_rakuten) {
    const int mod = 1000000007;
    ASSERT_EQ(3, GF_modulo(3,4,0, mod));
    ASSERT_EQ(4, GF_modulo(3,4,1, mod));
    ASSERT_EQ(7, GF_modulo(3,4,2, mod));
    ASSERT_EQ(11, GF_modulo(3,4,3, mod));
    ASSERT_EQ(18, GF_modulo(3,4,4, mod));
    ASSERT_EQ(29, GF_modulo(3,4,5, mod));
    //ASSERT_EQ(29, GF_modulo(3,4,1000000000, mod));

    ASSERT_EQ(0, diff_fib(0));
    ASSERT_EQ(0, diff_fib(1));
    ASSERT_EQ(0, diff_fib(2));
    ASSERT_EQ(0, diff_fib(13));
    ASSERT_EQ(134903163, diff_fib(1000000007));

    _2x2_m m1;
    ASSERT_EQ(0, m1.m[0][0]);
    ASSERT_EQ(0, m1.m[0][1]);
    ASSERT_EQ(0, m1.m[1][0]);
    ASSERT_EQ(0, m1.m[1][1]);

    using m_type = array<array<int, 2>, 2>;

    _2x2_m m2 = m_type{{{1,1}, {1,0}}};
    _2x2_m m3 = m_type{{{1,1}, {1,0}}};
    _2x2_m m4 = m2*m3;
    _2x2_m m4_1 = m_type{{{2,1},{1,1}}};
    ASSERT_EQ(m4_1, m4);
    _2x2_m m5 = m_type{{{3,2},{2,1}}};
    ASSERT_EQ(m5, m3.power(3));

    ASSERT_EQ(3, GF(3,4,0));
    ASSERT_EQ(4, GF(3,4,1));
    ASSERT_EQ(7, GF(3,4,2));
    ASSERT_EQ(11, GF(3,4,3));
    ASSERT_EQ(18, GF(3,4,4));
    ASSERT_EQ(29, GF(3,4,5));

    const int Lmod = 1000000007;
    const int LA = 2147483647;
    const int LB = 2147483647;
    const int LN = 1000000000;
    _2x2_m_mod Lm = {m_type{{{Lmod, Lmod+1}, {Lmod+2, Lmod+3}}}, Lmod};
    _2x2_m_mod Lm_1 = {{{{0,1},{2,3}}}, Lmod};
    ASSERT_EQ(Lm_1, Lm);
    ASSERT_GT(Lmod, Lm.power(LN)._m[0][0]);
    ASSERT_GT(Lmod, Lm.power(LN)._m[0][1]);
    ASSERT_GT(Lmod, Lm.power(LN)._m[1][0]);
    ASSERT_GT(Lmod, Lm.power(LN)._m[1][1]);

    // final solution test: GF_mod
    ASSERT_EQ(3, GF_mod(3, 4, 0, Lmod));
    ASSERT_EQ(4, GF_mod(3, 4, 1, Lmod));
    ASSERT_EQ(7, GF_mod(3, 4, 2, Lmod));
    ASSERT_EQ(11, GF_mod(3, 4, 3, Lmod));
    ASSERT_EQ(18, GF_mod(3, 4, 4, Lmod));
    ASSERT_EQ(29, GF_mod(3, 4, 5, Lmod));
    ASSERT_EQ(408990538, GF_mod(LA, LA, LN, Lmod));
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
    ASSERT_EQ(1, FindMaximumSubarray(B));
    ASSERT_EQ(1, FindMaximumSubarray2(B));
    ASSERT_EQ(1, FindMaximumSubarray2_1(B));
    ASSERT_EQ(1, FindMaximumSubarray3(B));
    ASSERT_EQ(1, FindMaximumSubarray4(B));
    B = {-5};
    ASSERT_EQ(0, FindMaximumSubarray(B));
    ASSERT_EQ(0, FindMaximumSubarray2(B));
    ASSERT_EQ(0, FindMaximumSubarray2_1(B));
    ASSERT_EQ(0, FindMaximumSubarray3(B));
    ASSERT_EQ(0, FindMaximumSubarray4(B));
    B = {0};
    ASSERT_EQ(0, FindMaximumSubarray(B));
    ASSERT_EQ(0, FindMaximumSubarray2(B));
    ASSERT_EQ(0, FindMaximumSubarray2_1(B));
    ASSERT_EQ(0, FindMaximumSubarray3(B));
    ASSERT_EQ(0, FindMaximumSubarray4(B));
    B = {0, 0};
    ASSERT_EQ(0, FindMaximumSubarray(B));
    ASSERT_EQ(0, FindMaximumSubarray2(B));
    ASSERT_EQ(0, FindMaximumSubarray2_1(B));
    ASSERT_EQ(0, FindMaximumSubarray3(B));
    ASSERT_EQ(0, FindMaximumSubarray4(B));
    B = {0, 0, 0};
    ASSERT_EQ(0, FindMaximumSubarray(B));
    ASSERT_EQ(0, FindMaximumSubarray2(B));
    ASSERT_EQ(0, FindMaximumSubarray2_1(B));
    ASSERT_EQ(0, FindMaximumSubarray3(B));
    ASSERT_EQ(0, FindMaximumSubarray4(B));
    B = {0, -5, 0};
    ASSERT_EQ(0, FindMaximumSubarray(B));
    ASSERT_EQ(0, FindMaximumSubarray2(B));
    ASSERT_EQ(0, FindMaximumSubarray2_1(B));
    ASSERT_EQ(0, FindMaximumSubarray3(B));
    ASSERT_EQ(0, FindMaximumSubarray4(B));
    B = {-2, -1};
    ASSERT_EQ(0, FindMaximumSubarray(B));
    ASSERT_EQ(0, FindMaximumSubarray2(B));
    ASSERT_EQ(0, FindMaximumSubarray2_1(B));
    ASSERT_EQ(0, FindMaximumSubarray3(B));
    ASSERT_EQ(0, FindMaximumSubarray4(B));
    B = {31, -41, 59};
    ASSERT_EQ(59, FindMaximumSubarray(B));
    ASSERT_EQ(59, FindMaximumSubarray2(B));
    ASSERT_EQ(59, FindMaximumSubarray2_1(B));
    ASSERT_EQ(59, FindMaximumSubarray3(B));
    ASSERT_EQ(59, FindMaximumSubarray4(B));
    B = {31, -41, 59, 26, -53, 58, 97, -93, -23, 84};
    ASSERT_EQ(187, FindMaximumSubarray(B));
    ASSERT_EQ(187, FindMaximumSubarray2(B));
    ASSERT_EQ(187, FindMaximumSubarray2_1(B));
    ASSERT_EQ(187, FindMaximumSubarray3(B));
    ASSERT_EQ(187, FindMaximumSubarray4(B));
    B = {904, 40, 523, 12, -335, -385, -124, 481, -31};
    ASSERT_EQ(1479, FindMaximumSubarray(B));
    ASSERT_EQ(1479, FindMaximumSubarray2(B));
    ASSERT_EQ(1479, FindMaximumSubarray2_1(B));
    ASSERT_EQ(1479, FindMaximumSubarray3(B));
    ASSERT_EQ(1479, FindMaximumSubarray4(B));

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        vector<int> A;
        uniform_int_distribution<int> dis(1, 1000);
        A = RandVector<int>(dis(gen));

        ASSERT_EQ(FindMaximumSubarray(A), FindMaximumSubarray2(A));
        ASSERT_EQ(FindMaximumSubarray2(A), FindMaximumSubarray3(A));
        ASSERT_EQ(FindMaximumSubarray2(A), FindMaximumSubarray2_1(A));
        ASSERT_EQ(FindMaximumSubarray3(A), FindMaximumSubarray4(A));

        /*
        CheckMaxSum(A, max_sum);
        CheckMaxSum(A, max_sum2);
        CheckMaxSum(A, max_sum3);
        CheckMaxSum(A, max_sum4);
        CheckMaxSum(A, max_sum5);
         */
    }
}

TEST_F(Ch17_DP_Fixture, score_combination_Function) {
    vector<int> individual_play_scores = {2, 3, 7};
    ASSERT_EQ(4, NumCombinationsForFinalScore(12, individual_play_scores));
    ASSERT_EQ(1, NumCombinationsForFinalScore(5, individual_play_scores));
    ASSERT_EQ(3, NumCombinationsForFinalScore(9, individual_play_scores));

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device()) ());
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

TEST_F(Ch17_DP_Fixture, score_combination_alternative) {
    vector<int> score_ways = {2, 3, 7};
    int c12 = CountCombinationsAlt(12, score_ways);
    // cout << "\nNumber of ways to 12 = " << c12 << endl;
    ASSERT_EQ(4, CountCombinationsAlt(12, score_ways));
    ASSERT_EQ(1, CountCombinationsAlt(5, score_ways));
    ASSERT_EQ(3, CountCombinationsAlt(9, score_ways));
    for (int i = 0; i < 100; i++) {
        ASSERT_EQ(CountCombinationsAlt(i, score_ways),
                  p_17_1_CheckAnswer(i, score_ways));
    }

    for (int i = 0; i < 1000; i++) {
        random_device rd;
        default_random_engine gen(rd());
        //default_random_engine gen((random_device()) ());
        int k;

        score_ways.clear();
        uniform_int_distribution<int> k_dis(0, 999);
        k = k_dis(gen);
        uniform_int_distribution<int> size_dis(1, 50);
        score_ways.resize(size_dis(gen));
        for (int i = 0; i < score_ways.size(); ++i) {
            uniform_int_distribution<int> score_dis(1, 1000);
            score_ways[i] = score_dis(gen);
        }

        ASSERT_EQ(CountCombinationsAlt(k, score_ways),
                  p_17_1_CheckAnswer(k, score_ways));
    }
}

TEST_F(Ch17_DP_Fixture, score_permutation) {
    int k = 12;
    vector<int> score_ways = {2, 3, 7};
    ASSERT_EQ(18, CountPermutations(k, score_ways));

    k = 4;
    score_ways = {1, 2};
    ASSERT_EQ(5, CountPermutations(k, score_ways));

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    score_ways.clear();
    uniform_int_distribution<int> k_dis(0, 999);
    k = k_dis(gen);
    uniform_int_distribution<int> size_dis(1, 50);
    score_ways.resize(size_dis(gen));

    for (int i = 0; i < score_ways.size(); ++i) {
        uniform_int_distribution<int> score_dis(1, 1000);
        score_ways[i] = score_dis(gen);
    }
    //cout << CountPermutations(k, score_ways) << endl;
    CountPermutations(k, score_ways);
}

TEST_F(Ch17_DP_Fixture, score_permutation_two_team) {
    two_scores A = {6, 3};
    vector<int> score_ways = {2, 3, 7};
    ASSERT_EQ(7, CountPermutations_two_teams(A, score_ways));

    A = {4, 3};
    score_ways = {2, 3, 7};
    ASSERT_EQ(3, CountPermutations_two_teams(A, score_ways));

    A = {5, 3};
    score_ways = {2, 3, 7};
    ASSERT_EQ(6, CountPermutations_two_teams(A, score_ways));
}

TEST_F(Ch17_DP_Fixture, lead_changes) {
    lead::two_scores A = {0, 0};
    vector<int> score_ways = {2, 3, 7};
    ASSERT_EQ(0, lead::max_lead_changes(A, score_ways));

    A = {0, 1};
    ASSERT_EQ(-1, lead::max_lead_changes(A, score_ways));

    A = {0, 2};
    ASSERT_EQ(0, lead::max_lead_changes(A, score_ways));

    A = {1, 0};
    ASSERT_EQ(-1, lead::max_lead_changes(A, score_ways));

    A = {1, 1};
    ASSERT_EQ(-1, lead::max_lead_changes(A, score_ways));

    A = {1, 2};
    ASSERT_EQ(-1, lead::max_lead_changes(A, score_ways));

    A = {2, 0};
    ASSERT_EQ(0, lead::max_lead_changes(A, score_ways));

    A = {2, 1};
    ASSERT_EQ(-1, lead::max_lead_changes(A, score_ways));

    A = {2, 2};
    ASSERT_EQ(0, lead::max_lead_changes(A, score_ways));

    A = {2, 3};
    ASSERT_EQ(1, lead::max_lead_changes(A, score_ways));

    A = {2, 4};
    ASSERT_EQ(0, lead::max_lead_changes(A, score_ways));

    A = {3, 0};
    ASSERT_EQ(0, lead::max_lead_changes(A, score_ways));

    A = {3, 1};
    ASSERT_EQ(-1, lead::max_lead_changes(A, score_ways));

    A = {3, 2};
    ASSERT_EQ(1, lead::max_lead_changes(A, score_ways));

    A = {3, 3};
    ASSERT_EQ(0, lead::max_lead_changes(A, score_ways));

    A = {4, 0};
    ASSERT_EQ(0, lead::max_lead_changes(A, score_ways));

    A = {4, 1};
    ASSERT_EQ(-1, lead::max_lead_changes(A, score_ways));

    A = {4, 2};
    ASSERT_EQ(0, lead::max_lead_changes(A, score_ways));

    A = {4, 3};
    ASSERT_EQ(2, lead::max_lead_changes(A, score_ways));

    A = {4, 4};
    ASSERT_EQ(0, lead::max_lead_changes(A, score_ways));

    A = {4, 6};
    ASSERT_EQ(3, lead::max_lead_changes(A, score_ways));

    A = {5, 0};
    ASSERT_EQ(0, lead::max_lead_changes(A, score_ways));

    A = {5, 1};
    ASSERT_EQ(-1, lead::max_lead_changes(A, score_ways));

    A = {5, 2};
    ASSERT_EQ(1, lead::max_lead_changes(A, score_ways));

    A = {5, 4};
    ASSERT_EQ(3, lead::max_lead_changes(A, score_ways));

    A = {5, 6};
    ASSERT_EQ(4, lead::max_lead_changes(A, score_ways));

    A = {7, 0};
    ASSERT_EQ(0, lead::max_lead_changes(A, score_ways));

    A = {7, 2};
    ASSERT_EQ(1, lead::max_lead_changes(A, score_ways));

    A = {7, 3};
    ASSERT_EQ(2, lead::max_lead_changes(A, score_ways));

    A = {7, 4};
    ASSERT_EQ(3, lead::max_lead_changes(A, score_ways));

    A = {7, 6};
    ASSERT_EQ(5, lead::max_lead_changes(A, score_ways));

    A = {10, 6};
    ASSERT_EQ(5, lead::max_lead_changes(A, score_ways));

    // EPI code count_lead_changes seems wrong.
    ASSERT_NE(4, lead::count_lead_changes(10, 6, score_ways));
    ASSERT_NE(3, lead::count_lead_changes(5, 4, score_ways));
}

TEST_F(Ch17_DP_Fixture, Levenshtein_distance_Function) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    string A, B;
    // Wiki example (http://en.wikipedia.org/wiki/Levenshtein_distance)
    A = "k", B = "sitt";
    ASSERT_EQ(4, LevenshteinDistance(A, B));
    A = "Saturday", B = "Sunday";
    ASSERT_EQ(3, LevenshteinDistance(A, B));
    A = "kitten", B = "sitting";
    ASSERT_EQ(3, LevenshteinDistance(A, B));

    for (int i = 0; i < 1000; i++) {
        uniform_int_distribution<int> dis(1, 100);
        A = RandString(dis(gen));
        B = RandString(dis(gen));
        // cout << A << endl << B << endl;
        // cout << LevenshteinDistance(A, B) << endl;
        ASSERT_EQ(LevenshteinDistance(A, B), p_17_2_CheckAnswer(A, B));
    }
}

TEST_F(Ch17_DP_Fixture, Number_ways_Function) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());

    for (int times = 0; times < 1000; ++times) {
        uniform_int_distribution<int> dis(1, 10);
        int n = dis(gen);
        int m = dis(gen);
        // cout << "n = " << n << ", m = " << m
        //     << ", number of ways = " << NumberOfWays(n, m) << endl;
        ASSERT_EQ(p_17_3_CheckAns(n + m - 2, m - 1), NumberOfWays(n, m));
        ASSERT_EQ(ComputeNumberOfWaysSpaceEfficient(n, m), NumberOfWays(n, m));
    }
}

TEST_F(Ch17_DP_Fixture, binomial_coefficients_Function) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());

    for (int times = 0; times < 1000; ++times) {
        uniform_int_distribution<int> n_dis(1, 21);
        int n = n_dis(gen);
        uniform_int_distribution<int> k_dis(0, n);
        int k = k_dis(gen);

        int res = ComputeBinomialCoefficient(n, k);
        // cout << "res = " << res << endl;
        ASSERT_EQ(res, p_17_4_CheckAns(n, k));
        ASSERT_EQ(res, ComputeBinomialCoefficientsSpaceEfficient(n, k));
        // cout << n << " out of " << k << " = " << res << endl;
    }
}

TEST_F(Ch17_DP_Fixture, string_in_matrix_Function) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(2, 10);
    int n = dis(gen);

    vector<vector<int>> A = p_17_5_RandMatrix(n);
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < A[i].size(); ++j) {
            cout << A[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "S = ";
    uniform_int_distribution<int> dis1(1, n * n / 2);
    vector<int> S(1 + dis1(gen));

    for (size_t i = 0; i < S.size(); ++i) {
        uniform_int_distribution<int> dis(0, n - 1);
        S[i] = dis(gen);
    }
    copy(S.begin(), S.end(), ostream_iterator<int>(cout, " "));
    cout << endl << boolalpha << IsPatternContainedInGrid(A, S) << endl;
}

TEST_F(Ch17_DP_Fixture, knapsack_Function) {
    // The example in the book.
    vector<Item> items = {{20, 65},  {8, 35},   {60, 245}, {55, 195},
                          {40, 65},  {70, 150}, {85, 275}, {25, 155},
                          {30, 120}, {65, 320}, {75, 75},  {10, 40},
                          {95, 200}, {50, 100}, {40, 220}, {10, 99}};
    ASSERT_EQ(695, OptimumSubjecToCapacity(items, 130));

    items = {{5, 60}, {3, 50}, {4, 70}, {2, 30}};
    ASSERT_EQ(80, OptimumSubjecToCapacity(items, 5));
}

TEST_F(Ch17_DP_Fixture, word_breaking_Function) {
    unordered_set<string> dictionary = {"bed", "bath", "and", "hand", "beyond"};
    auto ans = DecomposeIntoDictionaryWords("bedbathandbeyond", dictionary);
    vector<string> golden_ans = {"bed", "bath", "and", "beyond"};
    p_17_7_CheckAns("bedbathandbeyond", ans);
    ASSERT_TRUE(equal(ans.begin(), ans.end(), golden_ans.begin(), golden_ans.end()));

    dictionary = {"aa", "b", "ccc"};
    ans = DecomposeIntoDictionaryWords("b", dictionary);
    golden_ans = {"b"};
    p_17_7_CheckAns("b", ans);
    ASSERT_TRUE(equal(ans.begin(), ans.end(), golden_ans.begin(), golden_ans.end()));

    ans = DecomposeIntoDictionaryWords("ccc", dictionary);
    golden_ans = {"ccc"};
    p_17_7_CheckAns("ccc", ans);
    ASSERT_TRUE(equal(ans.begin(), ans.end(), golden_ans.begin(), golden_ans.end()));

    ans = DecomposeIntoDictionaryWords("aabccc", dictionary);
    golden_ans = {"aa", "b", "ccc"};
    p_17_7_CheckAns("aabccc", ans);
    ASSERT_TRUE(equal(ans.begin(), ans.end(), golden_ans.begin(), golden_ans.end()));

    ans = DecomposeIntoDictionaryWords("baabccc", dictionary);
    golden_ans = {"b", "aa", "b", "ccc"};
    p_17_7_CheckAns("baabccc", ans);
    ASSERT_TRUE(equal(ans.begin(), ans.end(), golden_ans.begin(), golden_ans.end()));

    dictionary.insert("bb");
    ans = DecomposeIntoDictionaryWords("bbb", dictionary);
    // Note: golden_ans relies on how our algorithm is implemented: our
    // algorithm chooses longest word ending at that index, so the answer
    // is "b", "bb", not "b", "b", "b" or "bb", "b".
    golden_ans = {"b", "bb"};
    p_17_7_CheckAns("bbb", ans);
    ASSERT_TRUE(equal(ans.begin(), ans.end(), golden_ans.begin(), golden_ans.end()));

    ans = DecomposeIntoDictionaryWords("bbcccb", dictionary);
    golden_ans = {"bb", "ccc", "b"};
    p_17_7_CheckAns("bbcccb", ans);
    ASSERT_TRUE(equal(ans.begin(), ans.end(), golden_ans.begin(), golden_ans.end()));

    ans = DecomposeIntoDictionaryWords("bbcccbabb", dictionary);
    golden_ans = {};
    ASSERT_TRUE(equal(ans.begin(), ans.end(), golden_ans.begin(), golden_ans.end()));

    ans = DecomposeIntoDictionaryWords("d", dictionary);
    golden_ans = {};
    ASSERT_TRUE(equal(ans.begin(), ans.end(), golden_ans.begin(), golden_ans.end()));

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        unordered_set<string> dictionary;
        string target;
        uniform_int_distribution<int> dis(1, 50);
        target = p_17_7_RandString(dis(gen));
        uniform_int_distribution<int> n_dis(1, 10000);
        int n = n_dis(gen);

        while (n--) {
            uniform_int_distribution<int> dis(1, 15);
            dictionary.emplace(p_17_7_RandString(dis(gen)));
        }

        vector<string> ans(DecomposeIntoDictionaryWords(target, dictionary));
        p_17_7_CheckAns(target, ans);
    }
}

TEST_F(Ch17_DP_Fixture, triangle_Function) {
    vector<vector<int>> A = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    ASSERT_EQ(11, MinimumPathWeight(A));
}

TEST_F(Ch17_DP_Fixture, picking_up_coins_Function) {
    vector<int> coins = {25, 5,  10, 5,  10, 5,  10, 25,
                         1,  25, 1,  25, 1,  25, 5,  10};
    ASSERT_EQ(140, MaximumRevenue(coins));
    ASSERT_EQ(MaximumRevenueAlternative(coins), MaximumRevenue(coins));
    ASSERT_EQ(120, Greedy(coins));

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    coins.clear();
    uniform_int_distribution<int> dis(1, 1000);
    coins.resize(dis(gen));
    for (int i = 0; i < coins.size(); ++i) {
        uniform_int_distribution<int> dis(0, 99);
        coins[i] = dis(gen);
    }

    /*
    for (size_t i = 0; i < coins.size(); ++i) {
        cout << coins[i] << ' ';
    }

    cout << endl;
    cout << MaximumRevenue(coins) << endl;
    */
    ASSERT_EQ(MaximumRevenue(coins), MaximumRevenueAlternative(coins));
}

TEST_F(Ch17_DP_Fixture, climb_stairs_Function) {
    ASSERT_EQ(5, way_to_step::NumberOfWaysToTop(4, 2));
    ASSERT_EQ(1, way_to_step::NumberOfWaysToTop(1, 2));
    ASSERT_EQ(1, way_to_step::NumberOfWaysToTop(0, 3));

    /*
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 20);
    int n = dis(gen);
    uniform_int_distribution<int> k_dis(1, n);
    int k = k_dis(gen);
    cout << "n = " << n << ", k = " << k << endl;
    cout << NumberOfWaysToTop(n, k) << endl;
    */
}

TEST_F(Ch17_DP_Fixture, pretty_printing_Function) {
    ASSERT_EQ(MinimumMessiness({"aaa", "bbb", "c", "d", "ee", "ff", "gggggg"}, 11), 45);
    ASSERT_EQ(MinimumMessiness({"a", "b", "c", "d"}, 5), 8);

    /*
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((17_7_random_device())());
    uniform_int_distribution<int> n_dis(1, 30);
    int n = n_dis(gen);
    uniform_int_distribution<int> L_dis(11, 20);
    int L = L_dis(gen);

    vector<string> W;
    for (int i = 0; i < n; ++i) {
        uniform_int_distribution<int> dis(1, 10);
        W.push_back(17_7_RandString(dis(gen)));
    }
    for (int i = 0; i < n; ++i) {
        cout << W[i] << ' ';
    }
    cout << L << endl;
    cout << MinimumMessiness(W, L) << endl;
    */
}

TEST_F(Ch17_DP_Fixture, LNS_Function) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());

    for (int times = 0; times < 10; ++times) {
        uniform_int_distribution<int> dis(1, 10000);
        int n = dis(gen);

        vector<int> A;

        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(0, 99999999);
            A.emplace_back(dis(gen));
        }

        // cout << "n = " << n << endl;
        int ret_length = LNS_nlogn::LongestNondecreasingSubsequenceLength(A);
        int another_length = LNS_n2::LongestNondecreasingSubsequenceLength(A);
        ASSERT_EQ(ret_length, another_length);
    }
}
