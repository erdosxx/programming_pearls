#ifndef ALGORITHM_ANALYSIS_SHORTEST_PATH_FEWEST_EDGES_H
#define ALGORITHM_ANALYSIS_SHORTEST_PATH_FEWEST_EDGES_H
// 19.9: Compute a Shortest Path with Fewest Edges

#include <limits>
#include <set>
#include <utility>
#include <vector>

using std::numeric_limits;
using std::set;
using std::vector;
//using std::function;

namespace short_path {

// @include
    struct GraphVertex {
        struct DistanceWithFewestEdges {
            int distance;
            int min_num_edges;
            // point to constant
            // So we can change the timestamp of pointer(addredd) but
            // can not change to timestamp that the pointer point to.
            // See C++PL page 187 and graphs_boot_camp.h with test.
            const GraphVertex *pred = nullptr;  // The predecessor in the shortest path.
        };

        struct AdjacentVertexWithWeight {
            GraphVertex* vertex;
            int weight;
        };

        DistanceWithFewestEdges distance_with_fewest_edges =
                DistanceWithFewestEdges{numeric_limits<int>::max(), 0};

        vector<AdjacentVertexWithWeight> edges;
        int id;  // The id of this vertex.
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

            // v is const. That is, we cannot change the target address of vertex and
            // weight timestamp. However, we can change the attribute of vertex.
            for (const GraphVertex::AdjacentVertexWithWeight &v : u->edges) {
                int v_distance = u->distance_with_fewest_edges.distance + v.weight;
                int v_num_edges = u->distance_with_fewest_edges.min_num_edges + 1;

                if (v.vertex->distance_with_fewest_edges.distance > v_distance ||
                    (v.vertex->distance_with_fewest_edges.distance == v_distance &&
                     v.vertex->distance_with_fewest_edges.min_num_edges > v_num_edges)) {
                    node_set.erase(v.vertex); // remove old vertex data
                    v.vertex->distance_with_fewest_edges.pred = u;
                    v.vertex->distance_with_fewest_edges = {v_distance, v_num_edges};
                    node_set.emplace(v.vertex);
                }
            }

            node_set.erase(node_set.cbegin());
        }

        // Outputs the shortest path with fewest edges.
        // OutputShortestPath(t);
    }

    void OutputShortestPath(const GraphVertex *v) {
        if (v) {
            OutputShortestPath(v->distance_with_fewest_edges.pred);
            cout << v->id << " ";
        }
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_SHORTEST_PATH_FEWEST_EDGES_H
