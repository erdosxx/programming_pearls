#include "column2.h"
#include <gtest/gtest.h>

using namespace std;

class RotateFixture : public ::testing::Test {
protected:
    enum {SUCCESS=-1};
    virtual void TearDown() {
    }

    virtual void SetUp() {
        set_value_target_array();
        set_value_std_target_array();
    }

    int size_ary=30;
    int* target_array = new int[size_ary];

    vector<int> std_target_array;

    void set_value_std_target_array() {
        for (int i=0; i<size_ary; ++i)
            std_target_array[i] = i;
    }

    void set_value_target_array () {
        for(int i=0; i< size_ary; i++) {
            target_array[i] = i;
        }
    };

    int checkrot(const int rotdist) {
        int i;
        for (i = 0; i < size_ary-rotdist; i++)
            if (target_array[i] != i+rotdist)
                return i;
        for (i = 0; i < rotdist; i++)
            if (target_array[size_ary-rotdist+i] != i)
                return size_ary-rotdist+i;
        return SUCCESS;
    }

    int check_std_rot(const int rotdist) {
        int i;
        for (i = 0; i < size_ary-rotdist; i++)
            if (std_target_array[i] != i+rotdist)
                return i;
        for (i = 0; i < rotdist; i++)
            if (std_target_array[size_ary-rotdist+i] != i)
                return size_ary-rotdist+i;
        return SUCCESS;
    }

    void print_ary(int* target_ary) {
        printf("\n");

        for (int i=0; i < size_ary; i++) {
            printf("%i, ", target_array[i]);
        }

        printf("\n");
    }

public:
    RotateFixture() : Test(), std_target_array(size_ary) {
    }

    virtual ~RotateFixture() {

    }
};

TEST_F(RotateFixture, test_gcd_Function) {
    ASSERT_EQ(1, gcd(3, 7));
    ASSERT_EQ(1, isogcd(3, 7));
    ASSERT_EQ(3, gcd(6, 9));
    ASSERT_EQ(3, isogcd(6, 9));
    ASSERT_EQ(3, gcd(1989, 1590));
    ASSERT_EQ(3, isogcd(1989, 1590));
}

TEST_F(RotateFixture, test_reverse_rotate_Function) {
    revrot(target_array, 10, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(10));

    revrot(target_array, 10, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(20));
}

TEST_F(RotateFixture, test_jogglerot1_rotate_Function) {
    jugglerot(target_array, 10, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(10));

    jugglerot(target_array, 10, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(20));
}

TEST_F(RotateFixture, test_jogglerot2_rotate_Function) {
    jugglerot2(target_array, 10, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(10));

    jugglerot2(target_array, 10, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(20));
}

TEST_F(RotateFixture, test_gcdrot_rotate_Function) {
    gcdrot(target_array, 10, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(10));

    gcdrot(target_array, 10, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(20));
}

TEST_F(RotateFixture, test_swapequals_Function) {
    swapequals(target_array, 0, 27, 3);
    //print_ary(target_array);
    ASSERT_EQ(27, target_array[0]);
    ASSERT_EQ(28, target_array[1]);
    ASSERT_EQ(29, target_array[2]);
    ASSERT_EQ(0, target_array[27]);
    ASSERT_EQ(1, target_array[28]);
    ASSERT_EQ(2, target_array[29]);
}

TEST_F(RotateFixture, test_gcdrot_rec_Function) {
    gcdrot_rec(target_array, 4, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(4));
    //print_ary(target_array);

    gcdrot_rec(target_array, 8, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(12));

    gcdrot_rec(target_array, 17, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(29));
}

TEST_F(RotateFixture, test_stdrot_Function) {
    std_rot(std_target_array, 10);
    ASSERT_EQ(SUCCESS, check_std_rot(10));

    std_rot(std_target_array, 10);
    ASSERT_EQ(SUCCESS, check_std_rot(20));
}

TEST_F(RotateFixture, test_getsign_Function) {
    char achar[]= "dgefseffs";
    char bchar[]= "";
    getsign(achar, bchar);

    ASSERT_STREQ("deefffgss", bchar);
}
