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

    int size_ary=1000000;
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

    int checkrot(int rotdist) {
        int i;
        for (i = 0; i < size_ary-rotdist; i++)
            if (target_array[i] != i+rotdist)
                return i;
        for (i = 0; i < rotdist; i++)
            if (target_array[size_ary-rotdist+i] != i)
                return size_ary-rotdist+i;
        return SUCCESS;
    }

    int check_std_rot(int rotdist) {
        int i;
        for (i = 0; i < size_ary-rotdist; i++)
            if (std_target_array[i] != i+rotdist)
                return i;
        for (i = 0; i < rotdist; i++)
            if (std_target_array[size_ary-rotdist+i] != i)
                return size_ary-rotdist+i;
        return SUCCESS;
    }

public:
    RotateFixture() : Test(), std_target_array(size_ary) {
    }

    virtual ~RotateFixture() {

    }
};

TEST_F(RotateFixture, test_reverse_rotate_Function) {
    revrot(target_array, 100, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(100));

    revrot(target_array, 900, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(1000));
}

TEST_F(RotateFixture, test_jogglerot1_rotate_Function) {
    jugglerot(target_array, 100, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(100));

    jugglerot(target_array, 900, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(1000));
}

TEST_F(RotateFixture, test_jogglerot2_rotate_Function) {
    jugglerot2(target_array, 100, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(100));

    jugglerot2(target_array, 900, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(1000));
}

TEST_F(RotateFixture, test_gcdrot_rotate_Function) {
    gcdrot(target_array, 100, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(100));

    gcdrot(target_array, 900, size_ary);
    ASSERT_EQ(SUCCESS, checkrot(1000));
}

TEST_F(RotateFixture, test_stdrot_Function) {
    std_rot(std_target_array, 100);
    ASSERT_EQ(SUCCESS, check_std_rot(100));

    std_rot(std_target_array, 900);
    ASSERT_EQ(SUCCESS, check_std_rot(1000));
}

TEST_F(RotateFixture, test_getsign_Function) {
    char achar[]= "dgefseffs";
    char bchar[]= "";
    getsign(achar, bchar);

    ASSERT_STREQ("deefffgss", bchar);
}
