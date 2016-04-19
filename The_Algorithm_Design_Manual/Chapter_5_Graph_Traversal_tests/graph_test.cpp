#include <gtest/gtest.h>
#include "graph_skeina.h"
#include "Vector.h"
#include "List.h"


class GraphAlgorithmFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    enum {DIRECTED=1, UNDIRECTED=0};

public:
    GraphAlgorithmFixture() : Test() {

    }

    virtual ~GraphAlgorithmFixture() {

    }
};

TEST_F(GraphAlgorithmFixture, graph_init_Function) {
    graph_skeina graph_test{6, UNDIRECTED};   // C++11 constructor {} syntax
    graph_test.insert_edges(1, 2);
    graph_test.insert_edges(1, 5);
    graph_test.insert_edges(1, 6);
    graph_test.insert_edges(2, 5);
    graph_test.insert_edges(2, 3);
    graph_test.insert_edges(3, 4);
    graph_test.insert_edges(4, 5);
    graph_test.print_graph();
}

TEST_F(GraphAlgorithmFixture, Vector_Function) {
    Vector<int> aV;
    ASSERT_EQ(0, aV.size());
    ASSERT_EQ(2, aV.capacity());
    aV.push_back(1);
    ASSERT_EQ(1, aV.size());
    ASSERT_EQ(1, aV.back());
    int tmpa = 2;
    aV.push_back(tmpa);
    ASSERT_EQ(2, aV.back());
    ASSERT_EQ(1, aV[0]);
    aV.pop_back();
    ASSERT_EQ(1, aV.back());
    aV.resize(10);
    ASSERT_EQ(10, aV.size());
    ASSERT_EQ(1, aV[0]);
    aV.push_back(11);
    aV[3]=4;
    ASSERT_EQ(11, aV[10]);
    Vector<int> bV;
    bV.push_back(10);
    bV.push_back(11);
    bV.push_back(12);
    aV = bV;
    int j=10;
    for (Vector<int>::iterator i = aV.begin(); i != aV.end(); i++, j++) {
        ASSERT_EQ(j, *i);
    }
}

TEST_F(GraphAlgorithmFixture, List_Function) {
    List<int> aL;
    ASSERT_EQ(0, aL.size());
    aL.push_back(1);
    aL.push_back(2);
    int j=1;
    for(List<int>::iterator i = aL.begin(); i != aL.end(); i++, j++) {
        ASSERT_EQ(j, *i);
    }

    aL.push_front(0);
    j=0;
    for(List<int>::iterator i = aL.begin(); i != aL.end(); i++, j++) {
        ASSERT_EQ(j, *i);
    }
    ASSERT_EQ(3, aL.size());
    ASSERT_EQ(2, aL.back());
    ASSERT_EQ(0, aL.front());
    ASSERT_FALSE(aL.empty());

    aL.erase(aL.begin());
    j=1;
    for(List<int>::iterator i = aL.begin(); i != aL.end(); i++, j++) {
        ASSERT_EQ(j, *i);
    }

    List<int> bL;
    bL.push_back(11);
    bL.push_back(12);
    bL.push_back(13);
    bL.push_back(14);
    aL = bL;
    j=11;
    for(List<int>::iterator i = aL.begin(); i != aL.end(); i++, j++) {
        ASSERT_EQ(j, *i);
    }

}
