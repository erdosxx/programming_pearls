#include <gtest/gtest.h>
#include <vector>
#include <deque>
#include <utility>
#include <tuple>
#include <string>
#include <functional>
#include <iostream>
#include "object_closure.h"
#include "encapsulating_arguments.h"
#include "booking_com_interview.h"

using std::vector;
using std::deque;
using std::pair;
using std::tuple;
using std::string;
using std::piecewise_construct;
using std::make_pair;
using std::get;
using std::bind;
using std::function;
using std::cin;
using std::cout;

class Getting_Ready_Fixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    Getting_Ready_Fixture() : Test() {

    }

    virtual ~Getting_Ready_Fixture() {
    }
};

TEST_F(Getting_Ready_Fixture, google_style_guide) {
    vector<bool> A={true, false};
    // following does not work. Compile error.
    // bool* pb = &A[0];

    deque<bool> A1={true, false};
    bool* pb1 = &A1[0];
    ASSERT_EQ(*pb1, true);

    vector<int> A2={1,2,3};
    int* pint = &A2[0];
    ASSERT_EQ(*pint, 1);
}

tuple<int, int, int> rotate(tuple<int, int, int> t) {
    //return tuple<int, int, int>{get<2>(t), get<0>(t), get<1>(t)};
    return {get<2>(t), get<0>(t), get<1>(t)};
};

TEST_F(Getting_Ready_Fixture, std_pair_tuple) {
    //// pair: holds two values. See C++PL page 983
    pair<string, int> p {"Cambridge", 1209};
    ASSERT_EQ("Cambridge", p.first);
    ASSERT_EQ(1209, p.second);
    p.second += 800;
    ASSERT_EQ(2009, p.second);

    // make_pair: create a pair without explicitly  mentioning its type.
    auto pr = make_pair("abc", 123);
    ASSERT_EQ("abc", pr.first);
    ASSERT_EQ(123, pr.second);

    // piecewise_construct
    struct Univ {
        Univ(const string& n, int r) : name{n}, rank{r} {}
        string name;
        int rank;
        string city = "unknown";
    };

    using Tup = tuple<string, int>;
    Tup t1 {"Columbia", 11};
    Tup t2 {"Cambridge", 2};

    pair<Tup,Tup> p1 {t1, t2};
    pair<Univ,Univ> p2 {piecewise_construct, t1, t2};

    ASSERT_EQ(p1.first, t1);
    ASSERT_EQ("Columbia", p2.first.name);

    tuple<string, int, double> t3{"Sild", 123, 3.14};

    ASSERT_EQ("Sild", get<0>(t3)); // get first element of tuple
    ASSERT_EQ(123, get<1>(t3));
    ASSERT_EQ(3.14, get<2>(t3));

    auto t4 = rotate({3,7,9});
    ASSERT_EQ(9, get<0>(t4));
    ASSERT_EQ(3, get<1>(t4));
    ASSERT_EQ(7, get<2>(t4));
}

TEST_F(Getting_Ready_Fixture, object_closure) {
    vector<int> A = {0,1,2,3,4,5,6,7,8,9};
    vector<int>* A_ptr = &A;

    vector<int> ans = {10,11,12,13,14,15,16,17,18,19};
    apply_to_A(plus_x(10), A_ptr);
    ASSERT_TRUE(equal(A.cbegin(), A.cend(), ans.cbegin(), ans.cend()));
}

TEST_F(Getting_Ready_Fixture, encapsulating_arguments) {
    call_foo cf(3, 3.14, 'x');
    schedule_at(cf, 1);

    function<void()> cf2 = bind(foo, 3, 3.14, 'x');
    schedule_at(cf2, 3);
}

TEST_F(Getting_Ready_Fixture, booking_com) {
    int input = 1;
    cout << input << endl;
}
