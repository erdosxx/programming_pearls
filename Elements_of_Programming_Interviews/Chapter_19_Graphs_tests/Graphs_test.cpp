#include <gtest/gtest.h>
#include <random>
#include <limits>
#include <unordered_set>
#include <cmath>
#include <string>
#include <bitset>
#include <deque>
#include "graphs_boot_camp.h"
#include "team_reachability.h"
#include "Search_maze.h"
#include "shortest_path_maze.h"
#include "shortest_path_maze_jaythe1st.h"
#include "shortest_path_maze_shkim.h"
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
using std::discrete_distribution;
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

TEST_F(Ch19_Graphs_Fixture, graphs_boot_camp) {
    // See C++PL: page 187
    const_with_null_test test_obj{2};
    // not work: for const  test_obj.a = 2;
    ASSERT_EQ(2, test_obj.a);

    int b = 3;
    test_obj.b_ptr = &b;
    ASSERT_EQ(3, *test_obj.b_ptr);

    // not work: for const *test_obj.a_ptr = 4;

    int a1= 1;
    int a2= 2;
    int a3= 3;
    vector<const_test> vec {{1, &a1}, {2, &a2}, {3, &a3}};

    for(const const_test& ele : vec) {
        // error for const: ele.a = 3;
        // error for const: ele.b_ptr = &a1;
        *ele.b_ptr = 10;
    }
    ASSERT_EQ(10, a1);
    ASSERT_EQ(10, a2);
    ASSERT_EQ(10, a3);

    ///// unique_ptr, make_unique
    int* a_ptr = make_unique<int>().get();
    *a_ptr = 2;
    int* b_ptr = a_ptr;
    // even though a_ptr is made by unique_ptr
    // a_ptr can be copied.
    ASSERT_EQ(2, *b_ptr);

    unique_ptr<int> uni_a_ptr(new int(12));
    ASSERT_EQ(12, *uni_a_ptr);

    // equivalent unique_ptr<int> uni_b_ptr(new int{22});
    unique_ptr<int> uni_b_ptr = make_unique<int>(int{22});
    ASSERT_EQ(22, *uni_b_ptr);

    // not work because uni_b_ptr is unique:
    // unique_ptr<int> uni_c_ptr = uni_b_ptr;
}

TEST_F(Ch19_Graphs_Fixture, team_reachability_Function) {
    vector<MatchResult> matches = {{"Texas", "Cal"},      {"Cal", "Stanford"},
                                   {"Stanford", "Texas"}, {"Stanford", "MIT"},
                                   {"Stanford", "CIT"},   {"UCLA", "USC"}};

    //         Ci
    //         ^
    //         |
    // T->Ca-> S->T    Uc->USC
    //         |
    //         v
    //         M

    ASSERT_EQ(CanTeamABeatTeamB_DFS(matches, "Texas", "MIT"),
              CanTeamABeatTeamB_BFS(matches, "Texas", "MIT"));

    ASSERT_EQ(CanTeamABeatTeamB_DFS(matches, "Cal", "UCLA"),
              CanTeamABeatTeamB_BFS(matches, "Cal", "UCLA"));
}

TEST_F(Ch19_Graphs_Fixture, search_maze_Function) {
    default_random_engine gen((random_device())());

    for (int times = 0; times < 1000; ++times) {
        uniform_int_distribution<int> dis(1, 30);
        int n = dis(gen);
        int m = dis(gen);

        vector<vector<Status>> maze(n, vector<Status>(m));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // for using uniform distribution, there are small number of path are exist.
                // for making more path(this case DFS is very slow), use discrete_distribution like this.
                // discrete_distribution<int> dis1({70, 30});
                uniform_int_distribution<int> zero_or_one(0, 1);
                maze[i][j] = zero_or_one(gen) ? ROAD : OBSTACLE;
            }
        }

        vector<Coordinate> roads;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (maze[i][j] == ROAD) {
                    roads.emplace_back(Coordinate{i, j});
                }
                // cout << maze[i][j] << ' ';
            }
            // cout << endl;
        }
        // cout << endl;

        if (roads.size()) {
            uniform_int_distribution<int> dis(0, roads.size() - 1);
            int start = dis(gen);
            int end = dis(gen);
            // cout << white[start].x << ' ' << white[start].y << endl;
            // cout << white[end].x << ' ' << white[end].y << endl;
            vector<Coordinate> path = SearchMaze(maze, roads[start], roads[end]);

            // test wheather starting and ending position is correct in path.
            if (!path.empty()) {
                ASSERT_TRUE(roads[start] == path.front() && roads[end] == path.back());
            }

            // test for every move(adjacent move) is valid.
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

TEST_F(Ch19_Graphs_Fixture, shortest_path_maze_Random_erdos_vs_jaythe1st) {
    for (int k= 0; k< 50; k++) {
        default_random_engine gen((random_device()) ());
        uniform_int_distribution<int> dis(5, 10);
        const int rows = dis(gen);
        const int cols = dis(gen);

        //cout << "rows= " << rows <<", cols= "<<cols << " ";

        int **maze_random = new int *[rows];

        for (int i = 0; i < rows; i++) {
            maze_random[i] = new int[cols];
        }

        discrete_distribution<int> dis1({70, 30});
        //uniform_int_distribution<int> dis1(0, 1);

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                maze_random[row][col] = dis1(gen);
            }
        }

        // start
        maze_random[0][0] = 0;

        uniform_int_distribution<int> dis2(0, rows - 1);
        int exitRow = dis2(gen);

        uniform_int_distribution<int> dis3(0, cols - 1);
        int exitCol = dis3(gen);

        //cout << "exitRow= " << exitRow <<", exitCol= "<< exitCol << " ";

        ASSERT_TRUE(exitRow >= 0 && exitRow <= rows - 1);
        ASSERT_TRUE(exitCol >= 0 && exitCol <= cols - 1);

        // Exit
        maze_random[exitRow][exitCol] = 0;

        int distance1 = findMinNumSteps(maze_random, rows, cols, exitRow, exitCol);
        int distance2 = jaythe1st::findMinNumSteps(maze_random, rows, cols, exitRow, exitCol);

        /*
        if (distance1 != distance2) {
            cout << "Dist1: " << distance1 <<", dist2: " << distance2 <<endl;
        } else {
            cout << "Dist: " << distance1 << endl;
        }
         */

        ASSERT_EQ(distance1 , distance2);
    }
}

TEST_F(Ch19_Graphs_Fixture, shortest_path_maze_simple_test) {
    int **maze = new int *[3];
    maze[0] = new int[4]{0, 0, 0, 0};
    maze[1] = new int[4]{1, 0, 1, 0};
    maze[2] = new int[4]{1, 0, 0, 0};

    position pos ={-1,1};
    ASSERT_FALSE(isValidPath(maze, pos, 3, 4));
    pos = {3,-1};
    ASSERT_FALSE(isValidPath(maze, pos, 3, 4));
    pos = {2,-1};
    ASSERT_FALSE(isValidPath(maze, pos, 3, 4));
    pos = {3,4};
    ASSERT_FALSE(isValidPath(maze, pos, 3, 4));
    pos = {2,4};
    ASSERT_FALSE(isValidPath(maze, pos, 3, 4));
    pos = {-1,3};
    ASSERT_FALSE(isValidPath(maze, pos, 3, 4));
    pos = {2,3};
    ASSERT_TRUE(isValidPath(maze, pos, 3, 4));
    pos = {0,3};
    ASSERT_TRUE(isValidPath(maze, pos, 3, 4));
    pos = {0,0};
    ASSERT_TRUE(isValidPath(maze, pos, 3, 4));

    initalize_maze(maze, 3, 4);
    ASSERT_EQ(-100, maze[1][0]);
    pos = {1,0};
    ASSERT_FALSE(isValidPath(maze, pos, 3, 4));
    pos = {2,0};
    ASSERT_FALSE(isValidPath(maze, pos, 3, 4));
    pos = {1,2};
    ASSERT_FALSE(isValidPath(maze, pos, 3, 4));

    reset_maze(maze, 3, 4);
    ASSERT_EQ(1, maze[1][0]);
    ASSERT_EQ(1, maze[1][2]);
    ASSERT_EQ(1, maze[2][0]);

    initalize_maze(maze, 3, 4);
    vector<position> result;
    pos = {0, 0};
    result = std::move(get_adjacent_nodes(maze, pos, 3, 4));
    ASSERT_EQ(1, result.size());
    ASSERT_EQ(0, result[0].row);
    ASSERT_EQ(1, result[0].col);

    pos = {0, 1};
    result = std::move(get_adjacent_nodes(maze, pos, 3, 4));
    ASSERT_EQ(3, result.size());

    pos = {0, 2};
    result = std::move(get_adjacent_nodes(maze, pos, 3, 4));
    ASSERT_EQ(2, result.size());

    pos = {0, 3};
    result = std::move(get_adjacent_nodes(maze, pos, 3, 4));
    ASSERT_EQ(2, result.size());

    pos = {1, 0};
    ASSERT_THROW(get_adjacent_nodes(maze, pos, 3, 4), invalid_argument);

    reset_maze(maze, 3, 4);
    ASSERT_EQ(0,findMinNumSteps(maze, 3, 4, 0, 0));

    ASSERT_EQ(4, findMinNumSteps(maze, 3, 4, 1, 3));

    /*
    for (int i = 0; i < 3; ++i) {
        delete [] maze[4];
    }
    delete [] maze;
     */

    int **maze2 = new int*[5];
    maze2[0] = new int[4]{0, 1, 0, 1};
    maze2[1] = new int[4]{0, 0, 1, 0};
    maze2[2] = new int[4]{1, 0, 0, 1};
    maze2[3] = new int[4]{1, 1, 0, 0};
    maze2[4] = new int[4]{0, 0, 0, 1};
    ASSERT_EQ(8, findMinNumSteps(maze2, 5, 4, 4, 0));

    /*
    for (int i = 0; i < 5; ++i) {
        delete [] maze2[4];
    }
    delete [] maze2;
     */

    int **maze3 = new int*[5];
    maze3[0] = new int[4]{0, 0, 0, 0};
    maze3[1] = new int[4]{0, 0, 1, 0};
    maze3[2] = new int[4]{0, 1, 1, 0};
    maze3[3] = new int[4]{0, 1, 1, 0};
    maze3[4] = new int[4]{0, 0, 0, 0};
    ASSERT_EQ(5, findMinNumSteps(maze3, 5, 4, 4, 1));
    ASSERT_EQ(5, jaythe1st::findMinNumSteps(maze3,5,4,4,1));

    /*
    for (int i = 0; i < 5; ++i) {
        delete [] maze3[4];
    }
    delete [] maze3;
     */

    int **maze4 = new int*[5];
    maze4[0] = new int[4]{0, 0, 0, 0};
    maze4[1] = new int[4]{0, 0, 1, 0};
    maze4[2] = new int[4]{1, 1, 1, 0};
    maze4[3] = new int[4]{0, 1, 1, 0};
    maze4[4] = new int[4]{0, 0, 1, 0};
    ASSERT_EQ(-1, findMinNumSteps(maze4, 5, 4, 4, 1));
    ASSERT_EQ(-1, jaythe1st::findMinNumSteps(maze4,5,4,4,1));

    /*
    for (int i = 0; i < 5; ++i) {
        delete [] maze4[4];
    }
    delete [] maze4;
     */

    int x = 10;
    int* p = &x;
    int** q = &p;
    ASSERT_EQ(*(*q), 10);
    ASSERT_EQ(**q, 10);

    //ASSERT_EQ(findMinNumSteps(maze5_ptr, 19, 19, 17, 18), 10);
              //jaythe1st::findMinNumSteps(maze5_ptr, 19, 19, 17, 18));
}

TEST_F(Ch19_Graphs_Fixture, shortest_path_maze_Random_testing_erdos) {
    for (int k= 0; k< 10; k++) {
        default_random_engine gen((random_device()) ());
        uniform_int_distribution<int> dis(10, 50);
        const int rows = dis(gen);
        const int cols = dis(gen);

        //cout << "rows= " << rows <<", cols= "<<cols << " ";

        int **maze_random = new int *[rows];

        for (int i = 0; i < rows; i++) {
            maze_random[i] = new int[cols];
        }

        // probability for path 80% and wall 20%
        discrete_distribution<int> dis1({80, 20});

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                maze_random[row][col] = dis1(gen);
            }
        }

        // start
        maze_random[0][0] = 0;

        uniform_int_distribution<int> dis2(0, rows - 1);
        int exitRow = dis2(gen);

        uniform_int_distribution<int> dis3(0, cols - 1);
        int exitCol = dis3(gen);

        // cout << "exitRow= " << exitRow <<", exitCol= "<< exitCol << " ";

        ASSERT_TRUE(exitRow >= 0 && exitRow <= rows - 1);
        ASSERT_TRUE(exitCol >= 0 && exitCol <= cols - 1);

        // Exit
        maze_random[exitRow][exitCol] = 0;

        int distance1 = findMinNumSteps(maze_random, rows, cols, exitRow, exitCol);

        // cout << "Dist: " << distance1 << endl;
    }
}

TEST_F(Ch19_Graphs_Fixture, shortest_path_maze_Random_testing_shkim) {
    for (int k= 0; k< 10; k++) {
        default_random_engine gen((random_device()) ());
        uniform_int_distribution<int> dis(10, 50);
        const int rows = dis(gen);
        const int cols = dis(gen);

        //cout << "rows= " << rows <<", cols= "<<cols << " ";

        int **maze_random = new int *[rows];

        for (int i = 0; i < rows; i++) {
            maze_random[i] = new int[cols];
        }

        // probability for path 80% and wall 20%
        discrete_distribution<int> dis1({80, 20});

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                maze_random[row][col] = dis1(gen);
            }
        }

        // start
        maze_random[0][0] = 0;

        uniform_int_distribution<int> dis2(0, rows - 1);
        int exitRow = dis2(gen);

        uniform_int_distribution<int> dis3(0, cols - 1);
        int exitCol = dis3(gen);

        // cout << "exitRow= " << exitRow <<", exitCol= "<< exitCol << " ";

        ASSERT_TRUE(exitRow >= 0 && exitRow <= rows - 1);
        ASSERT_TRUE(exitCol >= 0 && exitCol <= cols - 1);

        // Exit
        maze_random[exitRow][exitCol] = 0;

        int distance1 = shkim::findMinNumSteps(maze_random, rows, cols, exitRow, exitCol);

        // cout << "Dist: " << distance1 << endl;
    }
}

TEST_F(Ch19_Graphs_Fixture, shortest_path_maze_Random_testing_jaythe1st) {
    for (int k= 0; k< 10; k++) {
        default_random_engine gen((random_device()) ());
        uniform_int_distribution<int> dis(5, 10);
        const int rows = dis(gen);
        const int cols = dis(gen);

        // cout << "rows= " << rows <<", cols= "<<cols << " ";

        int **maze_random = new int *[rows];

        for (int i = 0; i < rows; i++) {
            maze_random[i] = new int[cols];
        }

        discrete_distribution<int> dis1({80, 20});

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                maze_random[row][col] = dis1(gen);
            }
        }

        // start
        maze_random[0][0] = 0;

        uniform_int_distribution<int> dis2(0, rows - 1);
        int exitRow = dis2(gen);

        uniform_int_distribution<int> dis3(0, cols - 1);
        int exitCol = dis3(gen);

        // cout << "exitRow= " << exitRow <<", exitCol= "<< exitCol << " ";

        ASSERT_TRUE(exitRow >= 0 && exitRow <= rows - 1);
        ASSERT_TRUE(exitCol >= 0 && exitCol <= cols - 1);

        // Exit
        maze_random[exitRow][exitCol] = 0;

        int distance1 = jaythe1st::findMinNumSteps(maze_random, rows, cols, exitRow, exitCol);

        // cout << "Dist: " << distance1 << endl;
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

    //PrintMatrix(A);
    FlipColor(static_cast<int>(i), static_cast<int>(j), &A);
    // cout << endl;
    //PrintMatrix(A);
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
    /*
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            cout << board[i][j];
        }
        cout << endl;
    }
     */
    FillSurroundedRegions(&board);
    // cout << endl;
    /*
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            cout << board[i][j];
        }
        cout << endl;
    }
     */
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
    // cout << TransformString(D, s, t) << endl;
    TransformString(D,s,t);
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
    G[0].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[1], 13});  // 0-1
    G[1].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[0], 13});  // 1-0

    G[0].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[2], 24});  // 0-2
    G[2].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[0], 24});  // 2-0

    G[0].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[3], 28});  // 0-3
    G[3].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[0], 28});  // 3-0

    G[0].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[4], 25});  // 0-4
    G[4].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[0], 25});  // 4-0

    G[0].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[5], 30});  // 0-5
    G[5].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[0], 30});  // 5-0

    G[0].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[6], 31});  // 0-6
    G[6].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[0], 31});  // 6-0

    G[0].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[7], 10});  // 0-7
    G[7].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[0], 10});  // 7-0

    G[0].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[8], 29});  // 0-8
    G[8].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[0], 29});  // 8-0

    G[1].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[8], 7});  // 1-8
    G[8].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[1], 7});  // 8-1

    G[2].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[8], 1});  // 2-8
    G[8].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[2], 1});  // 8-2

    G[7].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[8], 16});  // 7-8
    G[8].edges.push_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[7], 16});  // 8-7

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

    // the reason to use deque<bool> instead of vector<bool>, see EPI page 11.
    vector<deque<bool>> is_edge_exist(n, deque<bool>(n, false));

    // Make the graph as connected with n-1 edges.
    // G[i-1] <--- len ---> G[i]
    for (int i = 1; i < n; ++i) {
        uniform_int_distribution<int> dis(1, 100);
        int len = dis(gen);
        G[i - 1].edges.emplace_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[i], len});
        G[i].edges.emplace_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[i - 1], len});
        is_edge_exist[i - 1][i] = is_edge_exist[i][i - 1] = true;
    }

    uniform_int_distribution<int> dis1(1, n * (n - 1) / 2);
    int m = dis1(gen);

    // Generate edges randomly.
    m -= (n - 1);
    uniform_int_distribution<int> dis_n(0, n - 1);
    while (m-- > 0) {
        int a, b;

        // select two random nodes that do not have edge between them.
        do {
            a = dis_n(gen);
            b = dis_n(gen);
        } while (a == b || is_edge_exist[a][b] == true);

        is_edge_exist[a][b] = is_edge_exist[b][a] = true;
        uniform_int_distribution<int> one_to_100(1, 100);
        int len = one_to_100(gen);

        G[a].edges.emplace_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[b], len});
        G[b].edges.emplace_back(short_path::GraphVertex::AdjacentVertexWithWeight{&G[a], len});
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

