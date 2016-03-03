#ifndef PROGRAMMING_PEARLS_SORT_H
#define PROGRAMMING_PEARLS_SORT_H

#include <stdlib.h>

void swap(int x[], int i, int j) {
    int t = x[i];
    x[i] = x[j];
    x[j] = t;
}

void insertionSort(int *x, int n) {
    int i, j;
    for (i = 1; i < n; i++)
        for (j = i; j > 0 && x[j - 1] > x[j]; j--)
            swap(x, j - 1, j);
}

/* Write swap function inline */
void isort2(int x[], int n) {
    int i, j;
    int t;
    for (i = 1; i < n; i++)
        for (j = i; j > 0 && x[j - 1] > x[j]; j--) {
            t = x[j];
            x[j] = x[j - 1];
            x[j - 1] = t;
        }
}

/* Move assignments to and from t out of loop */
void isort3(int x[], int n) {
    int i, j;
    int t;
    for (i = 1; i < n; i++) {
        t = x[i];
        for (j = i; j > 0 && x[j - 1] > t; j--)
            x[j] = x[j - 1];
        x[j] = t;
    }
}

/* QUICKSORTS */
/* Simplest version, Lomuto partitioning */
void qsort1(int x[], int l, int u) {
    int i, m;
    if (l >= u)
        return;
    m = l;
    for (i = l + 1; i <= u; i++)
        if (x[i] < x[l])
            swap(x, ++m, i);
    swap(x, l, m);
    qsort1(x, l, m - 1);
    qsort1(x, m + 1, u);
}

/* Sedgewick's version of Lomuto, with sentinel */
void qsort2(int x[], int l, int u) {
    int i, m;
    if (l >= u)
        return;
    m = i = u + 1;
    do {
        do i--; while (x[i] < x[l]);
        swap(x, --m, i);
    } while (i > l);
    qsort2(x, l, m - 1);
    qsort2(x, m + 1, u);
}

/* Two-way partitioning */
void qsort3(int x[], int l, int u) {
    int i, j;
    int t;
    if (l >= u)
        return;
    t = x[l];
    i = l;
    j = u + 1;
    for (; ;) {
        do i++; while (i <= u && x[i] < t);
        do j--; while (x[j] > t);
        if (i > j)
            break;
        swap(x, i, j);
    }
    swap(x, l, j);
    qsort3(x, l, j - 1);
    qsort3(x, j + 1, u);
}

int randint(int l, int u) {
    //return l + (RAND_MAX * rand() + rand()) % (u - l + 1);
    return l + (rand() % (u - l + 1));
}

/* qsort3 + randomization + isort small subarrays + swap inline */
void qsort4(int x[], int l, int u, int cutoff) {
    int i, j;
    int t, temp;
    if (u - l < cutoff)
        return;
    swap(x, l, randint(l, u));
    t = x[l];
    i = l;
    j = u + 1;
    for (; ;) {
        do i++; while (i <= u && x[i] < t);
        do j--; while (x[j] > t);
        if (i > j)
            break;
        temp = x[i];
        x[i] = x[j];
        x[j] = temp;
    }
    swap(x, l, j);
    qsort4(x, l, j - 1, cutoff);
    qsort4(x, j + 1, u, cutoff);
}

#endif //PROGRAMMING_PEARLS_SORT_H
