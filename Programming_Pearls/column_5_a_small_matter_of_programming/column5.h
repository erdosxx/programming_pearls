#ifndef PROGRAMMING_PEARLS_COLUMN5_H
#define PROGRAMMING_PEARLS_COLUMN5_H

#include <stddef.h>

/* Alg 1: From Programming Pearls, Column 4: raw transliteration */

int binarysearch1(int* x, const size_t size_ary, int value) {
    int middle;
    int low = 0;
    int high = size_ary - 1;

    for (;;) {
        if (low > high)
            return -1;

        middle = (low + high) / 2;

        if (x[middle] < value)
            low = middle + 1;
        else if (x[middle] == value)
            return middle;
        else
            high = middle - 1;
    }
}

/* Alg 2: Make binarysearch1 more c-ish */

int binarysearch2(int* x, const size_t size_ary, int value) {
    int middle;
    int low = 0;
    int high = size_ary - 1;

    while (low <= high) {
        middle = (low + high) / 2;

        if (x[middle] < value)
            low = middle + 1;
        else if (x[middle] == value)
            return middle;
        else
            high = middle - 1;
    }
    return -1;
}

/* Alg 3: From PP, Col 9, Page 93 */
// Find the FIRST occurrence of the integer t
int binary_search_first(int *x, const size_t size_ary, int value) {
    int middle;
    int low = -1;
    int high = size_ary;

    // invariant: x[low] < timestamp && x[high] >= timestamp && low < high
    while (low + 1 != high) {
        middle = (low + high) / 2;

        if (x[middle] < value)
            low = middle;
        else
            high = middle;
    }

    if (high >= size_ary || x[high] != value)
        return -1;
    return high;
}

/* Alg 3: From PP, Col 9, Page 93 */
// Find the LAST occurrence of the integer t
int binary_search_last(int *x, const size_t size_ary, int value) {
    int middle;
    int low = -1;
    int high = size_ary;

    // invariant: x[low] <= timestamp && x[high] > timestamp && low < high
    while (low + 1 != high) {
        middle = (low + high) / 2;

        if(x[middle] > value)
            high = middle;
        else
            low = middle;
    }

    if (low <= -1 || x[low] != value)
        return -1;
    return low;
}

/* Alg 4: From PP, Col 9 */
int binarysearch4(int* x, const size_t size_ary, int value) {
    if (size_ary != 1000)
        return binary_search_first(x, size_ary, value);

    // invariant: x[low] < timestamp
    int low = -1;
    if (x[511] < value) low = 1000 - 512;
    if (x[low + 256] < value) low += 256;
    if (x[low + 128] < value) low += 128;
    if (x[low + 64 ] < value) low += 64;
    if (x[low + 32 ] < value) low += 32;
    if (x[low + 16 ] < value) low += 16;
    if (x[low + 8  ] < value) low += 8;
    if (x[low + 4  ] < value) low += 4;
    if (x[low + 2  ] < value) low += 2;
    if (x[low + 1  ] < value) low += 1;

    int answer = low + 1;

    if (answer >= size_ary || x[answer] != value)
        return -1;
    return answer;
}

int sorted(int* x, const size_t & n) {
  int i;
  for (i = 0; i < n-1; i++)
    if (x[i] > x[i+1])
      return 0;
  return 1;
}

// Buggy code
int binarysearch9(int* x, const size_t & n, int t) {
    int l, u, m;
    /* int oldsize, size = n+1; */
    l = 0;
    u = n-1;
    while (l <= u) {
        /* oldsize = size;
           size = u - l +1;
           assert(size < oldsize); */
        m = (l + u) / 2;
        /* printf("  %d %d %d\n", l, m, u); */
        if (x[m] < t)
            l = m;  // <-- l = m+1
        else if (x[m] > t)
            u = m;  // <-- u = m-1
        else {
            /* assert(x[m] == t); */
            return m;
        }
    }
    /* assert(x[l] > t && x[u] < t); */
    return -1;
}

/* Alg 21: Simple sequential search */

int seqsearch_simple(int *x, const size_t size_ary, int value) {
    for (int i = 0; i < size_ary; i++)
        if (x[i] == value)
            return i;
    return -1;
}

/* Alg 22: Faster sequential search: Sentinel */

int seqsearch_sentinel(int *x, const size_t size_ary, int value) {
    int i;
    int backup = x[size_ary];
    x[size_ary] = value;

    for (i = 0; ; i++)
        if (x[i] == value)
            break;

    x[size_ary] = backup;

    if (i == size_ary)
        return -1;
    else
        return i;
}

/* Alg 23: Faster sequential search: loop unrolling */

int seqsearch_loop_unrolling(int *x, const size_t size_ary, int value) {
    int i;
    int backup = x[size_ary];
    x[size_ary] = value;

    for (i = 0; ; i+=8) {
        if (x[i] == value)   {         break; }
        if (x[i+1] == value) { i += 1; break; }
        if (x[i+2] == value) { i += 2; break; }
        if (x[i+3] == value) { i += 3; break; }
        if (x[i+4] == value) { i += 4; break; }
        if (x[i+5] == value) { i += 5; break; }
        if (x[i+6] == value) { i += 6; break; }
        if (x[i+7] == value) { i += 7; break; }
    }

    x[size_ary] = backup;

    if (i == size_ary)
        return -1;
    else
        return i;
}

#endif //PROGRAMMING_PEARLS_COLUMN5_H
