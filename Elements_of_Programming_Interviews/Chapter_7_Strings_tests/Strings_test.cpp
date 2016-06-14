#include <gtest/gtest.h>
#include <random>
#include "Interconverting_string_integer.h"
#include "Convert_base.h"
#include "Spreadsheet_encoding.h"
#include "Replace_and_remove.h"
#include "valid-palindrome.h"
#include "Reverse_words.h"
#include "Phone_mnemonic.h"
#include "look-and-say.h"
#include "roman-to-integer.h"
#include "valid-IP-address.h"
#include "snake-string.h"
#include "Run_length_compression.h"
#include "rabin-karp.h"

using std::cout;
using std::default_random_engine;
using std::numeric_limits;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::max;
using rabin_karp::RabinKarp;

class Strings_Fixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    Strings_Fixture() : Test() {

    }

    virtual ~Strings_Fixture() {
    }
};

TEST_F(Strings_Fixture, interconverting_stirng_integer_Function) {
    default_random_engine gen((random_device()) ());

    for (int times = 0; times < 10000; ++times) {
        uniform_int_distribution<int> dis(numeric_limits<int>::min(),
                                          numeric_limits<int>::max());
        int x = dis(gen);
        string str = IntToString(x);
        ASSERT_EQ(stoi(str), x);

        uniform_int_distribution<int> len_dis(0, 9);
        str = RandIntString(len_dis(gen));
        x = StringToInt(str);
        ASSERT_EQ(stoi(str), x);
    }
}

TEST_F(Strings_Fixture, Convert_base_Function) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 100000; ++times) {
        uniform_int_distribution<int> len_dis(1, 9);
        string input = RandIntString(len_dis(gen));

        uniform_int_distribution<int> base_dis(2, 16);
        int base = base_dis(gen);
        ASSERT_EQ(input, ConvertBase(ConvertBase(input, 10, base), base, 10));
    }
}

TEST_F(Strings_Fixture, spreadsheet_encoding_Function) {
    ASSERT_EQ(1, SSDecodeColID("A"));
    ASSERT_EQ(2, SSDecodeColID("B"));
    ASSERT_EQ(26, SSDecodeColID("Z"));
    ASSERT_EQ(27, SSDecodeColID("AA"));
}

TEST_F(Strings_Fixture, replace_and_remove_Function) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 1000; ++times) {
        uniform_int_distribution<int> dis(1, 1000);
        string s = r_n_r::RandString(dis(gen));

        char *s_copy = new char[(s.size() << 1) + 1];
        strcpy(s_copy, s.c_str());
        int final_size = r_n_r::ReplaceAndRemove(s.size(), s_copy);
        ASSERT_TRUE(r_n_r::CheckAns(s, string(s_copy, final_size)));
    }
}

TEST_F(Strings_Fixture, test_palindrome_Function) {
    ASSERT_TRUE(IsPalindrome("A man, a plan, a canal: Panama"));
    ASSERT_FALSE(IsPalindrome("race a car"));
    ASSERT_TRUE(IsPalindrome("Able was I, ere I saw Elba!"));
    ASSERT_FALSE(IsPalindrome("Ray a Ray"));
    ASSERT_TRUE(IsPalindrome(""));
}

TEST_F(Strings_Fixture, Reverse_words_Function) {
    string input = "a cat and dog";
    reverse_words::ReverseWords(&input);
    ASSERT_TRUE(input.compare("dog and cat a") == 0);

    input = "dog";
    reverse_words::ReverseWords(&input);
    ASSERT_TRUE(input.compare("dog") == 0);

    input = "a  bbb cc";
    reverse_words::ReverseWords(&input);
    ASSERT_TRUE(input.compare("cc bbb  a") == 0);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 1000; ++times) {
        uniform_int_distribution<int> dis(0, 9999);
        string str = reverse_words::RandString(dis(gen));

        string original_str(str);
        reverse_words::ReverseWords(&str);

        ASSERT_TRUE(reverse_words::CheckAnswer(original_str, &str));
    }
}

/*  TODO: add testing with sort vector<string> and compare the result.
TEST_F(Strings_Fixture, phone_mnemonic_Function) {
    string num = phone::RandString(3);
    auto result = phone::PhoneMnemonic(num);
    cout << "number = " << num << endl;
    for (const string& str : result) {
        cout << str << endl;
    }
}
*/

TEST_F(Strings_Fixture, look_and_say_Function) {
    ASSERT_TRUE(LookAndSay(1).compare("1") == 0);
    ASSERT_TRUE(LookAndSay(2).compare("11") == 0);
    ASSERT_TRUE(LookAndSay(3).compare("21") == 0);
    ASSERT_TRUE(LookAndSay(4).compare("1211") == 0);
    ASSERT_TRUE(LookAndSay(5).compare("111221") == 0);
    ASSERT_TRUE(LookAndSay(6).compare("312211") == 0);
    ASSERT_TRUE(LookAndSay(7).compare("13112221") == 0);
    ASSERT_TRUE(LookAndSay(8).compare("1113213211") == 0);
}

TEST_F(Strings_Fixture, roman_to_integer_Function) {
    ASSERT_EQ(7, RomanToInteger("VII"));
    ASSERT_EQ(184, RomanToInteger("CLXXXIV"));
    ASSERT_EQ(9, RomanToInteger("IX"));
    ASSERT_EQ(40, RomanToInteger("XL"));
    ASSERT_EQ(60, RomanToInteger("LX"));
    ASSERT_EQ(1500, RomanToInteger("MD"));
    ASSERT_EQ(400, RomanToInteger("CD"));
    ASSERT_EQ(1900, RomanToInteger("MCM"));
    ASSERT_EQ(9919, RomanToInteger("MMMMMMMMMCMXIX"));
}

TEST_F(Strings_Fixture, valid_ip_address_Function) {
    auto res1 = GetValidIPAddress("255255255255");
    ASSERT_EQ(1, res1.size());
    ASSERT_TRUE(res1.front() == "255.255.255.255");

    auto res2 = GetValidIPAddress("19216811");
    ASSERT_EQ(9, res2.size());

    auto res3 = GetValidIPAddress("1111");
    ASSERT_EQ(1, res3.size());
    ASSERT_TRUE(res3.front().compare("1.1.1.1") == 0);

    auto res4 = GetValidIPAddress("11000");
    ASSERT_EQ(2, res4.size());
    sort(res4.begin(), res4.end());

    ASSERT_TRUE(res4[0].compare("1.10.0.0") == 0);
    ASSERT_TRUE(res4[1].compare("11.0.0.0") == 0);
}

TEST_F(Strings_Fixture, snake_string_Function) {
    ASSERT_TRUE(SnakeString("Hello World!").compare("e lHloWrdlo!") == 0);
}

TEST_F(Strings_Fixture, run_length_Function) {
    ASSERT_TRUE(string("4a1b3c2a") == Encoding("aaaabcccaa"));
    ASSERT_TRUE(string("eeeffffee") == Decoding("3e4f2e"));
    ASSERT_TRUE(string("aaaaaaaaaaffffee") == Decoding("10a4f2e"));
}

TEST_F(Strings_Fixture, rabin_karp_Function) {
    ASSERT_EQ(RabinKarp("GACGCCA", "CGC"), 2);
    ASSERT_EQ(RabinKarp("GATACCCATCGAGTCGGATCGAGT", "GAG"), 10);
    ASSERT_EQ(RabinKarp("FOOBARWIDGET", "WIDGETS"), -1);
    ASSERT_EQ(RabinKarp("A", "A"), 0);
    ASSERT_EQ(RabinKarp("A", "B"), -1);
    ASSERT_EQ(RabinKarp("A", ""), 0);
    ASSERT_EQ(RabinKarp("ADSADA", ""), 0);
    ASSERT_EQ(RabinKarp("", "A"), -1);
    ASSERT_EQ(RabinKarp("", "AAA"), -1);
    ASSERT_EQ(RabinKarp("A", "AAA"), -1);
    ASSERT_EQ(RabinKarp("AA", "AAA"), -1);
    ASSERT_EQ(RabinKarp("AAA", "AAA"), 0);
    ASSERT_EQ(RabinKarp("BAAAA", "AAA"), 1);
    ASSERT_EQ(RabinKarp("BAAABAAAA", "AAA"), 1);
    ASSERT_EQ(RabinKarp("BAABBAABAAABS", "AAA"), 8);
    ASSERT_EQ(RabinKarp("BAABBAABAAABS", "AAAA"), -1);
    ASSERT_GT(RabinKarp("FOOBAR", "BAR"), 0);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 10000; ++times) {
      uniform_int_distribution<int> t_dis(1, 1000);
      uniform_int_distribution<int> s_dis(1, 20);

      string t = rabin_karp::RandString(t_dis(gen));
      string s = rabin_karp::RandString(s_dis(gen));

      ASSERT_EQ(RabinKarp(t, s), rabin_karp::CheckAnswer(t, s));
    }
}
