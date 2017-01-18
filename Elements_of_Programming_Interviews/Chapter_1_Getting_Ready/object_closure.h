#ifndef PROGRAMMING_PEARLS_OBJECT_CLOSURE_H
#define PROGRAMMING_PEARLS_OBJECT_CLOSURE_H
// This code is from Programming Language Pragmatics: Page 513

#include <vector>

using std::vector;

template<typename T>
class un_op {
public:
    virtual T operator()(T i) const = 0;

};

class plus_x : public un_op<int> {
    const int x;
public:
    plus_x(int n) : x{n} {}
    virtual int operator()(int i) const { return i + x;}
};

void apply_to_A(const un_op<int>& f, vector<int>* A_ptr) {
    vector<int>& A = *A_ptr;
    int i;
    for (int i = 0; i < A.size(); ++i) A[i] = f(A[i]);
}


#endif //PROGRAMMING_PEARLS_OBJECT_CLOSURE_H
