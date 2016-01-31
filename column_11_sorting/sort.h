//
// Created by In Soo Oh on 1/31/16.
//

#ifndef PROGRAMMING_PEARLS_SORT_H
#define PROGRAMMING_PEARLS_SORT_H

void swap(int x[], int i, int j) {
    int t = x[i];
    x[i] = x[j];
    x[j] = t;
}

void isort1(int x[], int n) {
    int i, j;
    for (i = 1; i < n; i++)
        for (j = i; j > 0 && x[j - 1] > x[j]; j--)
            swap(x, j - 1, j);
}

#endif //PROGRAMMING_PEARLS_SORT_H
