#ifndef ALGORITHM_ANALYSIS_PRIME_SIEVE_BASIC_H
#define ALGORITHM_ANALYSIS_PRIME_SIEVE_BASIC_H

#include <cmath>
#include <vector>

using std::vector;

namespace prime_sieve_basic {
// @include
// Given n, return all primes up to and including n.
    vector<int> GeneratePrimes(int n) {
        vector<int> primes;
        // is_prime[p] represents if p is prime or not. Initially, set each to true,
        // excepting 0 and 1. Then use sieving to eliminate nonprimes.
        vector<bool> is_prime(n + 1, true);
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
// @exclude
}

#endif //ALGORITHM_ANALYSIS_PRIME_SIEVE_BASIC_H
