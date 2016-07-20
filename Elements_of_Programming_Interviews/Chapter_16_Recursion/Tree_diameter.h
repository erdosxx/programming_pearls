#ifndef ALGORITHM_ANALYSIS_TREE_DIAMETER_H
#define ALGORITHM_ANALYSIS_TREE_DIAMETER_H

#include <algorithm>
#include <array>
#include <limits>
#include <memory>
#include <vector>
#include <utility>

using std::array;
using std::make_unique;
using std::max;
using std::numeric_limits;
using std::unique_ptr;
using std::vector;

struct TreeNode;
struct HeightAndDiameter;
HeightAndDiameter ComputeHeightAndDiameter(const unique_ptr<TreeNode>&);

// @include
struct TreeNode {
    struct Edge {
        unique_ptr<TreeNode> root;
        double length;
    };

    vector<Edge> edges;
};

struct HeightAndDiameter {
    double height, diameter;
};

double ComputeDiameter(const unique_ptr<TreeNode>& T) {
    return T ? ComputeHeightAndDiameter(T).diameter : 0.0;
}

HeightAndDiameter ComputeHeightAndDiameter(const unique_ptr<TreeNode>& r) {
    double diameter = numeric_limits<double>::min();
    array<double, 2> heights = {{0.0, 0.0}};  // Stores the max two heights.

    for (const auto& e : r->edges) {
        HeightAndDiameter h_d = ComputeHeightAndDiameter(e.root);

        if (h_d.height + e.length > heights[0]) {
            heights[1] = heights[0];
            heights[0] = h_d.height + e.length;
        } else if (h_d.height + e.length > heights[1]) {
            heights[1] = h_d.height + e.length;
        }

        diameter = max(diameter, h_d.diameter);
    }
    return {heights[0], max(diameter, heights[0] + heights[1])};
}
// @exclude

#endif //ALGORITHM_ANALYSIS_TREE_DIAMETER_H
