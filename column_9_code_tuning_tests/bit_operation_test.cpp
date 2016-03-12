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

TEST_F(BitOperationFixture, test_bitcount_Function) {
    ASSERT_EQ(0, bitcount(0));
    ASSERT_EQ(1, bitcount(1));
    ASSERT_EQ(2, bitcount(0b100010));
    ASSERT_EQ(12, bitcount(0b11111101111110));
    ASSERT_EQ(13, bitcount(0b11111111111110));
}

TEST_F(BitOperationFixture, test_bitcount2_Function) {
    ASSERT_EQ(0, bitcount2(0));
    ASSERT_EQ(1, bitcount2(1));
    ASSERT_EQ(2, bitcount2(0b100010));
    ASSERT_EQ(12, bitcount2(0b11111101111110));
    ASSERT_EQ(13, bitcount2(0b11111111111110));
}

TEST_F(BitOperationFixture, test_getbits_Function) {
    ASSERT_EQ(0b0, getbits(0b10010100, 0, 1));
    ASSERT_EQ(0b101, getbits(0b10010100, 4, 3));
    ASSERT_EQ(0b1001, getbits(0b10010100, 7, 4));
}
