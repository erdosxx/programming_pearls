#include <gtest/gtest.h>
#include <random>
#include <limits>
#include <unordered_set>
#include <cmath>
#include <string>
#include "sorting_boot_camp.h"
#include "Square_root.h"
#include "Intersect_sorted_arrays1.h"
#include "Intersect_sorted_arrays2.h"
#include "Intersect_sorted_arrays3.h"
#include "merge-two-sorted-arrays-in-place.h"
#include "Eliminate_duplicate.h"
#include "Rendering_calendar.h"
#include "insert-interval.h"
#include "Union_intervals.h"
#include "partition-array.h"
#include "Team_photo_1.h"
#include "insertion-sort-list.h"
#include "sort-list.h"
#include "Completion_search.h"

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
    void p_14_6_CheckIntervals(const vector<p_14_6::Interval>&);
    string p_14_7_RandString(int len);

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

void Ch14_Sorting_Fixture::p_14_6_CheckIntervals(const vector<p_14_6::Interval>& A) {
    // Only check the intervals do not overlap with each other.
    for (size_t i = 1; i < A.size(); ++i) {
        ASSERT_TRUE(A[i - 1].right.val < A[i].left.val ||
               (A[i - 1].right.val == A[i].left.val && !A[i - 1].right.isClosed &&
                !A[i].left.isClosed));
    }
}

string Ch14_Sorting_Fixture::p_14_7_RandString(int len) {
    string ret;
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    uniform_int_distribution<int> char_dis(0, 25);
    while (len--) {
        ret += 'a' + char_dis(gen);
    }
    return ret;
}

TEST_F(Ch14_Sorting_Fixture, sorting_boot_camp) {
    vector<Student> students = { {"a", 3}, {"b", 5}, {"c", 2}, {"d", 4}};

    SortByName(&students);
    ASSERT_TRUE(
            students[0].name == "a" &&
            students[1].name == "b" &&
            students[2].name == "c" &&
            students[3].name == "d"
    );
    SortByGPA(&students);
    ASSERT_TRUE(
            Compare(students[0].grade_point_average, 5) == EQUAL &&
            Compare(students[1].grade_point_average, 4) == EQUAL &&
            Compare(students[2].grade_point_average, 3) == EQUAL &&
            Compare(students[3].grade_point_average, 2) == EQUAL
    );

}

TEST_F(Ch14_Sorting_Fixture, intersect_sorted_array_Function) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
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
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
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

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
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

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
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

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
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

TEST_F(Ch14_Sorting_Fixture, union_intervals_Function) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    for (int times = 0; times < 1000; ++times) {
        uniform_int_distribution<int> dis(1, 1000);
        int n = dis(gen);
        vector<p_14_6::Interval> A;

        for (int i = 0; i < n; ++i) {
            p_14_6::Interval temp;
            uniform_int_distribution<int> zero_or_one(0, 1);
            uniform_int_distribution<int> dis1(0, 9999);
            temp.left.isClosed = zero_or_one(gen);
            temp.left.val = dis1(gen);

            uniform_int_distribution<int> dis2(temp.left.val + 1,
                                               temp.left.val + 100);
            temp.right.isClosed = zero_or_one(gen);
            temp.right.val = dis2(gen);
            A.emplace_back(temp);
        }
        vector<p_14_6::Interval> ret = p_14_6::UnionOfIntervals(A);
        if (!ret.empty()) {
            p_14_6_CheckIntervals(ret);
        }
    }
}

TEST_F(Ch14_Sorting_Fixture, partition_array_Function) {
    vector<Person> people = {Person({20, "foo"}), Person({10, "bar"}),
                             Person({20, "widget"}), Person({20, "something"})};

    GroupByAge(&people);
    if (people[0].age == 10) {
        ASSERT_TRUE(people[1].age == 20 && people[2].age == 20 && people[3].age == 20);
    } else {
        ASSERT_TRUE(people[1].age == 20 && people[2].age == 20 && people[3].age == 10);
    }

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        uniform_int_distribution<int> dis(1, 10000);
        int size = dis(gen);

        uniform_int_distribution<int> dis1(1, size);
        int k = dis1(gen);

        vector<Person> person_array;
        uniform_int_distribution<int> k_dis(0, k - 1);
        uniform_int_distribution<int> len_dis(1, 10);

        for (int i = 0; i < size; ++i) {
            person_array.emplace_back(Person{k_dis(gen), p_14_7_RandString(len_dis(gen))});
        }

        unordered_set<int> age_set;
        for (const Person& p : person_array) {
            age_set.emplace(p.age);
        }

        GroupByAge(&person_array);

        // Check the correctness of sorting.
        int diff_count = 1;
        for (int i = 1; i < person_array.size(); ++i) {
            if (person_array[i].age != person_array[i - 1].age) {
                ++diff_count;
            }
        }
        ASSERT_EQ(diff_count, age_set.size());
    }
}

TEST_F(Ch14_Sorting_Fixture, team_photo_Function) {
    vector<int> height = {1, 5, 4};
    Team t1(height);
    height = {2, 3, 4};
    Team t2(height);
    ASSERT_TRUE(!Team::valid_placement_exists(t1, t2) &&
           !Team::valid_placement_exists(t2, t1));
    height = {0, 3, 2};
    Team t3(height);
    ASSERT_TRUE(Team::valid_placement_exists(t3, t1) &&
           !Team::valid_placement_exists(t1, t3) &&
           Team::valid_placement_exists(t3, t2) &&
           !Team::valid_placement_exists(t1, t2));
}

TEST_F(Ch14_Sorting_Fixture, sort_list_Function) {
    // 1 -> 4 -> 3 -> 2 -> 5
    shared_ptr<ListNode<int>> L;
    L = make_shared<ListNode<int>>(ListNode<int>{
            1, make_shared<ListNode<int>>(ListNode<int>{
                    4, make_shared<ListNode<int>>(ListNode<int>{
                            3, make_shared<ListNode<int>>(ListNode<int>{
                                    2, make_shared<ListNode<int>>(
                                            ListNode<int>{5, nullptr})})})})});
    auto result = InsertionSort(L);
    shared_ptr<ListNode<int>> pre = nullptr;
    while (result) {
        ASSERT_TRUE(!pre || pre->data <= result->data);
        pre = result;
        //cout << result->data << endl;
        result = result->next;
    }

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    for (int times = 0; times < 10000; ++times) {
        shared_ptr<ListNode<int>> L = nullptr;
        uniform_int_distribution<int> dis(0, 99);
        int n = dis(gen);

        for (int i = n; i > 0; --i) {
            shared_ptr<ListNode<int>> temp =
                    make_shared<ListNode<int>>(ListNode<int>{dis(gen), nullptr});
            temp->next = L;
            L = temp;
        }

        auto sorted_head = StableSortList(L);
        int count = 0;
        int pre = numeric_limits<int>::min();
        while (sorted_head) {
            ASSERT_LE(pre, sorted_head->data);
            pre = sorted_head->data;
            sorted_head = sorted_head->next;
            ++count;
        }
        ASSERT_EQ(count, n);
    }
}

TEST_F(Ch14_Sorting_Fixture, salary_threshold_Function) {
    vector<double> A = {20, 30, 40, 90, 100};
    double T = 210;
    ASSERT_EQ(FindSalaryCap(T, A), 60);
    T = 280;
    ASSERT_EQ(FindSalaryCap(T, A), 100);
    T = 50;
    ASSERT_EQ(FindSalaryCap(T, A), 10);
    T = 281;
    ASSERT_EQ(FindSalaryCap(T, A), -1.0);

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        A.clear();
        double tar;

        uniform_int_distribution<int> n_dis(1, 1000);
        int n = n_dis(gen);
        uniform_int_distribution<int> tar_dis(0, 99999);
        tar = tar_dis(gen);

        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(0, 9999);
            A.emplace_back(dis(gen));
        }
        // cout << "A = ";
        // copy(A.begin(), A.end(), ostream_iterator<double>(cout, " "));
        // cout << endl;
        // cout << "tar = " << tar << endl;
        double ret = FindSalaryCap(tar, A);
        sort(A.begin(), A.end());

        if (ret != -1.0) {
        //    cout << "ret = " << ret << endl;
            double sum = 0.0;
            for (int i = 0; i < n; ++i) {
                if (A[i] > ret) {
                    sum += ret;
                } else {
                    sum += A[i];
                }
            }
            tar -= sum;
        //    cout << "sum = " << sum << endl;
            ASSERT_LT(tar, 1.0e-8);
        }
    }
}
