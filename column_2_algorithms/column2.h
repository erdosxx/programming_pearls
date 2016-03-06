#ifndef PROGRAMMING_PEARLS_COLUMN2_H
#define PROGRAMMING_PEARLS_COLUMN2_H

#include <stdio.h>

/* Alg 1: Rotate by reversal */

void reverse(int* x,  int i, int j) {
    int t;
    while (i < j) {
        t = x[i]; x[i] = x[j]; x[j] = t;
        i++;
        j--;
    }
}

void revrot(int* x, int rotdist, int n) {
    reverse(x, 0, rotdist-1);
    reverse(x, rotdist, n-1);
    reverse(x, 0, n-1);
}

/* Alg 2: Juggling (dolphin) rotation */

int gcd(int i, int j) {
    int t;
    while (i != 0) {
        if (j >= i)
            j -= i;
        else {
            t = i; i = j; j = t;
        }
    }
    return j;
}

void jugglerot(int* x, int rotdist, int n) {
    int cycles, i, j, k, t;
    cycles = gcd(rotdist, n);
//    printf("gcd(%d, %d) = %d\n",
//           rotdist, n, cycles);

    for (i = 0; i < cycles; i++) {
        /* move i-th values of blocks */
        t = x[i];
//        printf("t   = [%d]\n", i);
        j = i;
        for (;;) {
            k = j + rotdist;
            if (k >= n)
                k -= n;
            if (k == i)
                break;
//            printf("[%d] = [%d]\n", j, k);
            x[j] = x[k];
            j = k;
        }
//        printf("[%d] = t\n", j);
        x[j] = t;
    }
}

void jugglerot2(int* x, int rotdist, int n) {
    int cycles, i, j, k, t;
    cycles = gcd(rotdist, n);
//    printf("gcd(%d, %d) = %d\n",
//           rotdist, n, cycles);
    for (i = 0; i < cycles; i++) {
        /* move i-th values of blocks */
        t = x[i];
//        printf("t   = [%d]\n", i);
        j = i;
        for (;;) {
            /* Replace with mod below
               k = j + rotdist;
               if (k >= n)
               k -= n;
               */
            k = (j + rotdist) % n;
            if (k == i)
                break;
//            printf("[%d] = [%d]\n", j, k);
            x[j] = x[k];
            j = k;
        }
//        printf("[%d] = t\n", j);
        x[j] = t;
    }
}

/* Alg 3: Recursive rotate (using gcd structure) */

void swap(int* x, int i, int j, int k) /* swap x[i..i+k-1] with x[j..j+k-1] */ {
    int t;
    while (k-- > 0) {
        t = x[i]; x[i] = x[j]; x[j] = t;
        i++;
        j++;
    }
}

void gcdrot(int* x, int rotdist, int n) {
    int i, j, p;
    if (rotdist == 0 || rotdist == n)
        return;
    i = p = rotdist;
    j = n - p;
    while (i != j) {
        /* invariant:
           x[0  ..p-i  ] is in final position
           x[p-i..p-1  ] = a (to be swapped with b)
           x[p  ..p+j-1] = b (to be swapped with a)
           x[p+j..n-1  ] in final position
           */
        if (i > j) {
            swap(x, p-i, p, j);
            i -= j;
        } else {
            swap(x, p-i, p+j-i, i);
            j -= i;
        }
    }
    swap(x, p-i, p, i);
}

int isogcd(int i, int j) {
    if (i == 0) return j;
    if (j == 0) return i;
    while (i != j) {
        if (i > j)
            i -= j;
        else
            j -= i;
    }
    return i;
}

#endif //PROGRAMMING_PEARLS_COLUMN2_H
