#ifndef ALGORITHM_ANALYSIS_QUEUE_FROM_STACKS_H
#define ALGORITHM_ANALYSIS_QUEUE_FROM_STACKS_H

#include <stack>
#include <stdexcept>

using std::exception;
using std::length_error;
using std::stack;

namespace queue_from_stack {
// @include
    class Queue {
    public:
        void Enqueue(int x) { enq_.emplace(x); }

        int Dequeue() {
            if (deq_.empty()) {
                // Transfers the elements in enq_ to deq_.
                while (!enq_.empty()) {
                    deq_.emplace(enq_.top());
                    enq_.pop();
                }
            }

            if (deq_.empty()) {  // deq_ is still empty!
                throw length_error("empty queue");
            }
            int ret = deq_.top();
            deq_.pop();
            return ret;
        }

    private:
        stack<int> enq_, deq_;
    };
// @exclude
}

#endif //ALGORITHM_ANALYSIS_QUEUE_FROM_STACKS_H