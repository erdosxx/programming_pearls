#ifndef ALGORITHM_ANALYSIS_TASK_ASSIGNMENT_H
#define ALGORITHM_ANALYSIS_TASK_ASSIGNMENT_H
// 18.1 Compute an optimum assignment of tasks

#include <algorithm>
#include <utility>
#include <vector>

using std::vector;

// @include
struct PairedTasks {
    int task_1, task_2;
};

vector<PairedTasks> OptimumTaskAssignment(vector<int> task_durations) {
    sort(task_durations.begin(), task_durations.end());

    vector<PairedTasks> optimum_assignments;

    for (int i = 0, j = task_durations.size() - 1; i < j; ++i, --j) {
        optimum_assignments.emplace_back(
                PairedTasks{task_durations[i], task_durations[j]});
    }

    return optimum_assignments;
}

// @exclude


#endif //ALGORITHM_ANALYSIS_TASK_ASSIGNMENT_H
