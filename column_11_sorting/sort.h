#ifndef PROGRAMMING_PEARLS_SORT_H
#define PROGRAMMING_PEARLS_SORT_H

#include <stdlib.h>

void swap(int* x, int i, int j) {
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
void isort2(int* x, int n) {
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
void isort3(int* x, int n) {
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
void qsort1(int* x, int l, int u) {
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
void qsort2(int* x, int l, int u) {
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
void qsort3(int* x, int l, int u) {
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
void qsort4(int* x, int l, int u, int cutoff) {
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

void select1(int* x,  int l, int u, int k) {
    int i, j;
    int t, temp;
    if (l >= u)
        return;
    swap(x, l, randint(l, u));
    t = x[l];
    i = l;
    j = u+1;
    for (;;) {
        do i++; while (i <= u && x[i] < t);
        do j--; while (x[j] > t);
        if (i > j)
            break;
        temp = x[i]; x[i] = x[j]; x[j] = temp;
    }
    swap(x, l, j);
    if (j < k)
        select1(x, j+1, u, k);
    else if (j > k)
        select1(x, l, j-1, k);
}

/* HEAP SORTS */

void siftup(int* x, int u) {
    int i, p;
    i = u;
    for (;;) {
        if (i == 1)
            break;
        p = i / 2;
        if (x[p] >= x[i])
            break;
        swap(x, p, i);
        i = p;
    }
}

void siftdown1(int* x, int l, int u) {
    int i, c;
    i = l;
    for (;;) {
        c = 2*i;
        if (c > u)
            break;
        if (c+1 <= u && x[c+1] > x[c])
            c++;
        if (x[i] > x[c])
            break;
        swap(x, i, c);
        i = c;
    }
}

void siftdown1b(int* x, int l, int u) /* More C-ish version of 1 */ {
    int i, c;
    for (i = l; (c = 2*i) <= u; i = c) {
        if (c+1 <= u && x[c+1] > x[c])
            c++;
        if (x[i] > x[c])
            break;
        swap(x, i, c);
    }
}

void hsort1(int* x, int n) {
    int i;
    x--;
    for (i = 2; i <= n; i++)
        siftup(x, i);
    for (i = n; i >= 2; i--) {
        swap(x, 1, i);
        siftdown1(x, 1, i-1);
    }
    x++;
}

void hsort2(int* x, int n) {
    int i;
    x--;
    for (i = n/2; i >= 1; i--)
        siftdown1(x, i, n);
    for (i = n; i >= 2; i--) {
        swap(x, 1, i);
        siftdown1(x, 1, i-1);
    }
    x++;
}

void siftdown3(int* x, int l, int u) /* push to bottom, then back up */ {
    int i, c, p;
    i = l;
    for (;;) {
        c = 2*i;
        if (c > u)
            break;
        if (c+1 <= u && x[c+1] > x[c])
            c++;
        swap(x, i, c);
        i = c;
    }
    for (;;) {
        p = i/2;
        if (p < l)
            break;
        if (x[p] > x[i])
            break;
        swap(x, p, i);
        i = p;
    }
}

void hsort3(int* x, int n) {
    int i;
    x--;
    for (i = n/2; i >= 1; i--)
        siftdown3(x, i, n);
    for (i = n; i >= 2; i--) {
        swap(x, 1, i);
        siftdown3(x, 1, i-1);
    }
    x++;
}

void siftdown4(int* x, int l, int u) /* replace swap with assignments */ {
    int i, c, p;
    int t;
    t = x[l];
    i = l;
    for (;;) {
        c = 2*i;
        if (c > u)
            break;
        if (c+1 <= u && x[c+1] > x[c])
            c++;
        x[i] = x[c];
        i = c;
    }
    x[i] = t;
    for (;;) {
        p = i/2;
        if (p < l)
            break;
        if (x[p] > x[i])
            break;
        swap(x, p, i);
        i = p;
    }
}

void hsort4(int* x, int n) {
    int i;
    x--;
    for (i = n/2; i >= 1; i--)
        siftdown4(x, i, n);
    for (i = n; i >= 2; i--) {
        swap(x, 1, i);
        siftdown4(x, 1, i-1);
    }
    x++;
}

void selsort(int* x, int n)  /* Selection sort */ {
    int i, j;
    for (i = 0; i < n-1; i++)
        for (j = i; j < n; j++)
            if (x[j] < x[i])
                swap(x, i, j);
}

void shellsort(int* x, int n) {
    int i, j, h;
    for (h = 1; h < n; h = 3*h + 1)
        ;
    for (;;) {
        h /= 3;
        if (h < 1) break;
        for (i = h; i < n; i++) {
            for (j = i; j >= h; j -= h) {
                if (x[j-h] < x[j]) break;
                swap(x, j-h, j);
            }
        }
    }
}

#endif //PROGRAMMING_PEARLS_SORT_H
