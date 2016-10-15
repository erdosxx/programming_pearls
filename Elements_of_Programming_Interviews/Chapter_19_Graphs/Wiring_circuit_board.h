#ifndef ALGORITHM_ANALYSIS_WIRING_CIRCUIT_BOARD_H
#define ALGORITHM_ANALYSIS_WIRING_CIRCUIT_BOARD_H

#include <queue>
#include <vector>

using std::queue;
using std::vector;

namespace circuit {
    struct GraphVertex;

    bool BFS(GraphVertex *s);

    enum {undiscovered = -1, white= 0, black = 1};

// @include
    struct GraphVertex {
        int state = undiscovered;
        vector<GraphVertex *> edges;
    };

    bool IsAnyPlacementFeasible(vector<GraphVertex> *G) {
        for (GraphVertex &v : *G) {
            if (v.state == undiscovered) {  // Unvisited vertex.
                v.state = white;
                if (!BFS(&v)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool BFS(GraphVertex *s) {
        queue<GraphVertex *> q;
        q.emplace(s);

        while (!q.empty()) {
            for (GraphVertex *&t : q.front()->edges) {
                if (t->state == undiscovered) {  // Unvisited vertex.
                    //t->state = q.front()->state + 1;
                    t->state = q.front()->state == white ? black: white;
                    q.emplace(t);
                } else if (t->state == q.front()->state) {
                    return false;
                }
            }
            q.pop();
        }
        return true;
    }
// @exclude

    bool DFS(GraphVertex *s) {
        for (GraphVertex *&t : s->edges) {
            if (t->state == undiscovered) {
                //t->state = !s->state;
                t->state = s->state == white ? black: white;

                if (!DFS(t)) {
                    return false;
                }
            } else if (t->state == s->state) {
                return false;
            }
        }
        return true;
    }

    bool IsTwoColorable(vector<GraphVertex> *G) {
        for (GraphVertex &v : *G) {
            v.state = undiscovered;
        }

        for (GraphVertex &v : *G) {
            if (v.state == undiscovered) {
                v.state = white;
                if (!DFS(&v)) {
                    return false;
                }
            }
        }
        return true;
    }
}

#endif //ALGORITHM_ANALYSIS_WIRING_CIRCUIT_BOARD_H
