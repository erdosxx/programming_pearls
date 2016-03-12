#ifndef PROGRAMMING_PEARLS_COLUMN5_H
#define PROGRAMMING_PEARLS_COLUMN5_H

#include <stddef.h>

/* Alg 1: From Programming Pearls, Column 4: raw transliteration */

int binarysearch1(int* x, const size_t & n, int t) {
    int l, u, m;
    l = 0;
    u = n-1;

    for (;;) {
        if (l > u)
            return -1;

        m = (l + u) / 2;

        if (x[m] < t)
            l = m+1;
        else if (x[m] == t)
            return m;
        else /* x[m] > t */
            u = m-1;
    }
}

/* Alg 2: Make binarysearch1 more c-ish */

int binarysearch2(int* x, const size_t & n, int t) {
    int l, u, m;
    l = 0;
    u = n-1;

    while (l <= u) {
        m = (l + u) / 2;

        if (x[m] < t)
            l = m+1;
        else if (x[m] == t)
            return m;
        else /* x[m] > t */
            u = m-1;
    }
    return -1;
}

/* Alg 3: From PP, Col 9, Page 93 */

int binarysearch3(int* x, const size_t & n, int t) {
    int l, u, m;
    l = -1;
    u = n;

    while (l+1 != u) {
        m = (l + u) / 2;

        if (x[m] < t)
            l = m;
        else
            u = m;
    }

    if (u >= n || x[u] != t)
        return -1;
    return u;
}

/* Alg 4: From PP, Col 9 */

int binarysearch4(int* x, const size_t & n, int t) {
    int l, p;
    if (n != 1000)
        return binarysearch3(x, n, t);

    l = -1;
    if (x[511]   < t) l = 1000 - 512;
    if (x[l+256] < t) l += 256;
    if (x[l+128] < t) l += 128;
    if (x[l+64 ] < t) l += 64;
    if (x[l+32 ] < t) l += 32;
    if (x[l+16 ] < t) l += 16;
    if (x[l+8  ] < t) l += 8;
    if (x[l+4  ] < t) l += 4;
    if (x[l+2  ] < t) l += 2;
    if (x[l+1  ] < t) l += 1;

    p = l+1;

    if (p >= n || x[p] != t)
        return -1;
    return p;
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
            l = m;
        else if (x[m] > t)
            u = m;
        else {
            /* assert(x[m] == t); */
            return m;
        }
    }
    /* assert(x[l] > t && x[u] < t); */
    return -1;
}

/* Alg 21: Simple sequential search */

int seqsearch1(int* x, const size_t & n, int t) {
    int i;
    for (i = 0; i < n; i++)
        if (x[i] == t)
            return i;
    return -1;
}

/* Alg 22: Faster sequential search: Sentinel */

int seqsearch2(int* x, const size_t & n, int t) {
    int i;
    int hold = x[n];
    x[n] = t;
    for (i = 0; ; i++)
        if (x[i] == t)
            break;
    x[n] = hold;
    if (i == n)
        return -1;
    else
        return i;
}

/* Alg 23: Faster sequential search: loop unrolling */

int seqsearch3(int* x, const size_t & n, int t) {
    int i;
    int hold = x[n];
    x[n] = t;
    for (i = 0; ; i+=8) {
        if (x[i] == t)   {          break; }
        if (x[i+1] == t) { i += 1; break; }
        if (x[i+2] == t) { i += 2; break; }
        if (x[i+3] == t) { i += 3; break; }
        if (x[i+4] == t) { i += 4; break; }
        if (x[i+5] == t) { i += 5; break; }
        if (x[i+6] == t) { i += 6; break; }
        if (x[i+7] == t) { i += 7; break; }
    }
    x[n] = hold;
    if (i == n)
        return -1;
    else
        return i;
}

#endif //PROGRAMMING_PEARLS_COLUMN5_H
