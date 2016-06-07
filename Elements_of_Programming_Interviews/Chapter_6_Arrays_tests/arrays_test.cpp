#include <gtest/gtest.h>
#include "Dutch_national_flag.h"
#include "dutch_national_flag_slow_inplace.h"
#include "dutch_national_flag_two_passes.h"
#include "dutch_national_flag_bentley.h"
#include "plus-one.h"
#include "Bignumber_multiplication.h"
#include "jump-game.h"
#include "remove-duplicates-from-sorted-array.h"
#include "buy-and-sell-stock.h"
#include "buy-and-sell-stock-twice.h"
#include "prime-sieve-basic.h"
#include "Prime_sieve.h"
#include "Permutation_array1.h"
#include "Permutation_array2.h"
#include "Next_permutation.h"
#include "Reservoir_sampling.h"
#include "compute_random_permutation.h"
#include "Online_sampling.h"
#include "nonuniform_random_number_generation.h"
#include "sudoku_check.h"
#include "Spiral_matrix_clockwise.h"
#include "Spiral_matrix.h"
#include "Matrix_rotation_constant.h"
#include "Matrix_rotation_naive.h"

using std::default_random_engine;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::invalid_argument;
using DutchFlag::Color;
using plusone::PlusOne;
using multiply::EqualVector;
using multiply::Multiply;
using multiply::VectorToString;
using std::istringstream;
using std::stringstream;
using std::ostream_iterator;

class Arrays_Fixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }
    const int kFourBitParityLookupTable=0x6996; // = 0b0110100110010110

public:
    Arrays_Fixture() : Test() {

    }

    virtual ~Arrays_Fixture() {
    }
};

TEST_F(Arrays_Fixture, Dutch_national_flag_Function) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 1000; ++times) {
        int n;
        uniform_int_distribution<int> dis(1, 100);
        n = dis(gen);

        vector<Color> A(DutchFlag::RandVector(n));
        uniform_int_distribution<int> dis2(0, A.size() - 1);
        int pivot_index = dis2(gen);

        Color pivot = A[pivot_index];
        DutchFlag::DutchFlagPartition(pivot_index, &A);

        int i = 0;
        while (i < A.size() && A[i] < pivot) {
            ++i;
        }
        while (i < A.size() && A[i] == pivot) {
            ++i;
        }
        while (i < A.size() && A[i] > pivot) {
            ++i;
        }
        ASSERT_EQ(i , A.size());
    }
}

TEST_F(Arrays_Fixture, Dutch_national_flag_slow_Function) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 1000; ++times) {
        int n;
        uniform_int_distribution<int> dis(1, 100);
        n = dis(gen);

        vector<Color> A(DutchFlag::RandVector(n));
        uniform_int_distribution<int> dis2(0, A.size() - 1);
        int pivot_index = dis2(gen);

        Color pivot = A[pivot_index];
        DutchFlag_slow::DutchFlagPartition(pivot_index, &A);

        int i = 0;
        while (i < A.size() && A[i] < pivot) {
            ++i;
        }
        while (i < A.size() && A[i] == pivot) {
            ++i;
        }
        while (i < A.size() && A[i] > pivot) {
            ++i;
        }
        ASSERT_EQ(i , A.size());
    }
}

TEST_F(Arrays_Fixture, Dutch_national_flag_two_Function) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 1000; ++times) {
        int n;
        uniform_int_distribution<int> dis(1, 100);
        n = dis(gen);

        vector<Color> A(DutchFlag::RandVector(n));
        uniform_int_distribution<int> dis2(0, A.size() - 1);
        int pivot_index = dis2(gen);

        Color pivot = A[pivot_index];
        DutchFlag_two::DutchFlagPartition(pivot_index, &A);

        int i = 0;
        while (i < A.size() && A[i] < pivot) {
            ++i;
        }
        while (i < A.size() && A[i] == pivot) {
            ++i;
        }
        while (i < A.size() && A[i] > pivot) {
            ++i;
        }
        ASSERT_EQ(i , A.size());
    }
}

TEST_F(Arrays_Fixture, Dutch_national_flag_bentley_Function) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 1000; ++times) {
        int n;
        uniform_int_distribution<int> dis(1, 100);
        n = dis(gen);

        vector<Color> A(DutchFlag::RandVector(n));
        uniform_int_distribution<int> dis2(0, A.size() - 1);
        int pivot_index = dis2(gen);

        Color pivot = A[pivot_index];
        DutchFlag_bentley::DutchFlagPartition(pivot_index, &A);

        int i = 0;
        while (i < A.size() && A[i] < pivot) {
            ++i;
        }
        while (i < A.size() && A[i] == pivot) {
            ++i;
        }
        while (i < A.size() && A[i] > pivot) {
            ++i;
        }
        ASSERT_EQ(i , A.size());
    }
}

TEST_F(Arrays_Fixture, plus_one_Function) {
    auto result = PlusOne({9, 9});
    ASSERT_TRUE(result.size() == 3 && result[0] == 1 && result[1] == 0 &&
           result[2] == 0);
    result = PlusOne({3, 1, 4});
    ASSERT_TRUE(result.size() == 3 && result[0] == 3 && result[1] == 1 &&
           result[2] == 5);
}

TEST_F(Arrays_Fixture, Bignumber_multiply_Function) {
    ASSERT_TRUE(EqualVector(Multiply({0}, {-1, 0, 0, 0}), {0}));
    ASSERT_TRUE(EqualVector(Multiply({0}, {1, 0, 0, 0}), {0}));
    ASSERT_TRUE(EqualVector(Multiply({9}, {9}), {8, 1}));
    ASSERT_TRUE(EqualVector(Multiply({9}, {9, 9, 9, 9}), {8, 9, 9, 9, 1}));
    ASSERT_TRUE(EqualVector(Multiply({1, 3, 1, 4, 1, 2}, {-1, 3, 1, 3, 3, 3, 2}),
                            {-1, 7, 2, 5, 8, 7, 5, 8, 4, 7, 8, 4}));
    ASSERT_TRUE(EqualVector(Multiply({7, 3}, {-3}), {-2, 1, 9}));

    for (int times = 0; times < 100; ++times) {
        default_random_engine gen((random_device()) ());
        uniform_int_distribution<int> dis(0, 19);
        vector<int> num1 = multiply::RandVector(dis(gen)), num2 = multiply::RandVector(dis(gen));
        auto res = Multiply(num1, num2);
        string command = "bash -c 'bc <<<" + VectorToString(num1) + "*" +
                         VectorToString(num2) + "'";
        string result = execute_shell(command);
        ASSERT_TRUE(result.substr(0, result.size() - 1) == VectorToString(res));
    }
}

TEST_F(Arrays_Fixture, jump_game_Function) {
    vector<int> max_advance_steps = {2, 3, 1, 1, 4};
    ASSERT_TRUE(CanReachEnd(max_advance_steps));
    max_advance_steps = {3, 2, 1, 0, 4};
    ASSERT_TRUE(!CanReachEnd(max_advance_steps));
    max_advance_steps = {3, 2, 1, -10, 4};
    ASSERT_TRUE(!CanReachEnd(max_advance_steps));
    max_advance_steps = {2, 3, -1, -1, 4};
    ASSERT_TRUE(CanReachEnd(max_advance_steps));
    max_advance_steps = {2, 2, -1, -1, 100};
    ASSERT_TRUE(!CanReachEnd(max_advance_steps));

    default_random_engine gen((random_device()) ());
    size_t n;
    uniform_int_distribution<size_t> dis(1, 1000);
    n = dis(gen);

    uniform_int_distribution<int> A_dis(1, 10);
    vector<int> max_advance_steps2;
    generate_n(back_inserter(max_advance_steps2), n, [&] { return A_dis(gen); });
    cout << std::boolalpha << CanReachEnd(max_advance_steps2) << endl;
}

TEST_F(Arrays_Fixture, remove_deplicate_Function) {
    vector<int> A = {2, 3, 5, 5, 7, 11, 11, 11, 13};
    ASSERT_EQ(6, DeleteDuplicates(&A));

    default_random_engine gen((random_device())());
    size_t n;
    uniform_int_distribution<size_t> dis_n(0, 10000);
    n = dis_n(gen);
    A.clear();

    for (int times = 0; times < 10; ++times) {
        uniform_int_distribution<int> A_dis(-1000, 1000);
        generate_n(back_inserter(A), n, [&] { return A_dis(gen); });
        sort(A.begin(), A.end());
        auto B(A);
        auto iter = unique(B.begin(), B.end());
        auto size = DeleteDuplicates(&A);
        ASSERT_EQ(size, distance(B.begin(), iter));
        ASSERT_TRUE(CheckAns(A, size));
    }
}

TEST_F(Arrays_Fixture, buy_and_sell_once_Function) {
    default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        int n;
        uniform_int_distribution<int> dis(1, 10000);
        n = dis(gen);

        vector<double> A;
        uniform_real_distribution<double> dis1(0, n);
        for (int i = 0; i < n; ++i) {
            A.emplace_back(dis1(gen));
        }
        ASSERT_EQ(buy_and_sell::CheckAns(A),buy_and_sell::BuyAndSellStockOnce(A));
    }
}

TEST_F(Arrays_Fixture, buy_and_sell_twice_Function) {
    default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<int> dis(1, 100);
        int n = dis(gen);
        vector<double> A;
        uniform_real_distribution<double> dis1(0.0, 10000.0);

        for (int i = 0; i < n; ++i) {
            A.emplace_back(dis1(gen));
        }
        ASSERT_EQ(buy_and_sell_twice::CheckAns(A), buy_and_sell_twice::BuyAndSellStockTwice(A));
    }
}

TEST_F(Arrays_Fixture, prime_sieve_basic_Function) {
    default_random_engine gen((random_device()) ());

    for (int times = 0; times < 1; ++times) {
        uniform_int_distribution<int> dis(2, 100000);
        int n = dis(gen);

        vector<int> primes = prime_sieve_basic::GeneratePrimes(n);
        for (size_t i = 0; i < primes.size(); ++i) {
            for (int j = 2; j < primes[i]; ++j) {
                ASSERT_TRUE(primes[i] % j);
            }
        }
    }
}

TEST_F(Arrays_Fixture, prime_sieve_Function) {
     default_random_engine gen((random_device()) ());

    for (int times = 0; times < 1; ++times) {
        uniform_int_distribution<int> dis(2, 100000);
        int n = dis(gen);

        vector<int> primes = prime_sieve::GeneratePrimes(n);
        for (size_t i = 0; i < primes.size(); ++i) {
            for (int j = 2; j < primes[i]; ++j) {
                ASSERT_TRUE(primes[i] % j);
            }
        }
    }
}

TEST_F(Arrays_Fixture, permutaion1_Function) {
    vector<int> ary = {0, 1, 2, 3};
    vector<int> perm = {2, 0, 1, 3};
    ApplyPermutation1::ApplyPermutation(&perm, &ary);
    ASSERT_TRUE(ary[0] == 1 && ary[1] == 2 && ary[2] == 0 && ary[3] == 3);
}

TEST_F(Arrays_Fixture, permutaion2_Function) {
    vector<int> ary = {0, 1, 2, 3};
    vector<int> perm = {2, 0, 1, 3};
    ApplyPermutation2::ApplyPermutation(&perm, &ary);
    ASSERT_TRUE(ary[0]  == 1 && ary[1] == 2 && ary[2] == 0 && ary[3] == 3);
}

TEST_F(Arrays_Fixture, next_permutation_Function) {
    default_random_engine gen((random_device())());
    for (int times = 0; times < 1000; ++times) {
        vector<int> perm;
        uniform_int_distribution<int> dis(1, 100);
        int n = dis(gen);
        uniform_int_distribution<int> n_dis(0, n - 1);
        generate_n(back_inserter(perm), n, [&] { return n_dis(gen); });

        vector<int> ans(NextPermutation(perm));
        // Use built-in function verification.
        bool has_next_one = next_permutation(perm.begin(), perm.end());
        ASSERT_TRUE((ans.size() == 0 && !has_next_one) ||
               equal(ans.cbegin(), ans.cend(), perm.cbegin(), perm.cend()));
    }
}

TEST_F(Arrays_Fixture, reservoir_sampling_Function) {
    int n, k;
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> n_dis(0, 99999);
    n = n_dis(gen);
    uniform_int_distribution<int> k_dis(1, n);
    k = k_dis(gen);

    vector<int> A(n);
    iota(A.begin(), A.end(), 0);
    string s;
    for (int i = 0; i < A.size(); ++i) {
        stringstream ss;
        ss << A[i];
        s += ss.str();
        s += ' ';
    }

    //cout << n << ' ' << k << endl;
    istringstream sin(s);

    vector<int> ans = OnlineRandomSample(&sin, k);
    ASSERT_EQ(k, ans.size());
}

TEST_F(Arrays_Fixture, random_permutation_Function) {
    int n;
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> n_dis(1, 1000000);
    n = n_dis(gen);

    auto result = ComputeRandomPermutation(n);
    sort(result.begin(), result.end());

    for (int i = 0; i < n; ++i) {
        ASSERT_EQ(i, result[i]);
    }
}

TEST_F(Arrays_Fixture, random_subset_Function) {
    default_random_engine gen((random_device())());

    uniform_int_distribution<int> n_dis(1, 10000);
    int n = n_dis(gen);
        uniform_int_distribution<int> k_dis(1, n);
    int k = k_dis(gen);

    for (int i = 0; i < 100; ++i) {
        vector<int> res = RandomSubset(n, k);
        ASSERT_EQ(k, res.size());
    }
}

TEST_F(Arrays_Fixture, nonuniform_random_Function) {
    default_random_engine gen((random_device())());
    size_t n;
    uniform_int_distribution<size_t> dis(1, 50);
    n = dis(gen);

    vector<int> T(n);
    iota(T.begin(), T.end(), 0);
    vector<double> P;
    double full_prob = 1.0;

    for (size_t i = 0; i < n - 1; ++i) {
        uniform_real_distribution<double> dis(0.0, full_prob);
        double pi = dis(gen);
        P.emplace_back(pi);
        full_prob -= pi;
    }
    P.emplace_back(full_prob);

    // Test. Perform the nonuniform random number generation for n * kTimes
    // times
    // and calculate the distribution of each bucket.
    const size_t kTimes = 100000;
    vector<int> counts(n, 0);
    for (size_t i = 0; i < n * kTimes; ++i) {
        int t = NonuniformRandomNumberGeneration(T, P);
        ++counts[t];
    }

    for (size_t i = 0; i < n; ++i) {
        ASSERT_TRUE(fabs(static_cast<double>(counts[i]) / (n * kTimes) - P[i]) < 0.01);
    }
}

TEST_F(Arrays_Fixture, sudoku_check_Function) {
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
    ASSERT_TRUE(IsValidSudoku(A));
    // There are two 3s.
    A[8] = {3, 3, 8, 0, 0, 0, 4, 6, 0};
    ASSERT_FALSE(IsValidSudoku(A));
}

TEST_F(Arrays_Fixture, sprial_matrix_clockwise_Function) {
    vector<vector<int>> A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto result = spiral_matrix_clockwise::MatrixInSpiralOrder(A);
    vector<int> golden_result = {1, 2, 3, 6, 9, 8, 7, 4, 5};
    ASSERT_TRUE(equal(result.begin(), result.end(), golden_result.begin(),
                      golden_result.end()));

    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 50);
    int N = dis(gen);

    vector<vector<int>> A1(N, vector<int>(N));
    int x = 1;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            A1[i][j] = x++;
        }
    }
    auto result1 = spiral_matrix_clockwise::MatrixInSpiralOrder(A1);

    // See http://oeis.org/A031878
    // TODO: search for the relationship between this and above link.
    int last = (N*N + N - (N-1)*(N % 2))/2;
    ASSERT_EQ(result1[N*N -1], last);
    //copy(result1.begin(), result1.end(), ostream_iterator<int>(cout, " "));
}

TEST_F(Arrays_Fixture, sprial_matrix_Function) {
    vector<vector<int>> A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto result = spiral_matrix::MatrixInSpiralOrder(A);
    vector<int> golden_result = {1, 2, 3, 6, 9, 8, 7, 4, 5};
    ASSERT_TRUE(equal(result.begin(), result.end(), golden_result.begin(),
                 golden_result.end()));

    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 50);
    int N = dis(gen);

    vector<vector<int>> A1(N, vector<int>(N));
    int x = 1;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            A1[i][j] = x++;
        }
    }

    auto result1 = spiral_matrix::MatrixInSpiralOrder(A1);
    //copy(result1.begin(), result1.end(), ostream_iterator<int>(cout, " "));
    int last = (N*N + N - (N-1)*(N % 2))/2;
    ASSERT_EQ(result1[N*N -1], last);
}

TEST_F(Arrays_Fixture, matrix_rotation_constant_Function) {
    int n;
    default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<int> dis(1, 10);
        n = dis(gen);
        vector<vector<int>> A(1 << n, vector<int>(1 << n));
        int k = 1;
        for (int i = 0; i < A.size(); ++i) {
            for (int j = 0; j < A[i].size(); ++j) {
                A[i][j] = k++;
            }
        }
        vector<vector<int>> B(A);
        matrix_rotation_constant::RotateMatrix(&B);
        ASSERT_TRUE(matrix_rotation_constant::CheckAnswer(A, B));
    }
}

TEST_F(Arrays_Fixture, matrix_rotation_naive_Function) {
    int n;
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 10);
    for (int times = 0; times < 100; ++times) {
        n = dis(gen);
        vector<vector<int>> A(1 << n, vector<int>(1 << n));
        int k = 1;

        for (int i = 0; i < A.size(); ++i) {
            for (int j = 0; j < A[i].size(); ++j) {
                A[i][j] = k++;
            }
        }

        matrix_rotation_naive::RotateMatrix(&A);
        ASSERT_TRUE(matrix_rotation_naive::CheckAnswer(A));
    }
}
