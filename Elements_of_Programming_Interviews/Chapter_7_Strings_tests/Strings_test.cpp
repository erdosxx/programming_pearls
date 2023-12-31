#include <gtest/gtest.h>
#include <random>
#include <stdexcept>
#include <cctype>
#include <cstdio> // for sprintf
#include "strings_boot_camp.h"
#include "Square_root.h" // for using Compare
#include "Interconverting_string_integer.h"
#include "Convert_base.h"
#include "Spreadsheet_encoding.h"
#include "Replace_and_remove.h"
#include "valid-palindrome.h"
#include "Reverse_words.h"
#include "Phone_mnemonic.h"
#include "Phone_mnemonic_iterative.h"
#include "look-and-say.h"
#include "roman-to-integer.h"
#include "integer-to-roman.h"
#include "valid-IP-address.h"
#include "snake-string.h"
#include "Run_length_compression.h"
#include "Run_length_compression_google.h"
#include "rabin-karp.h"

using std::cout;
using std::default_random_engine;
using std::numeric_limits;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::max;
using std::toupper;
using std::tolower;
using std::islower;
using std::isupper;
using std::isalnum;
using std::isdigit;
using std::sprintf;
using std::invalid_argument;
using std::to_string;
//using rabin_karp::RabinKarp;

class Strings_Fixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    string p_7_1_RandIntString(int len);
    string p_7_3_RandString(int len);
    int p_7_13_CheckAnswer(const string &t, const string &s);
    string p_7_13_RandString(int len);

    string p_7_4_RandString(int len);
    bool p_7_4_CheckAns(const string &s, const string &ans);
    string p_7_6_RandString(int len);
    bool p_7_6_CheckAnswer(const string &ori, string *str);
    string p_7_7_RandString(int len);
    string p_7_11_RandString(size_t len);

public:
    Strings_Fixture() : Test() {

    }


    virtual ~Strings_Fixture() {
    }
};

string Strings_Fixture::p_7_11_RandString(size_t len) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    uniform_int_distribution<char> dis('A', 'Z');
    string result;
    while (len--) {
        result += dis(gen);
    }
    return result;
}

string Strings_Fixture::p_7_7_RandString(int len) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device()) ());
    string ret;
    while (len--) {
        uniform_int_distribution<char> dis('0', '9');
        ret += dis(gen);
    }
    return ret;
}

string Strings_Fixture::p_7_4_RandString(int len) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device()) ());
    string ret;
    while (len--) {
        uniform_int_distribution<char> dis('a', 'd');
        ret += dis(gen);
    }
    return ret;
}

string Strings_Fixture::p_7_6_RandString(int len) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device()) ());
    string ret;

    while (len--) {
        uniform_int_distribution<int> dis(0, 52);
        int ch = dis(gen);

        if (ch == 52) {
            ret += ' ';
        } else if (ch < 26) {
            ret += ch + 'a';
        } else {
            ret += ch - 26 + 'A';
        }
    }
    return ret;
}

bool Strings_Fixture::p_7_6_CheckAnswer(const string &ori, string *str) {
    reverse_words::ReverseWords(str);
    return ori.compare(*str) == 0;
}

bool Strings_Fixture::p_7_4_CheckAns(const string &s, const string &ans) {
    string temp;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'a') {
            temp += 'd', temp += 'd';
        } else if (s[i] != 'b') {
            temp += s[i];
        }
    }
    return ans.compare(temp) == 0;
}

string Strings_Fixture::p_7_3_RandString(int len) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    string ret;
    uniform_int_distribution<int> dis('A', 'Z');
    while (len--) {
        ret.push_back(dis(gen));
    }
    return ret;
}

string Strings_Fixture::p_7_1_RandIntString(int len) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    string ret;
    if (len == 0) {
        return {"0"};
    }

    uniform_int_distribution<int> pos_or_neg(0, 1);
    if (pos_or_neg(gen)) {
        ret.push_back('-');
    }

    uniform_int_distribution<int> num_dis('1', '9');
    ret.push_back(num_dis(gen));

    while (--len) {
        uniform_int_distribution<int> dis('0', '9');
        ret.push_back(dis(gen));
    }

    return ret;
}

int Strings_Fixture::p_7_13_CheckAnswer(const string &t, const string &s) {
    for (int i = 0; i + s.size() - 1 < t.size(); ++i) {
        bool find = true;
        for (int j = 0; j < s.size(); ++j) {
            if (t[i + j] != s[j]) {
                find = false;
                break;
            }
        }
        if (find == true) {
            return i;
        }
    }
    return -1;  // No matching.
}

string Strings_Fixture::p_7_13_RandString(int len) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    string ret;
    while (len--) {
        uniform_int_distribution<char> dis('a', 'z');
        ret += dis(gen);
    }
    return ret;
}

TEST_F(Strings_Fixture, strings_boot_camp) {
    string s1 = "a";
    ASSERT_TRUE(IsPalindromic(s1));

    s1 = "ab";
    ASSERT_FALSE(IsPalindromic(s1));

    s1 = "aa";
    ASSERT_TRUE(IsPalindromic(s1));

    s1 = "abc";
    ASSERT_FALSE(IsPalindromic(s1));

    s1 = "aba";
    ASSERT_TRUE(IsPalindromic(s1));
}

TEST_F(Strings_Fixture, stl_library) {
    string s1 = "Paul";
    string s2 = "";

    s1.append(" Erdos");
    ASSERT_EQ("Paul Erdos", s1); // Paul Erdos

    s1.append(3, '-'); //append 3 copies of '-': "---"
    ASSERT_EQ("Paul Erdos---", s1); // Paul Erdos

    s1 = "a";
    s2 = "b";
    s1 += s2;
    ASSERT_EQ("ab", s1);

    s1= "a";
    s1.push_back('b'); // ab
    ASSERT_EQ("ab", s1);
    s1.pop_back(); //a
    ASSERT_EQ("a", s1);

    s1= "a";
    char* a_ch = new char('b');
    string s3(a_ch);
    s1 += s3;
    ASSERT_EQ("ab", s1);
    delete a_ch;

    // insert
    // s.insert(pos, x): Insert x before s[pos]; x can be a character, a string.
                        // a C-style string, or an initializer_list<char_type>
    s1="a b";
    s2="middle";
    //size_t p = s1.find(' ');
    auto p = s1.find(' ');
    ASSERT_EQ(1, p);
    s1.insert(p, ' '+ s2);  // insert before p.
    ASSERT_EQ("a middle b", s1);

    // find from start position
    s1="a b c d";
    size_t p1 = s1.find(" ",4); // search from c
    ASSERT_EQ(5, p1);

    s1= "a b";
    s1.insert(p, {' ', '|', 'm', '|'});
    ASSERT_EQ("a |m| b", s1);

    s1= "abcd";
    s1.insert(s1.begin() + 3, '|'); //insert | before d
    ASSERT_EQ("abc|d", s1);

    ASSERT_TRUE("abc" < "abcd");
    ASSERT_TRUE("abc" < "bcd");

    // s.erase(pos):  Remove trailing characters from s, starting with s[pos];
                     // s.size() becomes pos
    s1="abcd";
    s1.erase(s1.begin()+2); // remove c
    ASSERT_EQ("abd",s1);

    s1="abcde";
    s1.erase(s1.begin()+2, s1.begin()+4); // abcde  remove [b,e)
                                          //   ^^
    ASSERT_EQ("abe", s1);

    // not work.
    // See example: http://www.cplusplus.com/reference/string/string/erase/
    /*
    s1="abcde";
    s1.erase(s1.begin()+2,2);   // abcde  remove n characters from s, starting with s[pos];
                                //   ^^
    ASSERT_EQ("abe", s1);
     */

    s1="abcde";
    s1.erase(2,2);   // abcde  remove n characters from s, starting with s[pos];
                     //   ^^
    ASSERT_EQ("abe", s1);

    // Numeric conversions
    // sting -> integer
    // Initial whitespace is skpped
    s1 = "   123.45";
    int x1 = stoi(s1);  // convert to decimal x=123
    ASSERT_EQ(123, x1);

    double x2 = stod(s1);  // convert to double
    ASSERT_EQ(Compare(x2, 123.45), EQUAL);

    float x3 = stof(s1); // convert to float
    ASSERT_EQ(Compare(x3, 123.45), SMALLER);
    // for non numeric data, throw invalid_argument.
    s1 = "+";
    size_t idx;
    ASSERT_THROW(stoi(s1, &idx), invalid_argument);

    // integer -> string
    // itoa
    // This function is not defined in ANSI-C and is not part of C++, but is supported by some compilers.
    // see http://www.cplusplus.com/reference/cstdlib/itoa/
    int x = 324;
    char* carray = new char[4];
    // int sprintf ( char * str, const char * format, ... );
    // see http://www.cplusplus.com/reference/cstdio/sprintf/
    sprintf(carray, "%d", x);
    string str(carray);
    ASSERT_EQ("324", str);
    delete [] carray;
    // to_string
    x = 12;
    string x_str = to_string(x);
    ASSERT_EQ("12", x_str);
    x = -12;
    x_str = to_string(x);
    ASSERT_EQ("-12", x_str);

    // sort
    s1="dfceab";
    sort(s1.begin(), s1.end());
    ASSERT_EQ("abcdef", s1);

    // substring constructor
    // basic_string s {s2, pos, n}; s <= s2[pos:pos+n)
    s1="abcdefg";           //  abcdefg
    string sbstr {s1, 1, 3}; //   ^ ^
    ASSERT_EQ("bcd", sbstr);
    ASSERT_EQ("bcdefg", s1.substr(1));
    ASSERT_EQ("cdefg", s1.substr(2));
    ASSERT_EQ("fg", s1.substr(5));

    // substring copy
    // s2 = s.substr(pos, n)  s2=basic_string(&s[pos],m) where m=min(s.size()-pos, n);
    s1= "abcdefg";       // abcdefg
    s2= s1.substr(2,3);  //   ^ ^
    ASSERT_EQ("cde", s2);

    // substr more than size
    s1= "abcd";
    s2= s1.substr(0,5);
    ASSERT_EQ("abcd", s2);
    s2= s1.substr(0,15);  // just copy existing.
    ASSERT_EQ("abcd", s2);

    // n = s.compare(s2)
    // A lexicographical comparision of s and s2;
    // using char_traits<C>::compare() for comparison;
    // n=0 if s==s2; n<0 if s<s2; n>0 if s>s2; noexcept;

    s1="abcd";
    s2="abcde";
    ASSERT_TRUE(s1.compare(s2) < 0);  // s1 < s2

    // n2=s.compare(pos, n, s2)
    // n2= basic_string{s,pos,n}.compare(s2)
    s1="abcsubd";               //  abcsubd
    s2="sub2";                  //     ^ ^
    ASSERT_TRUE(s1.compare(3,3,s2) < 0 );  // sub < sub2

    // n2=s.compare(pos, n, s2, pos2, n2)
    // n2 = basic_string{s,pos,n}.compare(basic_string{s2,pos2,n2})
    s1="abcsubd";
    s2="sub2";
    ASSERT_TRUE(s1.compare(3,3,s2,0,3) == 0); // sub == sub

    // toupper, tolower
    s1 = "abc";
    s2 = "";
    for (const char& c : s1) {
        s2 += toupper(c);
        ASSERT_TRUE(islower(c));
        ASSERT_TRUE(isalpha(c));
        ASSERT_TRUE(isalnum(c));
        ASSERT_FALSE(isdigit(c));
    }
    ASSERT_EQ("ABC", s2);

    s1 = "ABC";
    s2 = "";
    for (const char& c : s1) {
        s2 += tolower(c);
        ASSERT_TRUE(isupper(c));
        ASSERT_TRUE(isalpha(c));
        ASSERT_TRUE(isalnum(c));
        ASSERT_FALSE(isdigit(c));
    }
    ASSERT_EQ("abc", s2);
}

TEST_F(Strings_Fixture, interconverting_stirng_integer_Function) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device()) ());
    // 2^31 -1 = 2147483648
    char* tmp_char = new char[11];

    for (int times = 0; times < 10000; ++times) {
        uniform_int_distribution<int> dis(numeric_limits<int>::min(),
                                          numeric_limits<int>::max());
        int x = dis(gen);
        string str = IntToString(x);
        sprintf(tmp_char, "%d", x);
        string str2(tmp_char);
        ASSERT_EQ(str2, str);
        ASSERT_EQ(stoi(str), x);

        uniform_int_distribution<int> len_dis(0, 9);
        str = p_7_1_RandIntString(len_dis(gen));
        x = StringToInt(str);
        ASSERT_EQ(stoi(str), x);
    }
    delete [] tmp_char;
}

TEST_F(Strings_Fixture, Convert_base_Function) {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());

    for (int times = 0; times < 100000; ++times) {
        uniform_int_distribution<int> len_dis(1, 9);
        string input = p_7_1_RandIntString(len_dis(gen));

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
    ASSERT_EQ(2, 1<<1);  // 1 = 1   -> 10   = 2
    ASSERT_EQ(4, 2<<1);  // 2 = 10  -> 100  = 4
    ASSERT_EQ(6, 3<<1);  // 3 = 11  -> 110  = 6
    ASSERT_EQ(8, 4<<1);  // 4 = 100 -> 1000 = 8
    ASSERT_EQ(10, 5<<1); // 5 = 101 -> 1010 = 10

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());

    for (int times = 0; times < 1000; ++times) {
        uniform_int_distribution<int> dis(1, 1000);
        string s = p_7_4_RandString(dis(gen));

        //char *s_copy = new char[2 * s.size() + 1];
        char *s_copy = new char[(s.size() << 1) + 1];
        strcpy(s_copy, s.c_str());
        int final_size = r_n_r::ReplaceAndRemove(s.size(), s_copy);
        ASSERT_TRUE(p_7_4_CheckAns(s, string(s_copy, final_size)));
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

    input = "a  abc cd";
    reverse_words::ReverseWords(&input);
    ASSERT_TRUE(input.compare("cd abc  a") == 0);

    input = " abc";
    reverse_words::ReverseWords(&input);
    ASSERT_TRUE(input.compare("abc ") == 0);

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    for (int times = 0; times < 1000; ++times) {
        uniform_int_distribution<int> dis(0, 9999);
        string str = p_7_6_RandString(dis(gen));

        string original_str(str);
        reverse_words::ReverseWords(&str);

        ASSERT_TRUE(p_7_6_CheckAnswer(original_str, &str));
    }
}

TEST_F(Strings_Fixture, phone_mnemonic_Function) {
    string num = "0";
    vector<string> result = PhoneMnemonic(num);
    vector<string> golden = {"0"};
    ASSERT_TRUE(equal(result.cbegin(), result.cend(), golden.cbegin(), golden.cend()));

    num = "2";
    result = PhoneMnemonic(num);
    golden = {"A", "B", "C"};
    ASSERT_TRUE(equal(result.cbegin(), result.cend(), golden.cbegin(), golden.cend()));

    num = "23";
    result = PhoneMnemonic(num);
    golden = {"AD", "AE", "AF", "BD", "BE", "BF", "CD", "CE", "CF"};
    ASSERT_TRUE(equal(result.cbegin(), result.cend(), golden.cbegin(), golden.cend()));

    /*
    string num = p_7_7_RandString(3);
    auto result = phone::PhoneMnemonic(num);
    cout << "number = " << num << endl;
    for (const string& str : result) {
        cout << str << endl;
    }
     */
}

TEST_F(Strings_Fixture, phone_mnemonic_iterative) {
    string num = "0";
    vector<string> result = PhoneMnemonic_iterative(num);
    vector<string> golden = {"0"};
    ASSERT_TRUE(equal(result.cbegin(), result.cend(), golden.cbegin(), golden.cend()));

    num = "2";
    result = PhoneMnemonic_iterative(num);
    golden = {"A", "B", "C"};
    ASSERT_TRUE(equal(result.cbegin(), result.cend(), golden.cbegin(), golden.cend()));

    num = "23";
    result = PhoneMnemonic_iterative(num);
    golden = {"AD", "AE", "AF", "BD", "BE", "BF", "CD", "CE", "CF"};
    ASSERT_TRUE(equal(result.cbegin(), result.cend(), golden.cbegin(), golden.cend()));

    for (int i = 0; i < 100; ++i) {
        num = p_7_7_RandString(4);
        result = PhoneMnemonic(num);
        vector<string> result2 = PhoneMnemonic_iterative(num);
        ASSERT_TRUE(equal(result.cbegin(), result.cend(), result2.cbegin(), result2.cend()));
    }
}


TEST_F(Strings_Fixture, look_and_say_Function) {
    ASSERT_EQ("1", LookAndSay(1));
    ASSERT_EQ("11", LookAndSay(2));
    ASSERT_EQ("21", LookAndSay(3));
    ASSERT_EQ("1211", LookAndSay(4));
    ASSERT_EQ("111221", LookAndSay(5));
    ASSERT_EQ("312211", LookAndSay(6));
    ASSERT_EQ("13112221", LookAndSay(7));
    ASSERT_EQ("1113213211", LookAndSay(8));
}

TEST_F(Strings_Fixture, roman_to_integer_Function) {
    ASSERT_EQ(4, RomanToInteger("IV"));
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

TEST_F(Strings_Fixture, integer_to_roman) {
    // int_to_roman works upto 3999
    ASSERT_EQ("I", int_to_roman(1));
    ASSERT_EQ("IV", int_to_roman(4));
    ASSERT_EQ("XXXIX", int_to_roman(39));
    ASSERT_EQ("MMMCCXXV", int_to_roman(3225));
    ASSERT_EQ("MMMCMXCIX", int_to_roman(3999));

    ASSERT_EQ("I", int_to_roman_erdos(1));
    ASSERT_EQ("IV", int_to_roman_erdos(4));
    ASSERT_EQ("XXXIX", int_to_roman_erdos(39));
    ASSERT_EQ("MMMCCXXV", int_to_roman_erdos(3225));
    ASSERT_EQ("MMMCMXCIX", int_to_roman_erdos(3999));
    ASSERT_EQ("MMMMMMMMMCMXIX", int_to_roman_erdos(9919));
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
    ASSERT_EQ("e lHloWrdlo!", SnakeString("Hello World!"));
}

TEST_F(Strings_Fixture, run_length_Function) {
    ASSERT_EQ("4a1b3c2a", Encoding("aaaabcccaa"));
    ASSERT_EQ("eeeffffee", Decoding("3e4f2e"));
    ASSERT_EQ("aaaaaaaaaaffffee", Decoding("10a4f2e"));
}

TEST_F(Strings_Fixture, run_length_google) {
    //// get_count
    int idx = 0;
    ASSERT_EQ(0, get_count("[ab]", &idx));
    ASSERT_EQ(0, idx);

    idx = 0;
    ASSERT_EQ(1, get_count("1[ab]", &idx));
    ASSERT_EQ(0, idx);

    idx = 0;
    ASSERT_EQ(12, get_count("12[ab]", &idx));
    ASSERT_EQ(1, idx);

    idx = 0;
    ASSERT_EQ(123, get_count("123[ab]", &idx));
    ASSERT_EQ(2, idx);

    idx = 7;
    ASSERT_EQ(32, get_count("123[ab]32[ac]", &idx));
    ASSERT_EQ(8, idx);

    //// get_pattern_str
    idx = 0;
    ASSERT_EQ("a", get_pattern_str("[a]", &idx));
    ASSERT_EQ(2, idx);

    idx = 0;
    ASSERT_EQ("a2[ab]c", get_pattern_str("[a2[ab]c]", &idx));
    ASSERT_EQ(8, idx);

    idx = 3;
    ASSERT_EQ("ab", get_pattern_str("[a2[ab]c]", &idx));
    ASSERT_EQ(6, idx);

    //// decoding_google
    ASSERT_EQ("a", decoding_google("a"));
    ASSERT_EQ("abab", decoding_google("2[ab]"));
    ASSERT_EQ("aabab", decoding_google("a2[ab]"));
    ASSERT_EQ("aababc", decoding_google("a2[ab]c"));
    ASSERT_EQ("aababcdebbb", decoding_google("a2[ab]cde3[b]"));
    ASSERT_EQ("aababcdebfbfbf", decoding_google("a2[ab]cde3[bf]"));
    ASSERT_EQ("aabfbfbfabfbfbfa", decoding_google("aa3[bf]a3[bf]a"));
    ASSERT_EQ("aabfbfbfabfbfbfa", decoding_google("a2[a3[bf]]a"));
    ASSERT_EQ("tgbfbfbfhgbfbfbfhc", decoding_google("t2[g3[bf]h]c"));
}

TEST_F(Strings_Fixture, rabin_karp_Function) {
    ASSERT_EQ(1, get_power_n(26, 1));
    ASSERT_EQ(26, get_power_n(26, 2));
    ASSERT_EQ(26*26, get_power_n(26, 3));

    string pattern = "CGC";
    string text = "GACGCCA";
    int prev_hash = 0;
    ASSERT_EQ('G'*26*26 + 'A'*26 + 'C', get_next_hash(&prev_hash, 3, 26, 26*26, &text, 0));
    prev_hash = 'G'*26*26 + 'A'*26 + 'C';
    ASSERT_EQ('A'*26*26 + 'C'*26 + 'G', get_next_hash(&prev_hash, 3, 26, 26*26, &text, 1));

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
    ASSERT_EQ(RabinKarp("FOOBAR", "BAR"), 3);
    ASSERT_EQ(RabinKarp("absycvh", "y"), 3);

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<int> t_dis(1, 1000);
        uniform_int_distribution<int> s_dis(1, 20);

        string t = p_7_13_RandString(t_dis(gen));
        string s = p_7_13_RandString(s_dis(gen));

        //cout << "text: " << t << endl;
        //cout << "pattern: " << s << endl;

        ASSERT_EQ(RabinKarp(t, s), p_7_13_CheckAnswer(t, s));
    }
}
