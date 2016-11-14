#ifndef ALGORITHM_ANALYSIS_STACK_QUEUE_USING_HEAP_H
#define ALGORITHM_ANALYSIS_STACK_QUEUE_USING_HEAP_H
// 11.7 Implement a stack API using a heap

#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <vector>
#include <utility>

using std::cout;
using std::endl;
using std::exception;
using std::function;
using std::length_error;
using std::numeric_limits;
using std::priority_queue;
using std::vector;

// @include
class Stack {
public:
    void Push(int x) { max_heap_.emplace(ValueWithRank{timestamp_++, x}); }

    int Pop() {
        if (max_heap_.empty()) {
            throw length_error("empty stack");
        }
        int val = max_heap_.top().rank;
        max_heap_.pop();
        return val;
    }

    int Peek() const { return max_heap_.top().rank; }

private:
    int timestamp_ = 0;

    struct ValueWithRank {
        int value, rank;

        bool operator<(const ValueWithRank& that) const {
            return value < that.value;
        }
    };
    priority_queue<ValueWithRank, vector<ValueWithRank>> max_heap_;
};
// @exclude

class Queue {
public:
    void Enqueue(int x) { max_heap_.emplace(ValueWithRank{order_--, x}); }

    int Dequeue() {
        if (max_heap_.empty()) {
            throw length_error("empty queue");
        }
        int ret = max_heap_.top().rank;
        max_heap_.pop();
        return ret;
    }

    int Head() const { return max_heap_.top().rank; }

private:
    int order_ = 0;

    struct ValueWithRank {
        int value, rank;

        bool operator<(const ValueWithRank& that) const {
            return value < that.value;
        }
    };
    priority_queue<ValueWithRank, vector<ValueWithRank>> max_heap_;
};

#endif //ALGORITHM_ANALYSIS_STACK_QUEUE_USING_HEAP_H
