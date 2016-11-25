#include <gtest/gtest.h>
#include <random>
#include <memory>
#include <algorithm>
#include <limits>
#include <unordered_set>
#include <cmath>
#include <string>
#include "binary_search_trees_boot_camp.h"
#include "is_binary_tree_a_BST.h"
#include "is_binary_tree_a_BST_BFS.h"
#include "is_binary_tree_a_BST_inorder.h"
#include "Search_BST_first_larger_k.h"
#include "Find_k_largest_BST.h"
#include "BST_lowest_common_ancestor.h"
#include "Rebuild_BST_preorder.h"
#include "Rebuild_BST_preorder_better.h"
#include "Rebuild_BST_postorder.h"
#include "Rebuild_BST_postorder_better.h"
#include "Minimum_distance_3_sorted_arrays.h"
#include "Generating_a_b_sqrt2.h"
#include "generating-a-b-sqrt2-improved.h"
#include "Build_BST_from_sorted_array.h"
#include "insertion-deletion-BST.h"
#include "Descendant_and_ancestor.h"
#include "range-lookup-BST.h"
#include "AddingCredits.h"

using std::istringstream;
using std::stringstream;
using std::default_random_engine;
using std::random_device;
using std::unique_ptr;
using std::shared_ptr;
using std::make_shared;
using std::numeric_limits;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::is_sorted;
using std::unordered_set;
using std::max;
using std::cout;
using std::endl;
using std::ostream_iterator;
using std::to_string;
using std::upper_bound;
using std::lower_bound;

class Ch15_BST_Fixture : public ::testing::Test {
private:

protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    void p_15_5_CheckAns(const unique_ptr<BSTNode<int>>& n, const int& pre);
    void TraversalCheck(const unique_ptr<BSTNode<int>>& tree, int* target);

public:
    Ch15_BST_Fixture() : Test() {

    }

    virtual ~Ch15_BST_Fixture() {
    }
};

void Ch15_BST_Fixture::p_15_5_CheckAns(const unique_ptr<BSTNode<int>>& n, const int& pre) {
    if (n) {
        p_15_5_CheckAns(n->left, pre);
        ASSERT_LE(pre, n->data);
        // cout << n->data << endl;
        p_15_5_CheckAns(n->right, n->data);
    }
}

void Ch15_BST_Fixture::TraversalCheck(const unique_ptr<BSTNode<int>>& tree, int* target) {
    if (tree) {
        TraversalCheck(tree->left, target);
        ASSERT_EQ(*target, tree->data);
        ++*target;
        TraversalCheck(tree->right, target);
    }
}

TEST_F(Ch15_BST_Fixture, binary_search_tree_boot_camp) {
    //      3
    //    2   5
    //  1    4 6
    auto tree = make_unique<BSTNode<int>>(BSTNode<int>{3});
    tree->left = make_unique<BSTNode<int>>(BSTNode<int>{2});
    tree->left->left = make_unique<BSTNode<int>>(BSTNode<int>{1});
    tree->right = make_unique<BSTNode<int>>(BSTNode<int>{5});
    tree->right->left =
            make_unique<BSTNode<int>>(BSTNode<int>{4});
    tree->right->right =
            make_unique<BSTNode<int>>(BSTNode<int>{6});

    BSTNode<int>* result = SearchBST(tree, 4);
    ASSERT_EQ(4, result->data);

    result = SearchBST(tree, 1);
    ASSERT_EQ(1, result->data);

    result = SearchBST(tree, 7);
    ASSERT_EQ(nullptr, result);

    vector<student> students = {{"a", 10}, {"b", 20}, {"c", 15}, {"d", 5}};
    set<student*, Comp_by_score> school_score;

    school_score.emplace(&students[0]);
    school_score.emplace(&students[1]);
    school_score.emplace(&students[2]);
    school_score.emplace(&students[3]);

    ASSERT_EQ((*school_score.cbegin())->name, "d");
    ASSERT_EQ((*school_score.cbegin())->score, 5);

    set<student*, Comp_by_name> school_name;
    school_name.emplace(&students[0]);
    school_name.emplace(&students[1]);
    school_name.emplace(&students[2]);
    school_name.emplace(&students[3]);

    ASSERT_EQ((*school_name.cbegin())->name, "a");
    ASSERT_EQ((*school_name.cbegin())->score, 10);

    bool (*compare_function_ptr)(const student* a_ptr, const student* b_ptr) = compare_by_score;

    set<student*, bool(*)(const student*, const student*)> school_score2(compare_function_ptr);
    school_score2.emplace(&students[0]);
    school_score2.emplace(&students[1]);
    school_score2.emplace(&students[2]);
    school_score2.emplace(&students[3]);

    ASSERT_EQ((*school_score2.cbegin())->name, "d");
    ASSERT_EQ((*school_score2.cbegin())->score, 5);

    // decltype(compare_function_ptr) : retunr type of function pointer.
    set<student*, decltype(compare_function_ptr)> school_score2_2(compare_function_ptr);
    school_score2_2.emplace(&students[0]);
    school_score2_2.emplace(&students[1]);
    school_score2_2.emplace(&students[2]);
    school_score2_2.emplace(&students[3]);

    ASSERT_EQ((*school_score2_2.cbegin())->name, "d");
    ASSERT_EQ((*school_score2_2.cbegin())->score, 5);

    students = {{"a", 10}, {"b", 20}, {"c", 15}, {"d", 5}};
    // &compare_by_name : address of the function
    // In this case, the parameter of decltype should be function pointer.
    set<student*, decltype(&compare_by_name)> school_name_2(&compare_by_name);
    school_name_2.emplace(&students[0]);
    school_name_2.emplace(&students[1]);
    school_name_2.emplace(&students[2]);
    school_name_2.emplace(&students[3]);

    ASSERT_EQ((*school_name_2.cbegin())->name, "a");
    ASSERT_EQ((*school_name_2.cbegin())->score, 10);

    set<student*, function<bool(const student*, const student*)>> school_score3(comp_score);
    school_score3.emplace(&students[0]);
    school_score3.emplace(&students[1]);
    school_score3.emplace(&students[2]);
    school_score3.emplace(&students[3]);

    ASSERT_EQ((*school_score3.cbegin())->name, "d");
    ASSERT_EQ((*school_score3.cbegin())->score, 5);
}

TEST_F(Ch15_BST_Fixture, stl_library) {
    ///// set
    set<int> bst = {5,2,3,1,4};
    ASSERT_EQ(1, *bst.begin());
    ASSERT_EQ(1, *bst.cbegin());
    ASSERT_EQ(5, *bst.rbegin());
    ASSERT_EQ(5, *bst.crbegin());

    // Because elements in a set are unique, the insertion operation
    // checks whether each inserted element is equivalent to an element
    // already in the container, and if so, the element is not inserted,
    // returning an iterator to this existing element (if the function
    // returns a value).
    bst.emplace(3);  // for set, insert existing element.
    ASSERT_EQ(5, bst.size()); // same as before.
    bst.insert(6);
    ASSERT_EQ(6, bst.size());
    ASSERT_EQ(1, bst.erase(6)); // erase return the number of erase elements.
    ASSERT_EQ(5, bst.size());
    ASSERT_EQ(0, bst.erase(7));

    bst = {10,10,10,20,20,20,30,30};
    //              ^        ^
    // method or function lower_bound/upper_bound are equivalent
    set<int>::iterator low = lower_bound(bst.cbegin(), bst.cend(), 20);
    set<int>::iterator low1 = bst.lower_bound(20);

    set<int>::iterator up = upper_bound(bst.cbegin(), bst.cend(), 20);
    set<int>::iterator up1 = bst.upper_bound(20);

    ASSERT_EQ(20, *low);
    ASSERT_EQ(30, *up);

    // See: http://stackoverflow.com/questions/13505562/getting-index-of-set-element-via-iterator
    // does not work:   ASSERT_EQ(3, low - bst.cbegin());
    auto distance = std::distance(bst.cbegin(), low);
    auto it = bst.cbegin();
    std::advance(it, distance);
    ASSERT_EQ(it, low);

    distance = std::distance(bst.cbegin(), up);
    it = bst.cbegin();
    std::advance(it, distance);
    ASSERT_EQ(it, up);

    std::pair<std::set<int>::const_iterator,std::set<int>::const_iterator> ret;
    std::pair<std::set<int>::const_iterator,std::set<int>::const_iterator> ret1;
    ret = bst.equal_range(20);
    ret1 = std::equal_range(bst.cbegin(), bst.cend(), 20);
    ASSERT_EQ(*ret.first, 20);
    ASSERT_EQ(*ret1.first, 20);
    ASSERT_EQ(*ret.second, 30);  // 30 which is next to last 20.
    ASSERT_EQ(*ret1.second, 30);

    distance = std::distance(bst.cbegin(), ret.first);
    it = bst.cbegin();
    std::advance(it, distance);
    ASSERT_EQ(it, ret.first);  // index: 3 of first 20

    distance = std::distance(bst.cbegin(), ret.second);
    it = bst.cbegin();
    std::advance(it, distance);
    ASSERT_EQ(it, ret.second);  // index: 6 of first 30.

    ///// map
    map<char, int> mymap = {{'a', 1}, {'b', 2}, {'c', 3}};
    ASSERT_EQ(1, mymap['a']);
    ASSERT_EQ(3, mymap['c']);

    // count : 1 if exist , 0 not.
    ASSERT_EQ(1, mymap.count('a'));
    ASSERT_EQ(0, mymap.count('d'));

    // find : return iterator
    ASSERT_EQ(1, mymap.find('a')->second);
    ASSERT_EQ(mymap.end(), mymap.find('d'));

    mymap.insert(pair<char,int>{'d',4});
    mymap.insert({'e',5});
    mymap.emplace('f',6);
    ASSERT_EQ(4, mymap['d']);
    ASSERT_EQ(5, mymap['e']);

    mymap.erase('f');
    ASSERT_EQ(mymap.size(), 5); // a:1 b:2 c:3 d:4 e:5

    mymap = {{'a', 1}, {'b', 2}, {'c', 3}};
    ASSERT_EQ(mymap.cbegin()->first, 'a');
    ASSERT_EQ(mymap.cbegin()->second, 1);

    ASSERT_EQ(mymap.crbegin()->first, 'c');
    ASSERT_EQ(mymap.crbegin()->second, 3);

    mymap = {{'a', 1}, {'b', 2}, {'c', 3}};
    mymap.insert({'b', 12});  // not insert for already exist key.
    ASSERT_EQ(mymap.size(), 3);
    ASSERT_EQ(2, mymap['b']);

    map<char,int>::iterator iter = mymap.find('b');
    ASSERT_EQ(iter->first, 'b');
    ASSERT_EQ(iter->second, 2);

    mymap = {{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}};
    // does not work: iter = lower_bound(mymap.cbegin(), mymap.cend(), 'b');
    iter = mymap.lower_bound('b');
    ASSERT_EQ(iter->first, 'b');
    ASSERT_EQ(iter->second, 2);

    iter = mymap.upper_bound('b');
    ASSERT_EQ(iter->first, 'c');
    ASSERT_EQ(iter->second, 3);

    std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> ret3;
    ret3 = mymap.equal_range('b');
    ASSERT_EQ(ret3.first->first, 'b');
    ASSERT_EQ(ret3.second->first, 'c');
    ASSERT_EQ(ret3.first->second, 2);
    ASSERT_EQ(ret3.second->second, 3);
}

TEST_F(Ch15_BST_Fixture, is_BST_Function) {
    //      3
    //    2   5
    //  1    4 6
    auto tree = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{3});
    tree->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{2});
    tree->left->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{1});
    tree->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{5});
    tree->right->left =
            make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{4});
    tree->right->right =
            make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{6});
    // should output true.
    ASSERT_EQ(IsBinaryTreeBST(tree), true);
    // cout << boolalpha << IsBinaryTreeBST(tree) << endl;
    //      10
    //    2   5
    //  1    4 6
    tree->data = 10;
    // should output false.
    ASSERT_FALSE(IsBinaryTreeBST(tree));
    // cout << boolalpha << IsBinaryTreeBST(tree) << endl;
    // should output true.
    ASSERT_EQ(IsBinaryTreeBST(nullptr), true);
    // cout << boolalpha << IsBinaryTreeBST(nullptr) << endl;
}

TEST_F(Ch15_BST_Fixture, is_BST_BFS_Function) {
    //      3
    //    2   5
    //  1    4 6
    auto tree = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{3});
    tree->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{2});
    tree->left->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{1});
    tree->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{5});
    tree->right->left =
            make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{4});
    tree->right->right =
            make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{6});
    // should output true
    ASSERT_EQ(bfs::IsBinaryTreeBST(tree), true);
    // cout << boolalpha << IsBinaryTreeBST(tree) << endl;
    //      10
    //    2   5
    //  1    4 6
    tree->data = 10;
    // should output false
    ASSERT_FALSE(bfs::IsBinaryTreeBST(tree));
    // cout << boolalpha << IsBinaryTreeBST(tree) << endl;
    // empty tree, should output true
    ASSERT_EQ(bfs::IsBinaryTreeBST(nullptr), true);
    // cout << boolalpha << IsBinaryTreeBST(nullptr) << endl;
}

TEST_F(Ch15_BST_Fixture, is_BST_inorder_Function) {
    //      3
    //    2   5
    //  1    4 6
    auto tree = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{3});
    tree->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{2});
    tree->left->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{1});
    tree->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{5});
    tree->right->left =
            make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{4});
    tree->right->right =
            make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{6});
    // should output true
    ASSERT_EQ(inorder::IsBinaryTreeBST(tree), true);
    // cout << boolalpha << IsBinaryTreeBST(tree) << endl;
    //      10
    //    2   5
    //  1    4 6
    tree->data = 10;
    // should output false
    ASSERT_FALSE(inorder::IsBinaryTreeBST(tree));
    // cout << boolalpha << IsBinaryTreeBST(tree) << endl;
    // empty tree, should output true
    ASSERT_EQ(inorder::IsBinaryTreeBST(nullptr), true);
    // cout << boolalpha << IsBinaryTreeBST(nullptr) << endl;
}

TEST_F(Ch15_BST_Fixture, Search_BST_first_larger_Function) {
    //    3
    //  2   5
    // 1   4 7
    auto tree = make_unique<BSTNode<int>>(BSTNode<int>{3});
    tree->left = make_unique<BSTNode<int>>(BSTNode<int>{2});
    tree->left->left = make_unique<BSTNode<int>>(BSTNode<int>{1});
    tree->right = make_unique<BSTNode<int>>(BSTNode<int>{5});
    tree->right->left = make_unique<BSTNode<int>>(BSTNode<int>{4});
    tree->right->right = make_unique<BSTNode<int>>(BSTNode<int>{7});

    ASSERT_EQ(FindFirstGreaterThanK(tree, 1), tree->left.get());
    ASSERT_EQ(FindFirstGreaterThanK(tree, 5), tree->right->right.get());
    ASSERT_EQ(FindFirstGreaterThanK(tree, 6), tree->right->right.get());
    ASSERT_EQ(FindFirstGreaterThanK(tree, 7), nullptr);
}

TEST_F(Ch15_BST_Fixture, find_k_largest_Function) {
    //    3
    //  2   5
    // 1   4 6
    unique_ptr<BSTNode<int>> tree = make_unique<BSTNode<int>>(BSTNode<int>{3});
    tree->left = make_unique<BSTNode<int>>(BSTNode<int>{2});
    tree->left->left = make_unique<BSTNode<int>>(BSTNode<int>{1});
    tree->right = make_unique<BSTNode<int>>(BSTNode<int>{5});
    tree->right->left = make_unique<BSTNode<int>>(BSTNode<int>{4});
    tree->right->right = make_unique<BSTNode<int>>(BSTNode<int>{6});
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());

    uniform_int_distribution<int> dis(1, 6);
    int k = dis(gen);

    // cout << "k = " << k << endl;
    vector<int> ans = FindKLargestInBST(tree, k);
    // for (int i = 0; i < ans.size(); ++i) {
    //     cout << ans[i] << endl;
    // }
    for (int i = 1; i < ans.size(); ++i) {
        ASSERT_GE(ans[i - 1], ans[i]);
    }
    ans = FindKLargestInBST(tree, 2);
    ASSERT_EQ(ans[0], 6);
    ASSERT_EQ(ans[1], 5);

    //    3
    //  3   4
    // 1   4 6
    tree = make_unique<BSTNode<int>>(BSTNode<int>{3});
    tree->left = make_unique<BSTNode<int>>(BSTNode<int>{3});
    tree->left->left = make_unique<BSTNode<int>>(BSTNode<int>{1});
    tree->right = make_unique<BSTNode<int>>(BSTNode<int>{4});
    tree->right->left = make_unique<BSTNode<int>>(BSTNode<int>{4});
    tree->right->right = make_unique<BSTNode<int>>(BSTNode<int>{6});
    ans = FindKLargestInBST(tree, 3);
    ASSERT_EQ(ans[0], 6);
    ASSERT_EQ(ans[1], 4);
    ASSERT_EQ(ans[1], 4);
}

TEST_F(Ch15_BST_Fixture, BST_LCA_Function) {
    //      3
    //    2   5
    //  1    4 6
    unique_ptr<BSTNode<int>> tree = make_unique<BSTNode<int>>(BSTNode<int>{3});
    tree->left = make_unique<BSTNode<int>>(BSTNode<int>{2});
    tree->left->left = make_unique<BSTNode<int>>(BSTNode<int>{1});
    tree->right = make_unique<BSTNode<int>>(BSTNode<int>{5});
    tree->right->left = make_unique<BSTNode<int>>(BSTNode<int>{4});
    tree->right->right = make_unique<BSTNode<int>>(BSTNode<int>{6});
    ASSERT_EQ(3, FindLCA(tree, tree->left->left, tree->right->left)->data);
    ASSERT_EQ(5, FindLCA(tree, tree->right->left, tree->right->right)->data);
    ASSERT_EQ(2, FindLCA(tree, tree->left->left, tree->left)->data);
    ASSERT_EQ(3, FindLCA(tree, tree->left->left, tree->right)->data);

    // Example at page 229
    tree = make_unique<BSTNode<int>>(BSTNode<int>{19});
    tree->left = make_unique<BSTNode<int>>(BSTNode<int>{7});
    tree->right = make_unique<BSTNode<int>>(BSTNode<int>{43});
    tree->left->left = make_unique<BSTNode<int>>(BSTNode<int>{3});
    tree->left->right = make_unique<BSTNode<int>>(BSTNode<int>{11});
    tree->left->left->left = make_unique<BSTNode<int>>(BSTNode<int>{2});
    tree->left->left->right = make_unique<BSTNode<int>>(BSTNode<int>{5});
    tree->left->right->right = make_unique<BSTNode<int>>(BSTNode<int>{17});
    tree->left->right->right->left = make_unique<BSTNode<int>>(BSTNode<int>{13});
    tree->right->left = make_unique<BSTNode<int>>(BSTNode<int>{23});
    tree->right->right = make_unique<BSTNode<int>>(BSTNode<int>{47});
    tree->right->left->right = make_unique<BSTNode<int>>(BSTNode<int>{37});
    tree->right->left->right->left = make_unique<BSTNode<int>>(BSTNode<int>{29});
    tree->right->left->right->right = make_unique<BSTNode<int>>(BSTNode<int>{41});
    tree->right->left->right->left->right = make_unique<BSTNode<int>>(BSTNode<int>{31});
    tree->right->right->right = make_unique<BSTNode<int>>(BSTNode<int>{53});
    ASSERT_EQ(37, FindLCA(tree, tree->right->left->right->left , tree->right->left->right->right)->data);
}

TEST_F(Ch15_BST_Fixture, rebuild_BST_preorder_Function) {
    //      3
    //    2   5
    //  1    4  6
    // should output 1, 2, 3, 4, 5, 6
    // preorder [3, 2, 1, 5, 4, 6]
    vector<int> preorder = {3, 2, 1, 5, 4, 6};
    unique_ptr<BSTNode<int>> tree(RebuildBSTFromPreorder(preorder));
    p_15_5_CheckAns(tree, numeric_limits<int>::min());
    ASSERT_EQ(3, tree->data);
    ASSERT_EQ(2, tree->left->data);
    ASSERT_EQ(1, tree->left->left->data);
    ASSERT_EQ(5, tree->right->data);
    ASSERT_EQ(4, tree->right->left->data);
    ASSERT_EQ(6, tree->right->right->data);
}

TEST_F(Ch15_BST_Fixture, rebuild_BST_preorder_better_Function) {
    //      3
    //    2   5
    //  1    4  6
    // should output 1, 2, 3, 4, 5, 6
    // preorder [3, 2, 1, 5, 4, 6]
    vector<int> preorder = {3, 2, 1, 5, 4, 6};
    unique_ptr<BSTNode<int>> tree(improved::RebuildBSTFromPreorder(preorder));
    p_15_5_CheckAns(tree, numeric_limits<int>::min());
    ASSERT_EQ(3, tree->data);
    ASSERT_EQ(2, tree->left->data);
    ASSERT_EQ(1, tree->left->left->data);
    ASSERT_EQ(5, tree->right->data);
    ASSERT_EQ(4, tree->right->left->data);
    ASSERT_EQ(6, tree->right->right->data);
}

TEST_F(Ch15_BST_Fixture, rebuild_BST_postorder) {
    //      3
    //    2   5
    //  1    4  6
    // should output 1, 2, 3, 4, 5, 6
    // preorder [1, 2, 4, 6, 5, 3]
    vector<int> postorder = {1, 2, 4, 6, 5, 3};
    unique_ptr<BSTNode<int>> root(RebuildBSTFromPostorder(postorder));
    p_15_5_CheckAns(root, numeric_limits<int>::min());
}

TEST_F(Ch15_BST_Fixture, rebuild_BST_postorder_better) {
    //      3
    //    2   5
    //  1    4  6
    // should output 1, 2, 3, 4, 5, 6
    // preorder [1, 2, 4, 6, 5, 3]
    vector<int> postorder = {1, 2, 4, 6, 5, 3};
    unique_ptr<BSTNode<int>> root(improved::RebuildBSTFromPostorder(postorder));
    p_15_5_CheckAns(root, numeric_limits<int>::min());
}

TEST_F(Ch15_BST_Fixture, min_distance_3_sorted_Function) {
    random_device rd;
    //default_random_engine gen((random_device())());
    default_random_engine gen(rd());
    for (int times = 0; times < 10; ++times) {
        vector<vector<int>> sorted_arrays;
        uniform_int_distribution<int> dis(1, 5);
        int n = dis(gen);

        sorted_arrays.resize(n);
        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(1, 40);
            int size = dis(gen);

            for (int j = 0; j < size; ++j) {
                uniform_int_distribution<int> dis(0, 9999);
                sorted_arrays[i].emplace_back(dis(gen));
            }
            sort(sorted_arrays[i].begin(), sorted_arrays[i].end());
        }
        int ans = FindClosestElementsInSortedArrays(sorted_arrays);
        // cout << ans << endl;
        ASSERT_EQ(BruteForceGenAnswer(sorted_arrays), ans);
    }

}

TEST_F(Ch15_BST_Fixture, generating_a_b_sqrt_2_Function) {
    vector<ABSqrt2> ans = GenerateFirstKABSqrt2(8);
    ASSERT_EQ(0.0, ans[0].val);
    ASSERT_EQ(1.0, ans[1].val);
    ASSERT_EQ(sqrt(2.0), ans[2].val);
    ASSERT_EQ(2.0, ans[3].val);
    ASSERT_EQ(1.0 + sqrt(2.0), ans[4].val);
    ASSERT_EQ(2.0 * sqrt(2.0), ans[5].val);
    ASSERT_EQ(3.0, ans[6].val);
    ASSERT_EQ(2.0 + sqrt(2.0), ans[7].val);

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        uniform_int_distribution<int> dis(1, 10000);
        int k = dis(gen);

        vector<ABSqrt2> ans(GenerateFirstKABSqrt2(k));
        for (size_t i = 0; i < ans.size(); ++i) {
        //    cout << ans[i].a << ' ' << ans[i].b << ' ' << ans[i].val << endl;
            if (i > 0) {
                ASSERT_GE(ans[i].val, ans[i - 1].val);
            }
        }
        auto gold_res = Golden(k);
        for (size_t i = 0; i < k; ++i) {
            ASSERT_EQ(ans[i].val, gold_res[i].val);
        }
    }
}

TEST_F(Ch15_BST_Fixture, generating_a_b_sqrt_2_improved_Function) {
    vector<improved::ABSqrt2> ans = improved::GenerateFirstKABSqrt2(8);
    ASSERT_EQ(0.0, ans[0].val);
    ASSERT_EQ(1.0, ans[1].val);
    ASSERT_EQ(sqrt(2.0), ans[2].val);
    ASSERT_EQ(2.0, ans[3].val);
    ASSERT_EQ(1.0 + sqrt(2.0), ans[4].val);
    ASSERT_EQ(2.0 * sqrt(2.0), ans[5].val);
    ASSERT_EQ(3.0, ans[6].val);
    ASSERT_EQ(2.0 + sqrt(2.0), ans[7].val);

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        uniform_int_distribution<int> dis(1, 10000);
        int k = dis(gen);

        vector<improved::ABSqrt2> ans(improved::GenerateFirstKABSqrt2(k));
        ASSERT_EQ(ans.size(), k);
        for (size_t i = 0; i < ans.size(); ++i) {
            // cout << ans[i].a << ' ' << ans[i].b << ' ' << ans[i].val << endl;
            if (i > 0) {
                ASSERT_GE(ans[i].val, ans[i - 1].val);
            }
        }
        auto gold_res = improved::Golden(k);

        for (size_t i = 0; i < k; ++i) {
            ASSERT_EQ(ans[i].val, gold_res[i].val);
        }
        // Following code are replaced by above code. This code does not compiled.
        // ASSERT_TRUE(equal(ans.begin(), ans.end(), gold_res.begin(), gold_res.end(),
        //             [](const ABSqrt2& a, const ABSqrt2& b) -> bool {
        //                 return a.val == b.val;
        //             }));

        // I defined == operator to support following code.
        ASSERT_TRUE(equal(ans.begin(), ans.end(), gold_res.begin(), gold_res.end()));
    }
}

TEST_F(Ch15_BST_Fixture, build_BST_from_sorted_array_Function) {
    vector<int> A = {1, 2, 3, 4};
    unique_ptr<BSTNode<int>> result = BuildMinHeightBSTFromSortedArray(A);
    ASSERT_EQ(3, result->data);
    ASSERT_EQ(2, result->left->data);
    ASSERT_EQ(1, result->left->left->data);
    ASSERT_EQ(4, result->right->data);

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    for (int times = 0; times < 1000; ++times) {
        uniform_int_distribution<int> dis(1, 1000);
        int n = dis(gen);
        vector<int> A(n);
        // iota: Assigns to every element in the range [first,last)
        // successive values of val, as if incremented with ++val
        // after each element is written.
        iota(A.begin(), A.end(), 0);

        unique_ptr<BSTNode<int>> tree = BuildMinHeightBSTFromSortedArray(A);
        int target = 0;
        TraversalCheck(tree, &target);
    }
}

TEST_F(Ch15_BST_Fixture, insertion_deletion_BST_Function) {
    BinarySearchTree<int> BST;
    ASSERT_TRUE(BST.Empty());
    ASSERT_TRUE(BST.Insert(7));
    ASSERT_TRUE(BST.Insert(8));
    ASSERT_TRUE(BST.Insert(9));
    ASSERT_TRUE(BST.Insert(4));
    ASSERT_TRUE(BST.Insert(3));
    ASSERT_FALSE(BST.Empty());
    ASSERT_TRUE(BST.Insert(2));
    ASSERT_TRUE(BST.Insert(5));
    ASSERT_TRUE(BST.Delete(7));
    ASSERT_TRUE(BST.Delete(9));
    // should output 8
    ASSERT_EQ(BST.GetRootVal(), 8);
    // cout << BST.GetRootVal() << endl;
    ASSERT_TRUE(BST.Delete(4));
    // should output 8
    ASSERT_EQ(BST.GetRootVal(), 8);
    // cout << BST.GetRootVal() << endl;
    ASSERT_TRUE(BST.Delete(8));
    // should output 5
    ASSERT_EQ(BST.GetRootVal(), 5);
    // cout << BST.GetRootVal() << endl;
    ASSERT_TRUE(BST.Delete(5));
    ASSERT_TRUE(BST.Delete(3));
    // should output 2
    ASSERT_EQ(BST.GetRootVal(), 2);
    // cout << BST.GetRootVal() << endl;
    ASSERT_TRUE(BST.Delete(2));
    ASSERT_FALSE(BST.Delete(1));
    ASSERT_TRUE(BST.Empty());
    BST.Insert(7);
    ASSERT_EQ(BST.GetRootVal(), 7);
    BST.Insert(9);
    ASSERT_EQ(BST.GetRootVal(), 7);
    BST.Delete(7);
    ASSERT_EQ(BST.GetRootVal(), 9);
}

TEST_F(Ch15_BST_Fixture, recursive_insertion_deletion_BST_Function) {
    BinarySearchTree<int> BST;
    ASSERT_TRUE(BST.Empty());
    ASSERT_TRUE(BST.rInsert(7));
    ASSERT_TRUE(BST.rInsert(8));
    ASSERT_FALSE(BST.rInsert(8));
    ASSERT_TRUE(BST.rInsert(9));
    ASSERT_TRUE(BST.rInsert(4));
    ASSERT_TRUE(BST.rInsert(3));
    ASSERT_FALSE(BST.Empty());
    ASSERT_TRUE(BST.rInsert(2));
    ASSERT_TRUE(BST.rInsert(5));

    ASSERT_TRUE(BST.rDelete(7));
    ASSERT_TRUE(BST.rDelete(9));
    ASSERT_FALSE(BST.rDelete(9));
    // should output 8
    ASSERT_EQ(BST.GetRootVal(), 8);
    // cout << BST.GetRootVal() << endl;
    ASSERT_TRUE(BST.rDelete(4));
    // should output 8
    ASSERT_EQ(BST.GetRootVal(), 8);
    // cout << BST.GetRootVal() << endl;
    ASSERT_TRUE(BST.rDelete(8));
    // should output 5
    ASSERT_EQ(BST.GetRootVal(), 5);
    // cout << BST.GetRootVal() << endl;
    ASSERT_TRUE(BST.rDelete(5));
    ASSERT_TRUE(BST.rDelete(3));
    // should output 2
    ASSERT_EQ(BST.GetRootVal(), 2);
    // cout << BST.GetRootVal() << endl;
    ASSERT_TRUE(BST.rDelete(2));
    ASSERT_FALSE(BST.rDelete(1));
    ASSERT_TRUE(BST.Empty());
    BST.rInsert(7);
    ASSERT_EQ(BST.GetRootVal(), 7);
    BST.rInsert(9);
    ASSERT_EQ(BST.GetRootVal(), 7);
    BST.Delete(7);
    ASSERT_EQ(BST.GetRootVal(), 9);
}

TEST_F(Ch15_BST_Fixture, descendant_and_ancestor_Function) {
    auto root = make_unique<BSTNode<int>>(BSTNode<int>{5});
    ASSERT_FALSE(PairIncludesAncestorAndDescendantOfM(root, root, root));
    root->left = make_unique<BSTNode<int>>(BSTNode<int>{2});
    root->left->right = make_unique<BSTNode<int>>(BSTNode<int>{4});
    ASSERT_FALSE(PairIncludesAncestorAndDescendantOfM(root, root->left,
                                                 root->left->right));
    ASSERT_TRUE(PairIncludesAncestorAndDescendantOfM(root, root->left->right,
                                                root->left));

    // Example of the first figure of BST chapter.
    root = make_unique<BSTNode<int>>(BSTNode<int>{19});
    root->left = make_unique<BSTNode<int>>(BSTNode<int>{7});
    root->left->left = make_unique<BSTNode<int>>(BSTNode<int>{3});
    root->left->left->left = make_unique<BSTNode<int>>(BSTNode<int>{2});
    root->left->left->right = make_unique<BSTNode<int>>(BSTNode<int>{5});
    root->left->right = make_unique<BSTNode<int>>(BSTNode<int>{11});
    root->left->right->right = make_unique<BSTNode<int>>(BSTNode<int>{17});
    root->left->right->right->left =
            make_unique<BSTNode<int>>(BSTNode<int>{13});
    root->right = make_unique<BSTNode<int>>(BSTNode<int>{43});
    root->right->left = make_unique<BSTNode<int>>(BSTNode<int>{23});
    root->right->left->right = make_unique<BSTNode<int>>(BSTNode<int>{37});
    root->right->left->right->left =
            make_unique<BSTNode<int>>(BSTNode<int>{29});
    root->right->left->right->left->right =
            make_unique<BSTNode<int>>(BSTNode<int>{31});
    root->right->left->right->right =
            make_unique<BSTNode<int>>(BSTNode<int>{41});
    root->right->right = make_unique<BSTNode<int>>(BSTNode<int>{47});
    root->right->right->right = make_unique<BSTNode<int>>(BSTNode<int>{53});

    ASSERT_FALSE(PairIncludesAncestorAndDescendantOfM(root->right, root->left,
                                                 root->right->left));
    ASSERT_TRUE(PairIncludesAncestorAndDescendantOfM(
            root, root->right->left->right->left->right, root->right->left));

    //      3
    //    2   5
    //  1    4 6
    root = make_unique<BSTNode<int>>(BSTNode<int>{3});
    root->left = make_unique<BSTNode<int>>(BSTNode<int>{2});
    root->left->left = make_unique<BSTNode<int>>(BSTNode<int>{1});
    root->right = make_unique<BSTNode<int>>(BSTNode<int>{5});
    root->right->left = make_unique<BSTNode<int>>(BSTNode<int>{4});
    root->right->right = make_unique<BSTNode<int>>(BSTNode<int>{6});
    ASSERT_TRUE(PairIncludesAncestorAndDescendantOfM(root, root->right->right,
                                                root->right));
    ASSERT_TRUE(PairIncludesAncestorAndDescendantOfM(root->right->right, root,
                                                root->right));
    ASSERT_FALSE(PairIncludesAncestorAndDescendantOfM(root, root->right,
                                                 root->right->right));
    ASSERT_FALSE(PairIncludesAncestorAndDescendantOfM(root->right, root,
                                                 root->right->right));
    ASSERT_FALSE(PairIncludesAncestorAndDescendantOfM(
            root->right->left, root->right->right, root->right));
    ASSERT_FALSE(PairIncludesAncestorAndDescendantOfM(
            root->right->left, root->left->left, root->right));
}

TEST_F(Ch15_BST_Fixture, range_lookup_BST_Function) {
    //          19
    //     7          43
    //   3   11    23   47
    // 2  5    17   37    53
    //        13  29  41
    //             31
    unique_ptr<BSTNode<int>> tree = make_unique<BSTNode<int>>(BSTNode<int>{19});
    tree->left = make_unique<BSTNode<int>>(BSTNode<int>{7});
    tree->left->left = make_unique<BSTNode<int>>(BSTNode<int>{3});
    tree->left->left->left = make_unique<BSTNode<int>>(BSTNode<int>{2});
    tree->left->left->right = make_unique<BSTNode<int>>(BSTNode<int>{5});
    tree->left->right = make_unique<BSTNode<int>>(BSTNode<int>{11});
    tree->left->right->right = make_unique<BSTNode<int>>(BSTNode<int>{17});
    tree->left->right->right->left =
            make_unique<BSTNode<int>>(BSTNode<int>{13});
    tree->right = make_unique<BSTNode<int>>(BSTNode<int>{43});
    tree->right->left = make_unique<BSTNode<int>>(BSTNode<int>{23});
    tree->right->left->right = make_unique<BSTNode<int>>(BSTNode<int>{37});
    tree->right->left->right->left =
            make_unique<BSTNode<int>>(BSTNode<int>{29});
    tree->right->left->right->left->right =
            make_unique<BSTNode<int>>(BSTNode<int>{31});
    tree->right->left->right->right =
            make_unique<BSTNode<int>>(BSTNode<int>{41});
    tree->right->right = make_unique<BSTNode<int>>(BSTNode<int>{47});
    tree->right->right->right = make_unique<BSTNode<int>>(BSTNode<int>{53});
    auto result = std::move(RangeLookupInBST(tree, {16, 31}));

    sort(result.begin(), result.end());
    vector<int> golden_result = {17, 19, 23, 29, 31};
    ASSERT_TRUE(equal(result.begin(), result.end(), golden_result.begin(),
                 golden_result.end()));

    result = std::move(RangeLookupInBST(tree, {38, 39}));
    ASSERT_EQ(0, result.size());

    result = std::move(RangeLookupInBST(tree, {38, 42}));
    ASSERT_TRUE((1 == result.size()) && (41 == result[0]));

    result = std::move(RangeLookupInBST(tree, {-1, 1}));
    ASSERT_EQ(0, result.size());

    result = std::move(RangeLookupInBST(
            tree, {numeric_limits<int>::max() - 1, numeric_limits<int>::max()}));
    ASSERT_EQ(0, result.size());
}

TEST_F(Ch15_BST_Fixture, adding_credits_Function) {
    ClientsCreditsInfo a;
    ASSERT_EQ(a.Max(), "");
    ASSERT_FALSE(a.Remove("foo"));
    a.Insert("foo", 10);
    a.Insert("foo", 1);
    a.Insert("bar", 2);
    a.AddAll(5);
    a.Insert("widget", 3);
    a.AddAll(5);
    a.Insert("dothis", 4);
    ASSERT_EQ(11, a.Lookup("foo"));
    ASSERT_EQ(12, a.Lookup("bar"));
    ASSERT_EQ(8, a.Lookup("widget"));
    ASSERT_EQ(4, a.Lookup("dothis"));
    ASSERT_TRUE(a.Remove("foo"));
    ASSERT_EQ(-1, a.Lookup("foo"));
    ASSERT_EQ(a.Max().compare("bar"), 0);
    a.Insert("xyz", 13);
    ASSERT_EQ(a.Max().compare("xyz"), 0);
    a.Insert("dd", 15);
    ASSERT_EQ(a.Max().compare("dd"), 0);
}
