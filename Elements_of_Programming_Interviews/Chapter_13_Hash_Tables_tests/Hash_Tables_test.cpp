#include <gtest/gtest.h>
#include <random>
#include <limits>
#include <unordered_set>
#include <cmath>
#include "hash_tables_boot_camp.h"
#include "Hash_dictionary.h"
#include "Anagrams.h"
#include "anagrams_needle_haystack.h"
#include "merge_contacts.h"
#include "Can_string_be_palindrome_hash.h"
#include "Can_string_be_palindrome_sorting.h"
#include "Anonymous_letter.h"
#include "LRUCache.h"
#include "Lowest_common_ancestor_hash.h"
#include "Nearest_repetition.h"
#include "Smallest_subarray_covering_set.h"
#include "Smallest_subarray_covering_set_stream.h"
#include "Subseq_cover.h"
#include "longest-subarray-with-distinct-entries.h"
#include "longest-contained-range.h"
#include "average-top-3-scores.h"
#include "substring-with-concatenation-of-all-words.h"
#include "Collatz_conjecture.h"

using std::istringstream;
using std::stringstream;
using std::default_random_engine;
using std::random_device;
using std::unique_ptr;
using std::numeric_limits;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::is_sorted;
using std::unordered_set;
using std::max;
using std::cout;
using std::endl;
using btree_with_parent::BinaryTreeNode;
using std::ostream_iterator;
using near::FindNearestRepetition;
using distinct::LongestSubarrayWithDistinctEntries;

class Ch13Hash_Tables_Fixture : public ::testing::Test {
private:

protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    void SimpleTestCase(const vector<string>& A, const vector<string>& dict, int start, int finish);
    string RandString(int len);
    int CheckAns(const vector<string>& A, const vector<string>& Q);

public:
    Ch13Hash_Tables_Fixture() : Test() {

    }

    virtual ~Ch13Hash_Tables_Fixture() {
    }
};

string Ch13Hash_Tables_Fixture::RandString(int len) {
    string ret;
    default_random_engine gen((random_device())());
    while (len--) {
        uniform_int_distribution<int> dis('a', 'z');
        ret += dis(gen);
    }
    return ret;
}

// O(n^2) solution
int Ch13Hash_Tables_Fixture::CheckAns(const vector<string>& A, const vector<string>& Q) {
    unordered_set<string> dict;
    for (const string& s : Q) {
        dict.emplace(s);
    }

    Subarray ans = Subarray{0, static_cast<int>(A.size() - 1)};
    for (int l = 0; l < A.size(); ++l) {
        unordered_map<string, int> count;
        for (int r = l; r < A.size() && r - l < ans.end - ans.start; ++r) {
            if (dict.find(A[r]) != dict.end()) {
                ++count[A[r]];
            }
            if (count.size() == Q.size()) {
                if (r - l < ans.end - ans.start) {
                    ans = {l, r};
                }
                break;
            }
        }
        count.clear();
    }
    return ans.end - ans.start;
}

void Ch13Hash_Tables_Fixture::SimpleTestCase(const vector<string>& A, const vector<string>& dict,
                    int start, int finish) {
    unordered_set<string> keywords = {dict.begin(), dict.end()};
    //auto res = FindSmallestSubarrayCoveringSet(A, {dict.begin(), dict.end()});
    auto res = FindSmallestSubarrayCoveringSet(A, keywords);
    // cout << "res = " << res.start << " " << res.end << endl;
    ASSERT_TRUE(res.start == start && res.end == finish);
    string s;
    for (int i = 0; i < A.size(); ++i) {
        s += A[i];
        s += ' ';
    }
    istringstream sin(s);
    Subarray res2(FindSmallestSubarrayCoveringSubset(&sin, dict));
    // cout << "res2 = " << res2.start << " " << res2.end << endl;
    ASSERT_TRUE(res2.start == start && res2.end == finish);
}

TEST_F(Ch13Hash_Tables_Fixture, anagram_needle_haystack) {
    string a = "abcde";
    string b = a.substr(0,3);
    ASSERT_EQ("abc", b);
    b = a.substr(2, 2);
    ASSERT_EQ("cd", b);

    ASSERT_FALSE(anagram_compare("abc", "abcd"));
    ASSERT_TRUE(anagram_compare("abc", "acb"));

    ASSERT_EQ("abcde", sort_string("bcdae"));

    ASSERT_EQ("abcde", insertion_sort_string("bcdae"));

    vector<int> result = getAnagramIndices("abdcghbaabcdij", "bcda");
    ASSERT_EQ(2, result.size());
    /*
    for (int i =0 ; i < result.size(); ++i) {
        cout << result[i] << endl;
    }
     */
    vector<int> ans = {0, 8};
    ASSERT_TRUE(equal(result.cbegin(), result.cend(), ans.cbegin(), ans.cend()));

    result = getAnagramIndices("bbbababaaabbab", "ab");
    ans = {2, 3, 4, 5, 6, 9, 11, 12};
    ASSERT_TRUE(equal(result.cbegin(), result.cend(), ans.cbegin(), ans.cend()));

    ASSERT_EQ(string_hash("abcd"), string_hash("dcba"));
    ASSERT_EQ(string_hash("abcd"), string_hash("badc"));
    ASSERT_NE(string_hash("abcd"), string_hash("dcbb"));
    ASSERT_NE(string_hash("defg"), string_hash("cefh"));

    // haystack.size() < needle.size()
    result = getAnagramIndices("bbb", "bbbbb");
    ans = {};
    ASSERT_TRUE(equal(result.cbegin(), result.cend(), ans.cbegin(), ans.cend()));

    size_t str_hash_val = string_hash("abcd");
    size_t str_hash_val_next = string_hash("bcde");
    // size_t rolling_hash(const char& new_char, const char& prev_char, const size_t& prev_hash) {
    size_t hash_val_new = rolling_hash('e', 'a', str_hash_val);
    ASSERT_EQ(str_hash_val_next, hash_val_new);

    result = getAnagramIndices2("abbababaaabbab", "ab");
    ans = {0, 2, 3, 4, 5, 6, 9, 11, 12};
    ASSERT_TRUE(equal(result.cbegin(), result.cend(), ans.cbegin(), ans.cend()));
}

TEST_F(Ch13Hash_Tables_Fixture, hash_tables_boot_camp) {
    ASSERT_EQ(97, hash<char>{}('a'));
    ASSERT_EQ(97, hash<char>()('a'));
    ASSERT_EQ(98, hash<char>{}('b'));
    ASSERT_EQ(98, hash<char>()('b'));

    // =<<
    size_t a = 1;
    a <<= 1;
    ASSERT_EQ(2, a);
    a = 1;
    a <<= 2;
    ASSERT_EQ(4, a);

    ASSERT_EQ(2603192927274642682, hash<string>()("a"));
    ASSERT_EQ(4947675599669400333, hash<string>()("b"));

    m = {{"andy", 7}, {"al", 9}, {"bill", -3}, {"barbara", 12}};
    m1 = {{"andy", 7}, {"al", 9}, {"bill", -3}, {"barbara", 12}};

    ASSERT_EQ(4, m.size());
    ASSERT_EQ(4, m1.size());
    /*
    for (const Record & rec : m) {
        cout << "{" << rec.name << "," <<  rec.val << "}" << endl;
    }
    */
    m2 = {{"andy", 7}, {"al", 9}, {"bill", -3}, {"barbara", 12}};
    /*
    for (const Record & rec : m2) {
        cout << "{" << rec.name << "," <<  rec.val << "}" << endl;
    }
     */
    ASSERT_EQ(4, m2.size());

    Record rec = {"erdos", 1};
    Record rec1 = {"ErdoS", 1};
    ASSERT_EQ(Nocase_hash()(rec), Nocase_hash()(rec1));
    ASSERT_TRUE(Nocase_equal()(rec, rec1));

    m3 = {{"andy", 7}, {"al", 9}, {"bill", -3}, {"barbara", 12}};
    ASSERT_EQ(4, m3.size());

    m4 = {{"andy", 7}, {"al", 9}, {"bill", -3}, {"barbara", 12}};
    ASSERT_EQ(4, m4.size());

    m4.insert({"erdos", 10});
    ASSERT_EQ(10, m4.find({"erdos", 10})->val);
    ASSERT_EQ("erdos", m4.find({"erdos", 10})->name);
    m4.erase({"erdos", 10});
    ASSERT_EQ(m4.end(), m4.find({"erdos", 10}));

    unordered_set<string> un_set = {"a", "b", "c", "d"};
    ASSERT_EQ("b", *un_set.find("b"));
    un_set.insert("e");
    ASSERT_EQ("e", *un_set.find("e"));
    un_set.emplace("f");
    ASSERT_EQ("f", *un_set.find("f"));

    unordered_map<string, int> un_map = {{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}};
    // count : 1 if an element with a key equivalent to k is found, or zero otherwise.
    ASSERT_EQ(1, un_map.count("c"));
    ASSERT_EQ(0, un_map.count("e"));
    ASSERT_EQ(4, un_map.size());
    un_map.insert({"e", 5});
    ASSERT_EQ(5, un_map.size());
    ASSERT_EQ(1, un_map.find("a")->second);
    ASSERT_EQ("a", un_map.find("a")->first);
    un_map.emplace("f", 6);
    ASSERT_EQ(6, un_map.size());
    ASSERT_EQ(6, un_map.find("f")->second);
    ASSERT_EQ("f", un_map.find("f")->first);

    un_map.erase("f");
    ASSERT_EQ(5, un_map.size());
    ASSERT_EQ(un_map.end(), un_map.find("f"));
}

TEST_F(Ch13Hash_Tables_Fixture, stringHash_Function) {
    default_random_engine gen((random_device()) ());
    string str;

    uniform_int_distribution<int> dis(1, 20);
    str = str_hash::RandString(dis(gen));

    cout << "string = " << str << endl;
    cout << str_hash::StringHash(str, 1 << (16)) << endl;
}

TEST_F(Ch13Hash_Tables_Fixture, anagrams) {
    vector<string> D = {"debit card",
                        "bad credit",
                        "the morse code",
                        "here come dots",
                        "the eyes",
                        "they see",
                        "THL"};
    auto result = FindAnagrams(D);
    // 3 nontrivial groups:
    // {"debit card", "bad credit"},
    // {"the morse code", "here come dots"}
    // {"the eyes",   "they see"
    // Since the string "THL" has no anagrams in D, the result
    // contains 3 entries
    ASSERT_EQ(3, result.size());

    default_random_engine gen((random_device())());

    uniform_int_distribution<int> n_dis(0, 99999);
    int n = n_dis(gen);

    // for making unique words in dictionary
    // we use unordered_set first.
    unordered_set<string> table;

    for (int i = 0; i < n; ++i) {
        uniform_int_distribution<int> dis(1, 12);
        table.emplace(RandString(dis(gen)));
    }

    vector<string> dictionary;
    for (const string& s : table) {
        dictionary.emplace_back(s);
    }

    FindAnagrams(dictionary);
}

TEST_F(Ch13Hash_Tables_Fixture, merge_contacts) {
    vector<ContactList> contacts = {
            {{"a", "b", "c"}},
            {{"a", "c", "b"}},
            {{"b", "c", "d"}}};
    auto result = MergeContactLists(contacts);
    ASSERT_EQ(2, result.size());
}

TEST_F(Ch13Hash_Tables_Fixture, palindrome_Function) {
    default_random_engine gen((random_device())());
    for (int times = 0; times < 1000; ++times) {
        string s;
        uniform_int_distribution<int> dis(1, 10);
        s = CanStringBeAPalindromeHash::RandString(dis(gen));
        // cout << s << endl;
        ASSERT_EQ(CanStringBeAPalindromeHash::CanFormPalindrome(s),
               CanStringBeAPalindromeSorting::CanFormPalindrome(s));
    }
}

TEST_F(Ch13Hash_Tables_Fixture, anonymous_letter_Function) {
    ASSERT_FALSE(IsLetterConstructibleFromMagazine("123", "456"));
    ASSERT_FALSE(IsLetterConstructibleFromMagazine("123", "12222222"));
    ASSERT_TRUE(IsLetterConstructibleFromMagazine("123", "1123"));
    ASSERT_TRUE(IsLetterConstructibleFromMagazine("123", "123"));
    ASSERT_FALSE(IsLetterConstructibleFromMagazine("12323", "123"));
    ASSERT_TRUE(
            IsLetterConstructibleFromMagazine("GATTACA", "A AD FS GA T ACA TTT"));
    ASSERT_FALSE(IsLetterConstructibleFromMagazine("a", ""));
    ASSERT_TRUE(IsLetterConstructibleFromMagazine("aa", "aa"));
    ASSERT_TRUE(IsLetterConstructibleFromMagazine("aa", "aaa"));
    ASSERT_TRUE(IsLetterConstructibleFromMagazine("", "123"));
    ASSERT_TRUE(IsLetterConstructibleFromMagazine("", ""));
}

TEST_F(Ch13Hash_Tables_Fixture, LRU_Cache_Function) {
    const int kCapacity = 2;
    {
        LRUCache<kCapacity> c;
        //cout << "c.Insert(1, 1)" << endl;
        c.Insert(1, 1);
        //cout << "c.Insert(1, 10)" << endl;
        c.Insert(1, 10);
        int val;
        //cout << "c.Lookup(2, val)" << endl;
        ASSERT_FALSE(c.Lookup(2, &val));
        //cout << "c.Lookup(1, val)" << endl;
        ASSERT_TRUE(c.Lookup(1, &val));
        ASSERT_EQ(val, 1);
        c.Erase(1);
        ASSERT_FALSE(c.Lookup(1, &val));
    }

    // test capacity constraints honored, also FIFO ordering
    {
        LRUCache<kCapacity> c;
        c.Insert(1, 1);
        c.Insert(2, 1);
        c.Insert(3, 1);
        c.Insert(4, 1);
        int val;
        ASSERT_FALSE(c.Lookup(1, &val));
        ASSERT_FALSE(c.Lookup(2, &val));
        ASSERT_TRUE(c.Lookup(3, &val));
        ASSERT_EQ(val, 1);
        ASSERT_TRUE(c.Lookup(4, &val));
        ASSERT_EQ(val, 1);
    }

    // test retrieval moves to front
    {
        LRUCache<kCapacity> c;
        c.Insert(1, 1);
        c.Insert(2, 1);
        c.Insert(3, 1);
        int val;
        c.Lookup(2, &val);
        c.Insert(4, 1);
        ASSERT_FALSE(c.Lookup(1, &val));
        ASSERT_TRUE(c.Lookup(2, &val));
        ASSERT_EQ(val, 1);
        ASSERT_FALSE(c.Lookup(3, &val));
        ASSERT_TRUE(c.Lookup(4, &val));
        ASSERT_EQ(val, 1);
    }

    // test update moves to front
    {
        LRUCache<kCapacity> c;
        c.Insert(1, 1);
        c.Insert(2, 1);
        c.Insert(3, 1);
        c.Insert(2, 2);
        c.Insert(4, 1);
        int val;
        ASSERT_FALSE(c.Lookup(1, &val));
        ASSERT_TRUE(c.Lookup(2, &val));
        ASSERT_EQ(val, 1);
        ASSERT_FALSE(c.Lookup(3, &val));
        ASSERT_TRUE(c.Lookup(4, &val));
        ASSERT_EQ(val, 1);
    }

    // test remove
    {
        LRUCache<kCapacity> c;
        c.Insert(1, 1);
        c.Insert(2, 1);
        c.Erase(2);
        c.Insert(3, 3);
        int val;
        ASSERT_TRUE(c.Lookup(1, &val));
        ASSERT_EQ(val, 1);
        ASSERT_FALSE(c.Lookup(2, &val));
        ASSERT_TRUE(c.Lookup(3, &val));
        ASSERT_EQ(val, 3);
    }
}

TEST_F(Ch13Hash_Tables_Fixture, LCA_Hash_Function) {
    //      3
    //    2   5
    //  1    4 6
    unique_ptr<BinaryTreeNode<int>> root = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{3, nullptr, nullptr});
    root->parent = nullptr;
    root->left = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{2, nullptr, nullptr});
    root->left->parent = root.get();
    root->left->left = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{1, nullptr, nullptr});
    root->left->left->parent = root->left.get();
    root->right = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{5, nullptr, nullptr});
    root->right->parent = root.get();
    root->right->left = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{4, nullptr, nullptr});
    root->right->left->parent = root->right.get();
    root->right->right = make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{6, nullptr, nullptr});
    root->right->right->parent = root->right.get();

    // should output 3
    ASSERT_EQ(LCA(root->left, root->right)->data, 3);
    //cout << (LCA(root->left, root->right))->data << endl;
    // should output 5
    ASSERT_EQ(LCA(root->right->left, root->right->right)->data, 5);
    //cout << (LCA(root->right->left, root->right->right)->data) << endl;
}

TEST_F(Ch13Hash_Tables_Fixture, nearest_repetition_Function) {
    vector<string> A = {"foo",    "bar",    "widget", "foo",
                        "widget", "widget", "adnan"};
    ASSERT_EQ(near::CheckAnswer(A), FindNearestRepetition(A));
    A = {"foo", "bar", "widget", "foo", "xyz", "widget", "bar", "adnan"};
    ASSERT_EQ(near::CheckAnswer(A), FindNearestRepetition(A));
    A = {"foo", "bar", "widget", "adnan"};
    ASSERT_EQ(near::CheckAnswer(A), FindNearestRepetition(A));
    A = {};
    ASSERT_EQ(near::CheckAnswer(A), FindNearestRepetition(A));
    A = {"foo", "foo", "foo"};
    ASSERT_EQ(near::CheckAnswer(A), FindNearestRepetition(A));
    default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<int> dis(1, 100);
        int n = dis(gen);

        vector<string> s;
        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(1, 10);
            s.emplace_back(near::RandString(dis(gen)));
        }
        ASSERT_EQ(near::CheckAnswer(s), FindNearestRepetition(s));
    }
}

TEST_F(Ch13Hash_Tables_Fixture, smallest_subarray_covering_Function) {
    vector<string> A = {"a", "b", "c", "b", "a", "d", "c",
                        "a", "e", "a", "a", "b", "e"};
    vector<string> dict = {"b", "c", "e"};
    SimpleTestCase(A, dict, 3, 8);
    dict = {"a", "c"};
    SimpleTestCase(A, dict, 6, 7);
    A = {"a", "b"};
    dict = {"a", "b"};
    SimpleTestCase(A, dict, 0, 1);
    A = {"a", "b"};
    dict = {"b", "a"};
    SimpleTestCase(A, dict, 0, 1);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        vector<string> A;
        uniform_int_distribution<int> dis(1, 100);
        int n = dis(gen);

        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(1, 10);
            A.emplace_back(RandString(dis(gen)));
        }
        /*
        for (int i = 0; i < A.size(); ++i) {
          cout << A[i] << ' ';
        }
        cout << endl;
        */
        unordered_set<string> dict;
        string s;
        for (int i = 0; i < A.size(); ++i) {
            dict.emplace(A[i]);
            s += A[i];
            s += ' ';
        }
        uniform_int_distribution<int> dis1(1, dict.size());
        int m = dis1(gen);
        vector<string> Q;
        for (auto it = dict.cbegin(); it != dict.cend(); ++it) {
            Q.emplace_back(*it);
            if (--m == 0) {
                break;
            }
        }

        /*
        for (int i = 0; i < Q.size(); ++i) {
          cout << Q[i] << ' ';
        }
        cout << endl;
        */
        unordered_set<string> input(Q.cbegin(), Q.cend());
        Subarray res(FindSmallestSubarrayCoveringSet(A, input));
        // cout << res.start << ", " << res.end << endl;
        dict.clear();
        for (int i = 0; i < Q.size(); ++i) {
            dict.emplace(Q[i]);
        }
        for (int i = res.start; i <= res.end; ++i) {
            if (dict.find(A[i]) != dict.end()) {
                dict.erase(A[i]);
            }
        }
        ASSERT_TRUE(dict.empty() == true);
        istringstream sin(s);
        Subarray res2(FindSmallestSubarrayCoveringSubset(&sin, Q));
        // cout << res2.start << ", " << res2.end << endl;
        dict.clear();
        for (int i = 0; i < Q.size(); ++i) {
            dict.emplace(Q[i]);
        }
        for (int i = res.start; i <= res.end; ++i) {
            if (dict.find(A[i]) != dict.end()) {
                dict.erase(A[i]);
            }
        }
        ASSERT_TRUE(dict.empty() == true);
        ASSERT_EQ(res.end - res.start, res2.end - res2.start);
        ASSERT_EQ(res.end - res.start, CheckAns(A, Q));
    }
}

TEST_F(Ch13Hash_Tables_Fixture, subseq_cover_Function) {
    vector<string> A3 = {"0", "1", "2", "3",  "4",  "5",  "6", "7", "8", "9",
                         "2", "4", "6", "10", "10", "10", "3", "2", "1", "0"};
    vector<string> subseq4 = {"0", "2", "9", "4", "6"};
    Subarray rr = FindSmallestSequentiallyCoveringSubset(A3, subseq4);
    ASSERT_TRUE(rr.start == 0 && rr.end == 12);

    default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        vector<string> A;
        uniform_int_distribution<int> dis(1, 10000);
        int n = dis(gen);

        uniform_int_distribution<int> dis1(1, 5);
        generate_n(back_inserter(A), n, [&] { return RandString(dis1(gen)); });
        unordered_set<string> dict;
        copy(A.begin(), A.end(), inserter(dict, dict.end()));
        // cout << "A = ";
        // copy(A.begin(), A.end(), ostream_iterator<string>(cout, ","));
        // cout << endl;
        uniform_int_distribution<int> m_dis(
                1, min(static_cast<int>(dict.size()), 10));
        int m = m_dis(gen);
        vector<string> Q;
        auto it = dict.begin();
        generate_n(back_inserter(Q), m, [&] { return *it++; });
        // cout << "Q = ";
        // copy(Q.begin(), Q.end(), ostream_iterator<string>(cout, ","));
        // cout << endl;

        Subarray res(FindSmallestSequentiallyCoveringSubset(A, Q));
        // cout << res.start << ", " << res.end << endl;
        if (res.start != -1 && res.end != Q.size()) {
            if (res.start != res.end) {
                // cout << res.start << ", " << res.end << endl;
            }
            dict.clear();
            copy(Q.begin(), Q.end(), inserter(dict, dict.end()));
            for (int i = res.start; i <= res.end; ++i) {
                if (dict.find(A[i]) != dict.end()) {
                    dict.erase(A[i]);
                }
            }
            ASSERT_TRUE(dict.empty());
        }
    }
}

TEST_F(Ch13Hash_Tables_Fixture, longest_distinct_subarray_Function) {
    ASSERT_EQ(1, LongestSubarrayWithDistinctEntries({1, 1, 1}));
    ASSERT_EQ(2, LongestSubarrayWithDistinctEntries({1, 2, 1}));
    ASSERT_EQ(3, LongestSubarrayWithDistinctEntries({1, 2, 1, 3, 1, 2, 1}));
    ASSERT_EQ(2,
           LongestSubarrayWithDistinctEntries({1, 2, 2, 3, 3, 1, 1, 2, 1}));

    default_random_engine gen((random_device())());
    uniform_int_distribution<size_t> dis(0, 1000);
    int n = dis(gen);
    // cout << "n = " << n << endl;
    for (int times = 0; times < 100; ++times) {
        vector<int> A;
        generate_n(back_inserter(A), n, [&] { return dis(gen); });
        /*
        for (int a : A) {
          cout << a << " ";
        }
        cout << endl;
        */
        int ans = LongestSubarrayWithDistinctEntries(A);
        int golden_ans = distinct::CheckAns(A);
        // cout << ans << " " << golden_ans << endl;
        ASSERT_EQ(ans, golden_ans);
    }
}

TEST_F(Ch13Hash_Tables_Fixture, longest_contained_range_Function) {
    default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<size_t> dis(0, 1000);
        size_t n = dis(gen);
        vector<int> A;
        uniform_int_distribution<int> dis_n(0, static_cast<int>(n));
        for (size_t i = 0; i < n; ++i) {
            A.emplace_back(dis_n(gen));
        }
        /*
        for (size_t i = 0; i < n; ++i) {
          cout << A[i] << " ";
        }
        cout << endl;
        //*/
        ASSERT_EQ(p_13_10::FindLongestContainedRange(A), p_13_10::CheckAns(A));
        ASSERT_EQ(p_13_10::LongestContainedRange(A), p_13_10::CheckAns(A));
    }
}

TEST_F(Ch13Hash_Tables_Fixture, average_top_3_Function) {
    ofstream ofs("scores.txt");
    ofs << "adnan 100";
    ofs << "amit 99";
    ofs << "adnan 98";
    ofs << "thl 90";
    ofs << "adnan 10";
    ofs << "amit 100";
    ofs << "thl 99";
    ofs << "thl 95";
    ofs << "adnan 95";
    ofs.close();

    ifstream ifs("scores.txt");
    string result = p_13_11::FindStudentWithHighestBestOfThreeScores(&ifs);
    // cout << "result = " << result << endl;
    ASSERT_EQ(result, "adnan");

    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 10000);
    int n = dis(gen);
    ofstream ofs1("/tmp/scores.txt");

    for (int i = 0; i < n; ++i) {
        uniform_int_distribution<int> test_num_dis(0, 20);
        int test_num = test_num_dis(gen);

        uniform_int_distribution<int> len_dis(5, 10);
        string name = p_13_11::RandString(len_dis(gen));

        while (test_num--) {
            uniform_int_distribution<int> score_dis(0, 100);
            ofs1 << name << " " << score_dis(gen) << endl;
        }
    }
    ofs1.close();

    ifstream ifs1("/tmp/scores.txt");
    string name = p_13_11::FindStudentWithHighestBestOfThreeScores(&ifs1);
    cout << "top student is " << name << endl;
    // Remove file after the execution.
    // remove("score.txt");
}

TEST_F(Ch13Hash_Tables_Fixture, concat_substring_Function) {
    string s = "barfoothefoobarman";
    auto result = FindAllSubstrings(s, {"foo", "bar"});
    ASSERT_TRUE(result.size() == 2 && result[0] == 0 && result[1] == 9);
    s = "dcacdabcd";
    result = FindAllSubstrings(s, {"cd", "ab"});
    ASSERT_TRUE(result.size() == 2 && result[0] == 3 && result[1] == 5);
}

TEST_F(Ch13Hash_Tables_Fixture, Collatz_conjecture_Function) {
    default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<int> dis(1, 10000);
        int n = dis(gen);
        //cout << "n = " << n << endl;
        bool res;
        // cout << boolalpha << (res = TestCollatzConjecture(n)) << endl;
        res = p_13_13::TestCollatzConjecture(n);
        ASSERT_EQ(res, p_13_13::Check(n));
    }
}
