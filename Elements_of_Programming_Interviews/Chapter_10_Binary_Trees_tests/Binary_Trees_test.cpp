#include <gtest/gtest.h>
#include <random>
#include <limits>
#include "tree_traversal.h"
#include "Balanced_binary_tree.h"
#include "largest_complete_subtree.h"
#include "k-balanced_binary_tree.h"
#include "k-balanced_binary_tree_erdos.h"
#include "Symmetric_binary_tree.h"
#include "Lowest_common_ancestor_no_parent.h"
#include "Lowest_common_ancestor_employee.h"
#include "Lowest_common_ancestor.h"
#include "sum-root-to-leaf-binary-tree.h"
#include "path-sum-binary-tree.h"
#include "BST_sorted_order.h"
#include "binary-tree-preorder-traversal-iterative.h"
#include "k-th_node_binary_tree.h"
#include "Successor.h"
#include "Inorder_traversal_with_parent.h"
#include "preorder_traversal_with_parent.h"
#include "postorder_traversal_with_parent.h"
#include "Reconstruct_binary_tree_pre_in_orders.h"
#include "Reconstruct_preorder_with_null.h"
#include "Connect_leaves_binary_tree.h"
#include "Exterior_binary_tree.h"
#include "populating-next-right-pointers.h"
#include "populating-next-right-pointers-any-binary-tree.h"
#include "Binary_tree_lock.h"

using std::istringstream;
using std::stringstream;
using std::default_random_engine;
using std::random_device;
using std::unique_ptr;
using std::numeric_limits;
using btree_node = btree::BinaryTreeNode<int>;
using btree_node_with_parent = btree_with_parent::BinaryTreeNode<int>;

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

TEST_F(BinaryTrees_Fixture, tree_traversal) {
    //      3
    //    2   5
    //  1    4 6
    unique_ptr<BinaryTreeNode<int>> tree =
            make_unique<BinaryTreeNode<int>>( BinaryTreeNode<int>{3, nullptr, nullptr});
    tree->left =
            make_unique<BinaryTreeNode<int>>( BinaryTreeNode<int>{2, nullptr, nullptr});
    tree->left->left =
            make_unique<BinaryTreeNode<int>>( BinaryTreeNode<int>{1, nullptr, nullptr});
    tree->right =
            make_unique<BinaryTreeNode<int>>( BinaryTreeNode<int>{5, nullptr, nullptr});
    tree->right->left =
            make_unique<BinaryTreeNode<int>>( BinaryTreeNode<int>{4, nullptr, nullptr});
    tree->right->right =
            make_unique<BinaryTreeNode<int>>( BinaryTreeNode<int>{6, nullptr, nullptr});
    //TreeTraversal(tree);

    vector<int> traversal;
    vector<int> ans;
    traversal = generate_traversal(tree, "inorder");
    ans = {1,2,3,4,5,6};
    ASSERT_TRUE(equal(traversal.cbegin(), traversal.cend(), ans.cbegin(), ans.cend()));
    traversal = generate_traversal(tree, "preorder");
    ans = {3,2,1,5,4,6};
    ASSERT_TRUE(equal(traversal.cbegin(), traversal.cend(), ans.cbegin(), ans.cend()));
    traversal = generate_traversal(tree, "postorder");
    ans = {1,2,4,6,5,3};
    ASSERT_TRUE(equal(traversal.cbegin(), traversal.cend(), ans.cbegin(), ans.cend()));
}

TEST_F(BinaryTrees_Fixture, balanced_binary_tree_Function) {
    //  balanced binary tree test
    //      3
    //    2   5
    //  1    4 6
    unique_ptr<btree_node> tree = make_unique<btree_node>(btree_node{3, nullptr, nullptr});
    tree->left = make_unique<btree_node>(btree_node{2, nullptr, nullptr});
    tree->left->left = make_unique<btree_node>(btree_node{1, nullptr, nullptr});
    tree->right = make_unique<btree_node>(btree_node{5, nullptr, nullptr});
    tree->right->left = make_unique<btree_node>(btree_node{4, nullptr, nullptr});
    tree->right->right = make_unique<btree_node>(btree_node{6, nullptr, nullptr});
    ASSERT_EQ(true, IsBalanced(tree));

    // Non-balanced binary tree test.
    //      3
    //    2
    //  1
    tree = make_unique<btree_node>(btree_node{3, nullptr, nullptr});
    tree->left = make_unique<btree_node>(btree_node{2, nullptr, nullptr});
    tree->left->left = make_unique<btree_node>(btree_node{1, nullptr, nullptr});
    ASSERT_EQ(false, IsBalanced(tree));
}

TEST_F(BinaryTrees_Fixture, largest_complete_subtree) {
    // Fig 10.1
    //                  314
    //            6               6
    //         271  561        2       271
    //       28  0     3         1         28
    //               17       401   257
    //                          641
    unique_ptr<btree_node> tree = make_unique<btree_node>(btree_node{314, nullptr, nullptr});
    tree->left = make_unique<btree_node>(btree_node{6, nullptr, nullptr});
    tree->right = make_unique<btree_node>(btree_node{6, nullptr, nullptr});
    tree->left->left = make_unique<btree_node>(btree_node{271, nullptr, nullptr});
    tree->left->right = make_unique<btree_node>(btree_node{561, nullptr, nullptr});
    tree->left->left->left = make_unique<btree_node>(btree_node{28, nullptr, nullptr});
    tree->left->left->right = make_unique<btree_node>(btree_node{0, nullptr, nullptr});
    tree->left->right->right = make_unique<btree_node>(btree_node{3, nullptr, nullptr});
    tree->left->right->right->left = make_unique<btree_node>(btree_node{17, nullptr, nullptr});
    tree->right->left = make_unique<btree_node>(btree_node{2, nullptr, nullptr});
    tree->right->right = make_unique<btree_node>(btree_node{271, nullptr, nullptr});
    tree->right->left->right = make_unique<btree_node>(btree_node{1, nullptr, nullptr});
    tree->right->left->right->left = make_unique<btree_node>(btree_node{401, nullptr, nullptr});
    tree->right->left->right->right = make_unique<btree_node>(btree_node{257, nullptr, nullptr});
    tree->right->left->right->left->right = make_unique<btree_node>(btree_node{641, nullptr, nullptr});
    tree->right->right->right = make_unique<btree_node>(btree_node{28, nullptr, nullptr});
    ASSERT_EQ(3, size_largest_complete_subtree(tree));

    // Fig 10.2
    //                  1
    //           2             3
    //         4    5       12   13
    //       6  7  8  9   14  15
    //     10 11
    tree = make_unique<btree_node>(btree_node{1, nullptr, nullptr});
    tree->left = make_unique<btree_node>(btree_node{2, nullptr, nullptr});
    tree->right = make_unique<btree_node>(btree_node{3, nullptr, nullptr});
    tree->left->left = make_unique<btree_node>(btree_node{4, nullptr, nullptr});
    tree->left->right = make_unique<btree_node>(btree_node{5, nullptr, nullptr});
    tree->left->left->left = make_unique<btree_node>(btree_node{6, nullptr, nullptr});
    tree->left->left->right = make_unique<btree_node>(btree_node{7, nullptr, nullptr});
    tree->left->left->left->left = make_unique<btree_node>(btree_node{10, nullptr, nullptr});
    tree->left->left->left->right = make_unique<btree_node>(btree_node{11, nullptr, nullptr});
    tree->left->right->left = make_unique<btree_node>(btree_node{8, nullptr, nullptr});
    tree->left->right->right = make_unique<btree_node>(btree_node{9, nullptr, nullptr});
    tree->right->left = make_unique<btree_node>(btree_node{12, nullptr, nullptr});
    tree->right->right = make_unique<btree_node>(btree_node{13, nullptr, nullptr});
    tree->right->left->left = make_unique<btree_node>(btree_node{14, nullptr, nullptr});
    tree->right->left->right = make_unique<btree_node>(btree_node{15, nullptr, nullptr});
    ASSERT_EQ(3, size_largest_complete_subtree(tree));

    // Fig 10.2-1
    //                  1
    //           2               3
    //         4       5      12    13
    //       6  7     8 9   14 15
    //   10 11 16 17
    tree = make_unique<btree_node>(btree_node{1, nullptr, nullptr});
    tree->left = make_unique<btree_node>(btree_node{2, nullptr, nullptr});
    tree->right = make_unique<btree_node>(btree_node{3, nullptr, nullptr});
    tree->left->left = make_unique<btree_node>(btree_node{4, nullptr, nullptr});
    tree->left->right = make_unique<btree_node>(btree_node{5, nullptr, nullptr});
    tree->left->left->left = make_unique<btree_node>(btree_node{6, nullptr, nullptr});
    tree->left->left->right = make_unique<btree_node>(btree_node{7, nullptr, nullptr});
    tree->left->left->right->left = make_unique<btree_node>(btree_node{16, nullptr, nullptr});
    tree->left->left->right->right = make_unique<btree_node>(btree_node{17, nullptr, nullptr});
    tree->left->left->left->left = make_unique<btree_node>(btree_node{10, nullptr, nullptr});
    tree->left->left->left->right = make_unique<btree_node>(btree_node{11, nullptr, nullptr});
    tree->left->right->left = make_unique<btree_node>(btree_node{8, nullptr, nullptr});
    tree->left->right->right = make_unique<btree_node>(btree_node{9, nullptr, nullptr});
    tree->right->left = make_unique<btree_node>(btree_node{12, nullptr, nullptr});
    tree->right->right = make_unique<btree_node>(btree_node{13, nullptr, nullptr});
    tree->right->left->left = make_unique<btree_node>(btree_node{14, nullptr, nullptr});
    tree->right->left->right = make_unique<btree_node>(btree_node{15, nullptr, nullptr});
    ASSERT_EQ(7, size_largest_complete_subtree(tree));
}

TEST_F(BinaryTrees_Fixture, k_balanced_binary_tree) {
    // Fig 10.1
    //                  314
    //            6               6
    //         271  561        2       271
    //       28  0     3         1         28
    //               17       401   257
    //                          641
    unique_ptr<btree_node> tree = make_unique<btree_node>(btree_node{314, nullptr, nullptr});
    tree->left = make_unique<btree_node>(btree_node{6, nullptr, nullptr});
    tree->right = make_unique<btree_node>(btree_node{6, nullptr, nullptr});
    tree->left->left = make_unique<btree_node>(btree_node{271, nullptr, nullptr});
    tree->left->right = make_unique<btree_node>(btree_node{561, nullptr, nullptr});
    tree->left->left->left = make_unique<btree_node>(btree_node{28, nullptr, nullptr});
    tree->left->left->right = make_unique<btree_node>(btree_node{0, nullptr, nullptr});
    tree->left->right->right = make_unique<btree_node>(btree_node{3, nullptr, nullptr});
    tree->left->right->right->left = make_unique<btree_node>(btree_node{17, nullptr, nullptr});
    tree->right->left = make_unique<btree_node>(btree_node{2, nullptr, nullptr});
    tree->right->right = make_unique<btree_node>(btree_node{271, nullptr, nullptr});
    tree->right->left->right = make_unique<btree_node>(btree_node{1, nullptr, nullptr});
    tree->right->left->right->left = make_unique<btree_node>(btree_node{401, nullptr, nullptr});
    tree->right->left->right->right = make_unique<btree_node>(btree_node{257, nullptr, nullptr});
    tree->right->left->right->left->right = make_unique<btree_node>(btree_node{641, nullptr, nullptr});
    tree->right->right->right = make_unique<btree_node>(btree_node{28, nullptr, nullptr});
    ASSERT_EQ(tree->right->left.get(), FindKUnbalancedNode(tree, 3));

    // Fig 10.2-1
    //                  1
    //             2             3
    //         4       5      12    13
    //       6  7            14 15
    //   10 11 16 17
    tree = make_unique<btree_node>(btree_node{1, nullptr, nullptr});
    tree->left = make_unique<btree_node>(btree_node{2, nullptr, nullptr});
    tree->right = make_unique<btree_node>(btree_node{3, nullptr, nullptr});
    tree->left->left = make_unique<btree_node>(btree_node{4, nullptr, nullptr});
    tree->left->right = make_unique<btree_node>(btree_node{5, nullptr, nullptr});
    tree->left->left->left = make_unique<btree_node>(btree_node{6, nullptr, nullptr});
    tree->left->left->right = make_unique<btree_node>(btree_node{7, nullptr, nullptr});
    tree->left->left->right->left = make_unique<btree_node>(btree_node{16, nullptr, nullptr});
    tree->left->left->right->right = make_unique<btree_node>(btree_node{17, nullptr, nullptr});
    tree->left->left->left->left = make_unique<btree_node>(btree_node{10, nullptr, nullptr});
    tree->left->left->left->right = make_unique<btree_node>(btree_node{11, nullptr, nullptr});
    tree->right->left = make_unique<btree_node>(btree_node{12, nullptr, nullptr});
    tree->right->right = make_unique<btree_node>(btree_node{13, nullptr, nullptr});
    tree->right->left->left = make_unique<btree_node>(btree_node{14, nullptr, nullptr});
    tree->right->left->right = make_unique<btree_node>(btree_node{15, nullptr, nullptr});
    ASSERT_EQ(tree->left.get(), FindKUnbalancedNode(tree, 2));

    // Fig 10.2
    //                  1
    //           2             3
    //         4    5       12   13
    //       6  7  8  9   14  15
    //     10 11
    tree = make_unique<btree_node>(btree_node{1, nullptr, nullptr});
    tree->left = make_unique<btree_node>(btree_node{2, nullptr, nullptr});
    tree->right = make_unique<btree_node>(btree_node{3, nullptr, nullptr});
    tree->left->left = make_unique<btree_node>(btree_node{4, nullptr, nullptr});
    tree->left->right = make_unique<btree_node>(btree_node{5, nullptr, nullptr});
    tree->left->left->left = make_unique<btree_node>(btree_node{6, nullptr, nullptr});
    tree->left->left->right = make_unique<btree_node>(btree_node{7, nullptr, nullptr});
    tree->left->left->left->left = make_unique<btree_node>(btree_node{10, nullptr, nullptr});
    tree->left->left->left->right = make_unique<btree_node>(btree_node{11, nullptr, nullptr});
    tree->left->right->left = make_unique<btree_node>(btree_node{8, nullptr, nullptr});
    tree->left->right->right = make_unique<btree_node>(btree_node{9, nullptr, nullptr});
    tree->right->left = make_unique<btree_node>(btree_node{12, nullptr, nullptr});
    tree->right->right = make_unique<btree_node>(btree_node{13, nullptr, nullptr});
    tree->right->left->left = make_unique<btree_node>(btree_node{14, nullptr, nullptr});
    tree->right->left->right = make_unique<btree_node>(btree_node{15, nullptr, nullptr});
    ASSERT_EQ(nullptr, FindKUnbalancedNode(tree, 7));
}

TEST_F(BinaryTrees_Fixture, k_balanced_binary_tree_erdos) {
    // Fig 10.1
    //                  314
    //            6               6
    //         271  561        2       271
    //       28  0     3         1         28
    //               17       401   257
    //                          641
    unique_ptr<btree_node> tree = make_unique<btree_node>(btree_node{314, nullptr, nullptr});
    tree->left = make_unique<btree_node>(btree_node{6, nullptr, nullptr});
    tree->right = make_unique<btree_node>(btree_node{6, nullptr, nullptr});
    tree->left->left = make_unique<btree_node>(btree_node{271, nullptr, nullptr});
    tree->left->right = make_unique<btree_node>(btree_node{561, nullptr, nullptr});
    tree->left->left->left = make_unique<btree_node>(btree_node{28, nullptr, nullptr});
    tree->left->left->right = make_unique<btree_node>(btree_node{0, nullptr, nullptr});
    tree->left->right->right = make_unique<btree_node>(btree_node{3, nullptr, nullptr});
    tree->left->right->right->left = make_unique<btree_node>(btree_node{17, nullptr, nullptr});
    tree->right->left = make_unique<btree_node>(btree_node{2, nullptr, nullptr});
    tree->right->right = make_unique<btree_node>(btree_node{271, nullptr, nullptr});
    tree->right->left->right = make_unique<btree_node>(btree_node{1, nullptr, nullptr});
    tree->right->left->right->left = make_unique<btree_node>(btree_node{401, nullptr, nullptr});
    tree->right->left->right->right = make_unique<btree_node>(btree_node{257, nullptr, nullptr});
    tree->right->left->right->left->right = make_unique<btree_node>(btree_node{641, nullptr, nullptr});
    tree->right->right->right = make_unique<btree_node>(btree_node{28, nullptr, nullptr});
    ASSERT_EQ(tree->right->left, *upper_k_balanced_subtree(tree, 3));


    // Fig 10.2-1
    //                  1
    //             2             3
    //         4       5      12    13
    //       6  7            14 15
    //   10 11 16 17
    tree = make_unique<btree_node>(btree_node{1, nullptr, nullptr});
    tree->left = make_unique<btree_node>(btree_node{2, nullptr, nullptr});
    tree->right = make_unique<btree_node>(btree_node{3, nullptr, nullptr});
    tree->left->left = make_unique<btree_node>(btree_node{4, nullptr, nullptr});
    tree->left->right = make_unique<btree_node>(btree_node{5, nullptr, nullptr});
    tree->left->left->left = make_unique<btree_node>(btree_node{6, nullptr, nullptr});
    tree->left->left->right = make_unique<btree_node>(btree_node{7, nullptr, nullptr});
    tree->left->left->right->left = make_unique<btree_node>(btree_node{16, nullptr, nullptr});
    tree->left->left->right->right = make_unique<btree_node>(btree_node{17, nullptr, nullptr});
    tree->left->left->left->left = make_unique<btree_node>(btree_node{10, nullptr, nullptr});
    tree->left->left->left->right = make_unique<btree_node>(btree_node{11, nullptr, nullptr});
    tree->right->left = make_unique<btree_node>(btree_node{12, nullptr, nullptr});
    tree->right->right = make_unique<btree_node>(btree_node{13, nullptr, nullptr});
    tree->right->left->left = make_unique<btree_node>(btree_node{14, nullptr, nullptr});
    tree->right->left->right = make_unique<btree_node>(btree_node{15, nullptr, nullptr});
    ASSERT_EQ(tree->left, *upper_k_balanced_subtree(tree, 2));

    // Fig 10.2
    //                  1
    //           2             3
    //         4    5       12   13
    //       6  7  8  9   14  15
    //     10 11
    tree = make_unique<btree_node>(btree_node{1, nullptr, nullptr});
    tree->left = make_unique<btree_node>(btree_node{2, nullptr, nullptr});
    tree->right = make_unique<btree_node>(btree_node{3, nullptr, nullptr});
    tree->left->left = make_unique<btree_node>(btree_node{4, nullptr, nullptr});
    tree->left->right = make_unique<btree_node>(btree_node{5, nullptr, nullptr});
    tree->left->left->left = make_unique<btree_node>(btree_node{6, nullptr, nullptr});
    tree->left->left->right = make_unique<btree_node>(btree_node{7, nullptr, nullptr});
    tree->left->left->left->left = make_unique<btree_node>(btree_node{10, nullptr, nullptr});
    tree->left->left->left->right = make_unique<btree_node>(btree_node{11, nullptr, nullptr});
    tree->left->right->left = make_unique<btree_node>(btree_node{8, nullptr, nullptr});
    tree->left->right->right = make_unique<btree_node>(btree_node{9, nullptr, nullptr});
    tree->right->left = make_unique<btree_node>(btree_node{12, nullptr, nullptr});
    tree->right->right = make_unique<btree_node>(btree_node{13, nullptr, nullptr});
    tree->right->left->left = make_unique<btree_node>(btree_node{14, nullptr, nullptr});
    tree->right->left->right = make_unique<btree_node>(btree_node{15, nullptr, nullptr});
    ASSERT_EQ(nullptr, upper_k_balanced_subtree(tree, 7));
}

TEST_F(BinaryTrees_Fixture, symmetric_binary_tree_Function) {
    auto symm_tree = make_unique<btree_node>(btree::BinaryTreeNode<int>());
    ASSERT_TRUE(IsSymmetric(symm_tree));

    symm_tree->left = make_unique<btree_node>(btree::BinaryTreeNode<int>());
    ASSERT_FALSE(IsSymmetric(symm_tree));

    symm_tree->right = make_unique<btree_node>(btree::BinaryTreeNode<int>());
    ASSERT_TRUE(IsSymmetric(symm_tree));

    symm_tree->right->right =
            make_unique<btree_node>(btree::BinaryTreeNode<int>());
    ASSERT_FALSE(IsSymmetric(symm_tree));

    // Non symmetric tree test.
    //      x
    //    x   x
    //  x    x x
    auto non_symm_tree =
            make_unique<btree_node>(btree::BinaryTreeNode<int>());
    non_symm_tree->left =
            make_unique<btree_node>(btree::BinaryTreeNode<int>());
    non_symm_tree->left->left =
            make_unique<btree_node>(btree::BinaryTreeNode<int>());
    non_symm_tree->right =
            make_unique<btree_node>(btree::BinaryTreeNode<int>());
    non_symm_tree->right->left =
            make_unique<btree_node>(btree::BinaryTreeNode<int>());
    non_symm_tree->right->right =
            make_unique<btree_node>(btree::BinaryTreeNode<int>());
    ASSERT_FALSE(IsSymmetric(non_symm_tree));

    // Symmetric tree test.
    symm_tree = make_unique<btree_node>(btree::BinaryTreeNode<int>());
    symm_tree->left = make_unique<btree_node>(btree::BinaryTreeNode<int>());
    symm_tree->right = make_unique<btree_node>(btree::BinaryTreeNode<int>());
    ASSERT_TRUE(IsSymmetric(symm_tree));
    symm_tree = nullptr;
    ASSERT_TRUE(IsSymmetric(symm_tree));

    symm_tree = make_unique<btree_node>(btree::BinaryTreeNode<int>({0, nullptr, nullptr}));
    symm_tree->left = make_unique<btree_node>(btree::BinaryTreeNode<int>({1, nullptr, nullptr}));
    symm_tree->right = make_unique<btree_node>(btree::BinaryTreeNode<int>({2, nullptr, nullptr}));
    ASSERT_FALSE(IsSymmetric(symm_tree));
}

TEST_F(BinaryTrees_Fixture, LCA_no_prarent_Function) {
    //      3
    //    2   5
    //  1    4 6
    auto tree = make_unique<btree_node>(
            btree_node {3, nullptr, nullptr});
    tree->left = make_unique<btree_node>(
            btree_node {2, nullptr, nullptr});
    tree->left->left = make_unique<btree_node>(
            btree_node {1, nullptr, nullptr});
    tree->right = make_unique<btree_node>(
            btree_node {5, nullptr, nullptr});
    tree->right->left = make_unique<btree_node>(
            btree_node {4, nullptr, nullptr});
    tree->right->right = make_unique<btree_node>(
            btree_node {6, nullptr, nullptr});
    // should output 3
    auto* x = lca_no_parenet::LCA(tree, tree->left, tree->right);
    ASSERT_EQ(x->data, 3);

    // should output 5
    x = lca_no_parenet::LCA(tree, tree->right->left, tree->right->right);
    ASSERT_EQ(x->data, 5);

    // should output 5
    x = lca_no_parenet::LCA(tree, tree->right, tree->right->right);
    ASSERT_EQ(x->data, 5);

    // should output 3
    x = lca_no_parenet::LCA(tree, tree->left->left, tree->right->right);
    ASSERT_EQ(x->data, 3);

    // should output 3
    x = lca_no_parenet::LCA(tree, tree->left->left, tree);
    ASSERT_EQ(x->data, 3);

    // should output 2
    x = lca_no_parenet::LCA(tree, tree->left, tree->left);
    ASSERT_EQ(x->data, 2);
}

TEST_F(BinaryTrees_Fixture, lowest_common_ancestor_employee) {
    //
    //          Bill ------------> CEO
    //       /     |    \            \
    //     DOM      SAMIR  MICHAEL    Erdos
    //      /  \  \
    //  Peter  Bob  Porter
    //   /   \
    // Milton Nina                          Other
    Employee Other{100, "Other", {}};
    Employee Nina{32, "Nina", {}};
    Employee Milton{31, "Milton", {}};
    Employee Porter{23, "Porter", {}};
    Employee Bob{22, "Bob", {}};
    Employee Peter{21, "Peter", {&Milton, &Nina}};
    Employee DOM{13, "DOM", {&Peter, &Bob, &Porter}};
    Employee SAMIR{12, "SAMIR", {}};
    Employee MICHAEL{11, "MICHAEL", {}};
    Employee Bill{1, "Bill", {&DOM, &SAMIR, &MICHAEL}};
    Employee Erdos{2, "Erdos", {}};
    Employee CEO{0, "CEO", {&Bill, &Erdos}};
    const Employee* ceo = &CEO;
    const Employee* peter = &Peter;
    const Employee* samir = &SAMIR;
    const Employee* milton = &Milton;
    const Employee* porter = &Porter;
    const Employee* other = &Other;

    ASSERT_EQ(closestCommonManager2(&CEO,peter,samir)->getName(), "Bill");
    ASSERT_EQ(closestCommonManager2(&CEO,milton,peter)->getName(), "Peter");
    ASSERT_EQ(closestCommonManager2(&CEO,milton,porter)->getName(), "DOM");
    ASSERT_EQ(closestCommonManager2(&CEO,peter,other), nullptr);
}

TEST_F(BinaryTrees_Fixture, lowest_common_ancestor_Function) {
    //      3
    //    2   5
    //  1    4 6
    auto root = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{3, nullptr, nullptr, nullptr});
    root->left = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{2, nullptr, nullptr, root.get()});
    root->left->left = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{1, nullptr, nullptr, root->left.get()});
    root->right = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{5, nullptr, nullptr, root.get()});
    root->right->left = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{4, nullptr, nullptr, root->right.get()});
    root->right->right = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{6, nullptr, nullptr, root->right.get()});

    ASSERT_EQ(0, lca::GetDepth(root.get()));
    ASSERT_EQ(1, lca::GetDepth((root->left).get()));
    ASSERT_EQ(1, lca::GetDepth((root->right).get()));
    ASSERT_EQ(2, lca::GetDepth((root->left->left).get()));
    ASSERT_EQ(2, lca::GetDepth((root->right->left).get()));

    ASSERT_EQ(lca::LCA(root->left, root->right)->data, 3);
    ASSERT_EQ(lca::LCA(root->right->left, root->right->right)->data, 5);
    ASSERT_EQ(lca::LCA(root->left, root->right->left)->data, 3);
    ASSERT_EQ(lca::LCA(root->left, root->left->left)->data, 2);
}

TEST_F(BinaryTrees_Fixture, sum_root_to_leaf_Function) {
    //      1
    //    1   0
    //  0    1 0
    unique_ptr<btree_node> root = make_unique<btree_node>(
            BinaryTreeNode<int>{1, nullptr, nullptr});
    ASSERT_EQ(SumRootToLeaf(root), 1);
    root->left = make_unique<btree_node>(
            BinaryTreeNode<int>{1, nullptr, nullptr});
    ASSERT_EQ(SumRootToLeaf(root), 3);
    root->left->left = make_unique<btree_node>(
            BinaryTreeNode<int>{0, nullptr, nullptr});
    ASSERT_EQ(SumRootToLeaf(root), 6);
    root->right = make_unique<btree_node>(
            BinaryTreeNode<int>{0, nullptr, nullptr});
    ASSERT_EQ(SumRootToLeaf(root), 8);
    root->right->left = make_unique<btree_node>(
            BinaryTreeNode<int>{1, nullptr, nullptr});
    ASSERT_EQ(SumRootToLeaf(root), 11);
    root->right->right = make_unique<btree_node>(
            BinaryTreeNode<int>{0, nullptr, nullptr});
    ASSERT_EQ(SumRootToLeaf(root), 15);
}

TEST_F(BinaryTrees_Fixture, path_sum_Function) {
    //      3
    //    2   5
    //  1    4 6
    unique_ptr<btree_node> tree = make_unique<btree_node>(
            btree::BinaryTreeNode<int>{3, nullptr, nullptr});
    ASSERT_TRUE(HasPathSum(tree, 3));
    tree->left = make_unique<btree_node>(
            btree::BinaryTreeNode<int>{2, nullptr, nullptr});
    ASSERT_TRUE(HasPathSum(tree, 5));
    tree->left->left = make_unique<btree_node>(
            btree::BinaryTreeNode<int>{1, nullptr, nullptr});
    ASSERT_TRUE(HasPathSum(tree, 6));
    tree->right = make_unique<btree_node>(
            btree::BinaryTreeNode<int>{5, nullptr, nullptr});
    ASSERT_TRUE(HasPathSum(tree, 8));
    ASSERT_FALSE(HasPathSum(tree, 7));
    tree->right->left = make_unique<btree_node>(
            btree::BinaryTreeNode<int>{4, nullptr, nullptr});
    ASSERT_TRUE(HasPathSum(tree, 12));
    ASSERT_FALSE(HasPathSum(tree, 1));
    ASSERT_FALSE(HasPathSum(tree, 3));
    ASSERT_FALSE(HasPathSum(tree, 5));
    tree->right->right = make_unique<btree_node>(
            btree::BinaryTreeNode<int>{6, nullptr, nullptr});
    ASSERT_TRUE(HasPathSum(tree, 6));
    ASSERT_FALSE(HasPathSum(tree, 7));
    ASSERT_TRUE(HasPathSum(tree, 14));
    ASSERT_FALSE(HasPathSum(tree, -1));
    ASSERT_FALSE(HasPathSum(tree, numeric_limits<int>::max()));
    ASSERT_FALSE(HasPathSum(tree, numeric_limits<int>::min()));
}

TEST_F(BinaryTrees_Fixture, BST_sorted_order_Function) {
    unique_ptr<BSTNode<int>> tree = make_unique<BSTNode<int>>(BSTNode<int>{43, nullptr});
    auto result = BSTInSortedOrder(tree);
    vector<int> golden_result = {43};
    ASSERT_TRUE(equal(golden_result.begin(), golden_result.end(), result.begin(), result.end()));

    tree->left = make_unique<BSTNode<int>>(BSTNode<int>{23, nullptr});
    result = BSTInSortedOrder(tree);
    golden_result = {23, 43};
    ASSERT_TRUE(equal(golden_result.begin(), golden_result.end(), result.begin(), result.end()));

    //        43
    //    23     47
    //      37      53
    //    29  41
    //     31
    tree = make_unique<BSTNode<int>>(BSTNode<int>{43, nullptr});
    tree->left = make_unique<BSTNode<int>>(BSTNode<int>{23, nullptr});
    tree->left->right = make_unique<BSTNode<int>>(BSTNode<int>{37, nullptr});
    tree->left->right->left =
            make_unique<BSTNode<int>>(BSTNode<int>{29, nullptr});
    tree->left->right->left->right =
            make_unique<BSTNode<int>>(BSTNode<int>{31, nullptr});
    tree->left->right->right =
            make_unique<BSTNode<int>>(BSTNode<int>{41, nullptr});
    tree->right = make_unique<BSTNode<int>>(BSTNode<int>{47, nullptr});
    tree->right->right = make_unique<BSTNode<int>>(BSTNode<int>{53, nullptr});
    result = BSTInSortedOrder(tree);
    vector<int> golden_res = {23, 29, 31, 37, 41, 43, 47, 53};
    ASSERT_TRUE(equal(golden_res.begin(), golden_res.end(), result.begin(), result.end()));
}

TEST_F(BinaryTrees_Fixture, btree_preorder_Function) {
    //      3
    //    2   5
    //  1    4 6
    unique_ptr<btree_node> tree = make_unique<btree_node>(
            BinaryTreeNode<int>{3, nullptr, nullptr});
    tree->left = make_unique<btree_node>(
            BinaryTreeNode<int>{2, nullptr, nullptr});
    tree->left->left = make_unique<btree_node>(
            BinaryTreeNode<int>{1, nullptr, nullptr});
    tree->right = make_unique<btree_node>(
            BinaryTreeNode<int>{5, nullptr, nullptr});
    tree->right->left = make_unique<btree_node>(
            BinaryTreeNode<int>{4, nullptr, nullptr});
    tree->right->right = make_unique<btree_node>(
            BinaryTreeNode<int>{6, nullptr, nullptr});
    auto res = PreorderTraversal(tree);
    auto golden_res = generate_preorder(tree);
    ASSERT_TRUE(equal(res.cbegin(), res.cend(), golden_res.cbegin(),
                 golden_res.cend()));
}

TEST_F(BinaryTrees_Fixture, kth_node_Function) {
    //  size field
    //      6
    //    2   3
    //  1    1 1
    //
    //  data field
    //      3
    //    2   5
    //  1    4 6
    auto root = make_unique<kthNode::BinaryTreeNode<int>>(kthNode::BinaryTreeNode<int>());
    root->size = 6;
    root->data = 3;
    root->left = make_unique<kthNode::BinaryTreeNode<int>>(kthNode::BinaryTreeNode<int>());
    root->left->size = 2;
    root->left->data = 2;
    root->left->left = make_unique<kthNode::BinaryTreeNode<int>>(kthNode::BinaryTreeNode<int>());
    root->left->left->size = 1;
    root->left->left->data = 1;
    root->right = make_unique<kthNode::BinaryTreeNode<int>>(kthNode::BinaryTreeNode<int>());
    root->right->size = 3;
    root->right->data = 5;
    root->right->left = make_unique<kthNode::BinaryTreeNode<int>>(kthNode::BinaryTreeNode<int>());
    root->right->left->size = 1;
    root->right->left->data = 4;
    root->right->right = make_unique<kthNode::BinaryTreeNode<int>>(kthNode::BinaryTreeNode<int>());
    root->right->right->size = 1;
    root->right->right->data = 6;
    // 0th node does not exist - leftmost node is node 1
    ASSERT_EQ(nullptr, FindKthNodeBinaryTree(root, 0));
    // should output 1
    ASSERT_EQ(FindKthNodeBinaryTree(root, 1)->data, 1);
    // should output 2
    ASSERT_EQ(FindKthNodeBinaryTree(root, 2)->data, 2);
    // should output 3
    ASSERT_EQ(FindKthNodeBinaryTree(root, 3)->data, 3);
    // should output 4
    ASSERT_EQ(FindKthNodeBinaryTree(root, 4)->data, 4);
    // should output 5
    ASSERT_EQ(FindKthNodeBinaryTree(root, 5)->data, 5);
    // should output 6
    ASSERT_EQ(FindKthNodeBinaryTree(root, 6)->data, 6);
    ASSERT_EQ(nullptr, FindKthNodeBinaryTree(root, 7));
}

TEST_F(BinaryTrees_Fixture, successor_Function) {
    //      3
    //    2   5
    //  1    4  6
    auto root = make_unique<btree_node_with_parent>(btree_with_parent::BinaryTreeNode<int>{3});
    root->parent = nullptr;
    ASSERT_EQ(successor::FindSuccessor(root), nullptr);
    root->left = make_unique<btree_node_with_parent>(btree_with_parent::BinaryTreeNode<int>{2});
    root->left->parent = root.get();
    ASSERT_EQ(successor::FindSuccessor(root->left)->data, 3);

    root->left->left = make_unique<btree_node_with_parent>(btree_with_parent::BinaryTreeNode<int>{1});
    root->left->left->parent = root->left.get();
    ASSERT_EQ(successor::FindSuccessor(root->left)->data, 3);
    ASSERT_EQ(successor::FindSuccessor(root->left->left)->data, 2);

    root->right = make_unique<btree_node_with_parent>(btree_with_parent::BinaryTreeNode<int>{5});
    root->right->parent = root.get();
    root->right->left =
            make_unique<btree_node_with_parent>(btree_with_parent::BinaryTreeNode<int>{4});
    root->right->left->parent = root->right.get();
    root->right->right =
            make_unique<btree_node_with_parent>(btree_with_parent::BinaryTreeNode<int>{6});
    root->right->right->parent = root->right.get();
    // should output 6
    auto* node = successor::FindSuccessor(root->right);
    ASSERT_EQ(6, node->data);
    // should output "null"
    node = successor::FindSuccessor(root->right->right);
    ASSERT_EQ(node, nullptr);
}

TEST_F(BinaryTrees_Fixture, inorder_with_parent_Function) {
    //      3
    unique_ptr<btree_node_with_parent> root = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{3, nullptr, nullptr});
    root->parent = nullptr;
    auto result = with_parent::InorderTraversal(root);
    vector<int> golden_res = {3};
    ASSERT_TRUE(equal(golden_res.begin(), golden_res.end(), result.begin(),
                 result.end()));

    //      3
    //    2
    //  1
    root->left = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{2, nullptr, nullptr});
    root->left->parent = root.get();
    root->left->left = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{1, nullptr, nullptr});
    root->left->left->parent = root->left.get();
    result = with_parent::InorderTraversal(root);
    golden_res = {1, 2, 3};
    ASSERT_TRUE(equal(golden_res.begin(), golden_res.end(), result.begin(),
                 result.end()));

    //      3
    //    2   5
    //  1    4 6
    root->right = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{5, nullptr, nullptr});
    root->right->parent = root.get();
    root->right->left = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{4, nullptr, nullptr});
    root->right->left->parent = root->right.get();
    root->right->right = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{6, nullptr, nullptr});
    root->right->right->parent = root->right.get();
    result = with_parent::InorderTraversal(root);
    golden_res = {1, 2, 3, 4, 5, 6};
    ASSERT_TRUE(equal(golden_res.begin(), golden_res.end(), result.begin(),
                 result.end()));
}

TEST_F(BinaryTrees_Fixture, preorder_traversal_with_parenet) {
    //      3
    unique_ptr<btree_node_with_parent> root = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{3, nullptr, nullptr});
    root->parent = nullptr;
    auto result = with_parent::PreorderTraversal(root);
    vector<int> golden_res = {3};
    ASSERT_TRUE(equal(golden_res.begin(), golden_res.end(), result.begin(),
                 result.end()));

    //      3
    //    2
    //  1
    root->left = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{2, nullptr, nullptr});
    root->left->parent = root.get();
    root->left->left = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{1, nullptr, nullptr});
    root->left->left->parent = root->left.get();
    result = with_parent::PreorderTraversal(root);
    golden_res = {3, 2, 1};
    ASSERT_TRUE(equal(golden_res.begin(), golden_res.end(), result.begin(),
                 result.end()));

    //      3
    //    2   5
    //  1    4 6
    root->right = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{5, nullptr, nullptr});
    root->right->parent = root.get();
    root->right->left = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{4, nullptr, nullptr});
    root->right->left->parent = root->right.get();
    root->right->right = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{6, nullptr, nullptr});
    root->right->right->parent = root->right.get();
    result = with_parent::PreorderTraversal(root);
    golden_res = {3, 2, 1, 5, 4, 6};
    ASSERT_TRUE(equal(golden_res.begin(), golden_res.end(), result.begin(),
                 result.end()));
}

TEST_F(BinaryTrees_Fixture, postorder_traversal_with_parenet) {
    //      3
    unique_ptr<btree_node_with_parent> root = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{3, nullptr, nullptr});
    root->parent = nullptr;
    auto result = with_parent::PostorderTraversal(root);
    vector<int> golden_res = {3};
    ASSERT_TRUE(equal(golden_res.begin(), golden_res.end(), result.begin(),
                 result.end()));

    //      3
    //    2
    //  1
    root->left = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{2, nullptr, nullptr});
    root->left->parent = root.get();
    root->left->left = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{1, nullptr, nullptr});
    root->left->left->parent = root->left.get();
    result = with_parent::PostorderTraversal(root);
    golden_res = {1, 2, 3};
    ASSERT_TRUE(equal(golden_res.begin(), golden_res.end(), result.begin(),
                 result.end()));

    //      3
    //    2   5
    //  1    4 6
    root->right = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{5, nullptr, nullptr});
    root->right->parent = root.get();
    root->right->left = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{4, nullptr, nullptr});
    root->right->left->parent = root->right.get();
    root->right->right = make_unique<btree_node_with_parent>(
            btree_with_parent::BinaryTreeNode<int>{6, nullptr, nullptr});
    root->right->right->parent = root->right.get();
    result = with_parent::PostorderTraversal(root);
    golden_res = {1, 2, 4, 6, 5, 3};
    ASSERT_TRUE(equal(golden_res.begin(), golden_res.end(), result.begin(),
                 result.end()));
}

TEST_F(BinaryTrees_Fixture, reconstruct_pre_inorder_Function) {
    auto res = BinaryTreeFromPreorderInorder({1}, {1});
    ASSERT_EQ(res->data, 1);

    res = BinaryTreeFromPreorderInorder({2, 1}, {1, 2});
    ASSERT_TRUE(res->data == 2 && res->left->data == 1 && res->right == nullptr);

    int N = 100;
    vector<int> inorder, preorder;
    for (int i = 0; i < N; ++i) {
        inorder.emplace_back(i);
        preorder.emplace_back((N - 1) - i);
    }

    res = BinaryTreeFromPreorderInorder(preorder, inorder);
    ASSERT_TRUE(res->data == N - 1 && res->left->data == N - 2 &&
           res->right == nullptr);

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<int> dis(1, 1000);
        int n = dis(gen);

        unique_ptr<btree::BinaryTreeNode<int>> root =
                generate_rand_binary_tree<int>(n, true);
        vector<int> pre = generate_preorder(root);
        vector<int> in = generate_inorder(root);
        auto res = BinaryTreeFromPreorderInorder(pre, in);
        ASSERT_TRUE(is_two_binary_trees_equal<int>(root, res));
        delete_binary_tree(&root);
        delete_binary_tree(&res);
    }
}

TEST_F(BinaryTrees_Fixture, reconstruct_preorder_with_null_Function) {
    int A[] = {1, 2, 3};
    vector<int*> preorder = {A, nullptr, nullptr};
    auto result = ReconstructPreorder(preorder);
    ASSERT_EQ(result->data, 1);
    ASSERT_EQ(result->left, nullptr);
    ASSERT_EQ(result->right, nullptr);

    preorder = {A, nullptr, A + 1, nullptr, nullptr};
    result = ReconstructPreorder(preorder);
    ASSERT_EQ(result->data, 1);
    ASSERT_EQ(result->left, nullptr);
    ASSERT_EQ(result->right->data, 2);

    preorder = {A, nullptr, A + 1, A + 2, nullptr, nullptr, nullptr};
    result = ReconstructPreorder(preorder);
    ASSERT_EQ(result->data, 1);
    ASSERT_EQ(result->left, nullptr);
    ASSERT_EQ(result->right->data, 2);
    ASSERT_EQ(result->right->left->data, 3);
    ASSERT_EQ(result->right->right, nullptr);

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    // Random test 1000 times.
    for (int times = 0; times < 100; ++times) {
        uniform_int_distribution<int> dis(1, 100);
        int n = dis(gen);

        unique_ptr<BinaryTreeNode<int>> root = generate_rand_binary_tree<int>(n);
        vector<int*> p;
        GenPreorderWithNull(root, &p);
        auto x = unique_ptr<BinaryTreeNode<int>>(ReconstructPreorder(p));
        ASSERT_TRUE(is_two_binary_trees_equal(root, x));
        delete_binary_tree(&root);
        delete_binary_tree(&x);
    }
}

TEST_F(BinaryTrees_Fixture, connect_leaves_Function) {
    //      3
    //    2   5
    //  1    4 6
    unique_ptr<btree_node> tree = make_unique<btree_node>(
            btree::BinaryTreeNode<int>{3, nullptr, nullptr});
    tree->left = make_unique<btree_node>(
            btree::BinaryTreeNode<int>{2, nullptr, nullptr});
    auto L = CreateListOfLeaves(tree);
    ASSERT_TRUE(L.size() == 1 && (*L.front())->data == 2);

    tree->left->left = make_unique<btree_node>(
            btree::BinaryTreeNode<int>{1, nullptr, nullptr});
    tree->right = make_unique<btree_node>(
            btree::BinaryTreeNode<int>{5, nullptr, nullptr});
    tree->right->left = make_unique<btree_node>(
            btree::BinaryTreeNode<int>{4, nullptr, nullptr});
    tree->right->right = make_unique<btree_node>(
            btree::BinaryTreeNode<int>{6, nullptr, nullptr});
    L = CreateListOfLeaves(tree);
    list<int> output;
    // should output 1, 4, 6
    for (const auto* l : L) {
        output.push_back((*l)->data);
        //cout << (*l)->data << endl;
    }
    list<int> golden_res = {1, 4, 6};
    ASSERT_TRUE(equal(output.begin(), output.end(), golden_res.begin(),
                 golden_res.end()));
}

TEST_F(BinaryTrees_Fixture, exterior_Function) {
    //        3
    //    2      5
    //      0    4 6
    //   -1 -2
    unique_ptr<btree_node> tree = make_unique<btree_node>(
            btree::BinaryTreeNode<int>{3, nullptr, nullptr});
    auto L = ExteriorBinaryTree(tree);
    list<int> result = CreateOutputList(L);
    list<int> golden_result = {3};
    ASSERT_TRUE(equal(result.begin(), result.end(), golden_result.begin(),
                 golden_result.end()));

    tree->left = make_unique<btree_node>(
            btree::BinaryTreeNode<int>{2, nullptr, nullptr});
    L = ExteriorBinaryTree(tree);
    result = CreateOutputList(L);
    golden_result = {3, 2};
    ASSERT_TRUE(equal(result.begin(), result.end(), golden_result.begin(),
                 golden_result.end()));

    tree->left->right = make_unique<btree_node>(
            btree::BinaryTreeNode<int>{0, nullptr, nullptr});
    tree->left->right->left = make_unique<BinaryTreeNode<int>>(
            btree::BinaryTreeNode<int>{-1, nullptr, nullptr});
    tree->left->right->right = make_unique<BinaryTreeNode<int>>(
            btree::BinaryTreeNode<int>{-2, nullptr, nullptr});
    tree->right = make_unique<BinaryTreeNode<int>>(
            btree::BinaryTreeNode<int>{5, nullptr, nullptr});
    tree->right->left = make_unique<BinaryTreeNode<int>>(
            btree::BinaryTreeNode<int>{4, nullptr, nullptr});
    tree->right->right = make_unique<BinaryTreeNode<int>>(
            btree::BinaryTreeNode<int>{6, nullptr, nullptr});
    L = ExteriorBinaryTree(tree);
    result = CreateOutputList(L);
    golden_result = {3, 2, 0, -1, -2, 4, 6, 5};
    ASSERT_TRUE(equal(result.begin(), result.end(), golden_result.begin(),
                 golden_result.end()));
}

TEST_F(BinaryTrees_Fixture, next_right_perfect_btree_Function) {
    //      3
    //    2   5
    unique_ptr<right_sibling::BinaryTreeNode<int>> root = make_unique<right_sibling::BinaryTreeNode<int>>(
            right_sibling::BinaryTreeNode<int>{3, nullptr, nullptr, nullptr});
    root->left = make_unique<right_sibling::BinaryTreeNode<int>>(
            right_sibling::BinaryTreeNode<int>{2, nullptr, nullptr, nullptr});
    root->right = make_unique<right_sibling::BinaryTreeNode<int>>(
            right_sibling::BinaryTreeNode<int>{5, nullptr, nullptr, nullptr});
    right_sibling::ConstructRightSibling(root.get());
    ASSERT_EQ(root->next, nullptr);
    ASSERT_EQ(root->left->next, root->right.get());
    ASSERT_EQ(root->right->next, nullptr);

    //      3
    //    2   5
    //  1  7 4 6
    root = make_unique<right_sibling::BinaryTreeNode<int>>(
            right_sibling::BinaryTreeNode<int>{3, nullptr, nullptr, nullptr});
    root->left = make_unique<right_sibling::BinaryTreeNode<int>>(
            right_sibling::BinaryTreeNode<int>{2, nullptr, nullptr, nullptr});
    root->left->right = make_unique<right_sibling::BinaryTreeNode<int>>(
            right_sibling::BinaryTreeNode<int>{7, nullptr, nullptr, nullptr});
    root->left->left = make_unique<right_sibling::BinaryTreeNode<int>>(
            right_sibling::BinaryTreeNode<int>{1, nullptr, nullptr, nullptr});
    root->right = make_unique<right_sibling::BinaryTreeNode<int>>(
            right_sibling::BinaryTreeNode<int>{5, nullptr, nullptr, nullptr});
    root->right->left = make_unique<right_sibling::BinaryTreeNode<int>>(
            right_sibling::BinaryTreeNode<int>{4, nullptr, nullptr, nullptr});
    root->right->right = make_unique<right_sibling::BinaryTreeNode<int>>(
            right_sibling::BinaryTreeNode<int>{6, nullptr, nullptr, nullptr});
    right_sibling::ConstructRightSibling(root.get());
    ASSERT_EQ(root->next, nullptr);
    ASSERT_EQ(root->left->next, root->right.get());
    ASSERT_EQ(root->left->left->next, root->left->right.get());
    ASSERT_EQ(root->left->right->next, root->right->left.get());
    ASSERT_EQ(root->right->left->next, root->right->right.get());
}

TEST_F(BinaryTrees_Fixture, next_right_any_btree_Function) {
    //      3
    //    2    5
    //       4   6
    //        8 9
    unique_ptr<right_any_btree::BinaryTreeNode<int>> root = make_unique<right_any_btree::BinaryTreeNode<int>>(
            right_any_btree::BinaryTreeNode<int>{3, nullptr, nullptr, nullptr});
    root->left = make_unique<right_any_btree::BinaryTreeNode<int>>(
            right_any_btree::BinaryTreeNode<int>{2, nullptr, nullptr, nullptr});
    root->right = make_unique<right_any_btree::BinaryTreeNode<int>>(
            right_any_btree::BinaryTreeNode<int>{5, nullptr, nullptr, nullptr});
    root->right->left = make_unique<right_any_btree::BinaryTreeNode<int>>(
            right_any_btree::BinaryTreeNode<int>{4, nullptr, nullptr, nullptr});
    root->right->left->right = make_unique<right_any_btree::BinaryTreeNode<int>>(
            right_any_btree::BinaryTreeNode<int>{8, nullptr, nullptr, nullptr});
    root->right->right = make_unique<right_any_btree::BinaryTreeNode<int>>(
            right_any_btree::BinaryTreeNode<int>{6, nullptr, nullptr, nullptr});
    root->right->right->left = make_unique<right_any_btree::BinaryTreeNode<int>>(
            right_any_btree::BinaryTreeNode<int>{9, nullptr, nullptr, nullptr});
    right_any_btree::populate_next_pointer(root.get());
    ASSERT_EQ(root->next, nullptr);
    ASSERT_EQ(root->left->next, root->right.get());
    ASSERT_EQ(root->right->left->next, root->right->right.get());
    ASSERT_EQ(root->right->left->right->next, root->right->right->left.get());
}

TEST_F(BinaryTrees_Fixture, lock_btree_Function) {
    //      *
    //    *   *
    //   * *
    auto root = make_shared<lock_tree::BinaryTreeNode>(lock_tree::BinaryTreeNode());
    root->left() = make_shared<lock_tree::BinaryTreeNode>(lock_tree::BinaryTreeNode());
    root->left()->parent() = root;
    root->right() = make_shared<lock_tree::BinaryTreeNode>(lock_tree::BinaryTreeNode());
    root->right()->parent() = root;
    root->left()->left() = make_shared<lock_tree::BinaryTreeNode>(lock_tree::BinaryTreeNode());
    root->left()->left()->parent() = root->left();
    root->left()->right() = make_shared<lock_tree::BinaryTreeNode>(lock_tree::BinaryTreeNode());
    root->left()->right()->parent() = root->left();

    ASSERT_FALSE(root->IsLocked());

    ASSERT_TRUE(root->Lock());
    ASSERT_TRUE(root->IsLocked());

    ASSERT_FALSE(root->left()->Lock());
    ASSERT_FALSE(root->left()->IsLocked());
    ASSERT_FALSE(root->right()->Lock());
    ASSERT_FALSE(root->right()->IsLocked());
    ASSERT_FALSE(root->left()->left()->Lock());
    ASSERT_FALSE(root->left()->left()->IsLocked());
    ASSERT_FALSE(root->left()->right()->Lock());
    ASSERT_FALSE(root->left()->right()->IsLocked());

    root->Unlock();
    ASSERT_TRUE(root->left()->Lock());
    ASSERT_FALSE(root->Lock());
    ASSERT_FALSE(root->left()->left()->Lock());
    ASSERT_FALSE(root->IsLocked());

    ASSERT_TRUE(root->right()->Lock());
    ASSERT_TRUE(root->right()->IsLocked());
}
