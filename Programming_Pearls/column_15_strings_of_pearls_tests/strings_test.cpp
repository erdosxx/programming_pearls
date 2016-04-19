#include "column15.h"
#include <gtest/gtest.h>
#include <map>
#include <set>
#include <string>

using namespace std;

class StringsFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    map<string, int> map_str_int;
    map<string, int>::iterator itr_map_str_int;

    StringSetSTL set_str;

    int size_ary=100000;
    int* target_array = new int[size_ary];

    int check_increate_array_without_duplicate(int* x, int n) {
        for(int i=1; i < n; i++){
            if (x[i] - x[i-1] <= 0)
                return 0;  // test fail
        }
        return 1; // test pass
    }

public:
    StringsFixture() : Test() {
    }

    virtual ~StringsFixture() {

    }
};

TEST_F(StringsFixture, map_str_int_Function) {
    string company[] = {"Samsung", "LG", "Apple", "Google", "Facebook", "Google", "Samsung", "Amazon"};

    for (int i=0; i<8; i++)
        map_str_int[company[i]]++;

    ASSERT_EQ(2, map_str_int["Samsung"]);
    ASSERT_EQ(1, map_str_int["LG"]);
    ASSERT_EQ(1, map_str_int["Apple"]);
    ASSERT_EQ(2, map_str_int["Google"]);
    ASSERT_EQ(1, map_str_int["Facebook"]);
    ASSERT_EQ(1, map_str_int["Amazon"]);
}

TEST_F(StringsFixture, set_str_Function) {
    string company[] = {"Samsung", "LG", "Apple", "Google", "Facebook", "Google", "Samsung", "Amazon"};

    for (int i=0; i<8; i++)
        set_str.insert(company[i]);

    string ordered_company[8];
    set_str.report(ordered_company);

    ASSERT_TRUE(ordered_company[0] == "Amazon");
    ASSERT_TRUE(ordered_company[1] == "Apple");
    ASSERT_TRUE(ordered_company[2] == "Facebook");
    ASSERT_TRUE(ordered_company[3] == "Google");
    ASSERT_TRUE(ordered_company[4] == "LG");
    ASSERT_TRUE(ordered_company[5] == "Samsung");
}

TEST_F(StringsFixture, countWord_Function) {
    countWord atest;

    char *input_chars[] = {"Samsung", "LG", "Apple", "Google", "Facebook", "Google", "Samsung", "Amazon"};
    //string input_chars[] = {"Samsung", "LG", "Apple", "Google", "Facebook", "Google", "Samsung", "Amazon"};

    for(int i=0; i<8; i++){
        atest.incword(input_chars[i]);
    }

    ASSERT_EQ(2, atest.findcount("Samsung"));
    ASSERT_EQ(1, atest.findcount("LG"));
    ASSERT_EQ(1, atest.findcount("Apple"));
    ASSERT_EQ(2, atest.findcount("Google"));
    ASSERT_EQ(1, atest.findcount("Facebook"));
    ASSERT_EQ(1, atest.findcount("Amazon"));
    ASSERT_EQ(0, atest.findcount("Doosan"));
}

TEST_F(StringsFixture, longDupSubStr_case1) {
    longDupSubStr atest;
    atest.getInputStr("banana");
    ASSERT_EQ(6, atest.get_size());

    ASSERT_STREQ("banana", atest.get_char(0));
    ASSERT_STREQ("anana", atest.get_char(1));
    ASSERT_STREQ("nana", atest.get_char(2));
    ASSERT_STREQ("ana", atest.get_char(3));
    ASSERT_STREQ("na", atest.get_char(4));
    ASSERT_STREQ("a", atest.get_char(5));

    atest.sortarray();
    ASSERT_STREQ("a", atest.get_char(0));
    ASSERT_STREQ("ana", atest.get_char(1));
    ASSERT_STREQ("anana", atest.get_char(2));
    ASSERT_STREQ("banana", atest.get_char(3));
    ASSERT_STREQ("na", atest.get_char(4));
    ASSERT_STREQ("nana", atest.get_char(5));

    char outchar[1000];
    atest.getMaxSubStr(1, outchar);
    ASSERT_EQ(1, atest.get_maxi());
    ASSERT_EQ(3, atest.get_maxlen());
    ASSERT_STREQ("ana", outchar);
}

TEST_F(StringsFixture, longDupSubStr_case2) {
    longDupSubStr atest;
    atest.getInputStr("AGCTTTCATGCTTAGGGCCTTCTAGGCT");

    char outchar[1000];
    atest.getMaxSubStr(1, outchar);
    ASSERT_EQ(13, atest.get_maxi());
    ASSERT_EQ(4, atest.get_maxlen());
    ASSERT_STREQ("GCTT", outchar);

    longDupSubStr btest;
    btest.getInputStr("AGCTTTCATGCTTAGGGCCTTCTAGGCT");
    char outchar1[1000];
    btest.getMaxSubStr(2, outchar1);
    ASSERT_EQ(8, btest.get_maxi());
    ASSERT_EQ(3, btest.get_maxlen());
    ASSERT_STREQ("CTT", outchar1);
}

TEST_F(StringsFixture, markov_case1_class) {
    char inputstring[]="of the people, by the people, for the people";

    markov atest(inputstring, 1);
    //ASSERT_EQ(8, atest.getnword());
    ASSERT_STREQ("of", atest.getword(0));
    ASSERT_STREQ("the", atest.getword(1));
    ASSERT_STREQ("people,", atest.getword(2));
    ASSERT_STREQ("by", atest.getword(3));
    ASSERT_STREQ("the", atest.getword(4));
    ASSERT_STREQ("people,", atest.getword(5));
    ASSERT_STREQ("for", atest.getword(6));
    ASSERT_STREQ("the", atest.getword(7));
    ASSERT_STREQ("people", atest.getword(8));

    atest.sort();
    ASSERT_STREQ("by", atest.getword(0));
    ASSERT_STREQ("for", atest.getword(1));
    ASSERT_STREQ("of", atest.getword(2));
    ASSERT_STREQ("people", atest.getword(3));
    ASSERT_STREQ("people,", atest.getword(4));
    ASSERT_STREQ("people,", atest.getword(5));
    ASSERT_STREQ("the", atest.getword(6));
    ASSERT_STREQ("the", atest.getword(7));
    ASSERT_STREQ("the", atest.getword(8));

    atest.gen_random_text_by_bin_search(20);
    ASSERT_EQ(9, atest.getnword());
    ASSERT_STREQ("by", atest.get_gen_word(0));
    //ASSERT_STREQ("the", atest.get_gen_word(1));
    //ASSERT_STREQ("people,", atest.get_gen_word(2));
    //ASSERT_STREQ("by", atest.get_gen_word(3));
    ASSERT_GE(20, atest.get_num_gen_word());
    atest.report_gen_text();
}

TEST_F(StringsFixture, wordncmp_test) {
    char inputstring[]="";

    markov atest(inputstring, 1);

    char a[] ="happy";
    char b[] ="happy";
    ASSERT_EQ(0, atest.get_wordncmp(a, b, 1));

    char c[]="happy\0 A";
    char d[] ="happy\0 B";
    ASSERT_EQ(0, atest.get_wordncmp(c, d, 1));
    ASSERT_NE(0, atest.get_wordncmp(c, d, 2));

    char e[]="happy\0 Day\0 A";
    char f[] ="happy\0 Day\0 B";
    ASSERT_EQ(0, atest.get_wordncmp(e, f, 1));
    ASSERT_EQ(0, atest.get_wordncmp(e, f, 2));
    ASSERT_NE(0, atest.get_wordncmp(e, f, 3));
}

TEST_F(StringsFixture, markov_case_binary_search) {
    char inputstring[]="Every reader, as he reads, is actually the reader of himself. "
            "The writer's work is only a kind of optical instrument he provides the "
            "reader so he can discern what he might never have seen in himself without this book. "
            "The reader's recognition in himself of what the book says is the proof of the book's truth.";

    markov atest(inputstring, 2);

    atest.gen_random_text_by_bin_search(30);
    atest.report_gen_text();
}

TEST_F(StringsFixture, markov_case_hash) {
    char inputstring[]="Every reader, as he reads, is actually the reader of himself. "
            "The writer's work is only a kind of optical instrument he provides the "
            "reader so he can discern what he might never have seen in himself without this book. "
            "The reader's recognition in himself of what the book says is the proof of the book's truth.";

    markov atest(inputstring, 2);

    atest.gen_random_text_by_hash(10);
    atest.report_gen_text();
}

TEST_F(StringsFixture, markovlet_case1) {
    char inputstring[]="of_the_people,_by_the_people,_for_the_people";

    markovlet atest(inputstring, 20, 2);

    atest.gen_random_chars();
    ASSERT_STREQ("of_the_people,_by_the_", atest.get_outputchar());
    ASSERT_EQ(22, strlen(atest.get_outputchar()));
}
