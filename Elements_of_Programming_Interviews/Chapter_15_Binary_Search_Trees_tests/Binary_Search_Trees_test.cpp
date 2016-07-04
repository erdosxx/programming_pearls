#include <gtest/gtest.h>
#include <random>
#include <limits>
#include <unordered_set>
#include <cmath>
#include <string>
#include "is_binary_tree_a_BST.h"
#include "is_binary_tree_a_BST_BFS.h"

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

public:
    Ch15_BST_Fixture() : Test() {

    }

    virtual ~Ch15_BST_Fixture() {
    }
};

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

