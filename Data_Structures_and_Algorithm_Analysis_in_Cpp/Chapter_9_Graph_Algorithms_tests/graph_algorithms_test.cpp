#include <gtest/gtest.h>
#include "Graph.h"

class GraphAlgorithmsFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    Graph g;

public:
    GraphAlgorithmsFixture() : Test() {

    }

    virtual ~GraphAlgorithmsFixture() {
    }
};

TEST_F(GraphAlgorithmsFixture, topological_sort_Function) {
    // See Fig 9.4 p401
    g.addEdge("1", "2");
    g.addEdge("1", "3");
    g.addEdge("1", "4");
    g.addEdge("2", "4");
    g.addEdge("2", "5");
    g.addEdge("3", "6");
    g.addEdge("4", "3");
    g.addEdge("4", "6");
    g.addEdge("4", "7");
    g.addEdge("5", "4");
    g.addEdge("5", "7");
    g.addEdge("7", "6");
    ASSERT_EQ(7, g.get_num_vertices());
    ASSERT_EQ(0, g.get_indegree("1"));
    ASSERT_EQ(3, g.get_outdegree("1"));
    ASSERT_EQ(1, g.get_indegree("2"));
    ASSERT_EQ(2, g.get_outdegree("2"));

    g.topsort();
    ASSERT_EQ(1, g.get_topological_order("1"));
    ASSERT_EQ(2, g.get_topological_order("2"));
    ASSERT_EQ(3, g.get_topological_order("5"));
    ASSERT_EQ(4, g.get_topological_order("4"));
    ASSERT_EQ(5, g.get_topological_order("3"));
    ASSERT_EQ(6, g.get_topological_order("7"));
    ASSERT_EQ(7, g.get_topological_order("6"));

    ASSERT_EQ(0, g.get_indegree("1"));
    ASSERT_EQ(1, g.get_indegree("2"));
    ASSERT_EQ(2, g.get_indegree("3"));
    ASSERT_EQ(3, g.get_indegree("4"));
    ASSERT_EQ(1, g.get_indegree("5"));
    ASSERT_EQ(3, g.get_indegree("6"));
    ASSERT_EQ(2, g.get_indegree("7"));
}

TEST_F(GraphAlgorithmsFixture, Unweighted_Shortest_Paths_Function) {
    // see Fig 9.10 p406
    g.addEdge("1", "2");
    g.addEdge("1", "4");
    g.addEdge("2", "4");
    g.addEdge("2", "5");
    g.addEdge("3", "1");
    g.addEdge("3", "6");
    g.addEdge("4", "3");
    g.addEdge("4", "5");
    g.addEdge("4", "6");
    g.addEdge("4", "7");
    g.addEdge("5", "7");
    g.addEdge("7", "6");

    g.unweighted("3");

    ASSERT_EQ(1, g.get_distance("1"));
    ASSERT_EQ(2, g.get_distance("2"));
    ASSERT_EQ(0, g.get_distance("3"));
    ASSERT_EQ(2, g.get_distance("4"));
    ASSERT_EQ(3, g.get_distance("5"));
    ASSERT_EQ(1, g.get_distance("6"));
    ASSERT_EQ(3, g.get_distance("7"));

    ASSERT_STREQ("3", g.get_prev_node("1").c_str());
    ASSERT_STREQ("1", g.get_prev_node("2").c_str());
    ASSERT_STREQ("1", g.get_prev_node("4").c_str());
    ASSERT_STREQ("2", g.get_prev_node("5").c_str());
    ASSERT_STREQ("3", g.get_prev_node("6").c_str());
    ASSERT_STREQ("4", g.get_prev_node("7").c_str());
}

TEST_F(GraphAlgorithmsFixture, Dijkstra_Function) {
    // see Fig 9.20 p406
    g.addEdge("1", "2", 2);
    g.addEdge("1", "4", 1);
    g.addEdge("2", "4", 3);
    g.addEdge("2", "5", 10);
    g.addEdge("3", "1", 4);
    g.addEdge("3", "6", 5);
    g.addEdge("4", "3", 2);
    g.addEdge("4", "5", 2);
    g.addEdge("4", "6", 8);
    g.addEdge("4", "7", 4);
    g.addEdge("5", "7", 6);
    g.addEdge("7", "6", 1);

    g.dijkstra("1");

    ASSERT_EQ(0, g.get_distance("1"));
    ASSERT_EQ(2, g.get_distance("2"));
    ASSERT_EQ(3, g.get_distance("3"));
    ASSERT_EQ(1, g.get_distance("4"));
    ASSERT_EQ(3, g.get_distance("5"));
    ASSERT_EQ(6, g.get_distance("6"));
    ASSERT_EQ(5, g.get_distance("7"));

    ASSERT_STREQ("1", g.get_prev_node("2").c_str());
    ASSERT_STREQ("4", g.get_prev_node("3").c_str());
    ASSERT_STREQ("1", g.get_prev_node("4").c_str());
    ASSERT_STREQ("4", g.get_prev_node("5").c_str());
    ASSERT_STREQ("7", g.get_prev_node("6").c_str());
    ASSERT_STREQ("4", g.get_prev_node("7").c_str());
}

TEST_F(GraphAlgorithmsFixture, Dijkstra_with_pairing_heap_Function) {
    // see Fig 9.20 p412
    g.addEdge("1", "2", 2);
    g.addEdge("1", "4", 1);
    g.addEdge("2", "4", 3);
    g.addEdge("2", "5", 10);
    g.addEdge("3", "1", 4);
    g.addEdge("3", "6", 5);
    g.addEdge("4", "3", 2);
    g.addEdge("4", "5", 2);
    g.addEdge("4", "6", 8);
    g.addEdge("4", "7", 4);
    g.addEdge("5", "7", 6);
    g.addEdge("7", "6", 1);

    g.dijkstra_with_pairing_heap("1");

    ASSERT_EQ(0, g.get_distance("1"));
    ASSERT_EQ(2, g.get_distance("2"));
    ASSERT_EQ(3, g.get_distance("3"));
    ASSERT_EQ(1, g.get_distance("4"));
    ASSERT_EQ(3, g.get_distance("5"));
    ASSERT_EQ(6, g.get_distance("6"));
    ASSERT_EQ(5, g.get_distance("7"));

    ASSERT_STREQ("1", g.get_prev_node("2").c_str());
    ASSERT_STREQ("4", g.get_prev_node("3").c_str());
    ASSERT_STREQ("1", g.get_prev_node("4").c_str());
    ASSERT_STREQ("4", g.get_prev_node("5").c_str());
    ASSERT_STREQ("7", g.get_prev_node("6").c_str());
    ASSERT_STREQ("4", g.get_prev_node("7").c_str());
}

TEST_F(GraphAlgorithmsFixture, negative_weighted_Function) {
    // see Fig 24.4 p589 in CLR
    g.addEdge("s", "t", 6);
    g.addEdge("s", "y", 7);
    g.addEdge("t", "x", 5);
    g.addEdge("t", "z", -4);
    g.addEdge("t", "y", 8);
    g.addEdge("x", "t", -2);
    g.addEdge("z", "x", 7);
    g.addEdge("z", "s", 2);
    g.addEdge("y", "x", -3);
    g.addEdge("y", "z", 9);

    g.negative("s");

    ASSERT_EQ(0, g.get_distance("s"));
    ASSERT_EQ(2, g.get_distance("t"));
    ASSERT_EQ(4, g.get_distance("x"));
    ASSERT_EQ(-2, g.get_distance("z"));
    ASSERT_EQ(7, g.get_distance("y"));

    ASSERT_STREQ("s", g.get_prev_node("y").c_str());
    ASSERT_STREQ("y", g.get_prev_node("x").c_str());
    ASSERT_STREQ("x", g.get_prev_node("t").c_str());
    ASSERT_STREQ("t", g.get_prev_node("z").c_str());
}

TEST_F(GraphAlgorithmsFixture, acyclic_Function) {
    // see Fig 24.5 p593 in CLR
    g.addEdge("r", "s", 5);
    g.addEdge("r", "t", 3);
    g.addEdge("s", "t", 2);
    g.addEdge("s", "x", 6);
    g.addEdge("t", "x", 7);
    g.addEdge("t", "y", 4);
    g.addEdge("t", "z", 2);
    g.addEdge("x", "y", -1);
    g.addEdge("x", "z", 1);
    g.addEdge("y", "z", -2);

    g.acyclic("s");

    // > 100000, INFINITY == INFINITY have some error.
    ASSERT_LT(100000, g.get_distance("r"));
    ASSERT_EQ(0, g.get_distance("s"));
    ASSERT_EQ(2, g.get_distance("t"));
    ASSERT_EQ(6, g.get_distance("x"));
    ASSERT_EQ(5, g.get_distance("y"));
    ASSERT_EQ(3, g.get_distance("z"));

    ASSERT_STREQ("s", g.get_prev_node("t").c_str());
    ASSERT_STREQ("s", g.get_prev_node("x").c_str());
    ASSERT_STREQ("x", g.get_prev_node("y").c_str());
    ASSERT_STREQ("y", g.get_prev_node("z").c_str());
}

TEST_F(GraphAlgorithmsFixture, acyclic_for_scheduling_problem) {
    // see Fig 9.34 p420
    // to get longest path, we change weight to nagative.
    g.addEdge("1", "2", -3);
    g.addEdge("1", "3", -2);
    g.addEdge("2", "4", -3);
    g.addEdge("2", "6'", 0);
    g.addEdge("3", "6'", 0);
    g.addEdge("3", "5", -1);
    g.addEdge("4", "7'", 0);
    g.addEdge("5", "8'", 0);
    g.addEdge("5", "9", -4);
    g.addEdge("6", "7'", 0);
    g.addEdge("6", "8'", 0);
    g.addEdge("6'", "6", -2);
    g.addEdge("7", "10'", 0);
    g.addEdge("7'", "7", -3);
    g.addEdge("8", "10'", 0);
    g.addEdge("8'", "8", -2);
    g.addEdge("9", "10'", 0);
    g.addEdge("10'", "10", -1);

    g.acyclic("1");

    ASSERT_EQ(0, g.get_distance("1"));
    ASSERT_EQ(-3, g.get_distance("2"));
    ASSERT_EQ(-2, g.get_distance("3"));
    ASSERT_EQ(-3, g.get_distance("6'"));
    ASSERT_EQ(-6, g.get_distance("4"));
    ASSERT_EQ(-5, g.get_distance("6"));
    ASSERT_EQ(-3, g.get_distance("5"));
    ASSERT_EQ(-6, g.get_distance("7'"));
    ASSERT_EQ(-9, g.get_distance("7"));
    ASSERT_EQ(-7, g.get_distance("8"));
    ASSERT_EQ(-5, g.get_distance("8'"));
    ASSERT_EQ(-7, g.get_distance("9"));
    ASSERT_EQ(-9, g.get_distance("10'"));
    ASSERT_EQ(-10, g.get_distance("10"));

    ASSERT_STREQ("1", g.get_prev_node("2").c_str());
    ASSERT_STREQ("2", g.get_prev_node("6'").c_str());
    ASSERT_STREQ("1", g.get_prev_node("3").c_str());
    ASSERT_STREQ("2", g.get_prev_node("4").c_str());
    ASSERT_STREQ("6'", g.get_prev_node("6").c_str());
    ASSERT_STREQ("3", g.get_prev_node("5").c_str());
    ASSERT_STREQ("4", g.get_prev_node("7'").c_str());
    ASSERT_STREQ("6", g.get_prev_node("8'").c_str());
    ASSERT_STREQ("7'", g.get_prev_node("7").c_str());
    ASSERT_STREQ("8'", g.get_prev_node("8").c_str());
    ASSERT_STREQ("5", g.get_prev_node("9").c_str());
    ASSERT_STREQ("7", g.get_prev_node("10'").c_str());
    ASSERT_STREQ("10'", g.get_prev_node("10").c_str());
}
