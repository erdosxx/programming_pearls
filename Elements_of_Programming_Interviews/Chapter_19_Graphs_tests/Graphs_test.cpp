#include <gtest/gtest.h>
#include <random>
#include <limits>
#include <unordered_set>
#include <cmath>
#include <string>
#include <bitset>
#include <deque>
#include "team_reachability.h"
#include "Search_maze.h"
#include "Painting_iterative.h"
#include "surrounded-regions.h"
#include "2-exists.h"
#include "clone-graph.h"
#include "Wiring_circuit_board.h"
#include "Transform_string_to_other.h"
#include "Team_photo_2.h"
#include "Shortest_path_fewest_edges.h"

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
using std::min;
using std::cout;
using std::endl;
using std::ostream_iterator;
using std::to_string;
using std::bitset;
using std::boolalpha;
using std::deque;
using std::string;

class Ch19_Graphs_Fixture : public ::testing::Test {
private:

protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    void p_19_0_Check(const vector<MatchResult>& matches, const string& team_a, const string& team_b);
    bool p_19_4_CheckAnswer(vector<GraphVertex>* G);
    void TestDirectedCycle();
    void TestDirectedStarTree();
    void TestDirectedLineTree();
    void TestDirectedBinaryTree();
    void TestDirectedTwoSeparateCycles();

    void CheckGraph(p_19_5::GraphVertex* node, const vector<p_19_5::GraphVertex>& G);

    string p_19_7_RandString(int len);

public:
    Ch19_Graphs_Fixture() : Test() {

    }

    virtual ~Ch19_Graphs_Fixture() {
    }
};

string Ch19_Graphs_Fixture::p_19_7_RandString(int len) {
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis('a', 'z');
    string ret;
    while (len--) {
        ret += dis(gen);
    }
    return ret;
}

void Ch19_Graphs_Fixture::CheckGraph(p_19_5::GraphVertex* node, const vector<p_19_5::GraphVertex>& G) {
    unordered_set<p_19_5::GraphVertex*> vertex_set;
    queue<p_19_5::GraphVertex*> q;
    q.emplace(node);
    vertex_set.emplace(node);

    while (!q.empty()) {
        auto vertex = q.front();
        q.pop();

        ASSERT_TRUE(vertex->label < G.size());
        vector<int> label1 = p_19_5::CopyLabels(vertex->edges);
        vector<int> label2 = p_19_5::CopyLabels(G[vertex->label].edges);

        sort(label1.begin(), label1.end());
        sort(label2.begin(), label2.end());
        ASSERT_TRUE(equal(label1.begin(), label1.end(), label2.begin(), label2.end()));

        for (p_19_5::GraphVertex* e : vertex->edges) {
            if (vertex_set.find(e) == vertex_set.end()) {
                vertex_set.emplace(e);
                q.emplace(e);
            }
        }
    }
}

// O(n^2) check answer.
bool Ch19_Graphs_Fixture::p_19_4_CheckAnswer(vector<GraphVertex>* G) {
    // marks all vertices as white.
    for (GraphVertex& n : *G) {
        n.color = GraphVertex::undiscovered;
    }

    for (GraphVertex& g : *G) {
        if (HasCycleExclusion(&g, nullptr)) {
            return true;
        }
        // Reset color to undiscovered.
        for (GraphVertex& n : *G) {
            n.color = GraphVertex::undiscovered;
        }
    }
    return false;
}

void Ch19_Graphs_Fixture::p_19_0_Check(const vector<MatchResult>& matches, const string& team_a,
           const string& team_b) {
    ASSERT_EQ(CanTeamABeatTeamB(matches, team_a, team_b),
           IsReachableBFS(BuildGraph(matches), team_a, team_b,
                          make_unique<unordered_set<string>>().get()));
}

TEST_F(Ch19_Graphs_Fixture, team_reachability_Function) {
    vector<MatchResult> matches = {{"Texas", "Cal"},      {"Cal", "Stanford"},
                                   {"Stanford", "Texas"}, {"Stanford", "MIT"},
                                   {"Stanford", "CIT"},   {"UCLA", "USC"}};
    p_19_0_Check(matches, "Texas", "MIT");
    p_19_0_Check(matches, "Cal", "UCLA");
}

TEST_F(Ch19_Graphs_Fixture, search_maze_Function) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 1000; ++times) {
        uniform_int_distribution<int> dis(1, 30);
        int n = dis(gen);
        int m = dis(gen);

        vector<vector<Color>> maze(n, vector<Color>(m));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                uniform_int_distribution<int> zero_or_one(0, 1);
                maze[i][j] = zero_or_one(gen) ? WHITE : BLACK;
            }
        }

        vector<Coordinate> white;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (maze[i][j] == WHITE) {
                    white.emplace_back(Coordinate{i, j});
                }
                // cout << maze[i][j] << ' ';
            }
            // cout << endl;
        }
        // cout << endl;

        if (white.size()) {
            uniform_int_distribution<int> dis(0, white.size() - 1);
            int start = dis(gen);
            int end = dis(gen);
            // cout << white[start].x << ' ' << white[start].y << endl;
            // cout << white[end].x << ' ' << white[end].y << endl;
            vector<Coordinate> path = SearchMaze(maze, white[start], white[end]);
            if (!path.empty()) {
                ASSERT_TRUE(white[start] == path.front() && white[end] == path.back());
            }
            for (int i = 0; i < path.size(); ++i) {
                if (i > 0) {
                    ASSERT_EQ(abs(path[i - 1].x - path[i].x) +
                           abs(path[i - 1].y - path[i].y),
                           1);
                }
                // cout << '(' << path[i].x << ',' << path[i].y << ')' << endl;
            }
        }
    }
}

TEST_F(Ch19_Graphs_Fixture, painting_iterative_Function) {
    default_random_engine gen((random_device())());

    uniform_int_distribution<size_t> dis(1, 100);
    size_t n = dis(gen);
    vector<deque<bool>> A(n, deque<bool>(n));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            uniform_int_distribution<int> zero_or_one(0, 1);
            A[i][j] = zero_or_one(gen);
        }
    }

    uniform_int_distribution<size_t> dis1(0, n - 1);
    size_t i = dis1(gen), j = dis1(gen);
    // cout << "color = " << i << ' ' << j << ' ' << A[i][j] << endl;

    PrintMatrix(A);
    FlipColor(static_cast<int>(i), static_cast<int>(j), &A);
    // cout << endl;
    PrintMatrix(A);
}

TEST_F(Ch19_Graphs_Fixture, surrounded_regions_Function) {
    vector<vector<char>> A = {{'B', 'B', 'B', 'B'},
                              {'W', 'B', 'W', 'B'},
                              {'B', 'W', 'W', 'B'},
                              {'B', 'B', 'B', 'B'}};
    FillSurroundedRegions(&A);
    vector<vector<char>> golden = {{'B', 'B', 'B', 'B'},
                                   {'W', 'B', 'B', 'B'},
                                   {'B', 'B', 'B', 'B'},
                                   {'B', 'B', 'B', 'B'}};
    ASSERT_TRUE(equal(A.begin(), A.end(), golden.begin(), golden.end()));

    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 100);
    int n = dis(gen);
    int m = dis(gen);

    vector<vector<char>> board(n, vector<char>(m));
    uniform_int_distribution<int> zero_or_one(0, 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            board[i][j] = zero_or_one(gen) ? 'B' : 'W';
        }
    }
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            cout << board[i][j];
        }
        cout << endl;
    }
    FillSurroundedRegions(&board);
    cout << endl;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            cout << board[i][j];
        }
        cout << endl;
    }
}

void Ch19_Graphs_Fixture::TestDirectedCycle() {
    vector<GraphVertex> G(3);
    G[0].edges.emplace_back(&G[1]);
    G[1].edges.emplace_back(&G[2]);
    G[2].edges.emplace_back(&G[0]);
    bool result = IsDeadlocked(&G);
    // cout << boolalpha << result << endl;
    ASSERT_EQ(p_19_4_CheckAnswer(&G), result);
    ASSERT_TRUE(result);
}

void Ch19_Graphs_Fixture::TestDirectedStarTree() {
    vector<GraphVertex> G(4);
    G[0].edges.emplace_back(&G[1]);
    G[0].edges.emplace_back(&G[2]);
    G[0].edges.emplace_back(&G[3]);
    bool result = IsDeadlocked(&G);
    // cout << boolalpha << result << endl;
    ASSERT_EQ(p_19_4_CheckAnswer(&G), result);
    ASSERT_FALSE(result);
}

void Ch19_Graphs_Fixture::TestDirectedLineTree() {
    vector<GraphVertex> G(4);
    G[0].edges.emplace_back(&G[1]);
    G[1].edges.emplace_back(&G[2]);
    G[2].edges.emplace_back(&G[3]);
    bool result = IsDeadlocked(&G);
    // cout << boolalpha << result << endl;
    ASSERT_EQ(p_19_4_CheckAnswer(&G), result);
    ASSERT_FALSE(result);
    G[3].edges.emplace_back(&G[1]);
    result = IsDeadlocked(&G);
    ASSERT_TRUE(result);
}

void Ch19_Graphs_Fixture::TestDirectedBinaryTree() {
    vector<GraphVertex> G(7);
    G[0].edges.emplace_back(&G[1]);
    G[0].edges.emplace_back(&G[2]);
    G[1].edges.emplace_back(&G[3]);
    G[1].edges.emplace_back(&G[4]);
    G[2].edges.emplace_back(&G[5]);
    G[2].edges.emplace_back(&G[6]);
    bool result = IsDeadlocked(&G);
    // cout << boolalpha << result << endl;
    ASSERT_EQ(p_19_4_CheckAnswer(&G), result);
    ASSERT_FALSE(result);
    G[4].edges.emplace_back(&G[6]);
    G[6].edges.emplace_back(&G[1]);
    result = IsDeadlocked(&G);
    ASSERT_TRUE(result);
}

void Ch19_Graphs_Fixture::TestDirectedTwoSeparateCycles() {
    vector<GraphVertex> G(6);
    G[0].edges.emplace_back(&G[1]);
    G[1].edges.emplace_back(&G[2]);
    G[2].edges.emplace_back(&G[0]);
    G[3].edges.emplace_back(&G[4]);
    G[4].edges.emplace_back(&G[5]);
    G[5].edges.emplace_back(&G[3]);
    bool result = IsDeadlocked(&G);
    ASSERT_TRUE(result);
}

TEST_F(Ch19_Graphs_Fixture, 2_exists_Function) {
    TestDirectedCycle();
    TestDirectedStarTree();
    TestDirectedLineTree();
    TestDirectedBinaryTree();
    TestDirectedTwoSeparateCycles();

    default_random_engine gen((random_device())());
    for (int times = 0; times < 10; ++times) {
        uniform_int_distribution<int> dis(2, 2000);
        int n = dis(gen);

        vector<GraphVertex> G(n);
        uniform_int_distribution<int> dis1(1, n * (n - 1) / 2);
        int m = dis1(gen);
        vector<deque<bool>> is_edge_exist(n, deque<bool>(n, false));

        // Make the graph become connected.
        for (int i = 1; i < n; ++i) {
            G[i - 1].edges.emplace_back(&G[i]);
            G[i].edges.emplace_back(&G[i - 1]);
            is_edge_exist[i - 1][i] = is_edge_exist[i][i - 1] = true;
        }

        // Generate edges randomly.
        m -= (n - 1);
        while (m-- > 0) {
            int a, b;
            do {
                uniform_int_distribution<int> dis(0, n - 1);
                a = dis(gen), b = dis(gen);
            } while (a == b || is_edge_exist[a][b] == true);

            is_edge_exist[a][b] = is_edge_exist[b][a] = true;
            G[a].edges.emplace_back(&G[b]);
            G[b].edges.emplace_back(&G[a]);
        }

        bool result = IsDeadlocked(&G);
        // cout << boolalpha << result << endl;
        ASSERT_EQ(p_19_4_CheckAnswer(&G), result);
    }
}

TEST_F(Ch19_Graphs_Fixture, clone_graph_Function) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 1000; ++times) {
        vector<p_19_5::GraphVertex> G;
        uniform_int_distribution<int> n_dis(2, 101);
        int n = n_dis(gen);

        for (int i = 0; i < n; ++i) {
            G.emplace_back(p_19_5::GraphVertex{i});
        }

        uniform_int_distribution<int> dis(1, n * (n - 1) / 2);
        int m = dis(gen);
        vector<deque<bool>> is_edge_exist(n, deque<bool>(n, false));
        // Make the graph become connected.

        for (int i = 1; i < n; ++i) {
            G[i - 1].edges.emplace_back(&G[i]);
            G[i].edges.emplace_back(&G[i - 1]);
            is_edge_exist[i - 1][i] = is_edge_exist[i][i - 1] = true;
        }

        // Generate some edges randomly.
        m -= (n - 1);
        while (m-- > 0) {
            int a, b;
            uniform_int_distribution<int> dis(0, n - 1);
            do {
                a = dis(gen), b = dis(gen);
            } while (a == b || is_edge_exist[a][b] == true);
            is_edge_exist[a][b] = is_edge_exist[b][a] = true;
            G[a].edges.emplace_back(&G[b]);
            G[b].edges.emplace_back(&G[a]);
        }

        auto res = p_19_5::CloneGraph(&G[0]);
        CheckGraph(res, G);
    }
}

TEST_F(Ch19_Graphs_Fixture, wiring_circuit_Function) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 90; ++times) {
        uniform_int_distribution<int> dis(2, 101);
        int n = dis(gen);

        vector<circuit::GraphVertex> G(n);
        uniform_int_distribution<int> dis1(1, n * (n - 1) / 2);
        int m = dis1(gen);
        // cout << times << ' ' << n << ' ' << m << endl;
        vector<deque<bool>> is_edge_exist(n, deque<bool>(n, false));

        while (m-- > 0) {
            uniform_int_distribution<int> dis(0, n - 1);
            int a, b;
            do {
                a = dis(gen), b = dis(gen);
            } while (a == b || is_edge_exist[a][b] == true);
            is_edge_exist[a][b] = is_edge_exist[b][a] = true;
            G[a].edges.emplace_back(&G[b]);
            G[b].edges.emplace_back(&G[a]);
        }

        /*
        for (int i = 0; i < G.size(); ++i) {
          cout << i << endl;
          for (int j = 0; j < G[i].edges.size(); ++j) {
            cout << ' ' << G[i].edges[j];
          }
          cout << endl;
        }
        */
        bool res = circuit::IsAnyPlacementFeasible(&G);
        // cout << boolalpha << res << endl;
        ASSERT_EQ(res, circuit::IsTwoColorable(&G));
    }
}

TEST_F(Ch19_Graphs_Fixture, transform_string_Function) {
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 10);
    int len = dis(gen);

    string s(p_19_7_RandString(len));
    string t(p_19_7_RandString(len));

    unordered_set<string> D;
    D.emplace(s);
    D.emplace(t);

    uniform_int_distribution<int> dis1(1, 1000000);
    int n = dis1(gen);
    for (size_t i = 0; i < n; ++i) {
        D.emplace(p_19_7_RandString(len));
    }
    /*
    for (const string &s : D) {
      cout << s << endl;
    }
    */
    // cout << s << ' ' << t << ' ' << D.size() << endl;
    cout << TransformString(D, s, t) << endl;
}

TEST_F(Ch19_Graphs_Fixture, team_photo_2_Function) {
    vector<photo_2::GraphVertex> G(3);
    G[0].edges.emplace_back(&G[2]);
    G[1].edges.emplace_back(&G[2]);
    ASSERT_EQ(2, photo_2::FindLargestNumberTeams(&G));
}

TEST_F(Ch19_Graphs_Fixture, shortest_path_Function) {
    // DBH test
    vector<short_path::GraphVertex> G;
    for (int i = 0; i < 9; ++i) {
        G.emplace_back(short_path::GraphVertex());
        G[i].id = i;
    }

    // G[0] is the source node that connects to 8 other nodes.
    G[0].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[1], 13});  // 0-1
    G[1].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[0], 13});  // 1-0

    G[0].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[2], 24});  // 0-2
    G[2].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[0], 24});  // 2-0

    G[0].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[3], 28});  // 0-3
    G[3].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[0], 28});  // 3-0

    G[0].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[4], 25});  // 0-4
    G[4].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[0], 25});  // 4-0

    G[0].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[5], 30});  // 0-5
    G[5].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[0], 30});  // 5-0

    G[0].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[6], 31});  // 0-6
    G[6].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[0], 31});  // 6-0

    G[0].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[7], 10});  // 0-7
    G[7].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[0], 10});  // 7-0

    G[0].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[8], 29});  // 0-8
    G[8].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[0], 29});  // 8-0

    G[1].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[8], 7});  // 1-8
    G[8].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[1], 7});  // 8-1

    G[2].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[8], 1});  // 2-8
    G[8].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[2], 1});  // 8-2

    G[7].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[8], 16});  // 7-8
    G[8].edges.push_back(short_path::GraphVertex::VertexWithDistance{G[7], 16});  // 8-7

    int s = 0;  // Source is G[0].
    int t = 2;  // Destination is G[2].

    // Minimum distance path should be:
    // G[0] => G[1] => G[8] => G[2],
    // distance is: 13 + 7 + 1 = 21.

    short_path::DijkstraShortestPath(&G[s], &G[t]);
    /*
    cout << endl
         << "Min distance: " << G[t].distance_with_fewest_edges.distance
         << endl;
         */
    ASSERT_EQ(G[t].distance_with_fewest_edges.distance, 21);

    /*
    cout << "Number of edges: " << G[t].distance_with_fewest_edges.min_num_edges
         << endl;
         */
    ASSERT_EQ(G[t].distance_with_fewest_edges.min_num_edges, 3);

    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(2, 1000);
    int n = dis(gen);

    // vector<short_path::GraphVertex> G;
    G.clear();

    for (int i = 0; i < n; ++i) {
        G.emplace_back(short_path::GraphVertex());
    }

    uniform_int_distribution<int> dis1(1, n * (n - 1) / 2);
    int m = dis1(gen);
    vector<deque<bool>> is_edge_exist(n, deque<bool>(n, false));

    // Make the graph as connected.
    for (int i = 1; i < n; ++i) {
        uniform_int_distribution<int> dis(1, 100);
        int len = dis(gen);
        G[i - 1].edges.emplace_back(short_path::GraphVertex::VertexWithDistance{G[i], len});
        G[i].edges.emplace_back(short_path::GraphVertex::VertexWithDistance{G[i - 1], len});
        is_edge_exist[i - 1][i] = is_edge_exist[i][i - 1] = true;
    }

    // Generate edges randomly.
    m -= (n - 1);
    uniform_int_distribution<int> dis_n(0, n - 1);
    while (m-- > 0) {
        int a, b;
        do {
            a = dis_n(gen), b = dis_n(gen);
        } while (a == b || is_edge_exist[a][b] == true);
        is_edge_exist[a][b] = is_edge_exist[b][a] = true;
        uniform_int_distribution<int> one_to_100(1, 100);
        int len = one_to_100(gen);

        G[a].edges.emplace_back(short_path::GraphVertex::VertexWithDistance{G[b], len});
        G[b].edges.emplace_back(short_path::GraphVertex::VertexWithDistance{G[a], len});
    }
    s = dis_n(gen);
    t = dis_n(gen);

    // cout << "source = " << s << ", terminal = " << t << endl;
    short_path::DijkstraShortestPath(&G[s], &G[t]);
    /*
    cout << endl
         << G[t].distance_with_fewest_edges.distance << " "
         << G[t].distance_with_fewest_edges.min_num_edges << endl;
         */
}