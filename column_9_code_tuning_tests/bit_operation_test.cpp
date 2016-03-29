#include "column9.h"
#include <gtest/gtest.h>

using namespace std;


class BitOperationFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    BitOperationFixture() : Test() {
    }

    virtual ~BitOperationFixture() {

    }
};

TEST_F(BitOperationFixture, test_bitcount_simple_Function) {
    ASSERT_EQ(0, bitcount_simple(0));
    ASSERT_EQ(1, bitcount_simple(1));
    ASSERT_EQ(2, bitcount_simple(0b100010));
    ASSERT_EQ(12, bitcount_simple(0b11111101111110));
    ASSERT_EQ(13, bitcount_simple(0b11111111111110));
}

TEST_F(BitOperationFixture, test_bitcount_rightmostbit_Function) {
    ASSERT_EQ(0, bitcount_rightmostbit(0));
    ASSERT_EQ(1, bitcount_rightmostbit(1));
    ASSERT_EQ(2, bitcount_rightmostbit(0b100010));
    ASSERT_EQ(12, bitcount_rightmostbit(0b11111101111110));
    ASSERT_EQ(13, bitcount_rightmostbit(0b11111111111110));
}

TEST_F(BitOperationFixture, test_getbits_Function) {
    ASSERT_EQ(0b0, getbits(0b10010100, 0, 1));
    ASSERT_EQ(0b101, getbits(0b10010100, 4, 3));
    ASSERT_EQ(0b1001, getbits(0b10010100, 7, 4));
}
