#include <gtest/gtest.h>
#include <random>
#include <limits>
#include <unordered_set>
#include <cmath>
#include <string>
#include "is_binary_tree_a_BST.h"
#include "is_binary_tree_a_BST_BFS.h"
#include "Search_BST_first_larger_k.h"
#include "Find_k_largest_BST.h"
#include "BST_lowest_common_ancestor.h"
#include "Rebuild_BST_preorder.h"
#include "Rebuild_BST_preorder_better.h"
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

class Ch15_BST_Fixture : public ::testing::Test {
private:

protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    void CheckAns(const unique_ptr<BSTNode<int>>& n, const int& pre) {
        if (n) {
            CheckAns(n->left, pre);
            ASSERT_LE(pre, n->data);
            // cout << n->data << endl;
            CheckAns(n->right, n->data);
        }
    }

    void TraversalCheck(const unique_ptr<BSTNode<int>>& tree, int* target);

public:
    Ch15_BST_Fixture() : Test() {

    }

    virtual ~Ch15_BST_Fixture() {
    }
};

void Ch15_BST_Fixture::TraversalCheck(const unique_ptr<BSTNode<int>>& tree, int* target) {
    if (tree) {
        TraversalCheck(tree->left, target);
        ASSERT_EQ(*target, tree->data);
        ++*target;
        TraversalCheck(tree->right, target);
    }
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
    ASSERT_EQ(IsBinaryTreeBST(tree), true);
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
    default_random_engine gen((random_device())());

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
}

TEST_F(Ch15_BST_Fixture, rebuild_BST_preorder_Function) {
    //      3
    //    2   5
    //  1    4  6
    // should output 1, 2, 3, 4, 5, 6
    // preorder [3, 2, 1, 5, 4, 6]
    vector<int> preorder = {3, 2, 1, 5, 4, 6};
    unique_ptr<BSTNode<int>> tree(RebuildBSTFromPreorder(preorder));
    CheckAns(tree, numeric_limits<int>::min());
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
    CheckAns(tree, numeric_limits<int>::min());
    ASSERT_EQ(3, tree->data);
    ASSERT_EQ(2, tree->left->data);
    ASSERT_EQ(1, tree->left->left->data);
    ASSERT_EQ(5, tree->right->data);
    ASSERT_EQ(4, tree->right->left->data);
    ASSERT_EQ(6, tree->right->right->data);
}

TEST_F(Ch15_BST_Fixture, min_distance_3_sorted_Function) {
    default_random_engine gen((random_device())());
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

    default_random_engine gen((random_device())());
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

    default_random_engine gen((random_device())());
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

    default_random_engine gen((random_device())());
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