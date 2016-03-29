#ifndef PROGRAMMING_PEARLS_PRIQUEUE_H
#define PROGRAMMING_PEARLS_PRIQUEUE_H

/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* priqueue.cpp -- priority queues (using heaps) */
// define and implement priority queues

template<class T>
class min_priqueue {
private:
	int size_x, _maxsize;
	T	*x;

	void swap(int i, int j) {
		T tmp = x[i];
        x[i] = x[j];
        x[j] = tmp;
    }

public:
	min_priqueue(int maxsize) {
        _maxsize = maxsize;
		x = new T[_maxsize + 1];
		size_x = 0;
	}

	void insert(T value) {
        int parent;
		x[++size_x] = value;
		for (int i = size_x; i > 1 && x[parent = i / 2] > x[i]; i = parent)
			swap(parent, i);
	}

	T extractmin() {
        int child;
		T minval = x[1];
		x[1] = x[size_x--];

		for (int i = 1; (child = 2 * i) <= size_x; i = child) {
			if (child + 1 <= size_x && x[child + 1] < x[child])
				child++;
			if (x[i] <= x[child])
				break;
			swap(child, i);
		}
		return minval;
	}
};

// sort with priority queues (heap sort is strictly better)

template<class T>
void pqsort(T* v, const int size_v) {
    min_priqueue<T> pq(size_v);

	for (int i = 0; i < size_v; i++)
		pq.insert(v[i]);

	for (int i = 0; i < size_v; i++)
		v[i] = pq.extractmin();
}

#endif
