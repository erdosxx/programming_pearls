#include <gtest/gtest.h>
#include "array_boot_camp.h"
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
#include "pascal-triangle-1.h"
#include "k-th_permutation.h"
#include "inverse_permutation.h"

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

TEST_F(Arrays_Fixture, even_odd_groupping) {
    vector<int> data = {2};
    even_odd_groupping(&data);
    vector<int> golden_sol = {2};
    ASSERT_TRUE(equal(data.begin(), data.end(), golden_sol.begin(), golden_sol.end()));

    data = {1,2};
    even_odd_groupping(&data);
    golden_sol = {2,1};
    ASSERT_TRUE(equal(data.begin(), data.end(), golden_sol.begin(), golden_sol.end()));

    data = {1,2,4};
    even_odd_groupping(&data);
    golden_sol = {4,2,1};
    ASSERT_TRUE(equal(data.begin(), data.end(), golden_sol.begin(), golden_sol.end()));

    data = {1,2,4,5};
    even_odd_groupping(&data);
    golden_sol = {4,2,5,1};
    ASSERT_TRUE(equal(data.begin(), data.end(), golden_sol.begin(), golden_sol.end()));
}

TEST_F(Arrays_Fixture, stl_functions) {
    //array: fixed size
    array<int,5> A = {1,2,3,4,5};
    ASSERT_EQ(3, A[2]);
    ASSERT_EQ(5, A.size());

    array<array<int,2>,3> A2{{{1,2}, {3,4}, {5,6}}};
    ASSERT_EQ(A2[1][0], 3);

    array<array<int,2>,3> A2_1 = {{{1,2}, {3,4}, {5,6}}};
    ASSERT_EQ(A2_1[1][0], 3);

    // this does not work
    // See: http://stackoverflow.com/questions/12844475/why-cant-simple-initialize-with-braces-2d-stdarray
    // array<array<int,2>,3> A2_2 = {{1,2}, {3,4}, {5,6}};
    // ASSERT_EQ(A2_2[1][0], 3);

    // copy array to vector
    vector<int> copy_A;
    copy(A.cbegin()+1, A.cend(), back_inserter(copy_A));
    ASSERT_EQ(copy_A[0], 2);
    ASSERT_EQ(copy_A.size(), 4);

    //vector to subarray
    vector<int> vA = {1,2,3,4,5};
    vector<int> subarray_vA(vA.cbegin()+1, vA.cbegin()+3);
    ASSERT_EQ(subarray_vA[0], 2);
    ASSERT_EQ(subarray_vA.size(), 2);

    vector<int> shift_vA(vA.cbegin()-1, vA.cend());
    ASSERT_EQ(shift_vA[1], 1);
    ASSERT_EQ(shift_vA.size(), 6);

    vector<int> copy_vA;
    copy(vA.cbegin()+1, vA.cbegin()+3, back_inserter(copy_vA));
    ASSERT_EQ(copy_vA.size(), 2);
    ASSERT_EQ(copy_vA[0], 2);

    vector<vector<int>> vA2 = {{1,2}, {3,4}, {5,6}};
    ASSERT_EQ(vA2[1][0], 3);

    vector<vector<int>> vA2_1{{{1,2}, {3,4}, {5,6}}};
    ASSERT_EQ(vA2_1[1][0], 3);

    // array vector
    vector<array<int,3>> vec_ary ={{1,2,3}, {4,5,6}, {7,8,9}};
    ASSERT_EQ(vec_ary[1][0], 4);
    vec_ary.push_back({10,11,12});
    ASSERT_EQ(vec_ary[3][0], 10);
    vec_ary.emplace_back(array<int,3>{{13,14,15}});
    ASSERT_EQ(vec_ary[4][0], 13);
    // following does not work.
    //vec_ary.emplace_back({16,17,18}); or vec_ary.emplace_back({{16,17,18}})
    //ASSERT_EQ(vec_ary[5][0], 16);

    // vector array
    array<vector<int>,3> ary_vec = {{{1}, {4,5}, {7,8,9}}};
    ASSERT_EQ(ary_vec[1][0], 4);

    // push_back, emplace_back
    vector<int> vA3 = {1,2,3};
    vA3.push_back(4);
    ASSERT_EQ(vA3.size(), 4);
    ASSERT_EQ(vA3[3], 4);

    vA3.emplace_back(5);
    ASSERT_EQ(vA3.size(), 5);
    ASSERT_EQ(vA3[4], 5);
    vector<vector<int>> vA4 = {{1,2,3}, {4,5,6}, {7,8,9}};
    // Following does not work.
    // vA4.emplace_back({10,11,12});
    // ASSERT_EQ(vA4[3,0], 10);
    vA4.push_back({10,11,12});
    ASSERT_EQ(vA4[3][0], 10);
    vA4.emplace_back(vector<int>{13,14,15});
    ASSERT_EQ(vA4[4][0], 13);

    // Deep equal in array
    // See: http://stackoverflow.com/questions/12866413/comparing-arrays-for-equality-in-c
    array<int, 5> ary1 = {1,2,3,4,5};
    array<int, 5> ary2 = {1,2,3,4,5};
    ASSERT_TRUE(ary1== ary2);

    int p_ary1[5] = {1,2,3,4,5};
    int p_ary2[5] = {1,2,3,4,5};
    ASSERT_TRUE(p_ary1 != p_ary2);
    ASSERT_TRUE(equal(p_ary1, p_ary1+5, p_ary2, p_ary2+5));
    ASSERT_TRUE(equal(std::begin(p_ary1), std::end(p_ary1), std::begin(p_ary2), std::end(p_ary2)));

    // binary_search and find
    // data must be sorted before using binary_search.
    vector<int> vA5 = {2,4,6,8,10,12,14,16,18,20};
    // binary_search return bool, so just can check the existence.
    ASSERT_TRUE(binary_search(vA5.cbegin(), vA5.cend(), 14));
    ASSERT_FALSE(binary_search(vA5.cbegin(), vA5.cend(), 15));
    // find is sequencial search, so searching time is O(n)
    auto iter = find(vA5.cbegin(), vA5.cend(), 12);
    ASSERT_TRUE(iter == vA5.cbegin()+5);
    ASSERT_EQ(*iter, 12);

    // search in sorted array
    // lower_bound: Returns an iterator pointing to the first element in the range [first,last)
    //               which does not compare less than val.
    // upper_bound : Returns an iterator pointing to the first element in the range
    //               [first,last) which compares greater than val.
    //                                        | upper_bound
    vector<int> vA6= {2,4,6,8,10,12,12,12,12,14,16,18,20};
    //                           ^ lower_bound
    auto low_iter = lower_bound(vA6.cbegin(), vA6.cend(), 12);
    auto up_iter = upper_bound(vA6.cbegin(), vA6.cend(), 12);
    ASSERT_EQ(5, low_iter - vA6.begin());
    ASSERT_EQ(9, up_iter - vA6.begin());

    array<int,13> aA6 = {2,4,6,8,10,12,12,12,12,14,16,18,20};
    auto low_a_iter = lower_bound(aA6.cbegin(), aA6.cend(), 12);
    auto up_a_iter = upper_bound(aA6.cbegin(), aA6.cend(), 12);
    ASSERT_EQ(5, low_a_iter - aA6.begin());
    ASSERT_EQ(9, up_a_iter - aA6.begin());

    // fill
    vector<int> vA7 = {0,1,2,3,4,5,6,7,8};
    fill(vA7.begin(), vA7.end(), -1);
    vector<int> vA7_1 = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
    ASSERT_TRUE(equal(vA7.cbegin(), vA7.cend(), vA7_1.cbegin(), vA7_1.cend()));

    array<int, 9> aA7 = {0,1,2,3,4,5,6,7,8};
    fill(aA7.begin(), aA7.end(), -1);
    array<int, 9> aA7_1 = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
    ASSERT_TRUE(equal(aA7.cbegin(), aA7.cend(), aA7_1.cbegin(), aA7_1.cend()));
    // cross equal between vector and array
    ASSERT_TRUE(equal(vA7.cbegin(), vA7.cend(), aA7.cbegin(), aA7.cend()));

    vector<int> vA8 = {0,1,2,3,4,5,6,7,8};
    // min_element, max_element
    // sequencial search O(n)
    auto min_v_iter = min_element(vA8.cbegin(), vA8.cend());
    auto max_v_iter = max_element(vA8.cbegin(), vA8.cend());
    ASSERT_TRUE(min_v_iter == vA8.begin());
    ASSERT_EQ(*min_v_iter, 0);
    ASSERT_TRUE(min_v_iter == vA8.cbegin());

    array<int, 9> aA8 = {0,1,2,3,4,5,6,7,8};
    auto min_a_iter = min_element(aA8.cbegin(), aA8.cend());
    auto max_a_iter = max_element(aA8.cbegin(), aA8.cend());
    ASSERT_TRUE(min_a_iter == aA8.cbegin());
    ASSERT_EQ(0, *min_a_iter);
    ASSERT_TRUE(max_a_iter == aA8.cend()-1);
    ASSERT_TRUE(max_a_iter == aA8.cbegin()+8);
    ASSERT_EQ(8, *max_a_iter);

    // reverse
    vector<int> vA9 = {0,1,2,3,4,5,6,7,8};
    vector<int> vA9_1 ={8,7,6,5,4,3,2,1,0};
    array<int, 9> aA9 = {0,1,2,3,4,5,6,7,8};
    array<int, 9> aA9_1 = {8,7,6,5,4,3,2,1,0};
    reverse(vA9.begin(), vA9.end());
    reverse(aA9.begin(), aA9.end());
    ASSERT_TRUE(equal(vA9.cbegin(), vA9.cend(), vA9_1.cbegin(), vA9_1.cend()));
    ASSERT_TRUE(equal(aA9.cbegin(), aA9.cend(), aA9_1.cbegin(), aA9_1.cend()));

    // rotate
    vector<int> vA10 = {0,1,2,3,4,5,6,7,8};
    vector<int> vA10_1 ={4,5,6,7,8,0,1,2,3};
    array<int, 9> aA10 = {0,1,2,3,4,5,6,7,8};
    array<int, 9> aA10_1 = {4,5,6,7,8,0,1,2,3};
    rotate(vA10.begin(), vA10.begin()+4, vA10.end());
    rotate(aA10.begin(), aA10.begin()+4, aA10.end());
    ASSERT_TRUE(equal(vA10.cbegin(), vA10.cend(), vA10_1.cbegin(), vA10_1.cend()));
    ASSERT_TRUE(equal(aA10.cbegin(), aA10.cend(), aA10_1.cbegin(), aA10_1.cend()));
}

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
    vector<int> example = {1,2,3,5,4,2};
    vector<int> answer(NextPermutation(example));
    vector<int> ans_ex =  {1,2,4,2,3,5};
    ASSERT_TRUE(equal(answer.cbegin(), answer.cend(), ans_ex.cbegin(), ans_ex.cend()));

    example = ans_ex;
    answer = NextPermutation(example);
    ans_ex = {1,2,4,2,5,3};
    ASSERT_TRUE(equal(answer.cbegin(), answer.cend(), ans_ex.cbegin(), ans_ex.cend()));

    example = ans_ex;
    answer = NextPermutation(example);
    ans_ex = {1,2,4,3,2,5};
    ASSERT_TRUE(equal(answer.cbegin(), answer.cend(), ans_ex.cbegin(), ans_ex.cend()));

    example = ans_ex;
    answer = NextPermutation(example);
    ans_ex = {1,2,4,3,5,2};
    ASSERT_TRUE(equal(answer.cbegin(), answer.cend(), ans_ex.cbegin(), ans_ex.cend()));

    example = ans_ex;
    answer = NextPermutation(example);
    ans_ex = {1,2,4,5,2,3};
    ASSERT_TRUE(equal(answer.cbegin(), answer.cend(), ans_ex.cbegin(), ans_ex.cend()));

    example = ans_ex;
    answer = NextPermutation(example);
    ans_ex = {1,2,4,5,3,2};
    ASSERT_TRUE(equal(answer.cbegin(), answer.cend(), ans_ex.cbegin(), ans_ex.cend()));

    example = ans_ex;
    answer = NextPermutation(example);
    ans_ex = {1,2,5,2,3,4};
    ASSERT_TRUE(equal(answer.cbegin(), answer.cend(), ans_ex.cbegin(), ans_ex.cend()));

    example = ans_ex;
    answer = NextPermutation(example);
    ans_ex = {1,2,5,2,4,3};
    ASSERT_TRUE(equal(answer.cbegin(), answer.cend(), ans_ex.cbegin(), ans_ex.cend()));

    example = ans_ex;
    answer = NextPermutation(example);
    ans_ex = {1,2,5,3,2,4};
    ASSERT_TRUE(equal(answer.cbegin(), answer.cend(), ans_ex.cbegin(), ans_ex.cend()));

    example = ans_ex;
    answer = NextPermutation(example);
    ans_ex = {1,2,5,3,4,2};
    ASSERT_TRUE(equal(answer.cbegin(), answer.cend(), ans_ex.cbegin(), ans_ex.cend()));

    example = ans_ex;
    answer = NextPermutation(example);
    ans_ex = {1,2,5,4,2,3};
    ASSERT_TRUE(equal(answer.cbegin(), answer.cend(), ans_ex.cbegin(), ans_ex.cend()));

    example = ans_ex;
    answer = NextPermutation(example);
    ans_ex = {1,2,5,4,3,2};
    ASSERT_TRUE(equal(answer.cbegin(), answer.cend(), ans_ex.cbegin(), ans_ex.cend()));

    example = ans_ex;
    answer = NextPermutation(example);
    ans_ex = {1,3,2,2,4,5};
    ASSERT_TRUE(equal(answer.cbegin(), answer.cend(), ans_ex.cbegin(), ans_ex.cend()));

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

TEST_F(Arrays_Fixture, offline_sampling_Function) {
    int n, k;
    default_random_engine gen((random_device())());

    uniform_int_distribution<int> n_dis(1, 1000000);
    n = n_dis(gen);
    uniform_int_distribution<int> k_dis(1, n);
    k = k_dis(gen);

    vector<int> A(n);
    iota(A.begin(), A.end(), 0);

    //cout << n << ' ' << k << endl;
    RandomSampling(k, &A);
    /*
    for (int i = 0; i < A.size(); i++) {
        cout << i << ":" << A[i] << " ";
    }
    cout << endl;
    */
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
    vector<int> result = RandomSubset(1, 1);
    sort(result.begin(), result.end());
    vector<int> golden_ans = {0};
    ASSERT_TRUE(equal(result.cbegin(), result.cend(), golden_ans.cbegin(), golden_ans.cend()));

    result = RandomSubset(2, 2);
    sort(result.begin(), result.end());
    golden_ans = {0,1};
    ASSERT_TRUE(equal(result.cbegin(), result.cend(), golden_ans.cbegin(), golden_ans.cend()));

    result = RandomSubset(10, 8);
    sort(result.begin(), result.end());
    auto iter = unique(result.begin(), result.end());

    cout << endl;
    for (int i =0; i < result.size(); i++) {
        cout << result[i] << ":";
    }
    cout << endl;

    ASSERT_TRUE(iter == result.cend()); // no duplicated data

    vector<int> A ={1,2,3,4};
    iter = unique(A.begin(), A.end());
    ASSERT_EQ(A.cend(), iter);

    A ={1,2,2,3};
    iter = unique(A.begin(), A.end());
    ASSERT_NE(A.cend(), iter);

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
    const size_t kTimes = 1000;
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

TEST_F(Arrays_Fixture, pascal_triangle_Function) {
    auto result = GeneratePascalTriangle(3);
    vector<vector<int>> golden_result = {{1}, {1, 1}, {1, 2, 1}};
    ASSERT_TRUE(equal(result.begin(), result.end(), golden_result.begin(),
                 golden_result.end()));
}

TEST_F(Arrays_Fixture, k_th_permutation) {
    ASSERT_EQ(120, n_factor(5));

    vector<int> known_ans = {0,1,2,3,4};
    vector<int> ans = generate_kth_permutation(5,1);
    ASSERT_TRUE(equal(known_ans.cbegin(), known_ans.cend(), ans.cbegin(), ans.cend()));

    known_ans = {0,1,2,4,3};
    ans = generate_kth_permutation(5,2);
    ASSERT_TRUE(equal(known_ans.cbegin(), known_ans.cend(), ans.cbegin(), ans.cend()));

    known_ans = {0,1,3,2,4};
    ans = generate_kth_permutation(5,3);
    ASSERT_TRUE(equal(known_ans.cbegin(), known_ans.cend(), ans.cbegin(), ans.cend()));

    known_ans = {4,3,2,1,0};
    ans = generate_kth_permutation(5,120);
    ASSERT_TRUE(equal(known_ans.cbegin(), known_ans.cend(), ans.cbegin(), ans.cend()));

    known_ans = {4,3,2,0,1};
    ans = generate_kth_permutation(5,119);
    ASSERT_TRUE(equal(known_ans.cbegin(), known_ans.cend(), ans.cbegin(), ans.cend()));

    known_ans = {1,2,4,0,3};
    ans = generate_kth_permutation(5,35);
    ASSERT_TRUE(equal(known_ans.cbegin(), known_ans.cend(), ans.cbegin(), ans.cend()));
}

TEST_F(Arrays_Fixture, inverse_permutation) {
    vector<int> perm = {0};
    inverse_permutation(&perm, 0);
    vector<int> ans = {0};
    ASSERT_TRUE(equal(perm.cbegin(), perm.cend(), ans.cbegin(), ans.cend()));

    perm = {1};
    inverse_permutation(&perm, 1);
    ans = {1};
    ASSERT_TRUE(equal(perm.cbegin(), perm.cend(), ans.cbegin(), ans.cend()));

    perm = {0,1};
    inverse_permutation(&perm, 0);
    ans = {0,1};
    ASSERT_TRUE(equal(perm.cbegin(), perm.cend(), ans.cbegin(), ans.cend()));

    perm = {1,2};
    inverse_permutation(&perm, 1);
    ans = {1,2};
    ASSERT_TRUE(equal(perm.cbegin(), perm.cend(), ans.cbegin(), ans.cend()));

    perm = {0,1,2};
    inverse_permutation(&perm, 0);
    ans = {0,1,2};
    ASSERT_TRUE(equal(perm.cbegin(), perm.cend(), ans.cbegin(), ans.cend()));

    perm = {1,2,3};
    inverse_permutation(&perm, 1);
    ans = {1,2,3};
    ASSERT_TRUE(equal(perm.cbegin(), perm.cend(), ans.cbegin(), ans.cend()));

    perm = {1,0};
    inverse_permutation(&perm, 0);
    ans = {1,0};
    ASSERT_TRUE(equal(perm.cbegin(), perm.cend(), ans.cbegin(), ans.cend()));

    perm = {2,1};
    inverse_permutation(&perm, 1);
    ans = {2,1};
    ASSERT_TRUE(equal(perm.cbegin(), perm.cend(), ans.cbegin(), ans.cend()));

    // 0->2->1
    // 0<-2<-1
    perm = {2,0,1};
    inverse_permutation(&perm, 0);
    ans = {1,2,0};
    ASSERT_TRUE(equal(perm.cbegin(), perm.cend(), ans.cbegin(), ans.cend()));

    perm = {3,1,2};
    inverse_permutation(&perm, 1);
    ans = {2,3,1};
    ASSERT_TRUE(equal(perm.cbegin(), perm.cend(), ans.cbegin(), ans.cend()));

    // 0->5->2, 1, 3->4
    // 0<-5<-2, 1, 3<-4
    perm = {5, 1, 0, 4, 3, 2};
    inverse_permutation(&perm, 0);
    ans = {2, 1, 5, 4, 3, 0};
    ASSERT_TRUE(equal(perm.cbegin(), perm.cend(), ans.cbegin(), ans.cend()));

    perm = {6, 2, 1, 5, 4, 3};
    inverse_permutation(&perm, 1);
    ans = {3, 2, 6, 5, 4, 1};
    ASSERT_TRUE(equal(perm.cbegin(), perm.cend(), ans.cbegin(), ans.cend()));

    // 0->2->5, 1->3, 4
    // 0<-2<-5, 1<-3, 4
    perm = {2, 3, 5, 1, 4, 0};
    inverse_permutation(&perm, 0);
    ans = {5, 3, 0, 1, 4, 2};
    ASSERT_TRUE(equal(perm.cbegin(), perm.cend(), ans.cbegin(), ans.cend()));

    perm = {3, 4, 6, 2, 5, 1};
    inverse_permutation(&perm, 1);
    ans = {6, 4, 1, 2, 5, 3};
    ASSERT_TRUE(equal(perm.cbegin(), perm.cend(), ans.cbegin(), ans.cend()));
}

/*
TEST_F(Arrays_Fixture, array_index_shift) {
    vector<int> perm = {1,2,3,4};
    vector<int>* perm_ptr = &perm;
    vector<int>* perm_shift_ptr = perm_ptr -1;

    vector<int>& perm_shift = *perm_shift_ptr;
    ASSERT_EQ(1, perm_shift[3]);

    int a[3] = {1,2,3};
    int* a_ptr = a-1;
    ASSERT_TRUE(a_ptr[1]==1 && a_ptr[2]==2 && a_ptr[3]==3);
}
*/

