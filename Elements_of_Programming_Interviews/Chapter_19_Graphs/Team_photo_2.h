#ifndef ALGORITHM_ANALYSIS_TEAM_PHOTO_2_H
#define ALGORITHM_ANALYSIS_TEAM_PHOTO_2_H

#include <algorithm>
#include <stack>
#include <vector>

using std::max;
using std::stack;
using std::vector;

namespace photo_2 {
    struct GraphVertex;

    stack<GraphVertex *> BuildTopologicalOrdering(vector<GraphVertex> *G);

    int FindLongestPath(stack<GraphVertex *> *vertex_order);

    void DFS(GraphVertex *cur, stack<GraphVertex *> *vertex_order);

// @include
    struct GraphVertex {
        vector<GraphVertex *> edges;
        int max_distance = 1;
        bool visited = false;
    };

    int FindLargestNumberTeams(vector<GraphVertex> *G) {
        // same as following stack<GraphVertex *> vertex_order = BuildTopologicalOrdering(G);
        stack<GraphVertex *> vertex_order(BuildTopologicalOrdering(G));
        return FindLongestPath(&vertex_order);
    }

    stack<GraphVertex *> BuildTopologicalOrdering(vector<GraphVertex> *G) {
        stack<GraphVertex *> vertex_order;

        for (auto &g : *G) {
            if (!g.visited) {
                DFS(&g, &vertex_order);
            }
        }
        return vertex_order;
    }

    int FindLongestPath(stack<GraphVertex *> *vertex_order) {
        int max_distance = 0;

        while (!vertex_order->empty()) {
            GraphVertex *u = vertex_order->top();
            max_distance = max(max_distance, u->max_distance);

            for (GraphVertex *&v : u->edges) {
                v->max_distance = max(v->max_distance, u->max_distance + 1);
            }
            vertex_order->pop();
        }
        return max_distance;
    }

    void DFS(GraphVertex *cur, stack<GraphVertex *> *vertex_order) {
        cur->visited = true;

        for (GraphVertex *next : cur->edges) {
            if (!next->visited) {
                DFS(next, vertex_order);
            }
        }
        vertex_order->emplace(cur);
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_TEAM_PHOTO_2_H
