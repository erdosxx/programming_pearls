#ifndef ALGORITHM_ANALYSIS_SEARCH_MAZE_H
#define ALGORITHM_ANALYSIS_SEARCH_MAZE_H

#include <array>
#include <vector>

using std::array;
using std::vector;

// @include
//typedef enum { WHITE, BLACK } Color;
using Status = enum { ROAD, OBSTACLE, VISITED };
// @exclude

struct Coordinate;
bool SearchMazeHelper(const Coordinate&, const Coordinate&,
                      vector<vector<Status>>*, vector<Coordinate>*);
bool IsFeasible(const Coordinate&, const vector<vector<Status>>&);

// @include
struct Coordinate {
    bool operator==(const Coordinate& that) const {
        return x == that.x && y == that.y;
    }

    int x, y;
};

vector<Coordinate> SearchMaze(vector<vector<Status>> maze, const Coordinate& start,
                              const Coordinate& goal) {
    vector<Coordinate> path;
    maze[start.x][start.y] = VISITED;
    path.emplace_back(start);

    if (!SearchMazeHelper(start, goal, &maze, &path)) {
        path.pop_back();
    }
    return path;  // Empty path means no path between s and e.
}

// Perform DFS to find a feasible path.
bool SearchMazeHelper(const Coordinate& cur, const Coordinate& goal,
                      vector<vector<Status>>* maze, vector<Coordinate>* path) {
    if (cur == goal) {
        return true;
    }

    const array<array<int, 2>, 4> kShift = {{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}};

    for (const array<int, 2>& s : kShift) {
        Coordinate next{cur.x + s[0], cur.y + s[1]};

        if (IsFeasible(next, *maze)) {
            (*maze)[next.x][next.y] = VISITED;

            path->emplace_back(next);
            if (SearchMazeHelper(next, goal, maze, path)) {
                return true;
            }
            path->pop_back();
        }
    }
    return false;
}

// Checks cur is within maze and is a white pixel.
bool IsFeasible(const Coordinate& cur, const vector<vector<Status>>& maze) {
    return cur.x >= 0 && cur.x < maze.size() && cur.y >= 0 &&
           cur.y < maze[cur.x].size() && maze[cur.x][cur.y] == ROAD;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_SEARCH_MAZE_H
