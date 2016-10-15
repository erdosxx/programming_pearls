#ifndef ALGORITHM_ANALYSIS_PICKING_UP_COINS_H
#define ALGORITHM_ANALYSIS_PICKING_UP_COINS_H

#include <algorithm>
#include <vector>

using std::max;
using std::min;
using std::vector;

enum {uninit_val= -1};

int ComputeMaximumRevenueForRange(const vector<int>&, int, int,
                                  vector<vector<int>>*);

// @include
int MaximumRevenue(const vector<int>& coins) {
    vector<vector<int>> maximum_revenue_for_range(coins.size(), vector<int>(coins.size(), uninit_val));

    return ComputeMaximumRevenueForRange(coins, 0, coins.size() - 1, &maximum_revenue_for_range);
}

int ComputeMaximumRevenueForRange(
        const vector<int>& coins, int left, int right,
        vector<vector<int>>* maximum_revenue_for_range_ptr) {
    if (left > right) {
        // No coins left.
        return 0;
    }

    vector<vector<int>>& maximum_revenue_for_range = *maximum_revenue_for_range_ptr;

    if (maximum_revenue_for_range[left][right] == uninit_val) {
        int max_revenue_left =
                coins[left] +
                min(ComputeMaximumRevenueForRange(coins, left + 2, right,
                                                  maximum_revenue_for_range_ptr),
                    ComputeMaximumRevenueForRange(coins, left + 1, right - 1,
                                                  maximum_revenue_for_range_ptr));
        int max_revenue_right =
                coins[right] +
                min(ComputeMaximumRevenueForRange(coins, left + 1, right - 1,
                                                  maximum_revenue_for_range_ptr),
                    ComputeMaximumRevenueForRange(coins, left, right - 2,
                                                  maximum_revenue_for_range_ptr));

        maximum_revenue_for_range[left][right] = max(max_revenue_left, max_revenue_right);
    }
    return maximum_revenue_for_range[left][right];
}
// @exclude

int MaximumRevenueAlternativeHelper(
        const vector<int>& coins, int left, int right, const vector<int>& prefix_sum,
        vector<vector<int>>* maximum_revenue_for_range_ptr) {
    if (left > right) {
        return 0;
    } else if (left == right) {
        return coins[left];
    }

    vector<vector<int>>& maximum_revenue_for_range = *maximum_revenue_for_range_ptr;

    if (maximum_revenue_for_range[left][right] == uninit_val) {
        maximum_revenue_for_range[left][right] = max(
                // Choose left coin
                coins[left] + prefix_sum[right] - (left >= 0 ? prefix_sum[left] : 0) -
                MaximumRevenueAlternativeHelper(coins, left + 1, right, prefix_sum,
                                                maximum_revenue_for_range_ptr),
                // Choose right coin
                coins[right] + prefix_sum[right - 1] - (left >= 1 ? prefix_sum[left - 1] : 0) -
                MaximumRevenueAlternativeHelper(coins, left, right - 1, prefix_sum,
                                                maximum_revenue_for_range_ptr));
    }
    return maximum_revenue_for_range[left][right];
}

int MaximumRevenueAlternative(const vector<int>& coins) {
    vector<int> prefix_sum;

    partial_sum(coins.begin(), coins.end(), back_inserter(prefix_sum));

    vector<vector<int>> maximum_revenue_for_range(
            coins.size(), vector<int>(coins.size(), uninit_val));

    return MaximumRevenueAlternativeHelper(
            coins, 0, coins.size() - 1, prefix_sum, &maximum_revenue_for_range);
}

int GreedyHelper(const vector<int>& coins, int start, int end) {
    if (start > end) {
        return 0;
    }

    int gain;
    if (coins[start] > coins[end]) {
        gain = coins[start];
        if (coins[start + 1] > coins[end]) {
            gain += GreedyHelper(coins, start + 2, end);
        } else {
            gain += GreedyHelper(coins, start + 1, end - 1);
        }
    } else {
        gain = coins[end];
        if (coins[start] > coins[end - 1]) {
            gain += GreedyHelper(coins, start + 1, end - 1);
        } else {
            gain += GreedyHelper(coins, start, end - 2);
        }
    }
    return gain;
}

int Greedy(const vector<int>& coins) {
    return GreedyHelper(coins, 0, coins.size() - 1);
}

#endif //ALGORITHM_ANALYSIS_PICKING_UP_COINS_H
