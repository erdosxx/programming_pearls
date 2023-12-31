#ifndef ALGORITHM_ANALYSIS_PRIME_SIEVE_BASIC_H
#define ALGORITHM_ANALYSIS_PRIME_SIEVE_BASIC_H
// 6.8 Enumerate all primes to n

#include <vector>
#include <deque>

using std::vector;
using std::deque;

namespace prime_sieve_basic {
// Given n, return all primes up to and including n.
    vector<int> GeneratePrimes(int n) {
        vector<int> primes;
        // is_prime[p] represents if p is prime or not. Initially, set each to true,
        // excepting 0 and 1. Then use sieving to eliminate nonprimes.
        deque<bool> is_prime(n + 1, true);
        is_prime[0] = is_prime[1] = false;

        for (int p = 2; p < n; ++p) {
            if (is_prime[p]) {
                primes.emplace_back(p);
                // Sieve p's multiples.
                for (int j = p; j <= n; j += p) {
                    is_prime[j] = false;
                }
            }
        }
        return primes;
    }
}

#endif //ALGORITHM_ANALYSIS_PRIME_SIEVE_BASIC_H
