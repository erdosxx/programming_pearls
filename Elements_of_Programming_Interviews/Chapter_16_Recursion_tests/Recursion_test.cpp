#include <gtest/gtest.h>
#include <random>
#include <limits>
#include <unordered_set>
#include <cmath>
#include <string>
#include <bitset>
#include "tower_hanoi.h"
#include "n-queens.h"
#include "permutations.h"
#include "permutations-alternative.h"
#include "Power_set.h"
#include "Power_set_alternative.h"
#include "combinations.h"
#include "generate-parentheses.h"
#include "palindrome-partitioning.h"
#include "unique-binary-trees-all.h"
#include "Sudoku_solve.h"
#include "gray-code-backtrack.h"
#include "gray-code.h"
#include "Tree_diameter.h"

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

class Ch16_Recursion_Fixture : public ::testing::Test {
private:

protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    void p_16_7_CheckAns(const vector<vector<string>>& vecs, const string& input);
    string p_16_7_RandString(size_t len);
    void p_16_10_CheckAns(const vector<int>& A);

public:
    Ch16_Recursion_Fixture() : Test() {

    }

    virtual ~Ch16_Recursion_Fixture() {
    }
};

void Ch16_Recursion_Fixture::p_16_10_CheckAns(const vector<int>& A) {
    for (size_t i = 0; i < A.size(); ++i) {
        int num_differ_bits = 0;
        bitset<10> prev(A[i]), now(A[(i + 1) % A.size()]);
        string prev_s = prev.to_string(), now_s = now.to_string();
        for (size_t i = 0; i < 10; ++i) {
            if (prev_s[i] != now_s[i]) {
                ++num_differ_bits;
            }
        }
        ASSERT_EQ(num_differ_bits, 1);
    }
}

void Ch16_Recursion_Fixture::p_16_7_CheckAns(const vector<vector<string>>& vecs, const string& input) {
    for (const vector<string>& vec : vecs) {
        string temp;
        for (const string& s : vec) {
            ASSERT_TRUE(IsPalindrome(s));
            temp += s;
        }
        ASSERT_TRUE(!temp.compare(input));
    }
}

string Ch16_Recursion_Fixture::p_16_7_RandString(size_t len) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    string ret;
    uniform_int_distribution<char> dis('a', 'z');
    while (len) {
        --len;
        ret += dis(gen);
    }
    return ret;
}

TEST_F(Ch16_Recursion_Fixture, tower_hanoi_Function) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
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
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
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
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
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
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
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
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
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
        random_device rd;
        default_random_engine gen(rd());
        //default_random_engine gen((random_device())());
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
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
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

TEST_F(Ch16_Recursion_Fixture, generate_parentheses_Function) {
    auto result = GenerateBalancedParentheses(1);
    ASSERT_TRUE(result.size() == 1 && !result.front().compare("()"));
    result = GenerateBalancedParentheses(2);
    ASSERT_TRUE(
            result.size() == 2 &&
            ((!result.front().compare("(())") && !result.back().compare("()()")) ||
             (!result.front().compare("()()") && !result.back().compare("(())"))));

    /*
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis_n(0, 10);
    int n = dis_n(gen);

    cout << "n = " << n << endl;
    auto result = GenerateBalancedParentheses(n);
    for (const string& s : result) {
        cout << s << " ";
    }
    cout << endl;
     */
}

TEST_F(Ch16_Recursion_Fixture, palindrome_partitioning_Function) {
    auto result = PalindromePartitioning("abbbac");
    vector<string> v0 = {"a", "b", "b", "b", "a", "c"};
    vector<string> v1 = {"a", "b", "bb", "a", "c"};
    vector<string> v2 = {"a", "bb", "b", "a", "c"};
    vector<string> v3 = {"a", "bbb", "a", "c"};
    vector<string> v4 = {"abbba", "c"};
    vector<vector<string>> golden = {v0, v1, v2, v3, v4};
    ASSERT_EQ(result, golden);

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device()) ());
    for (int times = 0; times < 1000; ++times) {
        uniform_int_distribution<size_t> dis_len(0, 10);
        string s = p_16_7_RandString(dis_len(gen));
        auto result = PalindromePartitioning(s);
        p_16_7_CheckAns(result, s);
        /*
        cout << "string s = " << s << endl;
        for (const vector<string> &vec : result) {
            for (const string &t : vec) {
                cout << t << " ";
            }
            cout << endl;
        }
         */
    }
}

TEST_F(Ch16_Recursion_Fixture, generate_binary_trees_Function) {
    ASSERT_EQ(GenerateAllBinaryTrees(1).size(), 1);
    ASSERT_EQ(GenerateAllBinaryTrees(2).size(), 2);
    ASSERT_EQ(GenerateAllBinaryTrees(3).size(), 5);
    ASSERT_EQ(GenerateAllBinaryTrees(4).size(), 14);
    ASSERT_EQ(GenerateAllBinaryTrees(5).size(), 42);
    ASSERT_EQ(GenerateAllBinaryTrees(10).size(), 16796);

    /*
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    int n;
    if (argc == 2) {
        n = stoi(argv[1]);
    } else {
        uniform_int_distribution<int> dis(1, 10);
        n = dis(gen);
    }
    cout << "n = " << n << endl;
    GenerateAllBinaryTrees(n);
    */
}

TEST_F(Ch16_Recursion_Fixture, sudoku_solve_Function) {
    vector<vector<int>> A(9, vector<int>(9, 0));
    A[0] = {0, 2, 6, 0, 0, 0, 8, 1, 0};
    A[1] = {3, 0, 0, 7, 0, 8, 0, 0, 6};
    A[2] = {4, 0, 0, 0, 5, 0, 0, 0, 7};
    A[3] = {0, 5, 0, 1, 0, 7, 0, 9, 0};
    A[4] = {0, 0, 3, 9, 0, 5, 1, 0, 0};
    A[5] = {0, 4, 0, 3, 0, 2, 0, 5, 0};
    A[6] = {1, 0, 0, 0, 3, 0, 0, 0, 2};
    A[7] = {5, 0, 0, 2, 0, 4, 0, 0, 9};
    A[8] = {0, 3, 8, 0, 0, 0, 4, 6, 0};
    ASSERT_TRUE(SolveSudoku(&A));

    vector<vector<int>> golden_A = {
            {7, 2, 6, 4, 9, 3, 8, 1, 5},
            {3, 1, 5, 7, 2, 8, 9, 4, 6},
            {4, 8, 9, 6, 5, 1, 2, 3, 7},
            {8, 5, 2, 1, 4, 7, 6, 9, 3},
            {6, 7, 3, 9, 8, 5, 1, 2, 4},
            {9, 4, 1, 3, 6, 2, 7, 5, 8},
            {1, 9, 4, 8, 3, 6, 5, 7, 2},
            {5, 6, 7, 2, 1, 4, 3, 8, 9},
            {2, 3, 8, 5, 7, 9, 4, 6, 1}};

    for (size_t i = 0; i < 9; ++i) {
        for (size_t j = 0; j < 9; ++j) {
            ASSERT_EQ(A[i][j], golden_A[i][j]);
        }
    }
}

TEST_F(Ch16_Recursion_Fixture, gray_code_backtracking_Function) {
    auto vec = backtrack::GrayCode(3);
    vector<int> expected = {0, 1, 3, 2, 6, 7, 5, 4};
    ASSERT_TRUE(equal(vec.begin(), vec.end(), expected.begin(), expected.end()));

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device()) ());
    uniform_int_distribution<int> dis(1, 9);
    int n = dis(gen);

    // cout << "n = " << n << endl;
    vec.clear();
    vec = backtrack::GrayCode(n);
    /*
    for (int a : vec) {
        cout << a << endl;
    }
     */
    p_16_10_CheckAns(vec);
}

TEST_F(Ch16_Recursion_Fixture, gray_code_Function) {
    auto vec = GrayCode(3);
    vector<int> expected = {0, 1, 3, 2, 6, 7, 5, 4};
    ASSERT_TRUE(equal(vec.begin(), vec.end(), expected.begin(), expected.end()));

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 9);
    int n = dis(gen);

    // cout << "n = " << n << endl;
    vec.clear();
    vec = GrayCode(n);
    /*
    for (int a : vec) {
        cout << a << endl;
    }
     */
    p_16_10_CheckAns(vec);
}

TEST_F(Ch16_Recursion_Fixture, tree_diameter_Function) {
    //       *
    //    /10   \ 20
    //    *       *
    //  /50 \ 100
    // *      *
    unique_ptr<TreeNode> r = nullptr;
    ASSERT_EQ(0.0, ComputeDiameter(r));
    r = make_unique<TreeNode>(TreeNode());
    r->edges.emplace_back(
            TreeNode::Edge{make_unique<TreeNode>(TreeNode()), 10});
    r->edges[0].root->edges.emplace_back(
            TreeNode::Edge{make_unique<TreeNode>(TreeNode()), 50});
    r->edges.emplace_back(
            TreeNode::Edge{make_unique<TreeNode>(TreeNode()), 20});
    ASSERT_EQ(80, ComputeDiameter(r));
    // cout << ComputeDiameter(r) << endl;
    r->edges[0].root->edges.emplace_back(
            TreeNode::Edge{make_unique<TreeNode>(TreeNode()), 100});
    ASSERT_EQ(150, ComputeDiameter(r));
    // cout << ComputeDiameter(r) << endl;
}
