#ifndef PROGRAMMING_PEARLS_COLUMN2_H
#define PROGRAMMING_PEARLS_COLUMN2_H

#include <stdio.h>
#include <vector>
#include <stdlib.h>

// see: http://www.drdobbs.com/go-parallel/article/print?articleId=232900395&siteSectionName=
//      http://homes.soic.indiana.edu/classes/fall2014/csci/c343-jsiek/lectures/lecture2.txt
//      http://arxiv.org/pdf/1406.5453.pdf

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

    for (i = 0; i < cycles; i++) {
        /* move i-th values of blocks */
        t = x[i];
        j = i;
        for (;;) {
            k = j + rotdist;
            if (k >= n)
                k -= n;
            if (k == i)
                break;

            x[j] = x[k];
            j = k;
        }

        x[j] = t;
    }
}

void jugglerot2(int* x, int rotdist, int n) {
    int cycles, i, j, k, t;
    cycles = gcd(rotdist, n);

    for (i = 0; i < cycles; i++) {
        /* move i-th values of blocks */
        t = x[i];
        j = i;
        for (;;) {
            k = (j + rotdist) % n;

            if (k == i)
                break;

            x[j] = x[k];
            j = k;
        }

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

void gcdrot(int* x, const int & rotdist, const int & n) {
    int i, j;
    if (rotdist == 0 || rotdist == n)
        return;
    i = rotdist;
    j = n - rotdist;
    while (i != j) {
        /* invariant:
           x[0  ..rotdist-i-1  ] is in final position
           x[rotdist-i..rotdist-1  ] = a (to be swapped with b)   # = j
           x[rotdist  ..rotdist+j-1] = b (to be swapped with a)   # = j
           x[rotdist+j..n-1  ] in final position
           */
        if (i > j) {
            swap(x, rotdist-i, rotdist, j);
            i -= j;
        } else {
            swap(x, rotdist-i, rotdist+j-i, i);
            j -= i;
        }
    }
    swap(x, rotdist-i, rotdist, i);
}

template <typename datatype>
void std_rot(std::vector<datatype> & target_array, const int & rotdist) {
    std::rotate(target_array.begin(), target_array.begin()+rotdist, target_array.end());
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

int charcomp(const void *x, const void *y) {
  return *(char *)x - *(char *)y;
}

void getsign(char* word, char* sig) {
  strcpy(sig, word);
  qsort(sig, strlen(sig), sizeof(char), charcomp);
}
#endif //PROGRAMMING_PEARLS_COLUMN2_H
