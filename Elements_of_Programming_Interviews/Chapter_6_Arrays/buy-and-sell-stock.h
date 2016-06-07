#ifndef ALGORITHM_ANALYSIS_BUY_AND_SELL_STOCK_H
#define ALGORITHM_ANALYSIS_BUY_AND_SELL_STOCK_H

#include <algorithm>
#include <limits>
#include <vector>

using std::max;
using std::min;
using std::numeric_limits;
using std::vector;

namespace buy_and_sell {
// @include
    double BuyAndSellStockOnce(const vector<double> &prices) {
        double min_price_so_far = numeric_limits<double>::max();
        double max_profit = 0;

        for (auto &price : prices) {
            double max_profit_sell_today = price - min_price_so_far;
            max_profit = max(max_profit, max_profit_sell_today);
            min_price_so_far = min(min_price_so_far, price);
        }
        return max_profit;
    }
// @exclude

// O(n^2) checking answer.
    double CheckAns(const vector<double> &h) {
        double cap = 0;
        for (int i = 1; i < h.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                cap = max(cap, h[i] - h[j]);
            }
        }
        return cap;
    }
}

#endif //ALGORITHM_ANALYSIS_BUY_AND_SELL_STOCK_H
