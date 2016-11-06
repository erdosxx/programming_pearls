#ifndef ALGORITHM_ANALYSIS_CLONE_GRAPH_H
#define ALGORITHM_ANALYSIS_CLONE_GRAPH_H
// Problem 19.5: Clone a Graph

#include <algorithm>
#include <queue>
#include <unordered_map>
#include <vector>

using std::queue;
using std::unordered_map;
using std::vector;

namespace p_19_5 {
// @include
    struct GraphVertex {
        int label;
        vector<GraphVertex *> edges;
    };

    GraphVertex *CloneGraph(GraphVertex *G) {
        if (!G) {
            return nullptr;
        }

        unordered_map<GraphVertex *, GraphVertex *> vertex_map;
        queue<GraphVertex *> q;
        q.emplace(G);
        vertex_map.emplace(G, new GraphVertex({G->label}));

        while (!q.empty()) {
            auto v = q.front();
            q.pop();

            for (GraphVertex *e : v->edges) {
                // Try to copy vertex e.
                if (vertex_map.find(e) == vertex_map.end()) {
                    vertex_map.emplace(e, new GraphVertex({e->label}));
                    q.emplace(e);
                }
                // Copy edge v->e.
                vertex_map[v]->edges.emplace_back(vertex_map[e]);
            }
        }
        return vertex_map[G];
    }
// @exclude

    vector<int> CopyLabels(const vector<GraphVertex *> &edges) {
        vector<int> labels;

        for (GraphVertex * e : edges) {
            labels.emplace_back(e->label);
        }
        return labels;
    }
}

#endif //ALGORITHM_ANALYSIS_CLONE_GRAPH_H
