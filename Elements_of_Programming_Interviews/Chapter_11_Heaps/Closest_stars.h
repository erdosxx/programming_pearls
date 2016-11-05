#ifndef ALGORITHM_ANALYSIS_CLOSEST_STARS_H
#define ALGORITHM_ANALYSIS_CLOSEST_STARS_H

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <vector>

using std::endl;
using std::array;
using std::istringstream;
using std::max;
using std::min;
using std::priority_queue;
using std::string;
using std::stringstream;
using std::stod;
using std::swap;
using std::vector;

// @include
struct Star {
    bool operator<(const Star& that) const {
        return Distance() < that.Distance();
    }

    double Distance() const { return sqrt(x * x + y * y + z * z); }

    double x, y, z;
};

vector<Star> FindClosestKStars(int k, istringstream* stars) {
    // max_heap to store the closest k stars seen so far.
    priority_queue<Star, vector<Star>> max_heap;

    string line;
    while (getline(*stars, line)) {
        stringstream line_stream(line);
        // array is a fixed size container
        array<double, 3> data;  // stores x, y, and z.

        for (int i = 0; i < 3; ++i) {
            string buf;
            getline(line_stream, buf, ',');
            data[i] = stod(buf);
        }

        // Add each star to the max-heap. If the max-heap size exceeds k,
        // remove the maximum element from the max-heap.
        max_heap.emplace(Star{data[0], data[1], data[2]});
        if (max_heap.size() == k + 1) {
            max_heap.pop();
        }
    }

    // Iteratively extract from the max-heap, which yields the stars
    // sorted according from furthest to closest.
    vector<Star> closest_stars;
    while (!max_heap.empty()) {
        closest_stars.emplace_back(max_heap.top());
        max_heap.pop();
    }
    reverse(closest_stars.begin(), closest_stars.end());
    return closest_stars;
}
// @exclude

string CreateStreamingString(const vector<Star>& stars) {
    string s;
    for (int i = 0; i < stars.size(); ++i) {
        stringstream ss;
        ss << stars[i].x << ',' << stars[i].y << ',' << stars[i].z << endl;
        s += ss.str();
    }
    return s;
}

#endif //ALGORITHM_ANALYSIS_CLOSEST_STARS_H
