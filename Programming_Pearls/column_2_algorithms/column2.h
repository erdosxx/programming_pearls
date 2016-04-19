#ifndef PROGRAMMING_PEARLS_COLUMN2_H
#define PROGRAMMING_PEARLS_COLUMN2_H

#include <stdio.h>
#include <vector>
#include <stdlib.h>

// see: http://www.drdobbs.com/go-parallel/article/print?articleId=232900395&siteSectionName=
//      http://homes.soic.indiana.edu/classes/fall2014/csci/c343-jsiek/lectures/lecture2.txt
//      http://arxiv.org/pdf/1406.5453.pdf

/* Alg 1: Rotate by reversal */

void reverse(int* x, int start, int end) {
    int tmp;
    /*
    while (start < end) {
        tmp = x[start]; x[start] = x[end]; x[end] = tmp;
        start++;
        end--;
    }
     */
    for ( ; start< end; start++, end--){
        tmp = x[start]; x[start] = x[end]; x[end] = tmp;
    }
}

void revrot(int* x, const int rotdist, const int size_ary) {
    reverse(x, 0, rotdist-1);
    reverse(x, rotdist, size_ary-1);
    reverse(x, 0, size_ary-1);
}

/* Alg 2: Juggling (dolphin) rotation */

int gcd(int i, int j) {
    int tmp;
    while (i != 0) {
        if (j >= i)
            j -= i;
        else {
            tmp = i; i = j; j = tmp;
        }
    }
    return j;
}

void jugglerot(int* x, const int rotdist, const int size_ary) {
    int cycles, dest_idx, source_idx, tmp;
    cycles = gcd(rotdist, size_ary);

    for (int i = 0; i < cycles; i++) {
        /* move i-th values of blocks */
        tmp = x[i];
        dest_idx = i;
        for (;;) {
            source_idx = dest_idx + rotdist;
            if (source_idx >= size_ary)
                source_idx -= size_ary;
            if (source_idx == i)
                break;

            x[dest_idx] = x[source_idx];
            dest_idx = source_idx;
        }

        x[dest_idx] = tmp;
    }
}

void jugglerot2(int* x, const int rotdist, const int size_ary) {
    int cycles, dest_idx, source_idx, tmp;
    cycles = gcd(rotdist, size_ary);

    for (int i = 0; i < cycles; i++) {
        /* move i-th values of blocks */
        tmp = x[i];
        dest_idx = i;
        for (;;) {
            source_idx = (dest_idx + rotdist) % size_ary;

            if (source_idx == i)
                break;

            x[dest_idx] = x[source_idx];
            dest_idx = source_idx;
        }

        x[dest_idx] = tmp;
    }
}

/* Alg 3: Recursive rotate (using gcd structure) */

/* swap x[i..i+k-1] with x[j..j+k-1] */
void swapequals(int *x, int i, int j, int k) {
    int tmp;
    while (k-- > 0) {
        tmp = x[i]; x[i] = x[j]; x[j] = tmp;
        i++;
        j++;
    }
}

// see: Gries and Mills Block Swapping in
// http://www.drdobbs.com/go-parallel/article/print?articleId=232900395&siteSectionName=
/* Problem 2.3 */
void gcdrot(int* x, const int rotdist, const int size_ary) {
    if (rotdist == 0 || rotdist == size_ary)
        return;

    int i = rotdist;
    int j = size_ary - rotdist;

    while (i != j) {
        /* invariant:
           x[0  ..rotdist-i-1  ] is in final position
           x[rotdist-i..rotdist-1  ] = a (to be swapped with b)   # = i
           x[rotdist  ..rotdist+j-1] = b (to be swapped with a)   # = j
           x[rotdist+j..n-1  ] in final position
           */
        if (i > j) {
            swapequals(x, rotdist - i, rotdist, j);
            i -= j;
        } else {
            swapequals(x, rotdist - i, rotdist + j - i, i);
            j -= i;
        }
    }
    swapequals(x, rotdist - i, rotdist, i);
}

void swap_sections(int* x, int m, int n, int p);

void gcdrot_rec(int* x, const int rotdist, const int size_ary) {
    swap_sections(x, 0, rotdist, size_ary);
}

void swap_sections(int* x, int m, int n, int p) {
    if (n - m == p - n) {
        swapequals(x, m, n, p - n);
    } else if (n - m > p - n) {
        swapequals(x, m, n, p - n);
        swap_sections(x, p-n+m, n, p);
    } else if (n - m < p - n) {
        swapequals(x, m, p-n+m, n - m);
        swap_sections(x, m, n, p-n+m);
    }
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

template <typename datatype>
void std_rot(std::vector<datatype> & target_array, const int & rotdist) {
    std::rotate(target_array.begin(), target_array.begin()+rotdist, target_array.end());
}

int charcomp(const void *x, const void *y) {
  return *(char *)x - *(char *)y;
}

void getsign(char* word, char* sig) {
  strcpy(sig, word);
  qsort(sig, strlen(sig), sizeof(char), charcomp);
}
#endif //PROGRAMMING_PEARLS_COLUMN2_H
