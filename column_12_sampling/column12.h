#ifndef PROGRAMMING_PEARLS_COLUMN12_H
#define PROGRAMMING_PEARLS_COLUMN12_H

#include <stdlib.h>
#include <set>
#include <iostream>

using namespace std;

int randint(int l, int u) {
    return l + rand() % (u-l+1);
}

void genknuth(int* output, int m, int n) {
    int j = 0;
    for (int i = 0; i < n; i++)
        /* select m of remaining n-i */
        if ((rand() % (n-i)) < m) {
            output[j++] = i;
            //cout << i << "\n";
            m--;
        }
}

void gensets(int* output, int m, int n) {
    set<int> S;
    set<int>::iterator i;

    while (S.size() < m) {
        int t = rand() % n;
        S.insert(t);
    }

    int j=0;
    for (i = S.begin(); i != S.end(); ++i)
        output[j++] = *i;
        // cout << *i << "\n";

}

void genshuf(int* output, int m, int n) {
    int i, j;
    int *x = new int[n];

    for (i = 0; i < n; i++)
        x[i] = i;

    for (i = 0; i < m; i++) {
        j = randint(i, n-1);
        int t = x[i]; x[i] = x[j]; x[j] = t;
    }

    sort(x, x+m);

    for (i = 0; i < m; i++)
        output[i] = x[i];
        //cout << x[i] << "\n";
}

void genfloyd(int* output, int m, int n) {
    set<int> S;
    set<int>::iterator i;

    for (int j = n-m; j < n; j++) {
        int t = rand() % (j+1);
        if (S.find(t) == S.end())
            S.insert(t); // t not in S
        else
            S.insert(j); // t in S
    }

    int k=0;
    for (i = S.begin(); i != S.end(); ++i)
        output[k++] = *i;
        //cout << *i << "\n";
}

#endif //PROGRAMMING_PEARLS_COLUMN12_H
