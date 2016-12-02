#ifndef ALGORITHM_ANALYSIS_STACK_QUEUE_USING_HEAP_H
#define ALGORITHM_ANALYSIS_STACK_QUEUE_USING_HEAP_H
// 11.7 Implement a stack API using a heap
// 11.7.1 Variant

#include <queue>
#include <stdexcept>
#include <vector>
#include <utility>

using std::exception;
using std::length_error;
using std::priority_queue;
using std::vector;

class Stack {
public:
    void Push(int x) { max_heap_.emplace(ValueWithRank{timestamp_++, x}); }

    int Pop() {
        if (max_heap_.empty()) {
            throw length_error("empty stack");
        }
        int val = max_heap_.top().value;
        max_heap_.pop();
        return val;
    }

    int Peek() const { return max_heap_.top().value; }

private:
    int timestamp_ = 0;

    struct ValueWithRank {
        int timestamp, value;

        bool operator<(const ValueWithRank& that) const {
            return timestamp < that.timestamp;
        }
    };

    priority_queue<ValueWithRank, vector<ValueWithRank>> max_heap_;
};

class Queue {
public:
    void Enqueue(int x) { max_heap_.emplace(ValueWithRank{order_--, x}); }

    int Dequeue() {
        if (max_heap_.empty()) {
            throw length_error("empty queue");
        }
        int val = max_heap_.top().value;
        max_heap_.pop();
        return val;
    }

    int Head() const { return max_heap_.top().value; }

private:
    int order_ = 0;

    struct ValueWithRank {
        int order, value;

        bool operator<(const ValueWithRank& that) const {
            return order < that.order;
        }
    };
    priority_queue<ValueWithRank, vector<ValueWithRank>> max_heap_;
};

#endif //ALGORITHM_ANALYSIS_STACK_QUEUE_USING_HEAP_H
