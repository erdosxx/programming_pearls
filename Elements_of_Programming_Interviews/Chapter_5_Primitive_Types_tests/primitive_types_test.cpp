#include <gtest/gtest.h>
#include <random>
#include "Parity1.h"
#include "Parity2.h"
#include "Parity3.h"
#include "Parity4.h"
#include "swapbits.h"
#include "Reverse_bits.h"
#include "Closest_int_same_bits.h"
#include "MultiplyShiftAdd.h"
#include "Division.h"
#include "power-x-y.h"
#include "reverse-integer.h"
#include "palindrome-number.h"
#include "Uniform_random_number_generation.h"
#include "intersect_rectangle.h"

using std::default_random_engine;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;
using std::invalid_argument;

class Primitive_Types_Fixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }
    const int kFourBitParityLookupTable=0x6996; // = 0b0110100110010110

public:
    Primitive_Types_Fixture() : Test() {

    }

    virtual ~Primitive_Types_Fixture() {
    }
};

TEST_F(Primitive_Types_Fixture, parity_Function) {
    ASSERT_EQ(1, Parity1::Parity(0b0001));
    ASSERT_EQ(1, Parity2::Parity(0b0001));
    ASSERT_EQ(1, Parity3::Parity(0b0001));
    ASSERT_EQ(1, Parity4::Parity(0b0001));

    ASSERT_EQ(0, Parity1::Parity(0b1001));
    ASSERT_EQ(0, Parity2::Parity(0b1001));
    ASSERT_EQ(0, Parity3::Parity(0b1001));
    ASSERT_EQ(0, Parity4::Parity(0b1001));

    int parity_val;

    for(int i =0; i< 16; i++) {
        parity_val= (kFourBitParityLookupTable >> i) & 1;
        ASSERT_EQ(parity_val, Parity1::Parity(i));
        ASSERT_EQ(parity_val, Parity2::Parity(i));
        ASSERT_EQ(parity_val, Parity3::Parity(i));
        ASSERT_EQ(parity_val, Parity4::Parity(i));
    }
}

TEST_F(Primitive_Types_Fixture, swap_bits_Function) {
    ASSERT_EQ(1, SwapBits(0b01000, 3, 0));
    ASSERT_EQ(8, SwapBits(0b01000, 2, 0));
}

TEST_F(Primitive_Types_Fixture, reverse_bits_Function) {
    CreatePrecomputedTable();
    default_random_engine gen((random_device())());

    for (int times = 0; times < 1000; ++times) {
        uniform_int_distribution<long> dis(0, numeric_limits<long>::max());
        long x = dis(gen);
        ASSERT_EQ(ReverseBits(x), ReverseX(x, 63));
    }
}

TEST_F(Primitive_Types_Fixture, closest_int_Function) {
    ASSERT_EQ(5, ClosestIntSameBitCount(6));
    ASSERT_EQ(11, ClosestIntSameBitCount(7));
    ASSERT_EQ(1, ClosestIntSameBitCount(2));
    ASSERT_EQ(16, ClosestIntSameBitCount(32));
    ASSERT_EQ(ClosestIntSameBitCount(numeric_limits<unsigned long>::max() - 1), numeric_limits<unsigned long>::max() - 2);
    ASSERT_THROW(ClosestIntSameBitCount(numeric_limits<unsigned long>::max()), std::invalid_argument);
    ASSERT_THROW(ClosestIntSameBitCount(0), std::invalid_argument);

    default_random_engine gen((random_device())());
    uniform_int_distribution<unsigned long> dis(0, numeric_limits<unsigned long>::max());
    unsigned long x = dis(gen);

    if ((x != 0) || (x != numeric_limits<unsigned long>::max())) {
        unsigned long res = ClosestIntSameBitCount(x);
        ASSERT_EQ(CountBitsSetTo1(x), CountBitsSetTo1(res));
    }
}

TEST_F(Primitive_Types_Fixture, multiply_shift_add_Function) {
    default_random_engine gen((random_device())());
    // Random test, only works if the product is not greater than 2^32 - 1.
    for (int i = 0; i < 100000; ++i) {
        uniform_int_distribution<int> dis(0, 65534);
        unsigned int x = dis(gen), y = dis(gen);
        unsigned int prod = Multiply(x, y);

        ASSERT_EQ(prod, x * y);
    }
}

TEST_F(Primitive_Types_Fixture, Division_Function) {
    ASSERT_EQ(64, Divide(64,1));
    ASSERT_EQ(32, Divide(64,2));
    ASSERT_EQ(21, Divide(64,3));
    ASSERT_EQ(16, Divide(64,4));
    ASSERT_EQ(12, Divide(64,5));
    ASSERT_EQ(32, Divide(65,2));
    ASSERT_EQ(1, Divide(2600540749,2590366799));

    ASSERT_EQ(2, DivideBsearch(4u, 2u));
    ASSERT_EQ(64, DivideBsearch(64, 1));
    ASSERT_EQ(32, DivideBsearch(64, 2));
    ASSERT_EQ(21, DivideBsearch(64, 3));
    ASSERT_EQ(16, DivideBsearch(64, 4));
    ASSERT_EQ(12, DivideBsearch(64, 5));
    ASSERT_EQ(32, DivideBsearch(64, 2));
    ASSERT_EQ(2, DivideBsearch(9444, 4714));
    ASSERT_EQ(430, DivideBsearch(8186, 19));
    ASSERT_EQ(1, DivideBsearch(2600540749,2590366799));
    ASSERT_EQ(2, DivideBsearch(3490742395, 1649034807));
    ASSERT_EQ(1, DivideBsearch(875283388, 574196434));
    ASSERT_EQ(2, DivideBsearch(82282176, 36803266));
    ASSERT_EQ(4, DivideBsearch(4240510108, 1035769031));

    default_random_engine gen((random_device())());
    uniform_int_distribution<size_t> dis(0, numeric_limits<size_t>::max());
    for (int times = 0; times < 100000; ++times) {
        unsigned x = dis(gen), y = dis(gen);
        y = (y == 0) ? 1 : y;  // ensure no divide by 0.
        ASSERT_EQ(x / y, Divide(x, y));
        ASSERT_EQ(x / y, DivideBsearch(x, y));
    }
}

TEST_F(Primitive_Types_Fixture, power_Function) {
    default_random_engine gen((random_device())());
    double x;
    int y;
    uniform_real_distribution<> dis_x(0.0, 10.0);
    uniform_int_distribution<> dis_y(-128, 128);
    for (int times = 0; times < 10000; ++times) {
        x = dis_x(gen);
        y = dis_y(gen);
        ASSERT_TRUE(!Compare(Power(x, y), std::pow(x, y)));
    }
}

TEST_F(Primitive_Types_Fixture, reverse_integer_Function) {
    default_random_engine gen((random_device())());
    int n;
    uniform_int_distribution<int> dis(numeric_limits<int>::min(),
                                      numeric_limits<int>::max());
    for (int times = 0; times < 1000; ++times) {
        n = dis(gen);
        ASSERT_EQ(CheckAns(n), Reverse(n));
    }
}

TEST_F(Primitive_Types_Fixture, palindrome_number_Function) {
    default_random_engine gen((random_device())());
    int x;
    uniform_int_distribution<int> dis(-99999, 99999);

    for (int times = 0; times < 1000; ++times) {
        x = dis(gen);
        ASSERT_EQ(palindrome_number::CheckAns(x), IsPalindromeNumber(x));
    }
}

TEST_F(Primitive_Types_Fixture, uniform_random_number_Function) {
    default_random_engine gen((random_device())());
    for (int times = 0; times < 1000; ++times) {
        int a, b;
        uniform_int_distribution<int> a_dis(0, 99);
        a = a_dis(gen);
        uniform_int_distribution<int> b_dis(a + 1, a + 100);
        b = b_dis(gen);
        int x = UniformRandom(a, b);
        ASSERT_TRUE(x >= a && x <= b);
    }
}

TEST_F(Primitive_Types_Fixture, Intersect_rectangle_Function) {
    Rectangle R1 = {0, 0, 2, 2}, R2 = {1, 1, 3, 3};
    auto result = IntersectRectangle(R1, R2);
    ASSERT_TRUE(result.x == 1 && result.y == 1 && result.width == 1 && result.height == 1);

    R1 = {0, 0, 1, 1}, R2 = {1, 1, 3, 3};
    result = IntersectRectangle(R1, R2);
    ASSERT_TRUE(result.x == 1 && result.y == 1 && result.width == 0 && result.height == 0);

    R1 = {0, 0, 1, 1}, R2 = {2, 2, 3, 3};
    result = IntersectRectangle(R1, R2);
    ASSERT_TRUE(result.x == 0 && result.y == 0 && result.width == -1 && result.height == -1);

    for (int times = 0; times < 10000; ++times) {
        Rectangle R1, R2;
        default_random_engine gen((random_device())());
        uniform_int_distribution<int> dis(1, 100);
        R1.x = dis(gen), R1.y = dis(gen), R1.width = dis(gen),
        R1.height = dis(gen);
        R2.x = dis(gen), R2.y = dis(gen), R2.width = dis(gen),
        R2.height = dis(gen);

        // Intersect rectangle.
        bool res = IsIntersect(R1, R2);
        Rectangle ans = IntersectRectangle(R1, R2);
        ASSERT_TRUE(res == false || (ans.width >= 0 && ans.height >= 0));
    }
}

TEST_F(Primitive_Types_Fixture, ETC_Function) {
    ASSERT_EQ(4, sizeof(unsigned));
    // 4294967295 = 2^32 -1
    ASSERT_EQ(4294967295, numeric_limits<unsigned>::max());
    ASSERT_EQ(1024, static_cast<unsigned>(1<<10) );
    ASSERT_EQ(1073741824, static_cast<unsigned>(1<<30) );
    ASSERT_EQ(2147483648, static_cast<unsigned>(1<<31) );
    ASSERT_NE(0, static_cast<unsigned>(1<<32) );
}