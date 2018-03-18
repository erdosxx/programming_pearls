#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "permute_the_elements_of_an_array_6_9.h"

using std::cout;
using std::endl;
using ::testing::IsNull;
using ::testing::ElementsAre;
using ::testing::Eq;
using ::testing::Each;
using ::testing::IsEmpty;
using ::testing::Pointee;

using permute_the_elements::apply;

class permute_elements_Fixture : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

public:
    permute_elements_Fixture() : Test() {
    }

    virtual ~permute_elements_Fixture() {
    }

};

TEST_F(permute_elements_Fixture, PIs0_returnSameArray) {
    const vector<int> *p_permutation = new vector<int>{0};
    vector<string> *p_array = new vector<string>{"a"};

    ASSERT_THAT(apply(p_permutation, p_array), ElementsAre("a"));
    delete p_permutation;
    delete p_array;
}

TEST(PermutationIsEmpty, ArrayIsEmpty_returnEmptryArray) {
    const vector<int> *empty_perm = new vector<int>{};
    vector<string> *empty_array = new vector<string>{};

    ASSERT_THAT(apply(empty_perm, empty_array), ElementsAre());
    delete empty_perm;
    delete empty_array;
}

TEST(PermutationIsEmpty, ArrayIsNotEmpty_returnEmptryArray) {
    const vector<int> *empty_perm = new vector<int>{};
    vector<string> *not_empty_array = new vector<string>{"not", "empty", "array"};

    ASSERT_THAT(apply(empty_perm, not_empty_array), ElementsAre());
    delete empty_perm;
    delete not_empty_array;
}

vector<int> *generate_identical_perm(int n) {
    if (n < 0)
        return nullptr;

    vector<int> *id_perm = new vector<int>{};

    for (int i = 0; i < n; i++)
        id_perm->emplace_back(i);

    return id_perm;
}

TEST(PermutationIsIdentical, Array_returnSameArray) {
    const vector<int> *identical_perm;

    identical_perm = generate_identical_perm(1);
    vector<string> *one_size_array = new vector<string>{"a"};
    ASSERT_THAT(apply(identical_perm, one_size_array), Eq(vector<string>{"a"}));
    delete identical_perm;

    identical_perm = generate_identical_perm(2);
    vector<string> *two_size_array = new vector<string>{"a", "b"};
    ASSERT_THAT(apply(identical_perm, two_size_array), Eq(vector<string>{"a", "b"}));
    delete identical_perm;

    identical_perm = generate_identical_perm(3);
    vector<string> *three_size_array = new vector<string>{"a", "b", "c"};
    ASSERT_THAT(apply(identical_perm, three_size_array), Eq(vector<string>{"a", "b", "c"}));
    delete identical_perm;
}

TEST(GenerateIdenticalPerm, sizeIsNegative_nullptr) {
    ASSERT_THAT(generate_identical_perm(-1), IsNull());
}

TEST(GenerateIdenticalPerm, sizeIsZero_empty) {
    vector<int> empty = {};
    ASSERT_THAT(*generate_identical_perm(0), empty);
}

TEST(GenerateIdenticalPerm, sizeIsOne_0) {
    vector<int> identiacalPerm = {0};
    ASSERT_THAT(*generate_identical_perm(1), identiacalPerm);
}

TEST(GenerateIdenticalPerm, sizeIsTwo_01) {
    vector<int> identiacalPerm = {0, 1};
    ASSERT_THAT(*generate_identical_perm(2), identiacalPerm);
}

TEST(GenerateIdenticalPerm, sizeIsThree_012) {
    vector<int> identiacalPerm = {0, 1, 2};
    ASSERT_THAT(*generate_identical_perm(3), identiacalPerm);
}

vector<string> *generate_array(int n) {
    if (n < 0)
        return nullptr;

    vector<string> *array = new vector<string>{};
    vector<string> alphabet = {"a", "b", "c", "d", "e",
                               "f", "g", "h" "i", "j",
                               "k", "l", "m", "n", "o",
                               "p", "q", "r", "s", "t",
                               "u", "v", "w", "x", "y",
                               "z"};

    for (int i = 0; i < n; i++)
        array->emplace_back(alphabet[i]);

    return array;
}

TEST(GenerateArray, sizeIsNegative_nullptr) {
    ASSERT_THAT(generate_array(-1), IsNull());
}

TEST(GenerateArray, sizeIsZero_empty) {
    vector<string> empty = {};
    ASSERT_THAT(*generate_array(0), empty);
}

TEST(GenerateArray, sizeIsOne_a) {
    vector<string> array = {"a"};
    ASSERT_THAT(*generate_array(1), array);
}

TEST(GenerateArray, sizeIsTwo_ab) {
    vector<string> array = {"a", "b"};
    ASSERT_THAT(*generate_array(2), array);
}

TEST(GenerateArray, sizeIsThree_abc) {
    vector<string> array = {"a", "b", "c"};
    ASSERT_THAT(*generate_array(3), array);
}
