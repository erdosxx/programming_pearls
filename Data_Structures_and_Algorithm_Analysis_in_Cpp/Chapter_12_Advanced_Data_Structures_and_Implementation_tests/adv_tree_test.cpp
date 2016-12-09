#include <gtest/gtest.h>
#include <vector>
#include "SplayTree.h"
#include "RedBlackTree.h"
#include "Treap.h"
#include "PairingHeap.h"
#include "Vector.h"
#include "SuffixArray.h"

using std::vector;

class Adv_Tree_Algorithm_Fixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    int NUMS = 40000;
    const int GAP  =   3711;

    SplayTree<int> stree;
    SplayTree<int> stree2;

    const int NEG_INF = -9999;
    RedBlackTree<int> rb1{ NEG_INF };
    int NUMS_RB = 400000;
    const int GAP_RB  =   37;

    RedBlackTree<int> rb2{ NEG_INF };

    Treap<int> tr;
    int NUMS_TR = 400000;
    const int GAP_TR  =   37;
    Treap<int> tr2;

    PairingHeap<int> ph;
    const int numItems_ph = 40000;

public:
    Adv_Tree_Algorithm_Fixture() : Test() {

    }

    virtual ~Adv_Tree_Algorithm_Fixture() {
        stree.makeEmpty();
        stree2.makeEmpty();
        rb1.makeEmpty();
        rb2.makeEmpty();
        tr.makeEmpty();
        tr2.makeEmpty();
    }
};

TEST_F(Adv_Tree_Algorithm_Fixture, Splay_tree_Function) {
    int i;

    for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        stree.insert( i );

    for( i = 1; i < NUMS; i+= 2 )
        stree.remove( i );

    ASSERT_EQ(2, stree.findMin());
    ASSERT_EQ(NUMS-2, stree.findMax());

    for( i = 2; i < NUMS; i+=2 )
        ASSERT_TRUE( stree.contains(i) );

    for( i = 1; i < NUMS; i+=2 )
        ASSERT_FALSE( stree.contains(i) );

    stree2 = stree;

    for( i = 2; i < NUMS; i+=2 )
        ASSERT_TRUE( stree2.contains(i) );

    for( i = 1; i < NUMS; i+=2 )
        ASSERT_FALSE( stree2.contains(i) );
}

TEST_F(Adv_Tree_Algorithm_Fixture, Red_Black_tree_Function) {
    for(int i = GAP_RB; i != 0; i = ( i + GAP_RB ) % NUMS_RB )
        rb1.insert( i );

    ASSERT_EQ(1, rb1.findMin());
    ASSERT_EQ(NUMS_RB-1, rb1.findMax());

    for(int i = 1; i < NUMS_RB; ++i )
        ASSERT_TRUE(rb1.contains(i));

    ASSERT_FALSE(rb1.contains(0));

    rb2 = rb1;

    for(int i = 1; i < NUMS_RB; ++i )
        ASSERT_TRUE(rb2.contains(i));

    ASSERT_FALSE(rb2.contains(0));
}

TEST_F(Adv_Tree_Algorithm_Fixture, Treap_Function) {
    for(int i = GAP_TR; i != 0; i = ( i + GAP_TR ) % NUMS_TR )
        tr.insert( i );
    for(int i = 1; i < NUMS_TR; i += 2 )
        tr.remove( i );

    ASSERT_EQ(2, tr.findMin());
    ASSERT_EQ(NUMS_TR-2, tr.findMax());

    for(int i = 2; i < NUMS_TR; i += 2 )
        ASSERT_TRUE(tr.contains(i));

    for(int i = 1; i < NUMS_TR; i += 2 )
        ASSERT_FALSE(tr.contains(i));

    tr2 = tr;

    for(int i = 2; i < NUMS_TR; i += 2 )
        ASSERT_TRUE(tr2.contains(i));

    for(int i = 1; i < NUMS_TR; i += 2 )
        ASSERT_FALSE(tr2.contains(i));
}

TEST_F(Adv_Tree_Algorithm_Fixture, Pairing_Heap_Function) {
    int i = 37;

    for( i = 37; i != 0; i = ( i + 37 ) % numItems_ph )
        ph.insert( i );

    for( i = 1; i < numItems_ph; ++i ) {
        int x;
        ph.deleteMin( x );
        ASSERT_EQ(x, i);
    }

    int j;
    Vector<PairingHeap<int>::Position> p( numItems_ph );
    for( i = 0, j = numItems_ph / 2; i < numItems_ph; ++i, j =(j+71)%numItems_ph )
        p[j] = ph.insert(j + numItems_ph );

    for( i = 0, j = numItems_ph / 2; i < numItems_ph; ++i, j =(j+53)%numItems_ph )
        ph.decreaseKey( p[j], j );

    i = -1;

    PairingHeap<int> ph2;

    ph2 = ph;
    while( !ph2.isEmpty() ) {
        int x;
        ph2.deleteMin( x );
        ASSERT_EQ(x, ++i);
    }
}

TEST_F(Adv_Tree_Algorithm_Fixture, suffix_array) {
    pair<int, int> a(1,1);
    pair<int, int> b(1,1);
    pair<int, int> c(1,2);
    ASSERT_EQ(a, b);
    ASSERT_NE(a, c);

    string str = "banana";
    vector<int> sufary(str.size());
    vector<int> lcp(str.size());

    createSuffixArraySlow(str, &sufary, &lcp);
    vector<int> golden_sufary = {5,3,1,0,4,2};
    vector<int> golden_lcp = {0,1,3,0,0,2};

    ASSERT_TRUE(equal(sufary.cbegin(), sufary.cend(), golden_sufary.cbegin(), golden_sufary.cend()));
    ASSERT_TRUE(equal(lcp.begin(), lcp.end(), golden_lcp.cbegin(), golden_lcp.cend()));

    vector<pair<int, int>> result = move(createSuffixArray_erdos(str));

    vector<pair<int, int>> golden_result = {{5,0}, {3,1}, {1,3}, {0,0}, {4,0}, {2,2}};
    ASSERT_TRUE(equal(result.cbegin(), result.cend(), golden_result.cbegin(), golden_result.cend()));
}
