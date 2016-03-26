#ifndef PROGRAMMING_PEARLS_SORT_H
#define PROGRAMMING_PEARLS_SORT_H

void build_heap_with_siftdown(int *x, const int size_ary);
void build_heap_with_siftup(int *x, const int size_ary);
int get_larger_child(int* x, int& current_idx, const int max_idx);

int push_to_bottom(int *x, const int max_idx, int current_idx);
void back_bottom_to_up(int *x, const int target_idx, int current_idx);

int push_to_bottom2(int *x, int target_idx, int max_idx, int current_idx);

#include <stdlib.h>

void swap(int* x, int i, int j) {
    int t = x[i];
    x[i] = x[j];
    x[j] = t;
}

/* invariant: x[0..i-1] is sorted
 * goal: shift x[i] down to its
 * proper place in x[0..i]
 */
void insertionSort(int *x, const int size_ary) {
    for (int i = 1; i < size_ary; i++)
        for (int j = i; j > 0 && x[j - 1] > x[j]; j--)
            swap(x, j - 1, j);
}

/* Write swap function inline */
void insertionSort2(int *x, int size_ary) {
    int t;
    for (int i = 1; i < size_ary; i++)
        for (int j = i; j > 0 && x[j - 1] > x[j]; j--) {
            t = x[j];
            x[j] = x[j - 1];
            x[j - 1] = t;
        }
}

/* Move assignments to and from t out of loop */
void insertionSort3(int *x, int size_ary) {
    int t, j;
    for (int i = 1; i < size_ary; i++) {
        t = x[i];
        for (j = i; j > 0 && x[j - 1] > t; j--)
            x[j] = x[j - 1];
        x[j] = t;
    }
}

/* QUICKSORTS */
/* Simplest version, Lomuto partitioning */
void qsort1(int* x, int min_idx, int max_idx) {
    if (min_idx >= max_idx)
        return;

    int boundary_idx = min_idx;
    int pivot = x[min_idx];

    for (int i = min_idx + 1; i <= max_idx; i++)
        if (x[i] < pivot)
            swap(x, ++boundary_idx, i);

    swap(x, min_idx, boundary_idx);
    qsort1(x, min_idx, boundary_idx - 1);
    qsort1(x, boundary_idx + 1, max_idx);
}

/* Sedgewick's version of Lomuto, with sentinel */
void qsort2(int* x, int min_idx, int max_idx) {
    if (min_idx >= max_idx)
        return;

    int pivot = x[min_idx];

    int boundary_idx = max_idx + 1;

    int i = boundary_idx;
    do {
        do i--; while (x[i] < pivot);
        swap(x, --boundary_idx, i);
    } while (i > min_idx);

    qsort2(x, min_idx, boundary_idx - 1);
    qsort2(x, boundary_idx + 1, max_idx);
}

/* Two-way partitioning */
void qsort3(int* x, int min_idx, int max_idx) {
    if (min_idx >= max_idx)
        return;

    int pivot = x[min_idx];
    int low_boundary = min_idx;
    int high_boundary = max_idx + 1;

    for (; ;) {
        do low_boundary++; while (low_boundary <= max_idx && x[low_boundary] < pivot);
        do high_boundary--; while (x[high_boundary] > pivot);
        if (low_boundary > high_boundary)
            break;
        swap(x, low_boundary, high_boundary);
    }

    swap(x, min_idx, high_boundary);
    qsort3(x, min_idx, high_boundary - 1);
    qsort3(x, high_boundary + 1, max_idx);
}

int randint(int l, int u) {
    //return l + (RAND_MAX * rand() + rand()) % (u - l + 1);
    return l + (rand() % (u - l + 1));
}

/* qsort3 + randomization + isort small subarrays + swap inline */
void qsort4(int* x, int min_idx, int max_idx, int cutoff) {
    if (max_idx - min_idx < cutoff)
        return;

    swap(x, min_idx, randint(min_idx, max_idx));

    int pivot = x[min_idx];

    int low_boundary = min_idx;
    int high_boundary = max_idx + 1;

    int temp;
    for (; ;) {
        do low_boundary++; while (low_boundary <= max_idx && x[low_boundary] < pivot);
        do high_boundary--; while (x[high_boundary] > pivot);
        if (low_boundary > high_boundary)
            break;
        temp = x[low_boundary];
        x[low_boundary] = x[high_boundary];
        x[high_boundary] = temp;
    }

    swap(x, min_idx, high_boundary);
    qsort4(x, min_idx, high_boundary - 1, cutoff);
    qsort4(x, high_boundary + 1, max_idx, cutoff);
}

void select1(int* x, int min_idx, int max_idx, int kth) {
    if (min_idx >= max_idx)
        return;
    swap(x, min_idx, randint(min_idx, max_idx));

    int pivot = x[min_idx];
    int low_boundary = min_idx;
    int high_boundary = max_idx + 1;

    int temp;
    for (;;) {
        do low_boundary++; while (low_boundary <= max_idx && x[low_boundary] < pivot);
        do high_boundary--; while (x[high_boundary] > pivot);
        if (low_boundary > high_boundary)
            break;
        temp = x[low_boundary]; x[low_boundary] = x[high_boundary]; x[high_boundary] = temp;
    }

    swap(x, min_idx, high_boundary);
    if (high_boundary < kth)
        select1(x, high_boundary + 1, max_idx, kth);
    else if (high_boundary > kth)
        select1(x, min_idx, high_boundary - 1, kth);
}

/* HEAP SORTS */

void maxheap_siftup(int *x, const int idx) {
    enum {TOP_NODE=1};
    int current_idx, parent;
    current_idx = idx;
    /*
     * invariant: heap(1..n) except perhaps
     * between i and its parent
     */
    for (;;) {
        if (current_idx == TOP_NODE)
            break;
        parent = current_idx / 2;
        if (x[parent] >= x[current_idx])
            break;
        swap(x, parent, current_idx);
        current_idx = parent;
    }
}

void maxheap_siftdown1(int *x, int target_idx, const int max_idx) {
    enum {NO_CHILD=-1};

    int child;
    int current_idx = target_idx;

    for (;;) {
        child = get_larger_child(x, current_idx, max_idx);
        if (child == NO_CHILD)
            break;

        if (x[current_idx] > x[child])
            break;
        swap(x, current_idx, child);
        current_idx = child;
    }
}

int get_larger_child(int* x, int& current_idx, const int max_idx){
    enum {NO_CHILD= -1};
    int child = 2 * current_idx;

    if (child > max_idx)
        return NO_CHILD;
    if (child + 1 <= max_idx && x[child + 1] > x[child])
        child++;

    return child;
}

/*
 * for loop changes in mexheap_siftdown1
 */
void maxheap_siftdown2(int *x, int target_idx, const int max_idx) {
    int current_idx, child;

    for (current_idx = target_idx; (child = 2 * current_idx) <= max_idx; current_idx = child) {
        if (child + 1 <= max_idx && x[child + 1] > x[child])
            child++;
        if (x[current_idx] > x[child])
            break;
        swap(x, current_idx, child);
    }
}

void hsort1(int* x, const int size_ary) {
    x--;  // change x to 1-based array

    build_heap_with_siftup(x, size_ary);

    for (int i = size_ary; i >= 2; i--) {
        swap(x, 1, i);
        maxheap_siftdown1(x, 1, i - 1);
    }

    x++;  // restore x to 0-based array
}

void hsort1b(int* x, const int size_ary) {
    x--;  // change x to 1-based array

    build_heap_with_siftup(x, size_ary);

    for (int i = size_ary; i >= 2; i--) {
        swap(x, 1, i);
        maxheap_siftdown2(x, 1, i - 1);
    }

    x++;  // restore x to 0-based array
}

void build_heap_with_siftup(int *x, const int size_ary) {
    for (int i = 2; i <= size_ary; i++)
        maxheap_siftup(x, i);
}

void hsort2(int* x, const int size_ary) {
    x--;

    build_heap_with_siftdown(x, size_ary);

    for (int i = size_ary; i >= 2; i--) {
        swap(x, 1, i);
        maxheap_siftdown1(x, 1, i - 1);
    }

    x++;
}

void build_heap_with_siftdown(int *x, const int size_ary) {
    for (int i = size_ary / 2; i >= 1; i--)
        maxheap_siftdown1(x, i, size_ary);
}

/* push to bottom, then back up */
void max_heap_siftdown3(int *x, const int target_idx, const int max_idx) {
    int current_idx = target_idx;

    current_idx = push_to_bottom(x, max_idx, current_idx);
    back_bottom_to_up(x, target_idx, current_idx);
}

int push_to_bottom(int *x, const int max_idx, int current_idx) {
    int child;

    for (;;) {
        child = 2 * current_idx;
        if (child > max_idx)
            break;
        if (child + 1 <= max_idx && x[child + 1] > x[child])
            child++;
        swap(x, current_idx, child);
        current_idx = child;
    }
    return current_idx;
}

void back_bottom_to_up(int *x, const int target_idx, int current_idx) {
    int parent;

    for (;;) {
        parent = current_idx / 2;
        if (parent < target_idx)
            break;
        if (x[parent] > x[current_idx])
            break;
        swap(x, parent, current_idx);
        current_idx = parent;
    }
}

void hsort3(int* x, const int size_ary) {
    x--;

    for (int i = size_ary / 2; i >= 1; i--)
        max_heap_siftdown3(x, i, size_ary);

    for (int i = size_ary; i >= 2; i--) {
        swap(x, 1, i);
        max_heap_siftdown3(x, 1, i - 1);
    }

    x++;
}

/* replace swap with assignments */
void max_heap_siftdown4(int *x, int target_idx, int max_idx) {
    int current_idx = target_idx;

    current_idx = push_to_bottom2(x, target_idx, max_idx, current_idx);

    back_bottom_to_up(x, target_idx, current_idx);
}

int push_to_bottom2(int *x, int target_idx, int max_idx, int current_idx) {
    int child;

    int tmp = x[target_idx];
    for (;;) {
        child = 2 * current_idx;
        if (child > max_idx)
            break;
        if (child + 1 <= max_idx && x[child + 1] > x[child])
            child++;
        x[current_idx] = x[child];
        current_idx = child;
    }
    x[current_idx] = tmp;

    return current_idx;
}

void hsort4(int* x, const int size_ary) {
    x--;

    for (int i = size_ary / 2; i >= 1; i--)
        max_heap_siftdown4(x, i, size_ary);

    for (int i = size_ary; i >= 2; i--) {
        swap(x, 1, i);
        max_heap_siftdown4(x, 1, i - 1);
    }

    x++;
}

/* Selection sort */
void selsort(int* x, const int size_ary) {
    for (int i = 0; i < size_ary - 1; i++)
        for (int j = i; j < size_ary; j++)
            if (x[j] < x[i])
                swap(x, i, j);
}

void shellsort(int* x, int size_ary) {
    int gap;
    for (gap = 1; gap < size_ary; gap = 3 * gap + 1)
        ;

    for (;;) {
        gap /= 3;
        if (gap < 1) break;
        for (int i = gap; i < size_ary; i++) {
            for (int j = i; j >= gap; j -= gap) {
                if (x[j - gap] < x[j]) break;
                swap(x, j - gap, j);
            }
        }
    }
}

#endif //PROGRAMMING_PEARLS_SORT_H
