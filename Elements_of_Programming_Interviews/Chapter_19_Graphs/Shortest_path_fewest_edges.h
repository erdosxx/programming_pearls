#ifndef ALGORITHM_ANALYSIS_SHORTEST_PATH_FEWEST_EDGES_H
#define ALGORITHM_ANALYSIS_SHORTEST_PATH_FEWEST_EDGES_H

#include <limits>
#include <set>
#include <utility>
#include <vector>

using std::numeric_limits;
using std::set;
using std::vector;

namespace short_path {
    struct GraphVertex;

    void OutputShortestPath(const GraphVertex *);

// @include
    struct GraphVertex {
        struct DistanceWithFewestEdges {
            int distance;
            int min_num_edges;
        };

        DistanceWithFewestEdges distance_with_fewest_edges =
                DistanceWithFewestEdges{numeric_limits<int>::max(), 0};

        struct VertexWithDistance {
            GraphVertex &vertex;
            int distance;
        };

        vector<VertexWithDistance> edges;
        int id;  // The id of this vertex.
        const GraphVertex *pred = nullptr;  // The predecessor in the shortest path.
    };

    struct Comp {
        bool operator()(const GraphVertex *lhs, const GraphVertex *rhs) {
          return lhs->distance_with_fewest_edges.distance < rhs->distance_with_fewest_edges.distance ||
                 (lhs->distance_with_fewest_edges.distance == rhs->distance_with_fewest_edges.distance &&
                  lhs->distance_with_fewest_edges.min_num_edges < rhs->distance_with_fewest_edges.min_num_edges);
        }
    };

    void DijkstraShortestPath(GraphVertex *s, const GraphVertex *t) {
        // Initialization of the distance of starting point.
        s->distance_with_fewest_edges = {0, 0};
        set<GraphVertex *, Comp> node_set;
        node_set.emplace(s);

        while (!node_set.empty()) {
            // Extracts the minimum distance vertex from heap.
            GraphVertex *u = *node_set.cbegin();
            if (u->id == t->id) {
                break;
            }

            // Relax neighboring vertices of u.
            for (const GraphVertex::VertexWithDistance &v : u->edges) {
                int v_distance = u->distance_with_fewest_edges.distance + v.distance;
                int v_num_edges = u->distance_with_fewest_edges.min_num_edges + 1;

                if (v.vertex.distance_with_fewest_edges.distance > v_distance ||
                    (v.vertex.distance_with_fewest_edges.distance == v_distance &&
                     v.vertex.distance_with_fewest_edges.min_num_edges > v_num_edges)) {
                    node_set.erase(&v.vertex); // remove old vertex data
                    v.vertex.pred = u;
                    v.vertex.distance_with_fewest_edges = {v_distance, v_num_edges};
                    node_set.emplace(&v.vertex);
                }
            }

            node_set.erase(node_set.cbegin());
        }

        // Outputs the shortest path with fewest edges.
        // OutputShortestPath(t);
    }

    void OutputShortestPath(const GraphVertex *v) {
        if (v) {
            OutputShortestPath(v->pred);
            cout << v->id << " ";
        }
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_SHORTEST_PATH_FEWEST_EDGES_H
