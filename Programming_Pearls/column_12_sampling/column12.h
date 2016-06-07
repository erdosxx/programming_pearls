#ifndef PROGRAMMING_PEARLS_COLUMN12_H
#define PROGRAMMING_PEARLS_COLUMN12_H

#include <stdlib.h>
#include <set>
#include <iostream>

using namespace std;

int randint(int l, int u) {
    return l + rand() % (u-l+1);
}

void genknuth(int* output, int num_gen, const int supremum) {
    int j = 0;

    for (int i = 0; i < supremum; i++)
        /* select m of remaining n-i */
        if ((rand() % (supremum - i)) < num_gen) {
            output[j++] = i;
            //cout << i << "\n";
            num_gen--;
        }
}

void gensets(int* output, int num_gen, const int supremum) {
    set<int> S;

    while (S.size() < num_gen) {
        int t = rand() % supremum;
        S.insert(t);
    }

    int j=0;
    set<int>::iterator i;
    for (i = S.begin(); i != S.end(); ++i)
        output[j++] = *i;
        // cout << *i << "\n";

}

void genshuf(int* output, int num_gen, const int supremum) {
    int *x = new int[supremum];

    for (int i = 0; i < supremum; i++)
        x[i] = i;

    int j;
    for (int i = 0; i < num_gen; i++) {
        j = randint(i, supremum - 1);
        int t = x[i]; x[i] = x[j]; x[j] = t;
    }

    sort(x, x + num_gen);

    for (int i = 0; i < num_gen; i++)
        output[i] = x[i];
        //cout << x[i] << "\n";
}

// See TAOCP II p.148 #17
void genfloyd(int* output, int num_gen, const int supremum) {
    set<int> S;

    for (int j = supremum - num_gen; j < supremum; j++) {
        int t = rand() % (j+1);   // 0,1,2, ... ,j
        if (S.find(t) == S.end()) // t not in S
            S.insert(t);
        else                      // t in S
            S.insert(j);
    }

    int k=0;
    set<int>::iterator i;

    for (i = S.begin(); i != S.end(); ++i)
        output[k++] = *i;
        //cout << *i << "\n";
}

#endif //PROGRAMMING_PEARLS_COLUMN12_H
