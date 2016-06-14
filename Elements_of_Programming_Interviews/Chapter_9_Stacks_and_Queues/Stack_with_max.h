#ifndef ALGORITHM_ANALYSIS_STACK_WITH_MAX_H
#define ALGORITHM_ANALYSIS_STACK_WITH_MAX_H

#include <algorithm>
#include <stack>
#include <stdexcept>
#include <utility>

using std::length_error;
using std::max;
using std::stack;

namespace stack_max {

// @include
    class Stack {
    public:
        bool Empty() const { return element_with_cached_max_.empty(); }

        int Max() const {
            if (Empty()) {
                throw length_error("Max(): empty stack");
            }
            return element_with_cached_max_.top().max;
        }

        int Pop() {
            if (Empty()) {
                throw length_error("Pop(): empty stack");
            }
            int pop_element = element_with_cached_max_.top().element;
            element_with_cached_max_.pop();
            return pop_element;
        }

        void Push(int x) {
            element_with_cached_max_.emplace(
                    ElementWithCachedMax{x, max(x, Empty() ? x : Max())});
        }

    private:
        struct ElementWithCachedMax {
            int element, max;
        };
        stack<ElementWithCachedMax> element_with_cached_max_;
    };
// @exclude
}

#endif //ALGORITHM_ANALYSIS_STACK_WITH_MAX_H
