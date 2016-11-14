#include <gtest/gtest.h>
#include <algorithm>
#include <random>
#include <limits>
#include <unordered_set>
#include <cmath>
#include "Bentleybsearch.h"
#include "student_search.h"
#include "Binary_search_first_k.h"
#include "Binary_search_Ai=i.h"
#include "Binary_search_circular_array.h"
#include "Binary_search_circular_array_with_duplicates.h"
#include "square-root-int.h"
#include "Square_root.h"
#include "Matrix_search.h"
#include "Finding_min_max.h"
#include "order_statistic.h"
#include "Missing_element.h"
#include "Find_missing_and_duplicate_XOR.h"

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
using std::binary_search;
using std::lower_bound;
using std::upper_bound;

class Ch12Searching_Fixture : public ::testing::Test {
private:
    static void CheckOrderStatistic(int K, bool increasing_order, vector<int>* A_ptr);

protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    static void RandomTestFixedN(int N);
    static void TestAllOrders(const vector<int>& order, vector<int>* A_ptr);

public:
    Ch12Searching_Fixture() : Test() {

    }

    virtual ~Ch12Searching_Fixture() {
    }
};

void Ch12Searching_Fixture::CheckOrderStatistic(int K, bool increasing_order,
                                vector<int>* A_ptr) {
    vector<int> B(*A_ptr);
    if (increasing_order) {
        FindKthSmallest(K, A_ptr);
    } else {
        FindKthLargest(K, A_ptr);
    }

    vector<int> B_sort(B);
    sort(B_sort.begin(), B_sort.end());
    if (!increasing_order) {
        reverse(B_sort.begin(), B_sort.end());
    }

    vector<int> A_sort(*A_ptr);
    sort(A_sort.begin(), A_sort.end());
    if (!increasing_order) {
        reverse(A_sort.begin(), A_sort.end());
    }

    ASSERT_TRUE(equal(A_sort.begin(), A_sort.end(), B_sort.begin(), B_sort.end()));
}

void Ch12Searching_Fixture::TestAllOrders(const vector<int>& order, vector<int>* A_ptr) {
    for (int K : order) {
        CheckOrderStatistic(K, true, A_ptr);
        CheckOrderStatistic(K, false, A_ptr);
    }
}

void Ch12Searching_Fixture::RandomTestFixedN(int N) {
    vector<int> order;
    for (int i = 0; i < 5; ++i) {
        order.emplace_back(min(N, i + 1));
    }
    order.emplace_back(min(N, 7));
    order.emplace_back(min(N, 9));
    order.emplace_back(min(N, 12));
    order.emplace_back(min(N, max(N / 2 - 1, 1)));
    order.emplace_back(min(N, max(N / 2, 1)));
    order.emplace_back(min(N, N / 2 + 1));
    order.emplace_back(max(1, N - 1));
    order.emplace_back(N);

    vector<int> A;
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(0, 9999999);
    for (int i = 0; i < N; ++i) {
        A.emplace_back(dis(gen));
    }
    TestAllOrders(order, &A);

    A.clear();
    uniform_int_distribution<int> n_dis(0, N - 1);
    for (int i = 0; i < N; ++i) {
        A.emplace_back(n_dis(gen));
    }
    TestAllOrders(order, &A);

    A.clear();
    uniform_int_distribution<int> n2_dis(0, 2 * N - 1);
    for (int i = 0; i < N; ++i) {
        A.emplace_back(n2_dis(gen));
    }
    TestAllOrders(order, &A);

    A.clear();
    uniform_int_distribution<int> n_half_dis(0, max(N / 2, 1) - 1);
    for (int i = 0; i < N; ++i) {
        A.emplace_back(n_half_dis(gen));
    }
    TestAllOrders(order, &A);
}

TEST_F(Ch12Searching_Fixture, Bentley_bsearch_Function) {
    vector<int> A = {1, 2, 3};
    ASSERT_EQ(0, bentley::bsearch(1, A));
    ASSERT_EQ(1, bentley::bsearch(2, A));
    ASSERT_EQ(2, bentley::bsearch(3, A));
    ASSERT_EQ(-1, bentley::bsearch(4, A));
    ASSERT_EQ(-1, bentley::bsearch(0, A));
    A = {2, 2, 2};
    ASSERT_TRUE(0 <= bentley::bsearch(2, A) && bentley::bsearch(2, A) <= 2);
    ASSERT_EQ(-1, bentley::bsearch(3, A));
    ASSERT_EQ(-1, bentley::bsearch(0, A));

    A.clear();
    A.emplace_back(1);
    A.emplace_back(2);
    A.emplace_back(2);
    A.emplace_back(2);
    A.emplace_back(2);
    A.emplace_back(3);
    A.emplace_back(3);
    A.emplace_back(3);
    A.emplace_back(5);
    A.emplace_back(6);
    A.emplace_back(10);
    A.emplace_back(100);
    ASSERT_EQ(0, bentley::bsearch(1, A));
    ASSERT_TRUE(1 <= bentley::bsearch(2, A) && bentley::bsearch(2, A) <= 4);
    ASSERT_LE(5, bentley::bsearch(3, A));
    ASSERT_EQ(-1, bentley::bsearch(4, A));
}

TEST_F(Ch12Searching_Fixture, student_search) {
    vector<Student> students = {{"A", 4.0}, {"C", 3.0}, {"B", 2.0}, {"D", 3.2}};
    sort(students.begin(), students.end(), CompGPA);
    ASSERT_TRUE(SearchStudent(students, {"A", 4.0}, CompGPA));
    ASSERT_FALSE(SearchStudent(students, {"A", 3.0}, CompGPA));
    ASSERT_FALSE(SearchStudent(students, {"B", 3.0}, CompGPA));
    ASSERT_TRUE(SearchStudent(students, {"D", 3.2}, CompGPA));
    ASSERT_TRUE(binary_search(students.cbegin(), students.cend(), Student{"A", 4.0}, CompGPA));

    ASSERT_TRUE(SearchStudent2(students, {"A", 4.0}, compGPA_lamda));
    ASSERT_FALSE(SearchStudent2(students, {"A", 3.0}, compGPA_lamda));
    ASSERT_FALSE(SearchStudent2(students, {"B", 3.0}, compGPA_lamda));
    ASSERT_TRUE(SearchStudent2(students, {"D", 3.2}, compGPA_lamda));

    // Not work: ASSERT_TRUE(binary_search(students.cbegin(), students.cend(), {"A", 4.0}, compGPA_lamda));
    ASSERT_TRUE(binary_search(students.cbegin(), students.cend(), Student{"A", 4.0}, compGPA_lamda));

    ASSERT_TRUE(binary_search(students.cbegin(), students.cend(), Student{"A", 4.0}, comp_student_f_ptr));

    vector<Student_with_compare> students_comp = {{"A", 40}, {"B", 30}, {"C", 30}, {"D", 20}, {"E", 32}};
    sort(students_comp.begin(), students_comp.end());
    ASSERT_EQ("A", students_comp[0].name);
    ASSERT_EQ("E", students_comp[1].name);
    ASSERT_EQ("B", students_comp[2].name);
    ASSERT_EQ("C", students_comp[3].name);
    ASSERT_EQ("D", students_comp[4].name);
    // Not work: ASSERT_TRUE(binary_search(students_comp.begin(), students_comp.end(), {"A", 40}));
    ASSERT_TRUE(binary_search(students_comp.cbegin(), students_comp.cend(), Student_with_compare{"A", 40}));
    // Not work: ASSERT_TRUE(binary_search(students_comp.begin(), students_comp.end(), {"A", 40}, compare_dec_gpa_inc_name()));

    ASSERT_TRUE(binary_search(students_comp.cbegin(), students_comp.cend(), Student_with_compare{"A", 40}, compare_dec_gpa_inc_name()));
    ASSERT_EQ("A", find(students_comp.cbegin(), students_comp.cend(), Student_with_compare{"A", 40})->name);
    ASSERT_EQ("B", lower_bound(students_comp.cbegin(), students_comp.cend(), Student_with_compare{"B", 30})->name);
    ASSERT_EQ("C", upper_bound(students_comp.cbegin(), students_comp.cend(), Student_with_compare{"B", 30})->name);

}

TEST_F(Ch12Searching_Fixture, first_k_bsearch_Function) {
    vector<int> A = {0, 1, 2, 3, 4, 5, 6, 7};
    ASSERT_EQ(0, SearchFirstOfK(A, 0));
    ASSERT_EQ(0, binary_search_first(A, 0));
    ASSERT_EQ(0, distance(A.cbegin(), lower_bound(A.cbegin(), A.cend(), 0)));

    ASSERT_EQ(1, SearchFirstOfK(A, 1));
    ASSERT_EQ(1, binary_search_first(A, 1));
    ASSERT_EQ(1, distance(A.cbegin(), lower_bound(A.cbegin(), A.cend(), 1)));

    ASSERT_EQ(4, SearchFirstOfK(A, 4));
    ASSERT_EQ(4, binary_search_first(A, 4));
    ASSERT_EQ(4, distance(A.cbegin(), lower_bound(A.cbegin(), A.cend(), 4)));

    ASSERT_EQ(6, SearchFirstOfK(A, 6));
    ASSERT_EQ(6, binary_search_first(A, 6));
    ASSERT_EQ(6, distance(A.cbegin(), lower_bound(A.cbegin(), A.cend(), 6)));

    ASSERT_EQ(7, SearchFirstOfK(A, 7));
    ASSERT_EQ(7, binary_search_first(A, 7));
    ASSERT_EQ(7, distance(A.cbegin(), lower_bound(A.cbegin(), A.cend(), 7)));

    ASSERT_EQ(-1, SearchFirstOfK(A, 8));
    ASSERT_EQ(-1, binary_search_first(A, 8));
    // lower_bound: If all the element in the range compare less than val,
    // the function returns last.
    ASSERT_EQ(0, distance(A.cend(), lower_bound(A.cbegin(), A.cend(), 8)));

    ASSERT_EQ(-1, SearchFirstOfK(A, numeric_limits<int>::min()));
    ASSERT_EQ(-1, binary_search_first(A, numeric_limits<int>::min()));
    ASSERT_EQ(0, distance(A.cbegin(), lower_bound(A.cbegin(), A.cend(), numeric_limits<int>::min())));

    A = {1, 1, 2, 3, 4, 5, 6, 7};
    ASSERT_EQ(0, SearchFirstOfK(A, 1));
    ASSERT_EQ(0, binary_search_first(A, 1));
    ASSERT_EQ(0, distance(A.cbegin(), lower_bound(A.cbegin(), A.cend(), 1)));

    A = {1, 1, 2, 3, 4, 4, 4, 7};
    ASSERT_EQ(4, SearchFirstOfK(A, 4));
    ASSERT_EQ(4, binary_search_first(A, 4));
    ASSERT_EQ(4, distance(A.cbegin(), lower_bound(A.cbegin(), A.cend(), 4)));

    A = {1, 1, 1, 1, 1, 2};
    ASSERT_EQ(-1, SearchFirstOfK(A, 0));
    ASSERT_EQ(-1, binary_search_first(A, 0));
    ASSERT_EQ(0, distance(A.cbegin(), lower_bound(A.cbegin(), A.cend(), 0)));
    ASSERT_EQ(0, SearchFirstOfK(A, 1));
    ASSERT_EQ(0, binary_search_first(A, 1));
    ASSERT_EQ(0, distance(A.cbegin(), lower_bound(A.cbegin(), A.cend(), 1)));
    ASSERT_EQ(5, SearchFirstOfK(A, 2));
    ASSERT_EQ(5, binary_search_first(A, 2));
    ASSERT_EQ(5, distance(A.cbegin(), lower_bound(A.cbegin(), A.cend(), 2)));

    A = {1, 1, 1, 1, 2, 2};
    ASSERT_EQ(4, SearchFirstOfK(A, 2));
    ASSERT_EQ(4, binary_search_first(A, 2));
    ASSERT_EQ(4, distance(A.cbegin(), lower_bound(A.cbegin(), A.cend(), 2)));

    A = {1, 3, 5, 7, 9, 11};
    ASSERT_EQ(-1, SearchFirstOfK(A, 6));
    ASSERT_EQ(-1, binary_search_first(A, 6));
    // lower_bound:
    // Returns an iterator pointing to the first element in the range [first,last)
    // which does not compare less than val.
    ASSERT_EQ(3, distance(A.cbegin(), lower_bound(A.cbegin(), A.cend(), 6))); // 7
    default_random_engine gen((random_device())());

    for (int times = 0; times < 10; ++times) {
        uniform_int_distribution<int> dis(1, 1000);
        int n = dis(gen);

        vector<int> A;
        uniform_int_distribution<int> k_dis(0, n - 1);
        int k = k_dis(gen);
        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(0, n - 1);
            A.emplace_back(dis(gen));
        }
        sort(A.begin(), A.end());
        int ans = SearchFirstOfK(A, k);
        int ans1 = binary_search_first(A, k);
        ASSERT_EQ(SearchFirstOfKAlternative(A, k), ans);
        ASSERT_EQ(SearchFirstOfKAlternative(A, k), ans1);
        /* cout << "k = " << k << " locates at " << ans << endl;
        if (ans != -1) {
            cout << "A[k] = " << A[ans] << endl;
        }
         */
        //cout << "fist = " << A[0] << " last = " << A[n-1] << " k = " << k << endl ;
        auto it = find(A.cbegin(), A.cend(), k);
        ASSERT_TRUE((it == A.cend() && ans == -1) ||
               (distance(A.cbegin(), it) == ans));

        auto it2 = lower_bound(A.cbegin(), A.cend(), k);
        if (it2 == A.cend()) {
            ASSERT_EQ(-1, ans);
        } else if (it2 == A.cbegin() && *A.cbegin() != k) {
            ASSERT_EQ(-1, ans);
        } else if (*it2 != k) { // if k is not exist in A.
            // lower_bound return min element > k.
            ASSERT_EQ(-1, ans);
        } else {
            ASSERT_EQ(distance(A.cbegin(), it2), ans);
        }
    }

}

TEST_F(Ch12Searching_Fixture, bsearch_ai_eq_i_Function) {
    vector<int> A = {0, 1, 2, 3};
    ASSERT_NE(-1, SearchEntryEqualToItsIndex(A));
    ASSERT_TRUE(0 <= SearchEntryEqualToItsIndex(A) &&
           SearchEntryEqualToItsIndex(A) <= 3);
    A[0] = -1;
    A[2] = 4;
    A[3] = 5;
    ASSERT_EQ(1, SearchEntryEqualToItsIndex(A));
    A = {0};
    ASSERT_NE(-1, SearchEntryEqualToItsIndex(A));
    A[0] = -1;
    ASSERT_EQ(-1, SearchEntryEqualToItsIndex(A));

    A.clear();
    default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        unordered_set<int> table;
        uniform_int_distribution<int> dis(1, 1000);
        int n = dis(gen);

        for (int i = 0; i < n; ++i) {
            int x;
            unordered_set<int>::iterator iter;
            do {
                uniform_int_distribution<int> dis(-999, 999);
                x = dis(gen);
                iter = table.find(x);
            } while (iter != table.cend());
            table.emplace_hint(iter, x);
            A.emplace_back(x);
        }
        sort(A.begin(), A.end());
        int ans = SearchEntryEqualToItsIndex(A);
        if (ans != -1) {
            // cout << "A[" << ans << "] = " << A[ans] << endl;
            ASSERT_EQ(ans, A[ans]);
        } else {
            // cout << "no entry where A[k] = k" << endl;
            ASSERT_EQ(ans, CheckAns(A));
        }
    }
}

TEST_F(Ch12Searching_Fixture, bsearch_circular_array_Function) {
    vector<int> A = {3, 1, 2};
    ASSERT_EQ(1, distinct::SearchSmallest(A));
    A = {0, 2, 4, 8};
    ASSERT_EQ(0, distinct::SearchSmallest(A));
    A[0] = 16;
    ASSERT_EQ(1, distinct::SearchSmallest(A));
    A = {2, 3, 4};
    ASSERT_EQ(0, distinct::SearchSmallest(A));
    A = {100, 101, 102, 2, 5};
    ASSERT_EQ(3, distinct::SearchSmallest(A));
    A = {10, 20, 30, 40, 5};
    ASSERT_EQ(4, distinct::SearchSmallest(A));
    //A = {3, 2, 1, 7, 6, 5, 4};
    //ASSERT_EQ(2, SearchSmallest(A));

    default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<int> dis(1, 1000);
        int n = dis(gen);

        vector<int> A;
        unordered_set<int> table;
        for (size_t i = 0; i < n; ++i) {
            while (true) {
                uniform_int_distribution<int> dis(0, 100000);
                int x = dis(gen);
                //  pair <iterator,bool> emplace ( Args&&... args );
                //  the function returns a pair with an iterator to the newly inserted element and a value of true.
                if (table.emplace(x).second) { // if x is unique in the set
                    A.emplace_back(x);
                    break;
                }
            }
        }
        sort(A.begin(), A.end());
        uniform_int_distribution<int> n_dis(0, n - 1);
        int shift = n_dis(gen);
        reverse(A.begin(), A.end());
        reverse(A.begin(), A.begin() + shift + 1);
        reverse(A.begin() + shift + 1, A.end());
        /*
           for (size_t i = 0; i < n; ++i) {
           cout << A[i] << ' ';
           }
           cout << endl;
         */
        ASSERT_EQ((shift + 1) % n, distinct::SearchSmallest(A));
    }

}

TEST_F(Ch12Searching_Fixture, bsearch_circular_with_dup_Function) {
    vector<int> A = {3, 1, 2};
    ASSERT_EQ(1, duplicate::SearchSmallest(A));
    A = {0, 2, 4, 8};
    ASSERT_EQ(0, duplicate::SearchSmallest(A));
    A[0] = 16;
    ASSERT_EQ(1, duplicate::SearchSmallest(A));

    A = {2, 2, 2};
    ASSERT_EQ(0, duplicate::SearchSmallest(A));
    A = {100, 2, 5, 5};
    ASSERT_EQ(1, duplicate::SearchSmallest(A));
    A = {1, 2, 3, 3, 3};
    ASSERT_EQ(0, duplicate::SearchSmallest(A));
    A = {5, 2, 3, 3, 3};
    ASSERT_EQ(1, duplicate::SearchSmallest(A));
    A = {5, 5, 2, 2, 2, 3, 3, 3};
    ASSERT_EQ(2, duplicate::SearchSmallest(A));

    default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<int> dis(1, 1000);
        int n = dis(gen);

        vector<int> A;
        uniform_int_distribution<int> A_dis(0, 999999);
        generate_n(back_inserter(A), n, [&] { return A_dis(gen); });
        sort(A.begin(), A.end());
        uniform_int_distribution<int> n_dis(0, n - 1);
        int shift = n_dis(gen);
        reverse(A.begin(), A.end());
        reverse(A.begin(), A.begin() + shift + 1);
        reverse(A.begin() + shift + 1, A.end());
        /*
        for (size_t i = 0; i < n; ++i) {
          cout << A[i] << ' ';
        }
        cout << endl;
        */
        ASSERT_EQ((shift + 1) % n, duplicate::SearchSmallest(A));
    }
}

TEST_F(Ch12Searching_Fixture, square_root_int_Function) {
    ASSERT_EQ(SquareRoot(0), 0);
    ASSERT_EQ(SquareRoot(1), 1);
    ASSERT_EQ(SquareRoot(2), 1);
    ASSERT_EQ(SquareRoot(3), 1);
    ASSERT_EQ(SquareRoot(4), 2);
    ASSERT_EQ(SquareRoot(7), 2);
    ASSERT_EQ(SquareRoot(121), 11);
    ASSERT_EQ(SquareRoot(64), 8);
    ASSERT_EQ(SquareRoot(300), 17);
    ASSERT_EQ(SquareRoot(numeric_limits<int>::max()), 46340);

    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(0, numeric_limits<int>::max());
    for (int times = 0; times < 100000; ++times) {
        int x = dis(gen);
        int result[2];
        result[0] = SquareRoot(x);
        result[1] = static_cast<int>(sqrt(x));
        //cout << "x is " << x << endl;
        //cout << (result[0] = SquareRoot(x)) << ' '
        //<< (result[1] = static_cast<int>(sqrt(x))) << endl;
        ASSERT_EQ(result[0], result[1]);
    }

}

TEST_F(Ch12Searching_Fixture, square_root_Function) {
    ASSERT_EQ(Compare(SquareRoot(1.0), sqrt(1.0)), EQUAL);
    ASSERT_EQ(Compare(SquareRoot(2.0), sqrt(2.0)), EQUAL);
    ASSERT_EQ(Compare(SquareRoot(0.001), sqrt(0.001)), EQUAL);
    ASSERT_EQ(Compare(SquareRoot(0.5), sqrt(0.5)), EQUAL);
    ASSERT_EQ(Compare(SquareRoot(100000000.001), sqrt(100000000.001)), EQUAL);
    ASSERT_EQ(Compare(SquareRoot(1024.0), sqrt(1024.0)), EQUAL);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 100000; ++times) {
        uniform_real_distribution<double> dis(0.0, 100000000.0);
        double x = dis(gen);

        double res[2];
        //cout << "x is " << x << endl;
        //cout << (res[0] = SquareRoot(x)) << ' ' << (res[1] = sqrt(x)) << endl;
        res[0] = SquareRoot(x);
        res[1] = sqrt(x);
        ASSERT_EQ(Compare(res[0], res[1]), EQUAL);
    }
}

TEST_F(Ch12Searching_Fixture, matrix_search_Function) {
    vector<vector<int>> A = {{1}};
    ASSERT_FALSE(MatrixSearch(A, 0));
    ASSERT_TRUE(MatrixSearch(A, 1));

    A = {{1, 5}, {2, 6}};
    ASSERT_FALSE(MatrixSearch(A, 0));
    ASSERT_TRUE(MatrixSearch(A, 1));
    ASSERT_TRUE(MatrixSearch(A, 2));
    ASSERT_TRUE(MatrixSearch(A, 5));
    ASSERT_TRUE(MatrixSearch(A, 6));
    ASSERT_FALSE(MatrixSearch(A, 3));
    ASSERT_FALSE(MatrixSearch(A, numeric_limits<int>::max()));

    A = {{2, 5}, {2, 6}};
    ASSERT_FALSE(MatrixSearch(A, 1));
    ASSERT_TRUE(MatrixSearch(A, 2));

    A = {{1, 5, 7}, {3, 10, 100}, {3, 12, numeric_limits<int>::max()}};
    ASSERT_TRUE(MatrixSearch(A, 1));
    ASSERT_FALSE(MatrixSearch(A, 2));
    ASSERT_FALSE(MatrixSearch(A, 4));
    ASSERT_TRUE(MatrixSearch(A, 3));
    ASSERT_TRUE(MatrixSearch(A, 10));
    ASSERT_TRUE(MatrixSearch(A, numeric_limits<int>::max()));
    ASSERT_FALSE(MatrixSearch(A, numeric_limits<int>::max() - 1));
    ASSERT_TRUE(MatrixSearch(A, 12));

    default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<int> dis(1, 100);
        int n = dis(gen);
        int m = dis(gen);

        vector<vector<int>> A(n, vector<int>(m));
        uniform_int_distribution<int> dis1(0, 99);
        A[0][0] = dis1(gen);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int up = (i == 0) ? 0 : A[i - 1][j];
                int left = (j == 0) ? 0 : A[i][j - 1];
                uniform_int_distribution<int> shift_dis(1, 20);
                A[i][j] = max(up, left) + shift_dis(gen);
            }
        }
        uniform_int_distribution<int> x_dis(0, 999);
        int x = x_dis(gen);
        ASSERT_EQ(BruteForceSearch(A, x), MatrixSearch(A, x));
    }
}

TEST_F(Ch12Searching_Fixture, finding_min_max_Function) {
    vector<int> A = {-1, 3, -4, 6, 4, 10, 4, 4, 9};
    auto res = FindMinMax(A);
    ASSERT_TRUE(-4 == res.min && 10 == res.max);
    A[5] = -12;
    res = FindMinMax(A);
    ASSERT_TRUE(-12 == res.min && 9 == res.max);

    A = {-1, 3, -4};
    res = FindMinMax(A);
    ASSERT_TRUE(-4 == res.min && 3 == res.max);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<int> dis(1, 10000);
        int n = dis(gen);

        vector<int> A;
        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(0, 999999);
            A.emplace_back(dis(gen));
        }
        MinMax res = FindMinMax(A);
        ASSERT_TRUE(res.min == *min_element(A.cbegin(), A.cend()) &&
               res.max == *max_element(A.cbegin(), A.cend()));
    }
}

TEST_F(Ch12Searching_Fixture, order_statistic_Function) {
    vector<int> C = {9, 5};
    ASSERT_EQ(9, FindKthLargest(1, &C));
    ASSERT_EQ(5, FindKthSmallest(1, &C));

    vector<int> B = {3, 2, 3, 5, 7, 3, 1};
    ASSERT_EQ(3, FindKthSmallest(4, &B));

    vector<int> A = {123};
    ASSERT_EQ(123, FindKthLargest(1, &A));

    A = {3, 1, 2, 0, 4, 6, 5};
    ASSERT_EQ(6, FindKthLargest(1, &A));
    ASSERT_EQ(5, FindKthLargest(2, &A));
    ASSERT_EQ(4, FindKthLargest(3, &A));
    ASSERT_EQ(3, FindKthLargest(4, &A));
    ASSERT_EQ(2, FindKthLargest(5, &A));
    ASSERT_EQ(1, FindKthLargest(6, &A));
    ASSERT_EQ(0, FindKthLargest(7, &A));
    A[2] = 6;
    ASSERT_EQ(6, FindKthLargest(1, &A));
    ASSERT_EQ(6, FindKthLargest(2, &A));
    ASSERT_EQ(5, FindKthLargest(3, &A));

    A = {0, -7, 3, 4, 4, 12, 6, 10, 0};
    // 12 10 6 4 4 3 0 0 -7
    ASSERT_EQ(12, FindKthLargest(1, &A));
    A = {0, -7, 3, 4, 4, 12, 6, 10, 0};
    ASSERT_EQ(10, FindKthLargest(2, &A));
    A = {0, -7, 3, 4, 4, 12, 6, 10, 0};
    ASSERT_EQ(6, FindKthLargest(3, &A));
    A = {0, -7, 3, 4, 4, 12, 6, 10, 0};
    ASSERT_EQ(4, FindKthLargest(4, &A));
    A = {0, -7, 3, 4, 4, 12, 6, 10, 0};
    ASSERT_EQ(4, FindKthLargest(5, &A));
    A = {0, -7, 3, 4, 4, 12, 6, 10, 0};
    ASSERT_EQ(3, FindKthLargest(6, &A));
    A = {0, -7, 3, 4, 4, 12, 6, 10, 0};
    ASSERT_EQ(4, FindKthLargest(5, &A));
    for (int i = 0; i < A.size(); ++i) {
        if (i < 3) {
            ASSERT_TRUE(A[i] > 4);
        } else if (i > 4) {
            ASSERT_TRUE(A[i] < 4);
        }
    }

    A = {3, 1, 2, 0, 4, 6, 5};
    ASSERT_EQ(0, FindKthSmallest(1, &A));
    ASSERT_EQ(1, FindKthSmallest(2, &A));
    ASSERT_EQ(2, FindKthSmallest(3, &A));
    ASSERT_EQ(3, FindKthSmallest(4, &A));
    ASSERT_EQ(4, FindKthSmallest(5, &A));
    ASSERT_EQ(5, FindKthSmallest(6, &A));
    ASSERT_EQ(6, FindKthSmallest(7, &A));
    A[2] = 6;
    ASSERT_EQ(6, FindKthSmallest(6, &A));
    ASSERT_EQ(6, FindKthSmallest(7, &A));
    ASSERT_EQ(5, FindKthSmallest(5, &A));

    A = {0, -7, 3, 4, 4, 12, 6, 10, 0};
    // -7 0 0 3 4 4 6 10 12
    ASSERT_EQ(-7, FindKthSmallest(1, &A));

    A = {0, -7, 3, 4, 4, 12, 6, 10, 0};
    ASSERT_EQ(0, FindKthSmallest(2, &A));

    A = {0, -7, 3, 4, 4, 12, 6, 10, 0};
    ASSERT_EQ(0, FindKthSmallest(3, &A));

    A = {0, -7, 3, 4, 4, 12, 6, 10, 0};
    ASSERT_EQ(3, FindKthSmallest(4, &A));

    A = {0, -7, 3, 4, 4, 12, 6, 10, 0};
    ASSERT_EQ(4, FindKthSmallest(5, &A));

    A = {0, -7, 3, 4, 4, 12, 6, 10, 0};
    ASSERT_EQ(4, FindKthSmallest(6, &A));

    A = {0, -7, 3, 4, 4, 12, 6, 10, 0};
    ASSERT_EQ(6, FindKthSmallest(7, &A));

    A = {0, -7, 3, 4, 4, 12, 6, 10, 0};
    ASSERT_EQ(10, FindKthSmallest(8, &A));

    A = {0, -7, 3, 4, 4, 12, 6, 10, 0};
    ASSERT_EQ(12, FindKthSmallest(9, &A));

    ASSERT_EQ(4, FindKthSmallest(6, &A));
    for (int i = 0; i < A.size(); i++) {
        if (i < 4) {
            ASSERT_TRUE(A[i] < 4);
        } else if (i > 5) {
            ASSERT_TRUE(A[i] > 4);
        }
    }

    vector<int> N = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 50, 100};
    for (int i = 0; i < N.size(); ++i) {
        for (int j = 0; j < 100; ++j) {
            RandomTestFixedN(N[i]);
        }
    }

    default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<int> n_dis(1, 100000);
        int n = n_dis(gen);
        uniform_int_distribution<int> k_dis(1, n - 1);
        int k = k_dis(gen);

        A.clear();
        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(0, 9999999);
            A.emplace_back(dis(gen));
        }
        int result = FindKthLargest(k, &A);
        nth_element(A.begin(), A.begin() + A.size() - k, A.end());
        ASSERT_EQ(result, A[A.size() - k]);
    }
}

/* Following test takes long time.
TEST_F(Ch12Searching_Fixture, missing_element_Function) {
    default_random_engine gen((random_device())());
    int n = 300000000;
    vector<int> A(1000000000);

    // Assign every elements with numbers in [0, size()-1]
    iota(A.begin(), A.end(), 0);
    unordered_set<int> hash;
    ofstream ofs("missing.txt");

    for (int i = 0; i < n; ++i) {
        hash.emplace(A[i]);
        ofs << A[i] << endl;
    }
    A.clear();
    ofs.close();
    ifstream ifs("missing.txt");
    // cout << "Before finding missing" << endl;

    int missing = FindMissingElement(&ifs);
    ASSERT_EQ(hash.find(missing), hash.cend());
    // Remove file after the execution.
    remove("missing.txt");
    // cout << missing << endl;
}
 */

TEST_F(Ch12Searching_Fixture, missing_and_dup_Function) {
    vector<int> A = {0, 1, 2, 4, 5, 6, 6};
    auto ans = FindDuplicateMissing(A);
    ASSERT_TRUE(ans.duplicate == 6 && ans.missing == 3);

    A = {0, 0, 1};
    ans = FindDuplicateMissing(A);
    ASSERT_TRUE(ans.duplicate == 0 && ans.missing == 2);

    A = {1, 3, 2, 5, 3, 4};
    ans = FindDuplicateMissing(A);
    ASSERT_TRUE(ans.duplicate == 3 && ans.missing == 0);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<int> n_dis(2, 10000);
        int n = n_dis(gen);

        vector<int> A(n);
        iota(A.begin(), A.end(), 0);
        uniform_int_distribution<int> dis(0, n - 1);
        int missing_idx = dis(gen);
        int missing = A[missing_idx];
        int dup_idx = dis(gen);
        while (dup_idx == missing_idx) {
            dup_idx = dis(gen);
        }
        int dup = A[dup_idx];
        A[missing_idx] = dup;
        DuplicateAndMissing ans = FindDuplicateMissing(A);
        // cout << "times = " << times << endl;
        // cout << dup << ' ' << missing << endl;
        // cout << ans.duplicate << ' ' << ans.missing << endl;
        ASSERT_TRUE(ans.duplicate == dup && ans.missing == missing);
    }
}
