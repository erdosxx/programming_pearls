#include "column2.h"
#include <gtest/gtest.h>

using namespace std;


class RotateFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
        set_value_target_array();
    }

    int size_ary=1000000;
    int* target_array = new int[size_ary];

    void set_value_target_array () {
        for(int i=0; i< size_ary; i++) {
            target_array[i] = i;
        }
    };

public:
    RotateFixture() : Test() {
    }

    virtual ~RotateFixture() {

    }
};

TEST_F(RotateFixture, test_reverse_rotate_Function) {
    revrot(target_array, 100, size_ary);
    ASSERT_EQ(100, target_array[0] );
    ASSERT_EQ(101, target_array[1] );
    ASSERT_EQ(99, target_array[999999] );
    ASSERT_EQ(98, target_array[999998] );
    ASSERT_EQ(97, target_array[999997] );
    ASSERT_EQ(0, target_array[999900] );

    revrot(target_array, 900, size_ary);
    ASSERT_EQ(1000, target_array[0] );
    ASSERT_EQ(1001, target_array[1] );
    ASSERT_EQ(999, target_array[999999] );
    ASSERT_EQ(998, target_array[999998] );
    ASSERT_EQ(0, target_array[999000] );
}

TEST_F(RotateFixture, test_jogglerot1_rotate_Function) {
    jugglerot(target_array, 100, size_ary);
    ASSERT_EQ(100, target_array[0] );
    ASSERT_EQ(101, target_array[1] );
    ASSERT_EQ(99, target_array[999999] );
    ASSERT_EQ(98, target_array[999998] );
    ASSERT_EQ(97, target_array[999997] );
    ASSERT_EQ(0, target_array[999900] );

    jugglerot(target_array, 900, size_ary);
    ASSERT_EQ(1000, target_array[0] );
    ASSERT_EQ(1001, target_array[1] );
    ASSERT_EQ(999, target_array[999999] );
    ASSERT_EQ(998, target_array[999998] );
    ASSERT_EQ(0, target_array[999000] );
}

TEST_F(RotateFixture, test_jogglerot2_rotate_Function) {
    jugglerot2(target_array, 100, size_ary);
    ASSERT_EQ(100, target_array[0] );
    ASSERT_EQ(101, target_array[1] );
    ASSERT_EQ(99, target_array[999999] );
    ASSERT_EQ(98, target_array[999998] );
    ASSERT_EQ(97, target_array[999997] );
    ASSERT_EQ(0, target_array[999900] );

    jugglerot2(target_array, 900, size_ary);
    ASSERT_EQ(1000, target_array[0] );
    ASSERT_EQ(1001, target_array[1] );
    ASSERT_EQ(999, target_array[999999] );
    ASSERT_EQ(998, target_array[999998] );
    ASSERT_EQ(0, target_array[999000] );
}

TEST_F(RotateFixture, test_gcdrot_rotate_Function) {
    gcdrot(target_array, 100, size_ary);
    ASSERT_EQ(100, target_array[0] );
    ASSERT_EQ(101, target_array[1] );
    ASSERT_EQ(99, target_array[999999] );
    ASSERT_EQ(98, target_array[999998] );
    ASSERT_EQ(97, target_array[999997] );
    ASSERT_EQ(0, target_array[999900] );

    gcdrot(target_array, 900, size_ary);
    ASSERT_EQ(1000, target_array[0] );
    ASSERT_EQ(1001, target_array[1] );
    ASSERT_EQ(999, target_array[999999] );
    ASSERT_EQ(998, target_array[999998] );
    ASSERT_EQ(0, target_array[999000] );
}
