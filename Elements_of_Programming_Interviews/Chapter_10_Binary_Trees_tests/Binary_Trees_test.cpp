#include <gtest/gtest.h>
#include <random>
#include <limits>
#include "Balanced_binary_tree.h"

using std::istringstream;
using std::stringstream;
using std::default_random_engine;
using std::random_device;
using std::unique_ptr;
using std::numeric_limits;

class BinaryTrees_Fixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    BinaryTrees_Fixture() : Test() {

    }

    virtual ~BinaryTrees_Fixture() {
    }
};

TEST_F(BinaryTrees_Fixture, balanced_binary_tree_Function) {
    //  balanced binary tree test
    //      3
    //    2   5
    //  1    4 6
    unique_ptr<BinaryTreeNode <int>>
    tree =
            make_unique <BinaryTreeNode <int>> (BinaryTreeNode<int>());
    tree->left = make_unique <BinaryTreeNode <int>> (BinaryTreeNode<int>());
    tree->left->left = make_unique <BinaryTreeNode <int>> (BinaryTreeNode<int>());
    tree->right = make_unique <BinaryTreeNode <int>> (BinaryTreeNode<int>());
    tree->right->left = make_unique <BinaryTreeNode <int>> (BinaryTreeNode<int>());
    tree->right->right =
            make_unique <BinaryTreeNode <int>> (BinaryTreeNode<int>());
    ASSERT_EQ(true, IsBalanced(tree));
    // Non-balanced binary tree test.
    tree = make_unique <BinaryTreeNode <int>> (BinaryTreeNode<int>());
    tree->left = make_unique <BinaryTreeNode <int>> (BinaryTreeNode<int>());
    tree->left->left = make_unique <BinaryTreeNode <int>> (BinaryTreeNode<int>());
    ASSERT_EQ(false, IsBalanced(tree));
}
