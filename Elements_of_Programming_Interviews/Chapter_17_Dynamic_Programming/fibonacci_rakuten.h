#ifndef ALGORITHM_ANALYSIS_FIBONACCI_RAKUTEN_H
#define ALGORITHM_ANALYSIS_FIBONACCI_RAKUTEN_H

#include <vector>

const int modulo = 1000000007;

const int MAX = 1000;

int f[MAX] = {0};

int fib(int n) {
    if (n == 0)
        return 0;
    if (n == 1 || n == 2)
        return (f[n] = 1);

    if (f[n])
        return f[n];

    int k = (n & 1)? (n+1)/2 : n/2;

    f[n] = (n & 1)? (fib(k) % modulo) * (fib(k) % modulo) + (fib(k-1) % modulo) * (fib(k-1) % modulo)
                  : ( (2*fib(k-1)) % modulo + fib(k) % modulo ) * (fib(k) % modulo);

    return f[n];
}

int solution(int A, int B, int N) {
    return (fib(N-1)*A+fib(N)*B) % modulo;
}

#endif
