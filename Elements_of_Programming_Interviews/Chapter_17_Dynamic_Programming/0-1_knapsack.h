#ifndef ALGORITHM_ANALYSIS_0_1_KNAPSACK_H
#define ALGORITHM_ANALYSIS_0_1_KNAPSACK_H

#include <algorithm>
#include <vector>

using std::max;
using std::vector;

struct Item;
int OptimumSubjectToItemAndCapacity(const vector<Item>&, int, int,
                                    vector<vector<int>>*);

enum {uncalculated = -1};

// @include
struct Item {
    int weight, value;
};

int OptimumSubjecToCapacity(const vector<Item>& items, int capacity) {
    // V[i][j] holds the optimum value when we choose from items[0 : i] and have
    // a capacity of j.
    vector<vector<int>> V( items.size(), vector<int>(capacity + 1, uncalculated) );
    return OptimumSubjectToItemAndCapacity(items, items.size() - 1, capacity,
                                           &V);
}

// Returns the optimum value when we choose from items[0 : k] and have a
// capacity of available_capacity.
int OptimumSubjectToItemAndCapacity(const vector<Item>& items, int k,
                                    int available_capacity,
                                    vector<vector<int>>* V_ptr) {
    if (k < 0) {
        // No items can be chosen.
        return 0;
    }

    vector<vector<int>>& V = *V_ptr;

    if (V[k][available_capacity] == uncalculated) {
        int without_curr_item = OptimumSubjectToItemAndCapacity(
                items, k - 1, available_capacity, V_ptr);

        int with_curr_item =
                available_capacity < items[k].weight
                ? 0
                : items[k].value + OptimumSubjectToItemAndCapacity(
                        items, k - 1,
                        available_capacity - items[k].weight,
                        V_ptr);

        V[k][available_capacity] = max(without_curr_item, with_curr_item);
    }
    return V[k][available_capacity];
}
// @exclude

#endif //ALGORITHM_ANALYSIS_0_1_KNAPSACK_H
