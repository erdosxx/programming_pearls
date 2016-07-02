#include <gtest/gtest.h>
#include <random>
#include <limits>
#include <unordered_set>
#include <cmath>
#include <string>
#include "Intersect_sorted_arrays1.h"
#include "Intersect_sorted_arrays2.h"
#include "Intersect_sorted_arrays3.h"
#include "merge-two-sorted-arrays-in-place.h"
#include "Eliminate_duplicate.h"
#include "Rendering_calendar.h"
#include "insert-interval.h"

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

class Ch14_Sorting_Fixture : public ::testing::Test {
private:

protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    void p_14_1_CheckAns(const vector<int>&, const vector<int>&, const vector<int>&);
    void p_14_2_CheckAns(const vector<int>&);
    void p_14_3_CheckAns(const vector<Name>&);
    void p_14_5_CheckIntervals(const vector<Interval>&);

public:
    Ch14_Sorting_Fixture() : Test() {

    }

    virtual ~Ch14_Sorting_Fixture() {
    }
};

void Ch14_Sorting_Fixture::p_14_1_CheckAns(const vector<int> &a, const vector<int> &b,
              const vector<int> &c) {
    ASSERT_TRUE(equal(a.begin(), a.end(), b.begin(), b.end()));
    ASSERT_TRUE(equal(b.begin(), b.end(), c.begin(), c.end()));
}

void Ch14_Sorting_Fixture::p_14_2_CheckAns(const vector<int>& A) {
    for (size_t i = 1; i < A.size(); ++i) {
        ASSERT_LE(A[i - 1], A[i]);
    }
}

void Ch14_Sorting_Fixture::p_14_3_CheckAns(const vector<Name>& A) {
    for (size_t i = 1; i < A.size(); ++i) {
        ASSERT_FALSE(A[i] == A[i - 1]);
    }
}

void Ch14_Sorting_Fixture::p_14_5_CheckIntervals(const vector<Interval>& result) {
    // Only check the intervals do not overlap with each other.
    for (size_t i = 1; i < result.size(); ++i) {
        ASSERT_LT(result[i - 1].right, result[i].left);
    }
}

TEST_F(Ch14_Sorting_Fixture, intersect_sorted_array_Function) {
    default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        vector<int> A, B;
        uniform_int_distribution<int> dis(1, 1000);
        int n = dis(gen);
        int m = dis(gen);

        uniform_int_distribution<int> n_dis(0, n - 1);
        for (int i = 0; i < n; ++i) {
            A.emplace_back(n_dis(gen));
        }

        uniform_int_distribution<int> m_dis(0, m - 1);
        for (int j = 0; j < m; ++j) {
            B.emplace_back(m_dis(gen));
        }

        sort(A.begin(), A.end());
        sort(B.begin(), B.end());

        vector<int> res1 =
            std::move(IntersectTwoSortedArrays1::IntersectTwoSortedArrays(A, B));
        vector<int> res2 =
            std::move(IntersectTwoSortedArrays2::IntersectTwoSortedArrays(A, B));
        vector<int> res3 =
            std::move(IntersectTwoSortedArrays3::IntersectTwoSortedArrays(A, B));
        p_14_1_CheckAns(res1, res2, res3);
    }
}

TEST_F(Ch14_Sorting_Fixture, merge_two_sorted_array_Function) {
    default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<size_t> size_dis(0, 1000);
        size_t m = size_dis(gen);
        size_t n = size_dis(gen);

        uniform_int_distribution<int> dis(-(m + n), m + n);
        vector<int> A(m + n), B;
        for (size_t i = 0; i < m; ++i) {
            A[i] = dis(gen);
        }

        generate_n(back_inserter(B), n, [&] { return dis(gen); });
        sort(A.begin(), A.begin() + m);
        sort(B.begin(), B.end());

        MergeTwoSortedArrays(A.data(), m, B.data(), n);
        p_14_2_CheckAns(A);
    }
}

TEST_F(Ch14_Sorting_Fixture, eliminate_duplicate_Function) {
    vector<Name> A = {{"Foo", "Bar"}, {"ABC", "XYZ"}, {"Foo", "Widget"}};
    EliminateDuplicate(&A);
    ASSERT_EQ(A.size(), 2);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 1000; ++times) {
        vector<Name> A;
        uniform_int_distribution<int> dis(0, 1000);
        int n = dis(gen);

        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(0, n - 1);
            A.emplace_back(Name{to_string(dis(gen)), to_string(dis(gen))});
        }
        EliminateDuplicate(&A);
        p_14_3_CheckAns(A);
    }
}

TEST_F(Ch14_Sorting_Fixture, rendering_calendar_Function) {
    vector<Event> A = {{1, 5},  {2, 7},   {4, 5},   {6, 10}, {8, 9},
                       {9, 17}, {11, 13}, {12, 15}, {14, 15}};
    ASSERT_EQ(FindMaxSimultaneousEvents(A), 3);

    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 100000);
    int n = dis(gen);

    A.clear();
    for (int i = 0; i < n; ++i) {
        Event temp;
        uniform_int_distribution<int> dis1(0, 99999);
        temp.start = dis1(gen);
        uniform_int_distribution<int> dis2(temp.start + 1, temp.start + 10000);
        temp.finish = dis2(gen);
        A.emplace_back(temp);
    }
    int ans = FindMaxSimultaneousEvents(A);
    cout << ans << endl;
}

TEST_F(Ch14_Sorting_Fixture, insert_interval_Function) {
    vector<Interval> A = {{1, 5}};
    Interval new_one = {0, 3};
    auto result = AddInterval(A, new_one);
    ASSERT_TRUE(result.size() == 1 && result.front().left == 0 &&
           result.front().right == 5);
    new_one = {0, 0};
    result = AddInterval(A, new_one);
    ASSERT_TRUE(result.size() == 2 && result.front().left == 0 &&
           result.front().right == 0 && result.back().left == 1 &&
           result.back().right == 5);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 1000; ++times) {
        uniform_int_distribution<size_t> dis(1, 10000);
        size_t n = dis(gen);

        A.clear();
        int pre = 0;
        uniform_int_distribution<int> dis1(1, 10);
        for (size_t i = 0; i < n; ++i) {
            Interval temp;
            temp.left = pre + dis1(gen);
            temp.right = temp.left + dis1(gen);
            pre = temp.right;
            A.emplace_back(temp);
        }
        uniform_int_distribution<int> tar_dis(0, 100);
        Interval target;
        target.left = tar_dis(gen);
        target.right = target.left + tar_dis(gen);
        auto result = AddInterval(A, target);
        p_14_5_CheckIntervals(result);
    }
}
