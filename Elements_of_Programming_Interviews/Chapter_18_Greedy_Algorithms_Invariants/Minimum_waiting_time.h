#ifndef ALGORITHM_ANALYSIS_MINIMUM_WAITING_TIME_H
#define ALGORITHM_ANALYSIS_MINIMUM_WAITING_TIME_H
// 18.2 Schedule to minimize waiting time

#include <algorithm>
#include <vector>

using std::vector;

// @include
int MinimumTotalWaitingTime(vector<int> service_times) {
    // Sort the service times in increasing order.
    sort(service_times.begin(), service_times.end());

    int total_waiting_time = 0;

    for (int i = 0; i < service_times.size(); ++i) {
        int num_remaining_queries = service_times.size() - (i + 1);
        total_waiting_time += service_times[i] * num_remaining_queries;
    }
    return total_waiting_time;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_MINIMUM_WAITING_TIME_H
