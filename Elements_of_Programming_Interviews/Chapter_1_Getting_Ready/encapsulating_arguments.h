#ifndef PROGRAMMING_PEARLS_ENCAPSULATING_ARGUMENTS_H
#define PROGRAMMING_PEARLS_ENCAPSULATING_ARGUMENTS_H
// THis code is from Programming Language Pragmatics P.515
#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::bind;
using std::function;

class fn_call {
public:
    virtual void operator()() = 0;
};

void foo(int a, double b, char c) {
    cout << "foo was executed" << endl;
}

void schedule_at(fn_call& fc, int time) {
    fc();
    cout << "fc was executed at " << time << endl;
}

void schedule_at(function<void()>& f, int time) {
    f();
    cout << "functor was executed at " << time << endl;
}

class call_foo : public fn_call {
    int arg1;
    double arg2;
    char arg3;

public:
    call_foo(int a, double b, char c): arg1{a}, arg2{b}, arg3{c} {}
    void operator()() {
        foo(arg1, arg2, arg3);
    }
};

#endif //PROGRAMMING_PEARLS_ENCAPSULATING_ARGUMENTS_H
