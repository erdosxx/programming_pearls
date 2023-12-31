#ifndef ALGORITHM_ANALYSIS_GENERATING_A_B_SQRT2_H
#define ALGORITHM_ANALYSIS_GENERATING_A_B_SQRT2_H
// 15.7 Enumerate numbers of the form a + b sqrt(2)

#include <queue>
#include <set>
#include <vector>

using std::queue;
using std::set;
using std::vector;

// These numbers have very interesting property, and people called it ugly
// numbers. It is also called Quadratic integer rings.
struct ABSqrt2 {
    ABSqrt2(int a, int b) : a{a}, b{b} {}

    bool operator>(const ABSqrt2& that) const {
        return a + b * sqrt(2) > that.a + that.b * sqrt(2);
    }

    bool operator>=(const ABSqrt2& that) const {
        return a + b * sqrt(2) > that.a + that.b * sqrt(2)
                || operator==(that);
    }

    bool operator<(const ABSqrt2& that) const {
        return a + b * sqrt(2) < that.a + that.b * sqrt(2);
    }

    bool operator==(const ABSqrt2& that) const {
        return a == that.a && b == that.b;
    }

    int a, b;
};

vector<ABSqrt2> GenerateFirstKABSqrt2(int k) {
    set<ABSqrt2> candidates;
    // Initial for 0 + 0 * sqrt(2).
    // std::queue::emplace
    // template <class... Args> void emplace (Args&&... args);
    // Arguments forwarded to construct the new element.
    // following is equivalent to candidates.emplace(ABSqrt2{0, 0});
    candidates.emplace(0, 0);
    // for using push we need to use value type
    // std::queue::push
    // void push (const value_type& val);
    // candidates.push(ABSqrt2{2,2})

    vector<ABSqrt2> result;
    while (result.size() < k) {
        auto next_smallest = candidates.cbegin();
        result.emplace_back(*next_smallest);

        // Adds the next two numbers derived from next_smallest.
        candidates.emplace(next_smallest->a + 1, next_smallest->b);
        candidates.emplace(next_smallest->a, next_smallest->b + 1);
        candidates.erase(next_smallest);
    }
    return result;
}

vector<ABSqrt2> Golden(int k) {
    vector<ABSqrt2> smallest;
    smallest.emplace_back(0, 0);

    queue<ABSqrt2> q1, q2;
    q1.emplace(1, 0);
    q2.emplace(0, 1);

    for (int i = 1; i < k; ++i) {
        auto q1_f = q1.front();
        auto q2_f = q2.front();

        if (q1_f < q2_f) {
            smallest.emplace_back(q1_f);
            q1.pop();
            q1.emplace(q1_f.a + 1, q1_f.b);
            q2.emplace(q1_f.a, q1_f.b + 1);
        } else {
            smallest.emplace_back(q2_f);
            q2.pop();
            q2.emplace(q2_f.a, q2_f.b + 1);
        }
    }
    return smallest;
}

#endif //ALGORITHM_ANALYSIS_GENERATING_A_B_SQRT2_H
