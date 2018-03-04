#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "introduction_to_google_test.h"

using std::vector;
using std::string;

TEST(Google_test, custom_failure_message) {
    vector<int> x = {1,2,3};
    vector<int> y = {1,2,2,4};

    EXPECT_EQ(x.size(), y.size()) << "Vectors x and y are of unequal length";

    for (int i = 0; i < x.size(); ++i) {
        EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
    }
}

TEST(StringComparision, stringObject) {
    string aStr = "same string object";
    string bStr = "same string object";
    ASSERT_EQ(aStr, bStr);

}

TEST(StringComparision, CString) {
    char* aCStr = "same C string";
    char* bCStr = "same C string";
    ASSERT_STREQ(aCStr, bCStr);
}

TEST(FactorialTest, HandlesZeroInput) {
    EXPECT_EQ(1, Factorial(0));
}

TEST(FactorialTest, HandlesPositiveInput) {
    EXPECT_EQ(1, Factorial(1));
    EXPECT_EQ(2, Factorial(2));
    EXPECT_EQ(6, Factorial(3));
}


