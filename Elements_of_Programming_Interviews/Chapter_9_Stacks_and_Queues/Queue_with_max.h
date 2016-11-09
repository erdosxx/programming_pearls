#ifndef ALGORITHM_ANALYSIS_QUEUE_WITH_MAX_H
#define ALGORITHM_ANALYSIS_QUEUE_WITH_MAX_H
// 9.10 Implement a queue with max API

#include <algorithm>
#include <stdexcept>

#include "Stack_with_max.h"

using std::exception;
using std::length_error;
using std::max;
using std::numeric_limits;

namespace original {
// @include
    class QueueWithMax {
    public:
        void Enqueue(int x) { enqueue_.Push(x); }

        int Dequeue() {
            if (dequeue_.Empty()) {
                while (enqueue_.Empty() == false) {
                    dequeue_.Push(enqueue_.Pop());
                }
            }
            if (dequeue_.Empty() == false) {
                return dequeue_.Pop();
            }
            throw length_error("empty queue");
        }

        int Max() const {
            if (enqueue_.Empty() == false) {
                return dequeue_.Empty() ? enqueue_.Max()
                                        : max(enqueue_.Max(), dequeue_.Max());
            }
            if (dequeue_.Empty() == false) {
                return dequeue_.Max();
            }
            throw length_error("empty queue");
        }

    private:
        stack_max::Stack enqueue_, dequeue_;
    };
// @exclude
}

#endif //ALGORITHM_ANALYSIS_QUEUE_WITH_MAX_H
