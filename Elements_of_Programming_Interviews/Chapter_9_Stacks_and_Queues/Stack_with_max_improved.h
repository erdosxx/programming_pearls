#ifndef ALGORITHM_ANALYSIS_STACK_WITH_MAX_IMPROVED_H
#define ALGORITHM_ANALYSIS_STACK_WITH_MAX_IMPROVED_H
// 9.1 Implement a stack with max API

#include <algorithm>
#include <stack>
#include <stdexcept>
#include <string>
#include <utility>

using std::exception;
using std::length_error;
using std::stack;

namespace stack_max_imp {
// @include
    class Stack {
    public:
        bool Empty() const { return element_.empty(); }

        int Max() const {
            if (Empty()) {
                throw length_error("Max(): empty stack");
            }
            return cached_max_with_count_.top().max;
        }

        int Pop() {
            if (Empty()) {
                throw length_error("Pop(): empty stack");
            }

            int pop_element = element_.top();
            element_.pop();

            const int current_max = cached_max_with_count_.top().max;

            if (pop_element == current_max) {
                int& max_frequency = cached_max_with_count_.top().count;
                --max_frequency;

                if (max_frequency == 0) {
                    cached_max_with_count_.pop();
                }
            }
            return pop_element;
        }

        void Push(int x) {
            element_.emplace(x);

            if (cached_max_with_count_.empty()) {
                cached_max_with_count_.emplace(MaxWithCount{x, 1});
            } else {
                const int current_max = cached_max_with_count_.top().max;
                if (x == current_max) {
                    int &max_frequency = cached_max_with_count_.top().count;
                    ++max_frequency;
                } else if (x > current_max) {
                    cached_max_with_count_.emplace(MaxWithCount{x, 1});
                }
            }
        }

    private:
        stack<int> element_;

        struct MaxWithCount {
            int max, count;
        };
        stack<MaxWithCount> cached_max_with_count_;
    };
// @exclude
}

#endif //ALGORITHM_ANALYSIS_STACK_WITH_MAX_IMPROVED_H
