#include <gtest/gtest.h>
#include "AvlTree.h"
#include "BinarySearchTree.h"

class TreeAlgorithmFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    int NUMS = 400000;
    const int GAP  =   3711;

    BinarySearchTree<int> bintree;
    BinarySearchTree<int> bintree2;
    AvlTree<int> avltree;
    AvlTree<int> avltree2;

public:
    TreeAlgorithmFixture() : Test() {

    }

    virtual ~TreeAlgorithmFixture() {
        bintree.makeEmpty();
        bintree2.makeEmpty();
        avltree.makeEmpty();
        avltree2.makeEmpty();
    }
};

TEST_F(TreeAlgorithmFixture, binary_tree_Function) {
    int i;

    for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        bintree.insert( i );

    for( i = 1; i < NUMS; i+= 2 )
        bintree.remove( i );

    ASSERT_EQ(2, bintree.findMin());
    ASSERT_EQ(NUMS-2, bintree.findMax());

    for( i = 2; i < NUMS; i+=2 )
        ASSERT_TRUE( bintree.contains(i) );

    for( i = 1; i < NUMS; i+=2 )
        ASSERT_FALSE( bintree.contains(i) );

    bintree2 = bintree;

    for( i = 2; i < NUMS; i+=2 )
        ASSERT_TRUE( bintree2.contains(i) );

    for( i = 1; i < NUMS; i+=2 )
        ASSERT_FALSE( bintree2.contains(i) );
}

TEST_F(TreeAlgorithmFixture, avl_tree_Function) {
    int i;

    for (i = GAP; i != 0; i = (i + GAP) % NUMS)
        avltree.insert(i);

    avltree.remove(0);

    for (i = 1; i < NUMS; i += 2)
        avltree.remove(i);

    ASSERT_EQ(2, avltree.findMin());
    ASSERT_EQ(NUMS - 2, avltree.findMax());

    for (i = 2; i < NUMS; i += 2)
        ASSERT_TRUE(avltree.contains(i));

    for (i = 1; i < NUMS; i += 2) {
        ASSERT_FALSE(avltree.contains(i));
    }

    // Copy Tree test
    avltree2 = avltree;

    for( i = 2; i < NUMS; i += 2 )
        ASSERT_TRUE(avltree2.contains(i));

    for( i = 1; i < NUMS; i += 2 ) {
        ASSERT_FALSE(avltree2.contains(i));
    }

}
