#ifndef ALGORITHM_ANALYSIS_FIBONACCI_RAKUTEN_H
#define ALGORITHM_ANALYSIS_FIBONACCI_RAKUTEN_H
// Rakuten(Codility)
// https://discuss.codechef.com/questions/84763/how-to-solve-a-such-problem-based-on-fiboncci

#include <vector>
#include <array>

using std::array;
using m_type = array<array<int, 2>, 2>;


// Time O(logN), Space(logN)
int fib_modulo(int n, const size_t& modulo) {
    int f[1000] = {0};

    if (n == 0)
        return 0;
    if (n == 1 || n == 2)
        return (f[n] = 1);

    if (f[n])
        return f[n];

    //int k = (n & 1)? (n+1)/2 : n/2;
    int half_n = (n+1)/2;

    f[n] = (n & 1)? (fib_modulo(half_n, modulo) * fib_modulo(half_n, modulo)) % modulo +
                    ((fib_modulo(half_n-1, modulo) * fib_modulo(half_n-1, modulo)) % modulo)
                  : (((2*fib_modulo(half_n-1, modulo)) % modulo + fib_modulo(half_n, modulo)) % modulo) * fib_modulo(half_n, modulo);

    return f[n] % modulo;
}

// see http://www.geeksforgeeks.org/program-for-nth-fibonacci-number/
// Time O(logN), Space(logN)
unsigned long fib(const size_t& n) {
    int f[1000] = {0};

    if (n == 0)
        return 0;
    if (n == 1 || n == 2)
        return (f[n] = 1);

    if (f[n])
        return f[n];

    //int k = (n & 1)? (n+1)/2 : n/2;
    int k = (n+1)/2;

    f[n] = (n & 1)? fib(k) * fib(k)  + fib(k-1) * fib(k-1)
                  : (2*fib(k-1) + fib(k)) * fib(k);

    return f[n];
}

// A, B = [0, 2147483647] 2^31 -1= 2147483647
//    N = [0, 1000000000]
// Time O(logN), Space(logN)
int GF_modulo(int A, int B, int N, const size_t& modulo) {
    int a_mod = A % modulo;
    int b_mod = B % modulo;

    if (N == 0) {
        return a_mod;
    }
    return (fib_modulo(N-1, modulo) * a_mod + fib_modulo(N, modulo)* b_mod) % modulo;
}

// if N is fibonacci number, return 0
unsigned long diff_fib(const unsigned long& N) {
    size_t i = 0;
    unsigned long fibo = fib(0);
    bool exist = false;

    while (fibo < N) {
        fibo = fib(++i);
    };

    return fibo - N;
}

// matrix

struct _2x2_m {
    m_type m;

    _2x2_m(m_type ma = {{{0,0}, {0,0}}}): m{ma} {};

    _2x2_m operator*(_2x2_m that){
        return m_type{{
                 {m[0][0] * that.m[0][0] + m[0][1] * that.m[1][0],
                  m[0][0] * that.m[0][1] + m[0][1] * that.m[1][1]},
                 {m[1][0] * that.m[0][0] + m[1][1] * that.m[1][0],
                  m[1][0] * that.m[0][1] + m[1][1] * that.m[1][1]}
               }};
    }

    bool operator==(const _2x2_m& that) const {
        return m[0][0] == that.m[0][0] &&
               m[0][1] == that.m[0][1] &&
               m[1][0] == that.m[1][0] &&
               m[1][1] == that.m[1][1];
    }

    // Time: O(logN), Space: O(1)
    _2x2_m power(size_t n) {
        _2x2_m result = m_type{{{1,0},{0,1}}};
        _2x2_m x = m;

        while (n) {
            if (n & 1) {
                result = result * x;
            }
            x = x * x;
            n >>= 1;
        }
        return result;
    }
};

// A, B = [0, 2147483647] 2^31 -1= 2147483647
//    N = [0, 1000000000]
unsigned long GF(const int& A, const int& B, const int& n) {
    if (n == 0) {
        return A;
    } else if (n == 1) {
        return B;
    }

    _2x2_m fib_m = m_type{{{1,1},{1,0}}};
    _2x2_m fib_m_power = fib_m.power(n-1);

    return A * fib_m_power.m[0][1] + B * fib_m_power.m[0][0];
}

struct _2x2_m_mod {
    m_type _m;
    size_t _mod = 1000000007;

    _2x2_m_mod(m_type ma): _m{ma} {
        _m[0][0] = ma[0][0] % _mod;
        _m[0][1] = ma[0][1] % _mod;
        _m[1][0] = ma[1][0] % _mod;
        _m[1][1] = ma[1][1] % _mod;
    };

    _2x2_m_mod(m_type ma, size_t mod): _m{ma}, _mod{mod} {
        _m[0][0] = ma[0][0] % _mod;
        _m[0][1] = ma[0][1] % _mod;
        _m[1][0] = ma[1][0] % _mod;
        _m[1][1] = ma[1][1] % _mod;
    };

    _2x2_m_mod operator*(_2x2_m_mod that){
        return {m_type{{
                 {_m[0][0] * that._m[0][0] + _m[0][1] * that._m[1][0],
                  _m[0][0] * that._m[0][1] + _m[0][1] * that._m[1][1]},
                 {_m[1][0] * that._m[0][0] + _m[1][1] * that._m[1][0],
                  _m[1][0] * that._m[0][1] + _m[1][1] * that._m[1][1]}
               }}, _mod};
    }

    bool operator==(const _2x2_m_mod& that) const {
        return _m[0][0] == that._m[0][0] &&
               _m[0][1] == that._m[0][1] &&
               _m[1][0] == that._m[1][0] &&
               _m[1][1] == that._m[1][1] &&
                _mod == that._mod;
    }

    // Time: O(logN), Space: O(1)
    _2x2_m_mod power(size_t n) {
        _2x2_m_mod result = {m_type{{{1,0},{0,1}}}, _mod};
        _2x2_m_mod x = _m;

        while (n) {
            if (n & 1) {
                result = result * x;
            }
            x = x * x;
            n >>= 1;
        }
        return result;
    }
};

unsigned long GF_mod(const int& A, const int& B, const int& n, const size_t mod) {
    size_t a_mod = A % mod;
    size_t b_mod = B % mod;

    if (n == 0) {
        return a_mod;
    } else if (n == 1) {
        return b_mod;
    }

    _2x2_m_mod fib_m = {m_type{{{1,1},{1,0}}}, mod};
    _2x2_m_mod fib_m_power = fib_m.power(n-1);

    return ( a_mod * fib_m_power._m[0][1] + b_mod * fib_m_power._m[0][0] ) % mod;
}

#endif
