#include "gtest/gtest.h"
#include "permute_the_elements_of_an_array_6_9.h"

using std::cout;
using std::endl;

using permute_the_elements::permute;

class permute_elements_Fixture : public ::testing::Test {
protected:
    virtual void SetUp() {
        cout << "SetUp is called" << endl;
    }

    virtual void TearDown() {
        cout << "TearDown is called" << endl;
    }

public:
    permute_elements_Fixture() : Test() {
        cout << endl << "Constructor is called" << endl;
    }

    virtual ~permute_elements_Fixture() {
        cout << "Destructor is called" << endl;
    }
};

//TEST_F(permute_elements_Fixture, PIsNullAndAIsNull_returnNull) {
//    //ASSERT_THAT(permute({}, {}), ElementsAre());
//}

TEST_F(permute_elements_Fixture, test_process_1) {
}

TEST_F(permute_elements_Fixture, test_process_2) {
}

TEST_F(permute_elements_Fixture, test_process_3) {
}

TEST_F(permute_elements_Fixture, test_process_4) {
}
