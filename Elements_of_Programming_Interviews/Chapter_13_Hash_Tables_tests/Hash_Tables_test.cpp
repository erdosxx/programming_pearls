#include <gtest/gtest.h>
#include <random>
#include <limits>
#include <unordered_set>
#include <cmath>
#include "hash_tables_boot_camp.h"
#include "Hash_dictionary.h"
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

TEST_F(Ch13Hash_Tables_Fixture, hash_tables_boot_camp) {

}

TEST_F(Ch13Hash_Tables_Fixture, stringHash_Function) {
    default_random_engine gen((random_device()) ());
    string str;
    uniform_int_distribution<int> dis(1, 20);
    str = str_hash::RandString(dis(gen));
    cout << "string = " << str << endl;
    cout << str_hash::StringHash(str, 1 << (16)) << endl;
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
