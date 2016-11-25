#include <gtest/gtest.h>
#include <random>
#include <limits>
#include "heaps_boot_camp.h"
#include "Merge_sorted_arrays.h"
#include "sort_k-increasing-decreasing_array.h"
#include "Approximate_sort.h"
#include "Closest_stars.h"
#include "Online_median.h"
#include "k-largest-elements-binary-heap.h"
#include "Stack_queue_using_heap.h"

using std::istringstream;
using std::stringstream;
using std::default_random_engine;
using std::random_device;
using std::unique_ptr;
using std::numeric_limits;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::is_sorted;

class Ch11Heaps_Fixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    Ch11Heaps_Fixture() : Test() {

    }

    virtual ~Ch11Heaps_Fixture() {
    }
};

TEST_F(Ch11Heaps_Fixture, heaps_boot_camp) {
    /*
    vector<string> input_data = {"1", "3bc", "2c", "7aaaaaa", "4ccc", "5addc", "6aeadf"};

    stringstream ss;
    for (string str : input_data) {
        ss << str << ' ';
    }
    istringstream str_sequence(ss.str());
    */
    string input_str = "1 3bc 2c 7aaaaaa 4ccc 5addc 6aeadf";
    istringstream str_sequence(input_str);

    vector<string> result;
    result = TopK(3, &str_sequence);
    sort(result.begin(), result.end());
    vector<string> golden_sol = {"5addc", "6aeadf", "7aaaaaa"};
    ASSERT_TRUE(equal(result.cbegin(), result.cend(), golden_sol.cbegin(), golden_sol.cend()));
}

TEST_F(Ch11Heaps_Fixture, stl_library) {
    // default is map_heap
    priority_queue<int, vector<int>> max_heap; // {4,2,3,5,6,8,9};
    max_heap.emplace(4);
    max_heap.emplace(2);
    max_heap.emplace(3);
    max_heap.emplace(5);
    max_heap.emplace(6);
    max_heap.emplace(8);
    max_heap.emplace(9);
    ASSERT_EQ(9, max_heap.top());
    max_heap.pop();
    ASSERT_EQ(8, max_heap.top());

    vector<int> data = {4,2,3,5,6,8,9};
    priority_queue<int> max_heap2; // = {4,2,3,5,6,8,9};
    max_heap2.emplace(4);
    max_heap2.emplace(2);
    max_heap2.emplace(3);
    max_heap2.emplace(5);
    max_heap2.emplace(6);
    max_heap2.emplace(8);
    max_heap2.emplace(9);
    ASSERT_EQ(7, max_heap2.size());
    max_heap2.pop();
    ASSERT_EQ(6, max_heap2.size());
    ASSERT_EQ(8, max_heap2.top());
    max_heap2.pop();
    max_heap2.pop();
    max_heap2.pop();
    max_heap2.pop();
    max_heap2.pop();
    max_heap2.pop();
    ASSERT_EQ(0, max_heap2.size());
    //max_heap2.pop(); // more pops than size, do not work.

    //same as following priority_queue<int, vector<int>, greater<int>> min_heap3;
    priority_queue<int, vector<int>, greater<>> min_heap3;
    min_heap3.emplace(4);
    min_heap3.emplace(2);
    min_heap3.emplace(3);
    min_heap3.emplace(5);
    min_heap3.emplace(6);
    min_heap3.emplace(8);
    min_heap3.emplace(9);
    ASSERT_EQ(2, min_heap3.top());
    min_heap3.pop();
    ASSERT_EQ(3, min_heap3.top());
}

TEST_F(Ch11Heaps_Fixture, merge_sorted_arrays_Function) {
    vector<vector<int>> S = {
            {1, 5, 10}, {2, 3, 100}, {2, 12, numeric_limits<int>::max()}};
    auto ans = MergeSortedArrays(S);
    vector<int> golden = {
            1, 2, 2, 3, 5, 10, 12, 100, numeric_limits<int>::max()};
    ASSERT_TRUE(equal(ans.begin(), ans.end(), golden.begin(), golden.end()));

    S = {{1}};
    ans = MergeSortedArrays(S);
    ASSERT_TRUE(ans.size() == 1 && ans.front() == 1);

    S = {{}, {1}, {2}};
    ans = MergeSortedArrays(S);
    ASSERT_TRUE(ans.size() == 2 && ans[0] == 1 && ans[1] == 2);

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<int> dis(1, 100);
        int n = dis(gen);

        vector<vector<int>> S(n, vector<int>());
        for (size_t i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(1, 50);
            S[i].resize(dis(gen));
            for (size_t j = 0; j < S[i].size(); ++j) {
                uniform_int_distribution<int> dis(-9999, 9999);
                S[i][j] = dis(gen);
            }
            sort(S[i].begin(), S[i].end());
        }
        vector<int> ans = MergeSortedArrays(S);
        for (size_t i = 1; i < ans.size(); ++i) {
            ASSERT_TRUE(ans[i - 1] <= ans[i]);
        }
    }
}

TEST_F(Ch11Heaps_Fixture, sort_k_inc_dec_Function) {
    vector<int> A = {1, 2, 3, 2, 1, 4, 5, 10, 9, 4, 4, 1, -1};
    auto ans = SortKIncreasingDecreasingArray(A);
    ASSERT_TRUE(ans.size() == A.size() && is_sorted(ans.cbegin(), ans.cend()));

    A = {numeric_limits<int>::min(), -1, 0, 1, 2, 4, 8,
         numeric_limits<int>::max()};
    ans = SortKIncreasingDecreasingArray(A);
    ASSERT_TRUE(ans.size() == A.size() && is_sorted(ans.cbegin(), ans.cend()));

    reverse(A.begin(), A.end());
    ans = SortKIncreasingDecreasingArray(A);
    ASSERT_TRUE(ans.size() == A.size() && is_sorted(ans.cbegin(), ans.cend()));

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<int> dis(1, 1000);
        int n = dis(gen);

        vector<int> A;
        uniform_int_distribution<int> dis1(-999999, 999999);
        generate_n(back_inserter(A), n, [&] { return dis1(gen); });
        vector<int> ans = SortKIncreasingDecreasingArray(A);
        ASSERT_EQ(ans.size(), A.size());
        ASSERT_TRUE(is_sorted(ans.cbegin(), ans.cend()));
    }
}

TEST_F(Ch11Heaps_Fixture, approximate_sort_Function) {
    vector<int> A = {2, 1, 5, 4, 3, 9, 8, 7, 6};
    stringstream ss;

    for (int a : A) {
        ss << a << ' ';
    }
    istringstream sequence(ss.str());

    vector<int> result;
    result = SortApproximatelySortedData(&sequence, 3);

    vector<int> golden_result = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    ASSERT_TRUE(equal(result.begin(), result.end(), golden_result.begin(),
                 golden_result.end()));

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    uniform_int_distribution<int> n_dis(1, 100000);
    int n = n_dis(gen);

    vector<int> A1;
    uniform_int_distribution<int> dis(1, 999999);
    for (int i = 0; i < n; ++i) {
        A1.push_back(dis(gen));
    }
    ASSERT_EQ(A1.size(), n);
    stringstream ss1;
    for (int a : A1) {
        ss1 << a << ' ';
    }
    istringstream sequence1(ss1.str());
    vector<int> result1 = SortApproximatelySortedData(&sequence1, n - 1);
    sort(A1.begin(), A1.end());
    ASSERT_TRUE(equal(result1.begin(), result1.end(), A1.begin(), A1.end()));
}

TEST_F(Ch11Heaps_Fixture, closest_stars_Function) {
    vector<Star> stars;
    stars.emplace_back((Star{1, 2, 3}));
    stars.emplace_back((Star{5, 5, 5}));
    stars.emplace_back((Star{0, 2, 1}));
    stars.emplace_back((Star{9, 2, 1}));
    stars.emplace_back((Star{1, 2, 1}));
    stars.emplace_back((Star{2, 2, 1}));
    istringstream sin(CreateStreamingString(stars));
    vector<Star> closest_stars = FindClosestKStars(3, &sin);
    ASSERT_EQ(3, closest_stars.size());
    ASSERT_EQ(closest_stars[0].Distance(), (Star{0, 2, 1}.Distance()));
    ASSERT_EQ(closest_stars[0].Distance(), (Star{2, 0, 1}.Distance()));
    ASSERT_EQ(closest_stars[1].Distance(), (Star{1, 2, 1}.Distance()));
    ASSERT_EQ(closest_stars[1].Distance(), (Star{1, 1, 2}.Distance()));

    stars.clear();
    stars.emplace_back((Star{1, 2, 3}));
    stars.emplace_back((Star{5, 5, 5}));
    stars.emplace_back((Star{4, 4, 4}));
    stars.emplace_back((Star{3, 2, 1}));
    stars.emplace_back((Star{5, 5, 5}));
    stars.emplace_back((Star{3, 2, 3}));
    stars.emplace_back((Star{3, 2, 3}));
    stars.emplace_back((Star{3, 2, 1}));
    istringstream sin2(CreateStreamingString(stars));
    closest_stars = FindClosestKStars(2, &sin2);
    ASSERT_EQ(2, closest_stars.size());
    ASSERT_EQ(closest_stars[0].Distance(), (Star{1, 2, 3}.Distance()));
    ASSERT_EQ(closest_stars[1].Distance(), (Star{3, 2, 1}.Distance()));

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        int num, k;
        uniform_int_distribution<int> num_dis(1, 100);
        num = num_dis(gen);
        uniform_int_distribution<int> k_dis(1, num);
        k = k_dis(gen);
        vector<Star> stars;
        // Randomly generate num of stars.
        uniform_real_distribution<double> dis(0, 10000);
        for (int i = 0; i < num; ++i) {
            stars.emplace_back(Star{dis(gen), dis(gen), dis(gen)});
        }
        istringstream sin(CreateStreamingString(stars));
        vector<Star> closest_stars(FindClosestKStars(k, &sin));
        sort(closest_stars.begin(), closest_stars.end());
        sort(stars.begin(), stars.end());
        //cout << "k = " << k << endl;
        //cout << stars[k - 1].x << " " << stars[k - 1].y << " " << stars[k - 1].z
        //<< " " << stars[k - 1].Distance() << endl;
        //cout << closest_stars.back().x << " " << closest_stars.back().y << " "
        //<< closest_stars.back().z << " " << closest_stars.back().Distance()
        //<< endl;
        ASSERT_TRUE(fabs(stars[k - 1].Distance() - closest_stars.back().Distance()) <
               1.0e-2);
    }
}

TEST_F(Ch11Heaps_Fixture, online_median_Function) {
    vector<double> result;
    istringstream sequence("5 4 3 2 1");
    result = move(OnlineMedian(&sequence));
    vector<double> golden = {5, 4.5, 4, 3.5, 3};
    ASSERT_TRUE(equal(golden.begin(), golden.end(), result.begin(),
                 result.end()));

    result.clear();
    istringstream sequence1("1 2 3 4 5");
    result = move(OnlineMedian(&sequence1));
    golden = {1, 1.5, 2, 2.5, 3};
    ASSERT_TRUE(equal(golden.begin(), golden.end(), result.begin(),
                 result.end()));

    result.clear();
    istringstream sequence2("1 0 3 5 2 0 1");
    result = move(OnlineMedian(&sequence2));
    golden = {1, 0.5, 1, 2, 2, 1.5, 1};
    ASSERT_TRUE(equal(golden.begin(), golden.end(), result.begin(),
                 result.end()));

    result.clear();
    istringstream sequence3("-1");
    result = move(OnlineMedian(&sequence3));
    golden = {-1.0};
    ASSERT_TRUE(equal(golden.begin(), golden.end(), result.begin(),
                 result.end()));

    result.clear();
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 100000);
    int num = dis(gen);

    vector<int> stream;
    for (int i = 0; i < num; ++i) {
        uniform_int_distribution<int> dis(1, 10000);
        stream.emplace_back(dis(gen));
    }
    string s;
    for (int i = 0; i < stream.size(); ++i) {
        //cout << stream[i] << endl;
        stringstream ss;
        ss << stream[i];
        s += ss.str();
        s += ' ';
    }
    // cout << endl;
    istringstream sequence4(s);
    result = move(OnlineMedian(&sequence4));
}

TEST_F(Ch11Heaps_Fixture, k_largest_elements_Function) {
    vector<int> max_heap = {10, 2, 9, 2, 2, 8, 8, 2, 2, 2, 2, 7, 7, 7, 7};
    auto result = KLargestInBinaryHeap(max_heap, 3);
    vector<int> expected_result = {10, 9, 8};
    ASSERT_TRUE(equal(result.begin(), result.end(), expected_result.begin(),
                 expected_result.end()));
    result = KLargestInBinaryHeap(max_heap, 5);
    expected_result = {10, 9, 8, 8, 7};
    ASSERT_TRUE(equal(result.begin(), result.end(), expected_result.begin(),
                 expected_result.end()));

    max_heap = {97, 84, 93, 83, 81, 90, 79, 83, 55, 42, 21, 73};
    result = KLargestInBinaryHeap(max_heap, 3);
    expected_result = {97, 93, 90};
    ASSERT_TRUE(equal(result.begin(), result.end(), expected_result.begin(),
                 expected_result.end()));

    max_heap = {100, 1, 5, 0, 0};
    result = KLargestInBinaryHeap(max_heap, 1);
    expected_result = {100};
    ASSERT_TRUE(equal(result.begin(), result.end(), expected_result.begin(),
                 expected_result.end()));
}

TEST_F(Ch11Heaps_Fixture, stack_queue_Function) {
    Stack s;
    s.Push(1);
    s.Push(2);
    s.Push(3);
    ASSERT_EQ(s.Peek(), 3);
    s.Pop();
    ASSERT_EQ(s.Peek(), 2);
    s.Pop();
    s.Push(4);
    ASSERT_EQ(s.Peek(), 4);
    s.Pop();
    s.Pop();
    ASSERT_THROW(s.Pop(), length_error);

    s.Push(0);
    s.Push(-1);
    s.Push(numeric_limits<int>::max());
    ASSERT_EQ(s.Peek(), numeric_limits<int>::max());
    s.Pop();
    ASSERT_EQ(s.Peek(), -1);
    s.Pop();
    ASSERT_EQ(s.Peek(), 0);
    s.Pop();
    ASSERT_THROW(s.Pop(), length_error);

    s.Push(0);
    ASSERT_EQ(s.Peek(), 0);

    Queue q;
    q.Enqueue(1);
    q.Enqueue(2);
    ASSERT_EQ(q.Head(), 1);
    q.Dequeue();
    ASSERT_EQ(q.Head(), 2);
    q.Dequeue();
    ASSERT_THROW(q.Dequeue(), length_error);
}
