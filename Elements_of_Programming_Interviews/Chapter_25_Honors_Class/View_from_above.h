#ifndef ALGORITHM_ANALYSIS_VIEW_FROM_ABOVE_H
#define ALGORITHM_ANALYSIS_VIEW_FROM_ABOVE_H

#include <algorithm>
#include <map>
#include <memory>
#include <unordered_set>
#include <vector>

using std::equal;
using std::make_unique;
using std::map;
using std::unique_ptr;
using std::vector;
using std::unordered_set;

// @include
struct LineSegment {
    int left, right;  // Specifies the interval.
    int color;
    int height;
};

struct Endpoint {
    bool operator<(const Endpoint& that) const {
        return Value() < that.Value();
    }

    int Value() const { return isLeft_ ? line_->left : line_->right; }

    bool isLeft_;
    const LineSegment* line_;
};

vector<LineSegment> CalculateViewFromAbove(const vector<LineSegment>& A) {
    vector<Endpoint> sorted_endpoints;

    for (const LineSegment& a : A) {
        sorted_endpoints.emplace_back(Endpoint{true, &a});
        sorted_endpoints.emplace_back(Endpoint{false, &a});
    }
    sort(sorted_endpoints.begin(), sorted_endpoints.end());

    vector<LineSegment> result;
    int prev_endpoint_val = sorted_endpoints.front().Value();  // Leftmost end point.

    unique_ptr<LineSegment> sol_candidate = nullptr;
    
    // Map height with LineSegment
    map<int, const LineSegment*> active_line_segments;

    for (const Endpoint& current_endpoint : sorted_endpoints) {
        if (!active_line_segments.empty() && prev_endpoint_val != current_endpoint.Value()) {
            if (sol_candidate == nullptr) {  // Found first segment.
                sol_candidate = make_unique<LineSegment>(
                        LineSegment{prev_endpoint_val, current_endpoint.Value(),
                                    active_line_segments.crbegin()->second->color,
                                    active_line_segments.crbegin()->second->height});
            } else {
                // if current endpoint is under solution candidate,
                // just extend the right endpoint of solution candidate
                if (sol_candidate->height == active_line_segments.crbegin()->second->height &&
                    sol_candidate->color == active_line_segments.crbegin()->second->color &&
                    prev_endpoint_val == sol_candidate->right) { // update right endpoint
                    sol_candidate->right = current_endpoint.Value();
                } else {
                    result.emplace_back(*sol_candidate);
                    *sol_candidate = {prev_endpoint_val, current_endpoint.Value(),
                             active_line_segments.crbegin()->second->color,
                             active_line_segments.crbegin()->second->height};
                }
            }
        }
        prev_endpoint_val = current_endpoint.Value();

        if (current_endpoint.isLeft_ == true) {  // Left end point.
            active_line_segments.emplace(current_endpoint.line_->height, current_endpoint.line_);
        } else {  // Right end point.
            active_line_segments.erase(current_endpoint.line_->height);
        }
    }

    // Output the remaining segment (if any).
    if (sol_candidate) {
        result.emplace_back(*sol_candidate);
    }
    return result;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_VIEW_FROM_ABOVE_H
