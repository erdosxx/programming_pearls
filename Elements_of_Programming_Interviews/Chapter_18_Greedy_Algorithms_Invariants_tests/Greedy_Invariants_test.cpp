#include <gtest/gtest.h>
#include <random>
#include <limits>
#include <unordered_set>
#include <cmath>
#include <string>
#include <deque>
#include "coin_change.h"
#include "Task_assignment.h"
#include "Minimum_waiting_time.h"
#include "Points_covering_intervals_sorting.h"
#include "Points_covering_intervals.h"
#include "Points_covering_intervals_alternative.h"
#include "2_sum.h"
#include "3-sum.h"
#include "Search_majority.h"
#include "Gassing_up.h"
#include "container-with-most-water.h"
#include "Largest_rectangle_under_skyline.h"

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

class Ch18_Greedy_Invariants_Fixture : public ::testing::Test {
private:

protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    void p_18_3_CheckAns(const vector<Interval>& intervals, const vector<int>& ans);
    void p_18_3_alt_CheckAns(const vector<alt::Interval>& intervals, const vector<int>& ans);
    void p_18_3_sorting_CheckAns(const vector<sorting::Interval>& intervals, const vector<int>& ans);
    bool p_18_4_CheckAns(const vector<int>& A, int t);
    bool p_18_4_1_CheckAns(const vector<int>& A, int t);
    string p_18_5_RandString(int len);
    void p_18_5_CheckAns(vector<string>& stream, const string& ans);
    void p_18_6_CheckAns(const vector<int>& gallons, const vector<int>& distances, size_t c);
    int p_18_7_CheckAns(const vector<int>& heights);
    int p_18_8_CheckAnswer(const vector<int>& A);

public:
    Ch18_Greedy_Invariants_Fixture() : Test() {

    }

    virtual ~Ch18_Greedy_Invariants_Fixture() {
    }
};

int Ch18_Greedy_Invariants_Fixture::p_18_8_CheckAnswer(const vector<int>& A) {
    int max = -1;
    for (int i = 0; i < A.size(); ++i) {
        int left = i - 1, right = i + 1;
        while (left >= 0 && A[left] >= A[i]) {
            --left;
        }
        while (right < A.size() && A[right] >= A[i]) {
            ++right;
        }
        int area = (right - left - 1) * A[i];
        if (area > max) {
            max = area;
        }
    }
    // cout << max << endl;
    return max;
}

// O(n^2) checking answer.
int Ch18_Greedy_Invariants_Fixture::p_18_7_CheckAns(const vector<int>& heights) {
  int res = 0;
  for (size_t i = 0; i < heights.size(); ++i) {
    for (size_t j = i + 1; j < heights.size(); ++j) {
      res = max(res, min(heights[i], heights[j]) * static_cast<int>(j - i));
    }
  }
  return res;
}

void Ch18_Greedy_Invariants_Fixture::p_18_6_CheckAns(const vector<int>& gallons, const vector<int>& distances, size_t c) {
    size_t s = c;
    int gas = 0;
    do {
        gas += gallons[s] - distances[s] / kMPG;
        ASSERT_GE(gas, 0);
        s = (s + 1) % gallons.size();
    } while (s != c);
}

string Ch18_Greedy_Invariants_Fixture::p_18_5_RandString(int len) {
    default_random_engine gen((random_device())());
    string ret;
    while (len--) {
        uniform_int_distribution<int> dis('a', 'z');
        ret += dis(gen);
    }
    return ret;
}

void Ch18_Greedy_Invariants_Fixture::p_18_5_CheckAns(vector<string>& stream, const string& ans) {
    sort(stream.begin(), stream.end());
    int candidate_count = 1;
    bool find = false;
    for (int i = 1; i < stream.size(); ++i) {
        if (stream[i].compare(stream[i - 1])) {
            if (candidate_count * 2 >= stream.size()) {
                ASSERT_EQ(ans.compare(stream[i - 1]), 0);
                find = true;
            }
            candidate_count = 1;
        } else {
            ++candidate_count;
        }
    }
    if (candidate_count * 2 >= stream.size()) {
        ASSERT_EQ(ans.compare(stream.back()), 0);
        find = true;
    }
    ASSERT_EQ(find, true);
}

bool Ch18_Greedy_Invariants_Fixture::p_18_4_CheckAns(const vector<int>& A, int t) {
    for (int i = 0; i < A.size(); ++i) {
        for (int j = i; j < A.size(); ++j) {
            if (A[i] + A[j] == t) {
                return true;
            }
        }
    }
    return false;
}

bool Ch18_Greedy_Invariants_Fixture::p_18_4_1_CheckAns(const vector<int>& A, int t) {
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A.size(); ++j) {
            for (int k = 0; k < A.size(); ++k) {
                if (A[i] + A[j] + A[k] == t) {
                    return true;
                }
            }
        }
    }
    return false;
}

// O(n^2) checking solution
void Ch18_Greedy_Invariants_Fixture::p_18_3_CheckAns(const vector<Interval>& intervals, const vector<int>& ans) {
    deque<bool> is_visited(intervals.size(), false);
    for (int a : ans) {
        for (int i = 0; i < intervals.size(); ++i) {
            if (a >= intervals[i].left && a <= intervals[i].right) {
                is_visited[i] = true;
            }
        }
    }

    for (bool b : is_visited) {
        ASSERT_EQ(b, true);
    }
}

void Ch18_Greedy_Invariants_Fixture::p_18_3_alt_CheckAns(const vector<alt::Interval>& intervals, const vector<int>& ans) {
    deque<bool> is_visited(intervals.size(), false);
    for (int a : ans) {
        for (int i = 0; i < intervals.size(); ++i) {
            if (a >= intervals[i].left && a <= intervals[i].right) {
                is_visited[i] = true;
            }
        }
    }

    for (bool b : is_visited) {
        ASSERT_EQ(b, true);
    }
}

void Ch18_Greedy_Invariants_Fixture::p_18_3_sorting_CheckAns(const vector<sorting::Interval>& intervals, const vector<int>& ans) {
    deque<bool> is_visited(intervals.size(), false);
    for (int a : ans) {
        for (int i = 0; i < intervals.size(); ++i) {
            if (a >= intervals[i].left && a <= intervals[i].right) {
                is_visited[i] = true;
            }
        }
    }

    for (bool b : is_visited) {
        ASSERT_EQ(b, true);
    }
}

TEST_F(Ch18_Greedy_Invariants_Fixture, coin_change) {
    ASSERT_EQ(1, ChangeMaking(100));
    ASSERT_EQ(2, ChangeMaking(101));
    ASSERT_EQ(6, ChangeMaking(68));
    ASSERT_EQ(136, ChangeMaking(13142));
}

TEST_F(Ch18_Greedy_Invariants_Fixture, task_assignment_Function) {
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 10000);
    int n = dis(gen);

    vector<int> A;
    for (size_t i = 0; i < n; ++i) {
        uniform_int_distribution<int> dis(0, 999);
        A.emplace_back(dis(gen));
    }

    vector<PairedTasks> P(OptimumTaskAssignment(A));

    int max = numeric_limits<int>::min();

    for (size_t i = 0; i < P.size(); ++i) {
        if (P[i].task_1 + P[i].task_2 > max) {
            max = P[i].task_1 + P[i].task_2;
        }
    }

    cout << max << endl;
}

TEST_F(Ch18_Greedy_Invariants_Fixture, min_waiting_time_Function) {
  ASSERT_EQ(10, MinimumTotalWaitingTime({5, 1, 2, 3}));

  /*
  default_random_engine gen((random_device())());
  uniform_int_distribution<int> dis(1, 100);
  int n = dis(gen);

  vector<int> waiting_time;
  for (int i = 0; i < n; ++i) {
    uniform_int_distribution<int> dis(0, 999);
    waiting_time.push_back(dis(gen));
  }

  for (int i = 0; i < n; ++i) {
    cout << waiting_time[i] << ' ';
  }
  cout << endl;
  cout << MinimumTotalWaitingTime(waiting_time) << endl;
  */
}

TEST_F(Ch18_Greedy_Invariants_Fixture, points_covering_Function) {
    vector<Interval> intervals;
    intervals.emplace_back(Interval{1, 4});
    intervals.emplace_back(Interval{2, 8});
    intervals.emplace_back(Interval{3, 6});
    intervals.emplace_back(Interval{3, 5});
    intervals.emplace_back(Interval{7, 10});
    intervals.emplace_back(Interval{9, 11});
    vector<int> ans = FindMinimumVisits(intervals);
    ASSERT_TRUE(ans.size() == 2 && ans[0] == 4 && ans[1] == 10);

    intervals.clear();
    intervals.emplace_back(Interval{1, 2});
    intervals.emplace_back(Interval{2, 3});
    intervals.emplace_back(Interval{3, 4});
    intervals.emplace_back(Interval{4, 5});
    intervals.emplace_back(Interval{5, 6});
    intervals.emplace_back(Interval{6, 7});
    ans = FindMinimumVisits(intervals);
    ASSERT_TRUE(ans.size() == 3 && ans[0] == 2 && ans[1] == 4 && ans[2] == 6);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        // cout << "Test " << times << endl;
        uniform_int_distribution<int> dis(1, 10000);
        int n = dis(gen);

        vector<Interval> A;
        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis1(0, 9999);
            int left = dis1(gen);
            uniform_int_distribution<int> dis2(left + 1, left + 100);
            int right = dis2(gen);
            A.emplace_back(Interval{left, right});
        }
        vector<int> ans(FindMinimumVisits(A));
        p_18_3_CheckAns(A, ans);
    }
}

TEST_F(Ch18_Greedy_Invariants_Fixture, points_covering_alt_Function) {
    vector<alt::Interval> intervals;
    intervals.emplace_back(alt::Interval{1, 4});
    intervals.emplace_back(alt::Interval{2, 8});
    intervals.emplace_back(alt::Interval{3, 6});
    intervals.emplace_back(alt::Interval{3, 5});
    intervals.emplace_back(alt::Interval{7, 10});
    intervals.emplace_back(alt::Interval{9, 11});
    vector<int> ans = alt::FindMinimumVisits(intervals);
    ASSERT_TRUE(ans.size() == 2 && ans[0] == 4 && ans[1] == 10);

    intervals.clear();
    intervals.emplace_back(alt::Interval{1, 2});
    intervals.emplace_back(alt::Interval{2, 3});
    intervals.emplace_back(alt::Interval{3, 4});
    intervals.emplace_back(alt::Interval{4, 5});
    intervals.emplace_back(alt::Interval{5, 6});
    intervals.emplace_back(alt::Interval{6, 7});
    ans = alt::FindMinimumVisits(intervals);
    ASSERT_TRUE(ans.size() == 3 && ans[0] == 2 && ans[1] == 4 && ans[2] == 6);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        // cout << "Test " << times << endl;
        uniform_int_distribution<int> dis(1, 10000);
        int n = dis(gen);

        vector<alt::Interval> A;
        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis1(0, 9999);
            int left = dis1(gen);
            uniform_int_distribution<int> dis2(left + 1, left + 100);
            int right = dis2(gen);
            A.emplace_back(alt::Interval{left, right});
        }
        vector<int> ans(alt::FindMinimumVisits(A));
        p_18_3_alt_CheckAns(A, ans);
    }
}

TEST_F(Ch18_Greedy_Invariants_Fixture, points_covering_sorting_Function) {
    vector<sorting::Interval> intervals;
    intervals.emplace_back(sorting::Interval{1, 4});
    intervals.emplace_back(sorting::Interval{2, 8});
    intervals.emplace_back(sorting::Interval{3, 6});
    intervals.emplace_back(sorting::Interval{3, 5});
    intervals.emplace_back(sorting::Interval{7, 10});
    intervals.emplace_back(sorting::Interval{9, 11});
    vector<int> ans = sorting::FindMinimumVisits(intervals);
    ASSERT_TRUE(ans.size() == 2 && ans[0] == 4 && ans[1] == 10);

    intervals.clear();
    intervals.emplace_back(sorting::Interval{1, 2});
    intervals.emplace_back(sorting::Interval{2, 3});
    intervals.emplace_back(sorting::Interval{3, 4});
    intervals.emplace_back(sorting::Interval{4, 5});
    intervals.emplace_back(sorting::Interval{5, 6});
    intervals.emplace_back(sorting::Interval{6, 7});
    ans = sorting::FindMinimumVisits(intervals);
    ASSERT_TRUE(ans.size() == 3 && ans[0] == 2 && ans[1] == 4 && ans[2] == 6);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        // cout << "Test " << times << endl;
        uniform_int_distribution<int> dis(1, 10000);
        int n = dis(gen);

        vector<sorting::Interval> A;
        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis1(0, 9999);
            int left = dis1(gen);
            uniform_int_distribution<int> dis2(left + 1, left + 100);
            int right = dis2(gen);
            A.emplace_back(sorting::Interval{left, right});
        }
        vector<int> ans(sorting::FindMinimumVisits(A));
        p_18_3_sorting_CheckAns(A, ans);
    }
}

TEST_F(Ch18_Greedy_Invariants_Fixture, 2_sum_Function) {
    default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        uniform_int_distribution<int> dis(1, 10000);
        int n = dis(gen);
        uniform_int_distribution<int> T_dis(0, n - 1);
        int T = T_dis(gen);

        vector<int> A;

        for (size_t i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(-100000, 100000);
            A.emplace_back(dis(gen));
        }
        sort(A.begin(), A.end());
        // cout << boolalpha << TwoSum::HasTwoSum(A, T) << endl;
        ASSERT_EQ(p_18_4_CheckAns(A, T), TwoSum::HasTwoSum(A, T));
    }
}

TEST_F(Ch18_Greedy_Invariants_Fixture, 3_sum_Function) {
    default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        uniform_int_distribution<int> dis(1, 10000);
        int n = dis(gen);
        uniform_int_distribution<int> T_dis(0, n - 1);
        int T = T_dis(gen);

        vector<int> A;

        for (size_t i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(-100000, 100000);
            A.emplace_back(dis(gen));
        }
        //cout << boolalpha << HasThreeSum(A, T) << endl;
        ASSERT_EQ(p_18_4_1_CheckAns(A, T), HasThreeSum(A, T));
    }
}

TEST_F(Ch18_Greedy_Invariants_Fixture, search_majority_Function) {
    default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        vector<string> stream;

        uniform_int_distribution<int> n_dis(1, 1000);
        int n = n_dis(gen);

        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(1, 5);
            stream.emplace_back(p_18_5_RandString(dis(gen)));
        }

        // generate the majority
        for (int i = 0; i < n; ++i) {
            stream.emplace_back(stream.back());
        }

        string s;

        for (int i = 0; i < stream.size(); ++i) {
            s += stream[i];
            s += ' ';
        }

        istringstream input_stream(s);
        string ret(MajoritySearch(&input_stream));
        // cout << ret << endl;
        p_18_5_CheckAns(stream, ret);
    }
}

TEST_F(Ch18_Greedy_Invariants_Fixture, gassing_up_Function) {
     // Example in the book.
    vector<int> gallons = {20, 15, 15, 15, 35, 25, 30, 15, 65, 45, 10, 45, 25};
    vector<int> distances = {15 * kMPG, 20 * kMPG, 50 * kMPG, 15 * kMPG,
                             15 * kMPG, 30 * kMPG, 20 * kMPG, 55 * kMPG,
                             20 * kMPG, 50 * kMPG, 10 * kMPG, 15 * kMPG,
                             15 * kMPG};
    size_t ans = FindAmpleCity(gallons, distances);
    ASSERT_EQ(ans, 8);
    p_18_6_CheckAns(gallons, distances, ans);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 1000; ++times) {
        uniform_int_distribution<int> dis(1, 10000);
        int n = dis(gen);

        vector<int> gallons, distances;
        int sum = 0;

        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(1, 200);
            int x = dis(gen);
            sum += x;
            gallons.emplace_back(x);
        }

        sum -= n;
        for (int i = 0; i < n; ++i) {
            int x = 0;
            if (sum) {
                uniform_int_distribution<int> dis(1, sum);
                x = dis(gen);
            }
            distances.emplace_back(x + 1);
            sum -= x;
        }

        distances.back() += sum;
        size_t c = FindAmpleCity(gallons, distances);
        // cout << "start city = " << c << endl;
        p_18_6_CheckAns(gallons, distances, c);
    }
}

TEST_F(Ch18_Greedy_Invariants_Fixture, container_water_Function) {
    vector<int> A = {1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1};
    ASSERT_EQ(48, GetMaxTrappedWater(A));

    default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        uniform_int_distribution<size_t> dis(2, 10000);
        size_t n = dis(gen);
        uniform_int_distribution<int> dis_1000(1, 1000);
        vector<int> heights;

        generate_n(back_inserter(heights), n, [&] { return dis_1000(gen); });
        //cout << GetMaxTrappedWater(heights) << endl;
        ASSERT_EQ(GetMaxTrappedWater(heights), p_18_7_CheckAns(heights));
    }
}

TEST_F(Ch18_Greedy_Invariants_Fixture, skyline_Function) {
    vector<int> A = {2, 3, 4, 1, 2};
    int area = CalculateLargestRectangle(A);
    int alter_area = CalculateLargestRectangleAlternative(A);
    ASSERT_EQ(area, alter_area);
    ASSERT_EQ(p_18_8_CheckAnswer(A), area);
    ASSERT_EQ(6, area);
    A = {2, 2, 2};
    ASSERT_EQ(6, CalculateLargestRectangle(A));
    A = {1, 1, 2};
    ASSERT_EQ(3, CalculateLargestRectangle(A));

    default_random_engine gen((random_device())());
    for (int times = 0; times < 30; ++times) {
        vector<int> A;
        uniform_int_distribution<int> dis(1, 1000);
        int n = dis(gen);

        while (n--) {
            uniform_int_distribution<int> dis(0, 999);
            A.emplace_back(dis(gen));
        }

        int area = CalculateLargestRectangle(A);
        int alter_area = CalculateLargestRectangleAlternative(A);
        // cout << area << " " << alter_area << endl;
        ASSERT_EQ(area, alter_area);
        ASSERT_EQ(p_18_8_CheckAnswer(A), area);
    }
}
