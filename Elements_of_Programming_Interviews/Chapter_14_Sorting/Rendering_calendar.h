#ifndef ALGORITHM_ANALYSIS_RENDERING_CALENDAR_H
#define ALGORITHM_ANALYSIS_RENDERING_CALENDAR_H
// 14.4 Render a calendar

#include <algorithm>
#include <vector>

using std::max;
using std::vector;

struct Event {
    int start, finish;
};

struct Endpoint {
    bool operator<(const Endpoint& e) const {
        // If times are equal, an endpoint that starts an interval comes first.
        return time != e.time ? time < e.time : (isStart && !e.isStart);
    }

    int time;
    bool isStart;
};

int FindMaxSimultaneousEvents(const vector<Event>& A) {
    // Builds an array of all endpoints.
    vector<Endpoint> E;
    for (const Event& event : A) {
        E.emplace_back(Endpoint{event.start, true});
        E.emplace_back(Endpoint{event.finish, false});
    }
    // Sorts the endpoint array according to the time, breaking ties
    // by putting start times before end times.
    sort(E.begin(), E.end());

    // Track the number of simultaneous events, and record the maximum
    // number of simultaneous events.
    int max_num_simultaneous_events = 0;
    int num_simultaneous_events = 0;

    for (const Endpoint& endpoint : E) {
        if (endpoint.isStart) {
            ++num_simultaneous_events;
            max_num_simultaneous_events =
                    max(num_simultaneous_events, max_num_simultaneous_events);
        } else {
            --num_simultaneous_events;
        }
    }
    return max_num_simultaneous_events;
}

#endif //ALGORITHM_ANALYSIS_RENDERING_CALENDAR_H
