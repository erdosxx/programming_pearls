#include <gtest/gtest.h>
#include "sort.h"

class sortAlgorithmFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    enum {
        SIZE_ARY = 1000};

    virtual void SetUp() {
        set_value_target_array();
        shuffle_array(SIZE_ARY);
    }


    int* target_array = new int[SIZE_ARY];

    void set_value_target_array () {
        for(int i=0; i < SIZE_ARY; i++) {
            target_array[i] = SIZE_ARY - (i + 1);
        }
    };

    void set_value_target_array_for_fat_pivot () {
        for(int i=0; i < SIZE_ARY; i++) {
            target_array[i] = i/(SIZE_ARY/4);
        }
    };

    void shuffle_array (int times) {
        for (int i = 0; i < times; i++) {
            int idx1 = rand() % SIZE_ARY;
            int idx2 = rand() % SIZE_ARY;
            swap(target_array, idx1, idx2);
        }
    }

public:
    sortAlgorithmFixture() : Test() {

    }

    virtual ~sortAlgorithmFixture() {

    }
};

TEST_F(sortAlgorithmFixture, test_insertion1Sort) {
    insertionSort(target_array, SIZE_ARY);

    for (int i=0; i < SIZE_ARY; i++) {
        EXPECT_EQ(i, target_array[i]);
    }
}

TEST_F(sortAlgorithmFixture, test_insertion2Sort) {
    insertionSort2(target_array, SIZE_ARY);

    for (int i=0; i < SIZE_ARY; i++) {
        EXPECT_EQ(i, target_array[i]);
    }
}

TEST_F(sortAlgorithmFixture, test_insertion3Sort) {
    insertionSort3(target_array, SIZE_ARY);

    for (int i=0; i < SIZE_ARY; i++) {
        EXPECT_EQ(i, target_array[i]);
    }
}

TEST_F(sortAlgorithmFixture, test_quick1Sort) {
    qsort1(target_array, 0, SIZE_ARY - 1);

    for (int i=0; i < SIZE_ARY; i++) {
        EXPECT_EQ(i, target_array[i]);
    }
}

TEST_F(sortAlgorithmFixture, test_quick2Sort) {
    qsort2(target_array, 0, SIZE_ARY - 1);

    for (int i=0; i < SIZE_ARY; i++) {
        EXPECT_EQ(i, target_array[i]);
    }
}

TEST_F(sortAlgorithmFixture, test_quick3Sort) {
    qsort3(target_array, 0, SIZE_ARY - 1);

    for (int i=0; i < SIZE_ARY; i++) {
        EXPECT_EQ(i, target_array[i]);
    }
}

TEST_F(sortAlgorithmFixture, test_quick4Sort) {
    qsort4(target_array, 0, SIZE_ARY - 1, 50);
    insertionSort3(target_array, SIZE_ARY);

    for (int i=0; i < SIZE_ARY; i++) {
        EXPECT_EQ(i, target_array[i]);
    }
}

TEST_F(sortAlgorithmFixture, test_quickSort_with_fat_pivot) {
    set_value_target_array_for_fat_pivot();
    qsort_fat_pivot(target_array, SIZE_ARY);

    for (int i=0; i < SIZE_ARY/4; i++) {
        EXPECT_EQ(0, target_array[i]);
    }
    for (int i= SIZE_ARY/4+1; i < 2*SIZE_ARY/4; i++) {
        EXPECT_EQ(1, target_array[i]);
    }
    for (int i= 2*SIZE_ARY/4+1; i < 3*SIZE_ARY/4; i++) {
        EXPECT_EQ(2, target_array[i]);
    }
    for (int i= 3*SIZE_ARY/4+1; i < SIZE_ARY; i++) {
        EXPECT_EQ(3, target_array[i]);
    }
}

TEST_F(sortAlgorithmFixture, test_select1) {
    select1(target_array, 0, SIZE_ARY - 1, 1);
    EXPECT_EQ(0, target_array[0]);
    select1(target_array, 0, SIZE_ARY - 1, 500);
    EXPECT_EQ(500, target_array[500]);
    select1(target_array, 0, SIZE_ARY - 1, 999);
    EXPECT_EQ(999, target_array[999]);
}

TEST_F(sortAlgorithmFixture, test_hsort1) {
    hsort1(target_array, SIZE_ARY);

    for (int i=0; i < SIZE_ARY; i++) {
        EXPECT_EQ(i, target_array[i]);
    }
}

TEST_F(sortAlgorithmFixture, test_hsort1b) {
    hsort1b(target_array, SIZE_ARY);

    for (int i=0; i < SIZE_ARY; i++) {
        EXPECT_EQ(i, target_array[i]);
    }
}

TEST_F(sortAlgorithmFixture, test_hsort2) {
    hsort2(target_array, SIZE_ARY);

    for (int i=0; i < SIZE_ARY; i++) {
        EXPECT_EQ(i, target_array[i]);
    }
}

TEST_F(sortAlgorithmFixture, test_hsort3) {
    hsort3(target_array, SIZE_ARY);

    for (int i=0; i < SIZE_ARY; i++) {
        EXPECT_EQ(i, target_array[i]);
    }
}

TEST_F(sortAlgorithmFixture, test_hsort4) {
    hsort4(target_array, SIZE_ARY);

    for (int i=0; i < SIZE_ARY; i++) {
        EXPECT_EQ(i, target_array[i]);
    }
}

TEST_F(sortAlgorithmFixture, test_selsort) {
    selsort(target_array, SIZE_ARY);

    for (int i=0; i < SIZE_ARY; i++) {
        EXPECT_EQ(i, target_array[i]);
    }
}

TEST_F(sortAlgorithmFixture, test_shellsort) {
    shellsort(target_array, SIZE_ARY);

    for (int i=0; i < SIZE_ARY; i++) {
        EXPECT_EQ(i, target_array[i]);
    }
}
