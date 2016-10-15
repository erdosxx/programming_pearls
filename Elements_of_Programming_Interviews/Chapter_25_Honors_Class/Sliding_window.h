#ifndef ALGORITHM_ANALYSIS_SLIDING_WINDOW_H
#define ALGORITHM_ANALYSIS_SLIDING_WINDOW_H

#include <queue>
#include <stdexcept>
#include <vector>

#include "Queue_with_max_alternative.h"

using std::length_error;
using std::queue;
using std::vector;
using QueueWithMaxAlternative::QueueWithMax;

// @include
struct TrafficElement {
    // Following operators are needed for QueueWithMax with maximum.
    bool operator>(const TrafficElement& that) const {
        return volume > that.volume ||
               (volume == that.volume && time > that.time);
    }

    bool operator==(const TrafficElement& that) const {
        return time == that.time && volume == that.volume;
    }

    bool operator>=(const TrafficElement& that) const {
        return *this > that || *this == that;
    }

    int time;
    double volume;
};

vector<TrafficElement> CalculateTrafficVolumes(
        const vector<TrafficElement>& A, int w) {
    QueueWithMax<TrafficElement> sliding_window;
    vector<TrafficElement> maximum_volumes;

    for (const auto traffic_info : A) {
        sliding_window.Enqueue(traffic_info);

        while (traffic_info.time - sliding_window.Head().time > w) {
            sliding_window.Dequeue();
        }

        maximum_volumes.emplace_back(
                TrafficElement{traffic_info.time, sliding_window.Max().volume});
    }

    return maximum_volumes;
}
// @exclude


#endif //ALGORITHM_ANALYSIS_SLIDING_WINDOW_H
