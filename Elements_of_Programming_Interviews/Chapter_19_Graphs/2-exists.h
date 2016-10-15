#ifndef ALGORITHM_ANALYSIS_2_EXISTS_H
#define ALGORITHM_ANALYSIS_2_EXISTS_H

#include <deque>
#include <vector>

using std::deque;
using std::vector;

struct GraphVertex;
bool HasCycle(GraphVertex*, const GraphVertex*);

// @include
struct GraphVertex {
    enum Color { undiscovered, discovered, processed } color = undiscovered;
    vector<GraphVertex*> edges;
};

bool IsDeadlocked(vector<GraphVertex>* G) {
    for (GraphVertex& vertex : *G) {
        if (vertex.color == GraphVertex::undiscovered && HasCycle(&vertex, nullptr)) {
            return true;
        }
    }
    return false;
}

bool HasCycle(GraphVertex* cur, const GraphVertex* parent) {
    // Visiting a discovered vertex means a cycle.
    if (cur->color == GraphVertex::discovered) {
        return true;
    }

    cur->color = GraphVertex::discovered;

    // Traverse the neighbor vertices.
    for (GraphVertex*& child : cur->edges) {
        if (child != parent && child->color != GraphVertex::processed) {
            if (HasCycle(child, cur)) {
                return true;
            }
        }
    }
    cur->color = GraphVertex::processed;
    return false;
}
// @exclude

bool HasCycleExclusion(GraphVertex* cur, GraphVertex* parent) {
    if (cur->color == GraphVertex::discovered) {
        return true;
    }

    cur->color = GraphVertex::discovered;

    for (GraphVertex*& child : cur->edges) {
        if (child != parent) {
            if (HasCycleExclusion(child, cur)) {
                return true;
            }
        }
    }
    return false;
}

#endif //ALGORITHM_ANALYSIS_2_EXISTS_H
