#include <gtest/gtest.h>
#include <random>
#include <limits>
#include <unordered_set>
#include <cmath>
#include <string>
#include <deque>
#include <thread>
#include "GCD1.h"
#include "GCD2.h"
#include "first-missing-positive.h"
#include "Max_difference_k_pairs.h"
#include "Biggest_product_n-1.h"
#include "Biggest_product_n-1_math.h"
#include "Longest_increasing_subarray.h"
#include "Rotate_array.h"
#include "Rotate_array_permutation.h"
#include "rook-attack.h"
#include "justify-text.h"
#include "Zipping_list.h"
#include "Copying_postings_list.h"
#include "longest-valid-parentheses.h"
#include "Sliding_window.h"
#include "binary-tree-postorder-traversal-iterative.h"
#include "binary-tree-postorder-traversal-iterative-alternative.h"
#include "bonus.h"
#include "bonus-improved.h"
#include "Binary_search_unknown_length.h"
#include "Find_kth_element_in_two_sorted_arrays.h"
#include "k-th_largest_element_large_n.h"
#include "Find_element_appears_once.h"
#include "Line_most_points.h"
#include "Shortest_unique_prefix.h"
#include "Sorted_list_to_BST.h"
#include "BST_to_sorted_doubly_list.h"
#include "Merge_two_BSTs.h"
#include "View_from_above.h"
#include "Regular_expression.h"
#include "Add_operators_in_string.h"
#include "Count_inversions.h"
#include "Drawing_skylines.h"
#include "drawing_skylines_alternative.h"
#include "Three_jugs.h"
#include "Maximum_subarray_in_circular_array.h"
#include "Maximum_subarray_in_circular_array_constant_space.h"
#include "Height_determination.h"
#include "Max_submatrix_rectangle.h"
#include "Max_submatrix_rectangle_improved.h"
#include "Max_submatrix_square.h"
#include "Huffman_encoding.h"
#include "trapping-rain-water.h"
#include "Search_a_pair_sorted_array.h"
#include "Search_frequent_items.h"
#include "Longest_subarray_k.h"
#include "Longest_subarray_k_improved.h"
#include "Road_network.h"
#include "Arbitrage.h"

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
using std::min;
using std::cout;
using std::endl;
using std::ostream_iterator;
using std::to_string;
using std::boolalpha;
using std::deque;
using std::string;
using std::thread;
using std::this_thread::sleep_for;

class Ch25_Honors_Class_Fixture : public ::testing::Test {
private:

protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    int p_25_2_CheckAns(vector<int> A);

    void p_25_3_CheckAnsHelper(const vector<double> &A, int l, int k, int pre,
                        double ans, double *max_ans);

    double p_25_3_CheckAns(const vector<double> &A, int k);

    int p_25_4_CheckAns(const vector<int>& A);

    int p_25_4_1_check_ans(const vector<int>& A);

    vector<int> p_25_6_RandVector(int len);
    void p_25_6_CheckAnswer(const vector<int> &A, int i, const vector<int> &rotated);

    void p_25_7_CheckAns(const vector<vector<int>>& A, const vector<vector<int>>& ans);

    void p_25_8_TestCase(const vector<string>& words, size_t L, const vector<string>& golden);

    void CheckPostingsListEqual(shared_ptr<PostingListNode> a,
                                shared_ptr<PostingListNode> b);

    void p_25_14_CheckAns(const vector<int>& productivity, const vector<int>& C);

    static void SimpleTestArray(vector<int> A);

    size_t p_25_19_Check(const vector<Point>& P);

    string RandString(int len);

    string p_25_20_CheckAns(const string& s, unordered_set<string>& D);

    void PrintBSTInorder(shared_ptr<BSTNode<int>> n, const int& pre);

    void p_25_29_CheckAnswer(const Skyline& ans);
    void p_25_29_CheckAnswer_alt(const alt::Skyline& ans);

    int p_25_31_CheckAns(const vector<int>& A);

    int p_25_32_CheckAnswer(int cases, int drops);

    int p_25_33_CheckAns(const vector<deque<bool>>& A);

    int p_25_35_CheckAnswer(const vector<int> &A);

    void p_25_37_CheckAns(vector<string>* stream, int k, vector<string>* items);

    string p_25_37_RandString(int len);

    void p_25_38_check_answer(const vector<int>& A, const long_sub::Subarray& ans, int k);
    void p_25_38_2_CheckAnswer(const vector<int> &A, int ans, const int &k);

public:
    Ch25_Honors_Class_Fixture() : Test() {

    }

    virtual ~Ch25_Honors_Class_Fixture() {
    }
};

// O(n^2) checking answer.
void Ch25_Honors_Class_Fixture::p_25_38_2_CheckAnswer(const vector<int> &A, int ans, const int &k) {
  vector<int> sum(A.size() + 1, 0);
  sum[0] = 0;
  for (size_t i = 0; i < A.size(); ++i) {
    sum[i + 1] = sum[i] + A[i];
  }
  if (ans != 0) {
    for (size_t i = 0; i < sum.size(); ++i) {
      for (size_t j = i + 1; j < sum.size(); ++j) {
        if (sum[j] - sum[i] <= k) {
          ASSERT_LE((j - i), ans);
        }
      }
    }
  } else {
    for (size_t i = 0; i < sum.size(); ++i) {
      for (size_t j = i + 1; j < sum.size(); ++j) {
        ASSERT_GT(sum[j] - sum[i], k);
      }
    }
  }
}

// O(n^2) checking answer
void Ch25_Honors_Class_Fixture::p_25_38_check_answer(const vector<int>& A, const long_sub::Subarray& ans, int k) {
    vector<int> sum(A.size() + 1, 0);
    sum[0] = 0;
    for (size_t i = 0; i < A.size(); ++i) {
        sum[i + 1] = sum[i] + A[i];
    }
    if (ans.start != -1 && ans.end != -1) {
        int s = 0;
        for (size_t i = ans.start; i <= ans.end; ++i) {
            s += A[i];
        }
        ASSERT_LE(s, k);
        for (size_t i = 0; i < sum.size(); ++i) {
            for (size_t j = i + 1; j < sum.size(); ++j) {
                if (sum[j] - sum[i] <= k) {
                    ASSERT_LE((j - i), (ans.end - ans.start + 1));
                }
            }
        }
    } else {
        for (size_t i = 0; i < sum.size(); ++i) {
            for (size_t j = i + 1; j < sum.size(); ++j) {
                ASSERT_GE(sum[j] - sum[i], k);
            }
        }
    }
}

string Ch25_Honors_Class_Fixture::p_25_37_RandString(int len) {
    string ret;
    default_random_engine gen((random_device())());
    while (len--) {
        uniform_int_distribution<int> dis('a', 'z');
        ret += dis(gen);
    }
    return ret;
}

void Ch25_Honors_Class_Fixture::p_25_37_CheckAns(vector<string>* stream, int k, vector<string>* items) {
    sort(items->begin(), items->end());
    sort(stream->begin(), stream->end());
    int count = 1, idx = 0;
    for (int i = 1; i < stream->size(); ++i) {
        if ((*stream)[i].compare((*stream)[i - 1])) {
            if (count > static_cast<double>(stream->size()) / k) {
                ASSERT_LT(idx, items->size());
                ASSERT_EQ((*stream)[i - 1].compare((*items)[idx++]), 0);
            }
            count = 1;
        } else {
            ++count;
        }
    }
    if (count > static_cast<double>(stream->size()) / k) {
        ASSERT_EQ((*stream).back().compare((*items)[idx++]), 0);
    }
    ASSERT_EQ(idx, items->size());
}

// Stack approach, O(n) time, O(n) space
int Ch25_Honors_Class_Fixture::p_25_35_CheckAnswer(const vector<int> &A) {
    struct HeightBound {
        int left_bound, right_bound;
    };

    stack<HeightBound> s;
    int sum = 0;
    for (int i = 0; i < A.size(); ++i) {
        while (!s.empty() && s.top().right_bound <= A[i]) {
            int bottom = s.top().right_bound;
            s.pop();
            if (s.empty()) {
                break;
            }
            int top = min(s.top().right_bound, A[i]);
            sum += (top - bottom) * (i - s.top().left_bound - 1);
        }
        s.emplace(HeightBound{i, A[i]});
    }
    return sum;
}

// O(m^3 n^3) time solution.
int Ch25_Honors_Class_Fixture::p_25_33_CheckAns(const vector<deque<bool>>& A) {
    int max = 0;
    for (int a = 0; a < A.size(); ++a) {
        for (int b = 0; b < A[a].size(); ++b) {
            for (int r = 1; a + r <= A.size() && b + r <= A[0].size(); ++r) {
                int count = 0;
                bool all_1 = true;
                for (int c = a; c < a + r; ++c) {
                    for (int d = b; d < b + r; ++d) {
                        if (A[c][d]) {
                            ++count;
                        } else {
                            all_1 = false;
                            count = 0;
                            break;
                        }
                    }
                    if (all_1 == false) {
                        break;
                    }
                }
                if (count > max) {
                    max = count;
                }
            }
        }
    }
    return max;
}

int Ch25_Honors_Class_Fixture::p_25_32_CheckAnswer(int cases, int drops) {
    if (cases <= 0 || drops <= 0) {
        return 0;
    }
    vector<int> row(cases, 0);
    for (int d = 0; d < drops; ++d) {
        for (int c = cases - 1; c >= 0; --c) {
            row[c] += (c == 0 ? 0 : row[c - 1]) + 1;
        }
    }
    return row.back();
}

// O(n^2) solution.
int Ch25_Honors_Class_Fixture::p_25_31_CheckAns(const vector<int>& A) {
    int ans = 0;
    for (int i = 0; i < A.size(); ++i) {
        int sum = 0;
        for (int j = 0; j < A.size(); ++j) {
            sum += A[(i + j) % A.size()];
            ans = max(ans, sum);
        }
    }
    // cout << "correct answer = " << ans << endl;
    return ans;
}

void Ch25_Honors_Class_Fixture::p_25_29_CheckAnswer(const Skyline& ans) {
    // Just check there is no overlap.
    for (int i = 0; i < ans.size(); ++i) {
        ASSERT_LE(ans[i].left, ans[i].right);
        if (i > 0) {
            ASSERT_LE(ans[i - 1].right, ans[i].left);
            ASSERT_TRUE(ans[i - 1].right != ans[i].left ||
                   ans[i - 1].height != ans[i].height);
        }
    }
}

void Ch25_Honors_Class_Fixture::p_25_29_CheckAnswer_alt(const alt::Skyline& ans) {
    // Just check there is no overlap.
    for (int i = 0; i < ans.size(); ++i) {
        ASSERT_LE(ans[i].left, ans[i].right);
        if (i > 0) {
            ASSERT_LE(ans[i - 1].right, ans[i].left);
            ASSERT_TRUE(ans[i - 1].right != ans[i].left ||
                   ans[i - 1].height != ans[i].height);
        }
    }
}

void Ch25_Honors_Class_Fixture::PrintBSTInorder(shared_ptr<BSTNode<int>> n, const int& pre) {
    if (n) {
        Ch25_Honors_Class_Fixture::PrintBSTInorder(n->left, pre);
        ASSERT_LE(pre, n->data);
        // cout << n->data << ' ';
        Ch25_Honors_Class_Fixture::PrintBSTInorder(n->right, n->data);
    }
}

string Ch25_Honors_Class_Fixture::p_25_20_CheckAns(const string& s, unordered_set<string>& D) {
    int len = 0;
    for (auto iter = D.cbegin(); iter != D.cend(); ++iter) {
        int i;
        for (i = 0; i < s.size() && i < (*iter).size(); ++i) {
            if (s[i] != (*iter)[i]) {
                break;
            }
        }
        if (i > len) {
            len = i;
        }
    }
    if (len == s.size()) {
        return string();
    } else {
        return s.substr(0, len + 1);
    }
}

string Ch25_Honors_Class_Fixture::RandString(int len) {
    default_random_engine gen((random_device())());
    string ret;
    while (len--) {
        uniform_int_distribution<int> dis(0, 25);
        ret += dis(gen) + 'a';
    }
    return ret;
}

// n^3 checking
size_t Ch25_Honors_Class_Fixture::p_25_19_Check(const vector<Point>& P) {
    int max_count = 0;

    for (int i = 0; i < P.size(); ++i) {
        for (int j = i + 1; j < P.size(); ++j) {
            int count = 2;
            Line temp(P[i], P[j]);
            for (int k = j + 1; k < P.size(); ++k) {
                if (Line(P[i], P[k]) == temp) {
                    ++count;
                }
            }
            max_count = max(max_count, count);
        }
    }

    return max_count;
}

void Ch25_Honors_Class_Fixture::SimpleTestArray(vector<int> A) {
    stringstream ss;
    for (int a : A) {
        ss << a << ' ';
    }
    for (int i = 0; i < A.size(); ++i) {
        // cout << "i = " << i << endl;
        istringstream sin(ss.str());
        int k = i + 1;
        int result = FindKthLargestUnknownLength(&sin, k);
        nth_element(A.begin(), A.begin() + A.size() - k, A.end());
        ASSERT_EQ(result, A[A.size() - k]);
    }
}

void Ch25_Honors_Class_Fixture::p_25_14_CheckAns(const vector<int>& productivity, const vector<int>& C) {
    for (size_t i = 0; i < productivity.size(); ++i) {
        if (i > 0) {
            ASSERT_TRUE((productivity[i] > productivity[i - 1] && C[i] > C[i - 1]) ||
                   (productivity[i] < productivity[i - 1] && C[i] < C[i - 1]) ||
                   productivity[i] == productivity[i - 1]);
        }
        if (i + 1 < productivity.size()) {
            ASSERT_TRUE((productivity[i] > productivity[i + 1] && C[i] > C[i + 1]) ||
                   (productivity[i] < productivity[i + 1] && C[i] < C[i + 1]) ||
                   productivity[i] == productivity[i + 1]);
        }
    }
}

void Ch25_Honors_Class_Fixture::CheckPostingsListEqual(shared_ptr<PostingListNode> a,
                            shared_ptr<PostingListNode> b) {
    while (a && b) {
        // cout << a->order << ' ';
        ASSERT_EQ(a->order, b->order);
        ASSERT_TRUE((a->jump == shared_ptr<PostingListNode>(nullptr) &&
                b->jump == shared_ptr<PostingListNode>(nullptr)) ||
               (a->jump && b->jump && a->jump->order == b->jump->order));
        if (a->jump) {
            // cout << a->jump->order;
        }
        // cout << endl;
        a = a->next, b = b->next;
    }
    ASSERT_TRUE(a == shared_ptr<PostingListNode>(nullptr) &&
           b == shared_ptr<PostingListNode>(nullptr));
}

void Ch25_Honors_Class_Fixture::p_25_8_TestCase(const vector<string>& words, size_t L,
              const vector<string>& golden) {
    auto result = JustifyText(words, L);
    /*
    for (const string& s : result) {
        cout << "\"" << s << "\"" << endl;
    }
    cout << endl;
    */
    ASSERT_TRUE(equal(result.begin(), result.end(), golden.begin(), golden.end()));
}

void Ch25_Honors_Class_Fixture::p_25_7_CheckAns(const vector<vector<int>>& A, const vector<vector<int>>& ans) {
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < A[i].size(); ++j) {
            if (!A[i][j]) {
                for (size_t k = 0; k < ans.size(); ++k) {
                    ASSERT_FALSE(ans[k][j]);
                }
                for (size_t k = 0; k < ans[i].size(); ++k) {
                    ASSERT_FALSE(ans[i][k]);
                }
            }
        }
    }
}

vector<int> Ch25_Honors_Class_Fixture::p_25_6_RandVector(int len) {
    default_random_engine gen((random_device())());
    vector<int> ret;
    uniform_int_distribution<int> dis(0, len);
    while (len--) {
        ret.emplace_back(dis(gen));
    }
    return ret;
}

void Ch25_Honors_Class_Fixture::p_25_6_CheckAnswer(const vector<int> &A, int i, const vector<int> &rotated) {
    ASSERT_EQ(A.size(), rotated.size());
    for (size_t idx = 0; idx < A.size(); ++idx) {
        ASSERT_EQ(rotated[(idx + i) % rotated.size()], A[idx]);
    }
}

// n^2 checking
int Ch25_Honors_Class_Fixture::p_25_4_1_check_ans(const vector<int>& A) {
    int max_product = numeric_limits<int>::min();
    for (int i = 0; i < A.size(); ++i) {
        int product = 1;
        for (int j = 0; j < i; ++j) {
            product *= A[j];
        }
        for (int j = i + 1; j < A.size(); ++j) {
            product *= A[j];
        }
        if (product > max_product) {
            max_product = product;
        }
    }
    // cout << max_product << endl;
    return max_product;
}

// n^2 checking.
int Ch25_Honors_Class_Fixture::p_25_4_CheckAns(const vector<int>& A) {
    int max_product = numeric_limits<int>::min();
    for (int i = 0; i < A.size(); ++i) {
        int product = 1;
        for (int j = 0; j < i; ++j) {
            product *= A[j];
        }
        for (int j = i + 1; j < A.size(); ++j) {
            product *= A[j];
        }
        if (product > max_product) {
            max_product = product;
        }
    }
    return max_product;
}

// O(n^k) checking answer.
void Ch25_Honors_Class_Fixture::p_25_3_CheckAnsHelper(const vector<double> &A, int l, int k, int pre,
                    double ans, double *max_ans) {
  if (l == k) {
    *max_ans = max(*max_ans, ans);
  } else {
    for (int i = pre; i < A.size(); ++i) {
      p_25_3_CheckAnsHelper(A, l + 1, k, i + 1, ans + ((l & 1) ? A[i] : -A[i]),
                     max_ans);
    }
  }
}

double Ch25_Honors_Class_Fixture::p_25_3_CheckAns(const vector<double> &A, int k) {
  double ans = 0, max_ans = numeric_limits<double>::lowest();

  p_25_3_CheckAnsHelper(A, 0, 2 * k, 0, ans, &max_ans);
  // cout << "max_ans = " << max_ans << endl;
  return max_ans;
}

int Ch25_Honors_Class_Fixture::p_25_2_CheckAns(vector<int> A) {
  sort(A.begin(), A.end());
  int target = 1;

  for (int a : A) {
    if (a > 0) {
      if (a == target) {
        ++target;
      } else if (a > target) {
        return target;
      }
    }
  }
  return target;
}

TEST_F(Ch25_Honors_Class_Fixture, GCD_Function) {
    long long x = 18, y = 12;

    ASSERT_EQ(GCD1::GCD(x, y), 6);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 1000; ++times) {
        uniform_int_distribution<long long> dis(
                1, numeric_limits<long long>::max());
        x = dis(gen), y = dis(gen);

        ASSERT_EQ(GCD1::GCD(x, y), GCD2::GCD(x, y));
    }
}

TEST_F(Ch25_Honors_Class_Fixture, first_missing_positive_Function) {
    vector<int> A1= {3,3,3,-1, 2, 2};
    ASSERT_EQ(FindFirstMissingPositive(A1), 1);

    default_random_engine gen((random_device())());

    for (int times = 0; times < 10; ++times) {
        uniform_int_distribution<size_t> dis(0, 500000);
        size_t n = dis(gen);

        vector<int> A;
        uniform_int_distribution<int> dis_n(0, static_cast<int>(n));
        generate_n(back_inserter(A), n, [&] { return dis_n(gen); });
        // cout << "n = " << n << endl;
        /*
        copy(A.cbegin(), A.cend(), ostream_iterator<int>(cout, " "));
        cout << endl;
        cout << FindFirstMissingPositive(A) << " " << CheckAns(A) << endl;
        */
        ASSERT_EQ(FindFirstMissingPositive(A), p_25_2_CheckAns(A));
    }
}

TEST_F(Ch25_Honors_Class_Fixture, max_difference_k_pairs_Function) {
    default_random_engine gen((random_device())());
    int n = 30, k = 4;
    // random tests for n = 30, k = 4 for 100 times/
    for (int times = 0; times < 5; ++times) {
        vector<double> A;
        uniform_real_distribution<double> dis(0, 99);
        for (int i = 0; i < n; ++i) {
            A.emplace_back(dis(gen));
        }
        // cout << "n = " << n << ", k = " << k << endl;
        // cout << MaxKPairsProfits(A, k) << endl;
        ASSERT_EQ(p_25_3_CheckAns(A, k), MaxKPairsProfits(A, k));
    }

    uniform_int_distribution<int> n_dis(1, 60);
    n = n_dis(gen);
    uniform_int_distribution<int> k_dis(1, n / 10);
    k = (k_dis(gen));

    vector<double> A;
    uniform_real_distribution<double> dis(0, 99);
    for (int i = 0; i < n; ++i) {
        A.emplace_back(dis(gen));
    }
    //cout << "n = " << n << ", k = " << k << endl;
    // cout << CheckAns(A, k) << ", " << MaxKPairsProfits(A, k) << endl;
    ASSERT_EQ(p_25_3_CheckAns(A, k), MaxKPairsProfits(A, k));
}

TEST_F(Ch25_Honors_Class_Fixture, biggest_product_n_1) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 10000; ++times) {
        vector<int> A;
        uniform_int_distribution<int> dis(2, 11);
        int n = dis(gen);

        for (size_t i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis1(-9, 9);
            A.emplace_back(dis1(gen));
            // cout << A[i] << ' ';
        }
        // cout << endl;
        int res = FindBiggestNMinusOneProduct(A);
        ASSERT_EQ(res, p_25_4_CheckAns(A));
        // cout << res << endl;
    }
}

TEST_F(Ch25_Honors_Class_Fixture, biggest_product_n_1_math) {
    default_random_engine gen((random_device())());
    for (int times = 0; times < 100000; ++times) {
        vector<int> A;
        uniform_int_distribution<int> dis(2, 11);
        int n = dis(gen);

        for (size_t i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis1(-9, 9);
            A.emplace_back(dis1(gen));
            // cout << A[i] << ' ';
        }
        // cout << endl;
        int res = alt_math::FindBiggestNMinusOneProduct(A);
        // cout << res << endl;
        ASSERT_EQ(res, p_25_4_1_check_ans(A));
    }
}

TEST_F(Ch25_Honors_Class_Fixture, longest_increasing_subarray) {
    auto ans = FindLongestIncreasingSubarray({-1, -1});
    ASSERT_TRUE(ans.start == 0 && ans.end == 0);
    ans = FindLongestIncreasingSubarray({1, 2});
    ASSERT_TRUE(ans.start == 0 && ans.end == 1);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        vector<int> A;
        uniform_int_distribution<int> dis(1, 10000);
        int n = dis(gen);

        uniform_int_distribution<int> pos_or_neg(0, 1);
        uniform_int_distribution<int> dis1(0, n - 1);
        for (int i = 0; i < n; ++i) {
            A.emplace_back((pos_or_neg(gen) ? -1 : 1) * dis1(gen));
        }

        Subarray result = FindLongestIncreasingSubarray(A);
        // cout << result.start << ' ' << result.end << endl;

        int len = 1;
        for (int i = 1; i < A.size(); ++i) {
            if (A[i] > A[i - 1]) {
                ++len;
            } else {
                len = 1;
            }
            ASSERT_LE(len, result.end - result.start + 1);
        }
    }
}

TEST_F(Ch25_Honors_Class_Fixture, rotate_array_Function) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 1000; ++times) {
        int len;
        uniform_int_distribution<int> dis(1, 10000);
        len = dis(gen);

        vector<int> A(p_25_6_RandVector(len));
        uniform_int_distribution<int> dis1(0, len - 1);
        int i = dis1(gen);

        vector<int> B(A);
        rotate_array1::RotateArray(i, &B);
        p_25_6_CheckAnswer(A, i, B);

        vector<int> C(A);
        rotate_array2::RotateArray(i, &C);
        p_25_6_CheckAnswer(A, i, C);
    }
}

TEST_F(Ch25_Honors_Class_Fixture, rook_attack_Function) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 1000; ++times) {
        size_t m, n;
        uniform_int_distribution<size_t> dis(1, 50);
        m = dis(gen), n = dis(gen);

        vector<vector<int>> A(m, vector<int>(n));
        uniform_int_distribution<int> zero_or_one(0, 1);
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                A[i][j] = zero_or_one(gen);
            }
        }
        auto copy_A(A);
        //cout << "m = " << m << ", n = " << n << endl;
        RookAttack(&A);
        p_25_7_CheckAns(copy_A, A);
    }
}

TEST_F(Ch25_Honors_Class_Fixture, justify_text_Function) {
    vector<string> words = {"Text", "justification", "is", "trickier", "than",
                            "it",   "seems!"};
    vector<string> golden = {"Text          ", "justification ",
                             "is    trickier", "than it seems!"};
    size_t L = 14;
    // cout << "L = " << L << endl;
    p_25_8_TestCase(words, L, golden);

    words = {"Listen", "to", "many,", "speak", "to", "a", "few."};
    golden = {"Listen", "to    ", "many, ", "speak ", "to   a", "few.  "};
    L = 6;
    // cout << "L = " << L << endl;
    p_25_8_TestCase(words, L, golden);

    words = {"The",  "quick", "brown", "fox",  "jumped",
             "over", "the",   "lazy",  "dogs."};
    golden = {"The   quick", "brown   fox", "jumped over", "the    lazy",
              "dogs.      "};
    L = 11;
    // cout << "L = " << L << endl;
    p_25_8_TestCase(words, L, golden);

    golden = {"The  quick brown", "fox  jumped over", "the lazy dogs.  "};
    L = 16;
    // cout << "L = " << L << endl;
    p_25_8_TestCase(words, L, golden);

    golden = {"The  quick  brown", "fox  jumped  over", "the lazy dogs.   "};
    L = 17;
    // cout << "L = " << L << endl;
    p_25_8_TestCase(words, L, golden);

    words = {"Hello", "World"};
    golden = {"Hello World   "};
    L = 14;
    p_25_8_TestCase(words, L, golden);
}

TEST_F(Ch25_Honors_Class_Fixture, zipping_list_Function) {
    default_random_engine gen((random_device())());
    shared_ptr<ListNode<int>> head = nullptr;

    uniform_int_distribution<int> dis(1, 20);
    int n = dis(gen);

    for (int i = n; i >= 0; --i) {
        auto curr = make_shared<ListNode<int>>(ListNode<int>{i, nullptr});
        curr->next = head;
        head = curr;
    }

    shared_ptr<ListNode<int>> curr = ZippingLinkedList(head);
    int idx = 0, pre;

    while (curr) {
        ++idx;
        cout << curr->data << endl;
        pre = curr->data;
        curr = curr->next;
    }
}

TEST_F(Ch25_Honors_Class_Fixture, copying_postings_list_Function) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 1000; ++times) {
        uniform_int_distribution<int> n_dis(1, 1000);
        int n = n_dis(gen);

        shared_ptr<PostingListNode> L = nullptr;
        shared_ptr<PostingListNode> curr = L;

        for (int i = 0; i < n; ++i) {
            auto temp = make_shared<PostingListNode>(PostingListNode{i, nullptr});
            if (L) {
                curr->next = temp;
                curr = temp;
            } else {
                curr = L = temp;
            }
            // Randomly assigned a jump node.
            uniform_int_distribution<int> dis(0, i + 1);
            int jump_num = dis(gen);
            shared_ptr<PostingListNode> jump = L;
            while (jump_num--) {
                jump = jump->next;
            }
            temp->jump = jump;
        }
        shared_ptr<PostingListNode> copied = CopyPostingsList(L);
        CheckPostingsListEqual(L, copied);
    }
}

TEST_F(Ch25_Honors_Class_Fixture, longest_valid_parentheses_Function) {
    ASSERT_EQ(LongestValidParentheses(")(((())()(()("), 6);
    ASSERT_EQ(LongestValidParentheses("((())()(()("), 6);
    ASSERT_EQ(LongestValidParentheses(")("), 0);
    ASSERT_EQ(LongestValidParentheses("()"), 2);
    ASSERT_EQ(LongestValidParentheses(""), 0);
    ASSERT_EQ(LongestValidParentheses("()()())"), 6);
}

TEST_F(Ch25_Honors_Class_Fixture, sliding_window_Function) {
    int w = 3;
    vector<TrafficElement> A = {
            TrafficElement{0, 1.3}, TrafficElement{2, 2.5}, TrafficElement{3, 3.7},
            TrafficElement{5, 1.4}, TrafficElement{6, 2.6}, TrafficElement{8, 2.2},
            TrafficElement{9, 1.7}, TrafficElement{14, 1.1}};
    auto result = CalculateTrafficVolumes(A, w);

    vector<TrafficElement> golden = {
            TrafficElement{0, 1.3}, TrafficElement{2, 2.5}, TrafficElement{3, 3.7},
            TrafficElement{5, 3.7}, TrafficElement{6, 3.7}, TrafficElement{8, 2.6},
            TrafficElement{9, 2.6}, TrafficElement{14, 1.1}};
    ASSERT_TRUE(equal(golden.begin(), golden.end(), result.begin(), result.end()));
}

TEST_F(Ch25_Honors_Class_Fixture, btree_postorder_iterative_Function) {
    //      3
    //    2   5
    //  1    4 6
    unique_ptr<BinaryTreeNode<int>> tree = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{3, nullptr, nullptr});
    tree->left = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{2, nullptr, nullptr});
    tree->left->left = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{1, nullptr, nullptr});
    tree->right = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{5, nullptr, nullptr});
    tree->right->left = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{4, nullptr, nullptr});
    tree->right->right = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{6, nullptr, nullptr});
    auto res = PostorderTraversal(tree), golden_res = generate_postorder(tree);
    ASSERT_TRUE(equal(res.cbegin(), res.cend(), golden_res.cbegin(),
                 golden_res.cend()));
}

TEST_F(Ch25_Honors_Class_Fixture, btree_postorder_iterative_alt_Function) {
    //      3
    //    2   5
    //  1    4 6
    unique_ptr<BinaryTreeNode<int>> tree = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{3, nullptr, nullptr});
    tree->left = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{2, nullptr, nullptr});
    tree->left->left = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{1, nullptr, nullptr});
    tree->right = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{5, nullptr, nullptr});
    tree->right->left = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{4, nullptr, nullptr});
    tree->right->right = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{6, nullptr, nullptr});
    auto res = alt::PostorderTraversal(tree), golden_res = generate_postorder(tree);
    ASSERT_TRUE(equal(res.cbegin(), res.cend(), golden_res.cbegin(),
                 golden_res.cend()));
}

TEST_F(Ch25_Honors_Class_Fixture, bonus_Function) {
    vector<int> A = {1, 2, 2};
    vector<int> golden_A = {1, 2, 1};
    ASSERT_TRUE(EqualVector(CalculateBonus(A), golden_A));

    A = {1, 2, 3, 2, 1};
    golden_A = {1, 2, 3, 2, 1};
    ASSERT_TRUE(EqualVector(CalculateBonus(A), golden_A));

    A = {300, 400, 500, 200};
    golden_A = {1, 2, 3, 1};
    ASSERT_TRUE(EqualVector(CalculateBonus(A), golden_A));

    default_random_engine gen((random_device())());
    for (int times = 0; times < 1000; ++times) {
        uniform_int_distribution<int> dis(1, 1000);
        int n = dis(gen);

        vector<int> ratings;
        uniform_int_distribution<int> dis1(1, 10000);

        for (int i = 0; i < n; ++i) {
            ratings.emplace_back(dis(gen));
        }
        auto T = CalculateBonus(ratings);
        p_25_14_CheckAns(ratings, T);
    }
}

TEST_F(Ch25_Honors_Class_Fixture, improved_bonus_Function) {
    vector<int> A = {1, 2, 2};
    vector<int> golden_A = {1, 2, 1};
    ASSERT_TRUE(imp::EqualVector(imp::CalculateBonus(A), golden_A));

    A = {1, 2, 3, 2, 1};
    golden_A = {1, 2, 3, 2, 1};
    ASSERT_TRUE(imp::EqualVector(imp::CalculateBonus(A), golden_A));

    A = {300, 400, 500, 200};
    golden_A = {1, 2, 3, 1};
    ASSERT_TRUE(imp::EqualVector(imp::CalculateBonus(A), golden_A));

    default_random_engine gen((random_device())());
    for (int times = 0; times < 1000; ++times) {
        uniform_int_distribution<int> dis(1, 1000);
        int n = dis(gen);

        vector<int> ratings;
        uniform_int_distribution<int> dis1(1, 10000);

        for (int i = 0; i < n; ++i) {
            ratings.emplace_back(dis(gen));
        }
        auto T = imp::CalculateBonus(ratings);
        p_25_14_CheckAns(ratings, T);
    }
}

TEST_F(Ch25_Honors_Class_Fixture, binary_search_unknown_length_Function) {
    vector<int> A = {1, 2, 3};
    ASSERT_EQ(BinarySearchUnknownLength(A, 3), 2);
    ASSERT_EQ(BinarySearchUnknownLength(A, 1), 0);
    ASSERT_EQ(BinarySearchUnknownLength(A, 2), 1);
    ASSERT_EQ(BinarySearchUnknownLength(A, 4), -1);
    ASSERT_EQ(BinarySearchUnknownLength(A, -1), -1);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        uniform_int_distribution<int> n_dis(1, 1000);
        int n = n_dis(gen);
        uniform_int_distribution<int> k_dis(0, (n * 2) - 1);
        int k = k_dis(gen);

        vector<int> A;
        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> k_dis(0, (n * 2) - 1);
            A.emplace_back(k_dis(gen));
        }

        sort(A.begin(), A.end());
        // cout << n << ' ' << k << endl;
        int idx = BinarySearchUnknownLength(A, k);
        // cout << idx << endl;
        ASSERT_TRUE((idx == -1 && !binary_search(A.cbegin(), A.cend(), k)) ||
               A[idx] == k);
    }
}

TEST_F(Ch25_Honors_Class_Fixture, find_kth_in_two_array_Function) {
    // AA: handwritten test
    vector<int> A0;
    vector<int> B0;
    A0.emplace_back(0);
    A0.emplace_back(1);
    A0.emplace_back(2);
    A0.emplace_back(3);
    B0.emplace_back(0);
    B0.emplace_back(1);
    B0.emplace_back(2);
    B0.emplace_back(3);
    ASSERT_EQ(0, FindKthInTwoSortedArrays(A0, B0, 1));
    ASSERT_EQ(0, FindKthInTwoSortedArrays(A0, B0, 2));
    ASSERT_EQ(1, FindKthInTwoSortedArrays(A0, B0, 3));
    ASSERT_EQ(1, FindKthInTwoSortedArrays(A0, B0, 4));
    ASSERT_EQ(2, FindKthInTwoSortedArrays(A0, B0, 5));

    default_random_engine gen((random_device())());
    // Random test 10000 times.
    for (int times = 0; times < 100; ++times) {
        vector<int> A, B;
        uniform_int_distribution<int> dis(1, 1000);
        int n = dis(gen);
        int m = dis(gen);
        uniform_int_distribution<int> k_dis(1, n + m);
        int k = k_dis(gen);

        uniform_int_distribution<int> dis1(0, 9999);
        for (size_t i = 0; i < n; ++i) {
            A.emplace_back(dis1(gen));
        }

        for (size_t i = 0; i < m; ++i) {
            B.emplace_back(dis1(gen));
        }

        sort(A.begin(), A.end()), sort(B.begin(), B.end());
        /*
        for (int i = 0; i < A.size(); ++i) {
          cout << A[i] << ' ';
        }
        cout << endl;
        for (int j = 0; j < B.size(); ++j) {
          cout << B[j] << ' ';
        }
        cout << endl;
        */
        int ans = FindKthInTwoSortedArrays(A, B, k);
        // cout << k << "th = " << ans << endl;
        ASSERT_EQ(ans, CheckAnswer(A, B, k));
    }
}

TEST_F(Ch25_Honors_Class_Fixture, find_kth_in_two_array_template_Function) {
    // AA: handwritten test
    vector<int> A0;
    vector<int> B0;
    A0.emplace_back(0);
    A0.emplace_back(1);
    A0.emplace_back(2);
    A0.emplace_back(3);
    B0.emplace_back(0);
    B0.emplace_back(1);
    B0.emplace_back(2);
    B0.emplace_back(3);
    ASSERT_EQ(0, FindKthInTwoSortedArrays<int>(A0, B0, 1));
    ASSERT_EQ(0, FindKthInTwoSortedArrays<int>(A0, B0, 2));
    ASSERT_EQ(1, FindKthInTwoSortedArrays<int>(A0, B0, 3));
    ASSERT_EQ(1, FindKthInTwoSortedArrays<int>(A0, B0, 4));
    ASSERT_EQ(2, FindKthInTwoSortedArrays<int>(A0, B0, 5));

    default_random_engine gen((random_device())());
    // Random test 10000 times.
    for (int times = 0; times < 100; ++times) {
        vector<int> A, B;
        uniform_int_distribution<int> dis(1, 1000);
        int n = dis(gen);
        int m = dis(gen);
        uniform_int_distribution<int> k_dis(1, n + m);
        int k = k_dis(gen);

        uniform_int_distribution<int> dis1(0, 9999);
        for (size_t i = 0; i < n; ++i) {
            A.emplace_back(dis1(gen));
        }

        for (size_t i = 0; i < m; ++i) {
            B.emplace_back(dis1(gen));
        }

        sort(A.begin(), A.end()), sort(B.begin(), B.end());
        /*
        for (int i = 0; i < A.size(); ++i) {
          cout << A[i] << ' ';
        }
        cout << endl;
        for (int j = 0; j < B.size(); ++j) {
          cout << B[j] << ' ';
        }
        cout << endl;
        */
        int ans = FindKthInTwoSortedArrays<int>(A, B, k);
        // cout << k << "th = " << ans << endl;
        ASSERT_EQ(ans, CheckAnswer(A, B, k));
    }
}

TEST_F(Ch25_Honors_Class_Fixture, k_th_largest_elements_large_n) {
    vector<int> A = {5, 6, 2, 1, 3, 0, 4};
    SimpleTestArray(A);
    A = {5, -1, 2, 1, 3, 1, 4, (2 << 31) - 1, 5};
    SimpleTestArray(A);
    default_random_engine gen((random_device())());
    int N = 1000;
    A = {};
    for (int i = 0; i < N; ++i) {
        uniform_int_distribution<int> dis(0, 10 - 1);
        A.emplace_back(dis(gen));
    }
    SimpleTestArray(A);
    A = {};
    for (int i = 0; i < N; ++i) {
        uniform_int_distribution<int> dis(0, 100000000 - 1);
        A.emplace_back(dis(gen));
    }
    SimpleTestArray(A);

    for (int times = 0; times < 10; ++times) {
        int n, k;
        uniform_int_distribution<int> n_dis(1, 100000);
        n = n_dis(gen);
        uniform_int_distribution<int> k_dis(1, n);
        k = k_dis(gen);

        vector<int> A;
        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(0, 9999999);
            A.emplace_back(dis(gen));
        }
        stringstream ss;
        for (int a : A) {
            ss << a << ' ';
        }
        istringstream sin(ss.str());
        int result = FindKthLargestUnknownLength(&sin, k);
        nth_element(A.begin(), A.begin() + A.size() - k, A.end());
        // cout << result << endl << A[A.size() - k] << endl;
        ASSERT_EQ(result, A[A.size() - k]);
    }
}

TEST_F(Ch25_Honors_Class_Fixture, find_element_appears_once) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 10000; ++times) {
        vector<int> A;
        uniform_int_distribution<int> n_dis(1, 10000);
        int n = n_dis(gen);

        uniform_int_distribution<int> dis(0, n - 1);
        int single = dis(gen);
        for (int i = 0; i < n; ++i) {
            A.emplace_back(i);
            if (i != single) {
                A.emplace_back(i);
                A.emplace_back(i);
            }
        }
        // cout << "Singleton element: " << FindElementAppearsOnce(A) << endl;
        ASSERT_EQ(FindElementAppearsOnce(A), single);
        ASSERT_EQ(FindElementAppearsOnceAlternative(A), single);
    }
}

TEST_F(Ch25_Honors_Class_Fixture, line_most_points) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 100; ++times) {
        // cout << times << endl;

        // Needs at least two points to form a line.
        uniform_int_distribution<int> dis(2, 100);
        int n = dis(gen);

        vector<Point> points;
        unordered_set<Point, HashPoint> t;

        do {
            uniform_int_distribution<int> dis(0, 999);
            Point p{dis(gen), dis(gen)};
            if (t.find(p) == t.cend()) {
                points.push_back(p);
                t.emplace(p);
            }
        } while (t.size() < n);
        /*
        for (int i = 0; i < points.size(); ++i) {
          cout << points[i].x << ", " << points[i].y << endl;
        }
        */
        size_t l = FindLineWithMostPoints(points);
        // cout << l.slope.numerator << " " << l.slope.denominator << " "
        //     << l.intercept.numerator << " " << l.intercept.denominator << endl;
        size_t res = p_25_19_Check(points);
        ASSERT_EQ(res, l);
    }
}

TEST_F(Ch25_Honors_Class_Fixture, shortest_unique_prefix) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 100; ++times) {
        unordered_set<string> D;
        uniform_int_distribution<int> dis(1, 10);
        string s = RandString(dis(gen));

        uniform_int_distribution<int> dis1(1, 10000);
        int n = dis1(gen);
        while (n--) {
            uniform_int_distribution<int> dis(1, 10);
            D.emplace(RandString(dis(gen)));
        }
        // cout << s << ' ' << "shortest prefix = " << FindShortestPrefix(s, D)
        //     << endl;
        ASSERT_EQ(FindShortestPrefix(s, D), p_25_20_CheckAns(s, D));
    }
}

TEST_F(Ch25_Honors_Class_Fixture, sorted_list_to_BST) {
    auto temp0 =
            make_shared<DL::ListNode<int>>(DL::ListNode<int>{0});
    auto temp1 =
            make_shared<DL::ListNode<int>>(DL::ListNode<int>{1});
    auto temp2 =
            make_shared<DL::ListNode<int>>(DL::ListNode<int>{2});
    auto temp3 =
            make_shared<DL::ListNode<int>>(DL::ListNode<int>{3});

    temp0->next = temp1;
    temp1->next = temp2;
    temp2->next = temp3;
    temp3->next = nullptr;

    temp0->prev = nullptr;
    temp1->prev = temp0;
    temp2->prev = temp1;
    temp3->prev = temp2;

    shared_ptr<DL::ListNode<int>> L = temp0;
    auto tree = BuildBSTFromSortedDoublyList(L, 4);
    InorderTraversal(tree, -1, 0);
    // Break the links of shared_ptr to prevent memory leak.
    // See: http://talk.elementsofprogramminginterviews.com/t/doubly-linked-list-memory-leak/335
    temp1->prev = temp2->prev = temp3->prev = nullptr;

    auto node0 = make_shared<DL::ListNode<int>>(DL::ListNode<int>{2});
    auto node1 = make_shared<DL::ListNode<int>>(DL::ListNode<int>{3});
    auto node2 = make_shared<DL::ListNode<int>>(DL::ListNode<int>{5});
    auto node3 = make_shared<DL::ListNode<int>>(DL::ListNode<int>{7});
    auto node4 = make_shared<DL::ListNode<int>>(DL::ListNode<int>{11});

    // 2 - 3 - 5 - 7 - 11
    node0->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = nullptr;

    node0->prev = nullptr;
    node1->prev = node0;
    node2->prev = node1;
    node3->prev = node2;
    node4->prev = node3;

    auto tree1 = BuildBSTFromSortedDoublyList(node0, 5);
    //       5
    //     3   11
    //   2    7
    InorderTraversal(tree1, -1, 0);
    node1->prev = node2->prev = node3->prev = node4->prev = nullptr;
}

TEST_F(Ch25_Honors_Class_Fixture, BST_to_sorted_doubly_list) {
    //    3
    //  2   5
    // 1   4 6
    auto root = make_shared<BSTNode<int>>(BSTNode<int>{3});
    root->left = make_shared<BSTNode<int>>(BSTNode<int>{2});
    root->left->left = make_shared<BSTNode<int>>(BSTNode<int>{1});
    root->right = make_shared<BSTNode<int>>(BSTNode<int>{5});
    root->right->left = make_shared<BSTNode<int>>(BSTNode<int>{4});
    root->right->right = make_shared<BSTNode<int>>(BSTNode<int>{6});
    shared_ptr<BSTNode<int>> L = BSTToDoublyLinkedList(root);
    shared_ptr<BSTNode<int>> curr = L;

    int pre = numeric_limits<int>::min();

    do {
        ASSERT_LE(pre, curr->data);
        // cout << curr->data << endl;
        pre = curr->data;
        curr = curr->right;
    } while (curr);
}

TEST_F(Ch25_Honors_Class_Fixture, merge_two_BSTs) {
    //      3
    //    2   5
    //  1    4 6
    auto L = make_shared<BSTNode<int>>(BSTNode<int>{3});
    L->left = make_shared<BSTNode<int>>(BSTNode<int>{2});
    L->left->left = make_shared<BSTNode<int>>(BSTNode<int>{1});
    L->right = make_shared<BSTNode<int>>(BSTNode<int>{5});
    L->right->left = make_shared<BSTNode<int>>(BSTNode<int>{4});
    L->right->right = make_shared<BSTNode<int>>(BSTNode<int>{6});
    //     7
    //   2   8
    // 0
    auto R = make_shared<BSTNode<int>>(BSTNode<int>{7});
    R->left = make_shared<BSTNode<int>>(BSTNode<int>{2});
    R->left->left = make_shared<BSTNode<int>>(BSTNode<int>{0});
    R->right = make_shared<BSTNode<int>>(BSTNode<int>{8});

    shared_ptr<BSTNode<int>> root = MergeTwoBSTs(L, R);
    // should output 0 1 2 2 3 4 5 6 7 8
    PrintBSTInorder(root, numeric_limits<int>::min());
}

TEST_F(Ch25_Honors_Class_Fixture, view_from_above) {
    vector<LineSegment> A = {LineSegment{1, 2, 0, 1}, LineSegment{3, 4, 0, 1}};
    auto result = CalculateViewFromAbove(A);
    vector<LineSegment> golden_result = {LineSegment{1, 2, 0, 1},
                                         LineSegment{3, 4, 0, 1}};
    ASSERT_TRUE(equal(result.begin(), result.end(), golden_result.begin(),
                 golden_result.end(),
                 [](const LineSegment& a, const LineSegment& b) {
                     return a.left == b.left && a.right == b.right &&
                            a.color == b.color && a.height == b.height;
                 }));

    A = {
            LineSegment{0, 4, 0, 0},     (LineSegment{1, 3, 1, 2}),
            (LineSegment{2, 7, 2, 1}),   (LineSegment{4, 5, 3, 3}),
            (LineSegment{5, 7, 3, 0}),   (LineSegment{6, 10, 0, 2}),
            (LineSegment{8, 9, 0, 1}),   (LineSegment{9, 18, 4, 0}),
            (LineSegment{11, 13, 3, 2}), (LineSegment{12, 15, 4, 1}),
            (LineSegment{14, 15, 2, 2}), (LineSegment{16, 17, 3, 2})};
    result = CalculateViewFromAbove(A);
    golden_result = {
            LineSegment{0, 1, 0, 0},   LineSegment{1, 3, 1, 2},
            LineSegment{3, 4, 2, 1},   LineSegment{4, 5, 3, 3},
            LineSegment{5, 6, 2, 1},   LineSegment{6, 10, 0, 2},
            LineSegment{10, 11, 4, 0}, LineSegment{11, 13, 3, 2},
            LineSegment{13, 14, 4, 1}, LineSegment{14, 15, 2, 2},
            LineSegment{15, 16, 4, 0}, LineSegment{16, 17, 3, 2},
            LineSegment{17, 18, 4, 0}};
    ASSERT_TRUE(equal(result.begin(), result.end(), golden_result.begin(),
                 golden_result.end(),
                 [](const LineSegment& a, const LineSegment& b) {
                     return a.left == b.left && a.right == b.right &&
                            a.color == b.color && a.height == b.height;
                 }));
}

TEST_F(Ch25_Honors_Class_Fixture, regular_expression) {
    ASSERT_TRUE(IsMatch(".", "a"));
    ASSERT_TRUE(IsMatch("a", "a"));
    ASSERT_TRUE(!IsMatch("a", "b"));
    ASSERT_TRUE(IsMatch("a.9", "aW9"));
    ASSERT_TRUE(!IsMatch("a.9", "aW19"));
    ASSERT_TRUE(IsMatch("^a.9", "aW9"));
    ASSERT_TRUE(!IsMatch("^a.9", "baW19"));
    ASSERT_TRUE(IsMatch(".*", "a"));
    ASSERT_TRUE(IsMatch(".*", ""));
    ASSERT_TRUE(IsMatch("c*", "c"));
    ASSERT_TRUE(!IsMatch("aa*", "c"));
    ASSERT_TRUE(IsMatch("ca*", "c"));
    ASSERT_TRUE(IsMatch(".*", "asdsdsa"));
    ASSERT_TRUE(IsMatch("9$", "xxxxW19"));

    ASSERT_TRUE(IsMatch(".*a", "ba"));

    ASSERT_TRUE(IsMatch(".*a", "ba"));
    ASSERT_TRUE(IsMatch("^a.*9$", "axxxxW19"));

    ASSERT_TRUE(IsMatch("^a.*W19$", "axxxxW19"));
    ASSERT_TRUE(IsMatch(".*a.*W19", "axxxxW19123"));
    ASSERT_TRUE(!IsMatch(".*b.*W19", "axxxxW19123"));
    ASSERT_TRUE(IsMatch("n.*", "n"));
    ASSERT_TRUE(IsMatch("a*n.*", "an"));
    ASSERT_TRUE(IsMatch("a*n.*", "ana"));
    ASSERT_TRUE(IsMatch("a*n.*W19", "anaxxxxW19123"));
    ASSERT_TRUE(IsMatch(".*a*n.*W19", "asdaaadnanaxxxxW19123"));
    ASSERT_TRUE(IsMatch(".*.*.a*n.*W19", "asdaaadnanaxxxxW19123"));
}

TEST_F(Ch25_Honors_Class_Fixture, add_operator_n_string) {
    vector<int> A = {2, 3, 4};
    int k = 4;
    ASSERT_FALSE(ExpressionSynthesis(A, k));
    A = {1, 2, 3, 4};
    k = 11;
    ASSERT_TRUE(ExpressionSynthesis(A, k));
    A = {1, 2, 3, 2, 5, 3, 7, 8, 5, 9};
    k = 995;
    ASSERT_TRUE(ExpressionSynthesis(A, k));
    A = {5, 2, 3, 4, 1};
    k = 20;
    ASSERT_TRUE(ExpressionSynthesis(A, k));
    A = {1, 1, 2, 3};
    k = 124;
    ASSERT_TRUE(ExpressionSynthesis(A, k));
}

TEST_F(Ch25_Honors_Class_Fixture, count_inversions) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 10; ++times) {
        int n;
        uniform_int_distribution<int> dis(1, 10000);
        n = dis(gen);
        vector<int> A;

        for (size_t i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(-1000000, 1000000);
            A.emplace_back(dis(gen));
        }
        ASSERT_EQ(N2Check(A), CountInversions(A));
    }
}

TEST_F(Ch25_Honors_Class_Fixture, draw_skyline) {
    default_random_engine gen((random_device())());
    for (int times = 0; times < 20; ++times) {
        uniform_int_distribution<int> dis(1, 5000);
        int n = dis(gen);
        vector<Rectangle> A;

        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> left_dis(0, 999);
            int left = left_dis(gen);
            uniform_int_distribution<int> right_dis(left, left + 200);
            int right = right_dis(gen);
            uniform_int_distribution<int> height_dis(0, 99);
            int height = height_dis(gen);
            A.emplace_back(Rectangle{left, right, height});
        }
        Skyline ans = ComputeSkyline(A);
        // cout << "n = " << n << endl;
        p_25_29_CheckAnswer(ans);
    }
}

TEST_F(Ch25_Honors_Class_Fixture, draw_skyline_alt) {
    default_random_engine gen((random_device()) ());
    for (int times = 0; times < 20; ++times) {
        uniform_int_distribution<int> dis(1, 5000);
        int n = dis(gen);
        vector<alt::Rectangle> A;

        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> left_dis(0, 999);
            int left = left_dis(gen);
            uniform_int_distribution<int> right_dis(left, left + 200);
            int right = right_dis(gen);
            uniform_int_distribution<int> height_dis(0, 99);
            int height = height_dis(gen);
            A.emplace_back(alt::Rectangle{left, right, height});
        }
        alt::Skyline ans = alt::ComputeSkyline(A);
        // cout << "n = " << n << endl;
        p_25_29_CheckAnswer_alt(ans);
    }
}

TEST_F(Ch25_Honors_Class_Fixture, three_jugs) {
    int n;
    vector<Jug> jugs = {{230, 240}, {290, 310}, {500, 515}};
    ASSERT_TRUE(CheckFeasible(jugs, 2100, 2300));
    jugs.clear();
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 100);
    n = dis(gen);

    for (int i = 0; i < n; ++i) {
        Jug t;
        uniform_int_distribution<int> dis1(0, 999);
        t.low = dis1(gen);
        uniform_int_distribution<int> dis2(t.low + 1, t.low + 20);
        t.high = dis2(gen);
        jugs.emplace_back(t);
    }
    uniform_int_distribution<int> dis1(0, 9999);
    int l = dis1(gen);
    uniform_int_distribution<int> dis2(l + 1, l + 5000);
    int h = dis2(gen);
    // cout << boolalpha << CheckFeasible(jugs, l, h) << endl;
}

TEST_F(Ch25_Honors_Class_Fixture, max_subarray_in_circular) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 10; ++times) {
        vector<int> A;
        uniform_int_distribution<int> dis(1, 10000);
        int n = dis(gen);

        while (n--) {
            uniform_int_distribution<int> dis(-10000, 10000);
            A.emplace_back(dis(gen));
        }

        int ans = MaxSubarraySumInCircular(A);
        /*
        for (size_t i = 0; i < A.size(); ++i) {
          cout << A[i] << ' ';
        }
        */
        // cout << endl << "maximum sum = " << ans << endl;
        ASSERT_EQ(ans, p_25_31_CheckAns(A));
    }
}

TEST_F(Ch25_Honors_Class_Fixture, max_subarray_in_circular_constant_space) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 10; ++times) {
        vector<int> A;
        uniform_int_distribution<int> dis(1, 10000);
        int n = dis(gen);

        while (n--) {
            uniform_int_distribution<int> dis(-10000, 10000);
            A.emplace_back(dis(gen));
        }

        int ans = const_sp::MaxSubarraySumInCircular(A);
        /*
        for (size_t i = 0; i < A.size(); ++i) {
          cout << A[i] << ' ';
        }
        */
        // cout << endl << "maximum sum = " << ans << endl;
        ASSERT_EQ(ans, p_25_31_CheckAns(A));
    }
}

TEST_F(Ch25_Honors_Class_Fixture, hegiht_determination) {
    ASSERT_EQ(GetHeight(1, 10), 10);
    ASSERT_EQ(GetHeight(2, 1), 1);
    ASSERT_EQ(GetHeight(2, 2), 3);
    ASSERT_EQ(GetHeight(2, 3), 6);
    ASSERT_EQ(GetHeight(2, 4), 10);
    ASSERT_EQ(GetHeight(2, 5), 15);
    ASSERT_EQ(GetHeight(3, 2), 3);
    ASSERT_EQ(GetHeight(100, 2), 3);
    ASSERT_EQ(GetHeight(3, 5), 25);
    ASSERT_EQ(GetHeight(8, 11), 1980);
    ASSERT_EQ(GetHeight(3, 0), 0);
    ASSERT_EQ(GetHeight(3, 1), 1);
    ASSERT_EQ(GetHeight(3, 3), 7);
    ASSERT_EQ(GetHeight(0, 10), 0);
    ASSERT_EQ(GetHeight(0, 0), 0);

    ASSERT_EQ(p_25_32_CheckAnswer(1, 10), 10);
    ASSERT_EQ(p_25_32_CheckAnswer(2, 1), 1);
    ASSERT_EQ(p_25_32_CheckAnswer(2, 2), 3);
    ASSERT_EQ(p_25_32_CheckAnswer(2, 3), 6);
    ASSERT_EQ(p_25_32_CheckAnswer(2, 4), 10);
    ASSERT_EQ(p_25_32_CheckAnswer(2, 5), 15);
    ASSERT_EQ(p_25_32_CheckAnswer(3, 2), 3);
    ASSERT_EQ(p_25_32_CheckAnswer(100, 2), 3);
    ASSERT_EQ(p_25_32_CheckAnswer(3, 5), 25);
    ASSERT_EQ(p_25_32_CheckAnswer(8, 11), 1980);
    ASSERT_EQ(p_25_32_CheckAnswer(3, 0), 0);
    ASSERT_EQ(p_25_32_CheckAnswer(3, 1), 1);
    ASSERT_EQ(p_25_32_CheckAnswer(3, 3), 7);
    ASSERT_EQ(p_25_32_CheckAnswer(0, 10), 0);
    ASSERT_EQ(p_25_32_CheckAnswer(0, 0), 0);
}

TEST_F(Ch25_Honors_Class_Fixture, max_submatrix_rectangle) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 10; ++times) {
        uniform_int_distribution<int> dis(1, 50);
        int n = dis(gen);
        int m = dis(gen);

        vector<deque<bool>> A(n, deque<bool>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                uniform_int_distribution<int> true_or_false(0, 1);
                A[i][j] = true_or_false(gen) ? true : false;
            }
        }

        /*
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << A[i][j] << ' ';
            }
            cout << endl;
        }
        */
        // cout << MaxRectangleSubmatrix(A) << endl;
        int test_area = MaxRectangleSubmatrixBruteForce(A);
        // cout << test_area << endl;
        ASSERT_EQ(test_area, MaxRectangleSubmatrix(A));
    }
}

TEST_F(Ch25_Honors_Class_Fixture, max_submatrix_rectangle_improved) {
    default_random_engine gen((random_device()) ());

    for (int times = 0; times < 10; ++times) {
        uniform_int_distribution<int> dis(1, 60);
        int n = dis(gen);
        int m = dis(gen);
        vector<deque<bool>> A(n, deque<bool>(m));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                uniform_int_distribution<int> true_or_false(0, 1);
                A[i][j] = true_or_false(gen);
            }
        }
        /*
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < m; ++j) {
            cout << A[i][j] << ' ';
          }
          cout << endl;
        }
        */
        // cout << MaxRectangleSubmatrix(A) << endl;
        // cout << MaxRectangleSubmatrixBruteForce(A) << endl;
        ASSERT_EQ(MaxRectangleSubmatrixBruteForce(A), impl::MaxRectangleSubmatrix(A));
    }
}

TEST_F(Ch25_Honors_Class_Fixture, max_submatrix_square) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 10; ++times) {
        uniform_int_distribution<int> dis(1, 50);
        int n = dis(gen);
        int m = dis(gen);

        vector<deque<bool>> A(n, deque<bool>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                uniform_int_distribution<int> true_or_false(0, 1);
                A[i][j] = true_or_false(gen) ? true : false;
            }
        }
        /*
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << A[i][j] << ' ';
            }
            cout << endl;
        }
        cout << MaxSquareSubmatrix(A) << endl;
        cout << CheckAns(A) << endl;
         */
        ASSERT_EQ(p_25_33_CheckAns(A), square::MaxSquareSubmatrix(A));
    }
}

TEST_F(Ch25_Honors_Class_Fixture, huffman_encoding) {
    int n = 26;
    default_random_engine gen((random_device())());

    vector<huffman::CharWithFrequency> symbols;
    int sum = 0;

    for (int i = 0; i < n; ++i) {
        huffman::CharWithFrequency t;
        t.character = 'a' + i;
        t.freq = huffman::kEnglishFreq[i];
        symbols.emplace_back(t);
    }

    auto result = huffman::HuffmanEncoding(&symbols);
    double avg = 0.0;

    for (const auto& symbol : symbols) {
        // cout << symbol.character << " " << symbol.freq << " " << result[symbol.character] << endl;
        avg += symbol.freq / 100 * result[symbol.character].size();
    }
    //cout << "average huffman code length = " << avg << endl;
    ASSERT_EQ(result['a'], "1110");
    ASSERT_EQ(result['b'], "110000");
    ASSERT_EQ(result['c'], "01001");
    ASSERT_EQ(result['d'], "11111");
    ASSERT_EQ(result['e'], "100");
    ASSERT_EQ(result['f'], "00101");
    ASSERT_EQ(result['g'], "110011");
    ASSERT_EQ(result['h'], "0110");
    ASSERT_EQ(result['i'], "1011");
    ASSERT_EQ(result['j'], "001001011");
    ASSERT_EQ(result['k'], "0010011");
    ASSERT_EQ(result['l'], "11110");
    ASSERT_EQ(result['m'], "00111");
    ASSERT_EQ(result['n'], "1010");
    ASSERT_EQ(result['o'], "1101");
    ASSERT_EQ(result['p'], "110001");
    ASSERT_EQ(result['q'], "001001001");
    ASSERT_EQ(result['r'], "0101");
    ASSERT_EQ(result['s'], "0111");
    ASSERT_EQ(result['t'], "000");
    ASSERT_EQ(result['u'], "01000");
    ASSERT_EQ(result['v'], "001000");
    ASSERT_EQ(result['w'], "00110");
    ASSERT_EQ(result['x'], "001001010");
    ASSERT_EQ(result['y'], "110010");
    ASSERT_EQ(result['z'], "001001000");
    ASSERT_GE(avg, 4.205);
    ASSERT_LT(avg, 4.206);
}

TEST_F(Ch25_Honors_Class_Fixture, trapping_rain_water) {
    vector<int> A = {1, 0, 3, 2, 5, 0, 1};
    ASSERT_EQ(CalculateTrappingWater(A), 3);
    A = {1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1};
    ASSERT_EQ(CalculateTrappingWater(A), 18);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<int> n_dis(1, 1000);
        int n = n_dis(gen);

        vector<int> A;
        uniform_int_distribution<int> A_dis(0, 10);

        generate_n(back_inserter(A), n, [&] { return A_dis(gen); });
        // copy(A.cbegin(), A.cend(), ostream_iterator<int>(cout, " "));
        // cout << endl;
        // cout << CheckAnswer(A) << " " << CalculateTrappingWater(A) << endl;
        ASSERT_EQ(p_25_35_CheckAnswer(A), CalculateTrappingWater(A));
    }
}

TEST_F(Ch25_Honors_Class_Fixture, search_pair_sorted_array) {
    vector<int> A = {0, 0, -1, 2, -3, -3};
    IndexPair ans = FindPairSumK(A, 2);
    ASSERT_NE(ans.index_1, -1);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        uniform_int_distribution<int> dis(1, 10000);
        int n = dis(gen);

        vector<int> A;
        uniform_int_distribution<int> dis1(-10000, 10000);
        generate_n(back_inserter(A), n, [&] { return dis1(gen); });
        sort(A.begin(), A.end(), [](int x, int y) { return abs(x) < abs(y); });
        int k = dis1(gen);
        IndexPair ans = FindPairSumK(A, k);

        if (ans.index_1 != -1 && ans.index_2 != -1) {
            ASSERT_EQ(A[ans.index_1] + A[ans.index_2], k);
            // cout << A[ans.index_1] << "+" << A[ans.index_2] << "=" << k << endl;
        } else {
            sort(A.begin(), A.end());
            int l = 0, r = A.size() - 1;
            bool found = false;
            while (l < r) {
                if (A[l] + A[r] == k) {
                    // cout << A[l] << "+" << A[r] << "=" << k << endl;
                    found = true;
                    break;
                } else if (A[l] + A[r] < k) {
                    ++l;
                } else {
                    --r;
                }
            }
            // cout << "no answer" << endl;
            ASSERT_FALSE(found);
        }
    }
}

TEST_F(Ch25_Honors_Class_Fixture, search_frequent_items) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 10; ++times) {
        // cout << times << endl;
        vector<string> stream;
        uniform_int_distribution<int> n_dis(0, 99999);
        int n = n_dis(gen);
        uniform_int_distribution<int> k_dis(1, n);
        int k = k_dis(gen);

        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(1, 5);
            stream.emplace_back(p_25_37_RandString(dis(gen)));
        }

        string s;
        for (int i = 0; i < stream.size(); ++i) {
            s += stream[i];
            s += ' ';
        }
        istringstream sin(s);
        vector<string> items = SearchFrequentItems(k, &sin);
        p_25_37_CheckAns(&stream, k, &items);
    }
}

TEST_F(Ch25_Honors_Class_Fixture, longest_subarray_k) {
    vector<int> A0 = {431, -15, 639, 342, -14, 565, -924, 635, 167, -70};
    long_sub::Subarray res = long_sub::find_longest_subarray_less_equal_k(A0, 184);
    ASSERT_EQ(res.start, 3);
    ASSERT_EQ(res.end, 6);

    default_random_engine gen((random_device())());

    for (int times = 0; times < 10; ++times) {
        uniform_int_distribution<int> n_dis(1, 10000);
        int n = n_dis(gen);
        uniform_int_distribution<int> k_dis(0, 9999);
        int k = k_dis(gen);
        vector<int> A;

        for (size_t i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(-1000, 1000);
            A.emplace_back(dis(gen));
        }
        /*
        copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
        */
        long_sub::Subarray ans = long_sub::find_longest_subarray_less_equal_k(A, k);
        // cout << k << ' ' << ans.start << ' ' << ans.end << endl;
        p_25_38_check_answer(A, ans, k);
    }
}

TEST_F(Ch25_Honors_Class_Fixture, logest_subarray_k_improved) {
    vector<int> A = {1, 1};
    int k = 0;
    int res = FindLongestSubarrayLessEqualK(A, k);
    ASSERT_EQ(res, 0);
    k = -100;
    res = FindLongestSubarrayLessEqualK(A, k);
    ASSERT_EQ(res, 0);

    A = {431, -15, 639, 342, -14, 565, -924, 635, 167, -70};
    res = FindLongestSubarrayLessEqualK(A, 184);
    ASSERT_EQ(res, 4);

    default_random_engine gen((random_device()) ());
    for (int times = 0; times < 10; ++times) {
        uniform_int_distribution<int> n_dis(1, 10000);
        int n = n_dis(gen);
        uniform_int_distribution<int> k_dis(0, 9999);
        int k = k_dis(gen);

        vector<int> A;
        for (size_t i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(-1000, 1000);
            A.emplace_back(dis(gen));
        }
        int ans = FindLongestSubarrayLessEqualK(A, k);
        // cout << k << ' ' << ans << endl;
        p_25_38_2_CheckAnswer(A, ans, k);
    }
}

TEST_F(Ch25_Honors_Class_Fixture, road_network) {
    vector<HighwaySection> H = {HighwaySection{0, 1, 10},
                                HighwaySection{1, 2, 10},
                                HighwaySection{2, 3, 10}};
    vector<HighwaySection> P = {HighwaySection{0, 3, 1},
                                HighwaySection{0, 2, 2},
                                HighwaySection{0, 1, 3}};
    HighwaySection t = FindBestProposals(H, P, 4);
    ASSERT_TRUE(t.x == 0 && t.y == 3 && t.distance == 1.0);

    for (int times = 0; times < 10; ++times) {
        default_random_engine gen((random_device())());

        uniform_int_distribution<int> five_to_100(5, 100);
        int n = five_to_100(gen);
        uniform_int_distribution<int> dis1(1, n * ((n - 1) / 2) - 1);
        int m = dis1(gen);
        uniform_int_distribution<int> dis2(1, n * ((n - 1) / 2) - m);
        int k = dis2(gen);

        //cout << "n = " << n << ", m = " << m << ", k = " << k << endl;

        vector<deque<bool>> have_edges(n, deque<bool>(n, false));
        vector<HighwaySection> H;  // Existing highway sections
        uniform_int_distribution<int> vertex_dis(0, n - 1);
        uniform_real_distribution<double> cost_dis(1.0, 10000.0);
        for (int i = 0; i < m; ++i) {
            int a, b;
            do {
                a = vertex_dis(gen), b = vertex_dis(gen);
            } while (a == b || have_edges[a][b] == true);
            have_edges[a][b] = have_edges[b][a] = true;
            H.emplace_back(HighwaySection{a, b, cost_dis(gen)});
        }
        /*
        for (int i = 0; i < m; ++i) {
            cout << "H[i] = " << H[i].x << " " << H[i].y << " " << H[i].distance
                 << endl;
        }
        */

        vector<HighwaySection> P;  // Proposals
        for (int i = 0; i < k; ++i) {
            int a, b;
            do {
                a = vertex_dis(gen), b = vertex_dis(gen);
            } while (a == b || have_edges[a][b] == true);
            have_edges[a][b] = have_edges[b][a] = true;
            uniform_real_distribution<double> new_cost_dis(1.0, 50.0);
            P.emplace_back(HighwaySection{a, b, new_cost_dis(gen)});
        }
        /*
        for (int i = 0; i < k; ++i) {
            cout << "P[i] = " << P[i].x << " " << P[i].y << " " << P[i].distance
                 << endl;
        }
        */

        HighwaySection t = FindBestProposals(H, P, n);
        // cout << t.x << ' ' << t.y << ' ' << t.distance << endl;
    }
}

TEST_F(Ch25_Honors_Class_Fixture, arbitrage) {
    default_random_engine gen((random_device())());

    uniform_int_distribution<int> n_dis(1, 100);
    int n = n_dis(gen);

    vector<vector<double>> G(n, vector<double>(n));
    // Assume the input is a complete graph.
    for (size_t i = 0; i < G.size(); ++i) {
        G[i][i] = 1;
        for (size_t j = i + 1; j < G.size(); ++j) {
            uniform_real_distribution<double> dis(0, 1);
            G[i][j] = dis(gen);
            G[j][i] = 1.0 / G[i][j];
        }
    }
    bool res = IsArbitrageExist(G);
    // cout << boolalpha << res << endl;

    vector<vector<double>> g(3, vector<double>(3));
    for (size_t i = 0; i < 3; ++i) {
        g[i][i] = 1;
    }
    g[0][1] = 2, g[1][0] = 0.5, g[0][2] = g[2][0] = 1, g[1][2] = 4,
    g[2][1] = 0.25;
    res = IsArbitrageExist(g);
    ASSERT_EQ(res, true);
    // cout << boolalpha << IsArbitrageExist(g) << endl;
}
