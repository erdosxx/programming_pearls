//
// Created by In Soo Oh on 3/4/16.
//

#ifndef PROGRAMMING_PEARLS_COLUMN1_H
#define PROGRAMMING_PEARLS_COLUMN1_H

#include <set>
#include <stdbool.h>

#define SHIFT 5  // log2(BITSPERWORD); i.e. how many numbers we can
                 // store per element in the array[].
#define MASK 0x1F // i.e. 0001 1111 (5 bits) to mask of all but the contents.


void set(int *a, int i) {
    //a[i>>SHIFT] |= (1<<(i & MASK));
    // above is equivalent to the following code
    //a[i/32] |= (1<<(i % 32));
    int i_quotient_by_32 = i >> SHIFT;
    int i_remainder_by_32 = i & MASK;
    int get_1_position_by_remainder_shift = 1 << i_remainder_by_32;
    a[i_quotient_by_32] |= get_1_position_by_remainder_shift;
}

void clr(int* a, int i) {
    //a[i>>SHIFT] &= ~(1<<(i & MASK));
    // above is equivalent to the following code
    //a[i/32] &= ~(1<<(i % 32));
    int i_quotient_by_32 = i >> SHIFT;
    int i_remainder_by_32 = i & MASK;
    int get_1_position_by_remainder_shift_and_make_compliment  = ~(1 << i_remainder_by_32);
    a[i_quotient_by_32] &=  get_1_position_by_remainder_shift_and_make_compliment;
}

int tst(int* a, int i){
    //return a[i>>SHIFT] & (1<<(i & MASK));
    // above is equivalent to the following code
    //return a[i/32] & (1<<(i % 32));
    int i_quotient_by_32 = i >> SHIFT;
    int i_remainder_by_32 = i & MASK;
    int get_1_position_by_remainder_shift = 1 << i_remainder_by_32;
    int get_1_position_by_remainder_shift_at_relevant_position_of_array = a[i_quotient_by_32] & get_1_position_by_remainder_shift;
    return get_1_position_by_remainder_shift_at_relevant_position_of_array;
}

void count_bit_sort(int* a, int array_size, int max_val){
    const int BITSPERWORD = 32;

    int top = 1 + max_val/BITSPERWORD;

    int* count_array = new int[top];

    for (int i = 0; i < top; i++)
	    count_array[i] = 0;

    // Need to check other scanf return values for error.
    //while (scanf("%d", &i) != EOF) {
    for (int i = 0; i < array_size; i++) {
        if ((a[i] < 0) || (a[i] >= max_val)) {
            fprintf(stderr, "Out of range 0 >= %d < %d\n", a[i], max_val);
            exit(1);
        }
        if (tst(count_array, a[i])) {
            fprintf(stderr, "Already passed %d\n", i);
            exit(1);
        }
        set(count_array, a[i]);
    }

    int index=0;
    for (int i = 0; i < max_val; i++) {
        if (tst(count_array,i))
            a[index++] = i;
    }

}

int intcomp (const void *x, const void *y) {
    return (*(int *)x - *(int *)y);
}

void sort_by_default_quick_sort(int* a, int a_size) {
    qsort(a, a_size, sizeof(int), intcomp);
}

void sort_by_set_adt(int* a, int a_size) {
    std::set<int> S;
    std::set<int>::iterator j;

    for (int i=0; i<a_size; i++)
        S.insert(a[i]);

    int k=0;
    for (j = S.begin(); j != S.end(); ++j)
        a[k++]= *j;
}

class bitCount {
private:
    enum { _BITSPERWORD = 32, _SHIFT = 5, _MASK = 0x1F };
    int* count_array;
    int _max_val;
    int _top;

    void set(int i) {
        //a[i>>SHIFT] |= (1<<(i & MASK));
        // above is equivalent to the following code
        //a[i/32] |= (1<<(i % 32));
        int i_quotient_by_32 = i >> _SHIFT;
        int i_remainder_by_32 = i & _MASK;
        int get_1_position_by_remainder_shift = 1 << i_remainder_by_32;
        count_array[i_quotient_by_32] |= get_1_position_by_remainder_shift;
    }

    void clr(int i) {
        //a[i>>SHIFT] &= ~(1<<(i & MASK));
        // above is equivalent to the following code
        //a[i/32] &= ~(1<<(i % 32));
        int i_quotient_by_32 = i >> _SHIFT;
        int i_remainder_by_32 = i & _MASK;
        int get_1_position_by_remainder_shift_and_make_compliment  = ~(1 << i_remainder_by_32);
        count_array[i_quotient_by_32] &=  get_1_position_by_remainder_shift_and_make_compliment;
    }

    int tst(int i){
        //return a[i>>SHIFT] & (1<<(i & MASK));
        // above is equivalent to the following code
        //return a[i/32] & (1<<(i % 32));
        int i_quotient_by_32 = i >> _SHIFT;
        int i_remainder_by_32 = i & _MASK;
        int get_1_position_by_remainder_shift = 1 << i_remainder_by_32;
        int get_1_position_by_remainder_shift_at_relevant_position_of_array = count_array[i_quotient_by_32] & get_1_position_by_remainder_shift;
        return get_1_position_by_remainder_shift_at_relevant_position_of_array;
    }

    void check_valid_input(int input) {
        if ((input < 0) || (input >= _max_val)) {
            fprintf(stderr, "Out of range 0 >= %d < %d\n", input, _max_val);
            exit(1);
        }
        if (tst(input)) {
            fprintf(stderr, "Already passed %d\n", input);
            exit(1);
        }
    }

public:
    bitCount(int max_val): _max_val(max_val) {
        _top = 1 + _max_val / _BITSPERWORD;

        count_array = new int[_top];
    }

    void init() {
        for (int i = 0; i < _top; i++)
            count_array[i] = 0;
    }

    void bit_init() {
        for (int i = 0; i < _max_val; i++)
            clr(i);
    }

    void sort(int* a, int array_size){
        for (int i = 0; i < array_size; i++) {
            check_valid_input(a[i]);
            set(a[i]);
        }

        int index=0;
        for (int i = 0; i < _max_val; i++) {
            if (tst(i))
                a[index++] = i;
        }
    }
};

class bitCountSparseSet {
private:
    enum { _BITSPERWORD = 32, _SHIFT = 5, _MASK = 0x1F };
    int* count_array;
    int* from;
    int* to;
    int _max_val;
    int _max_idx;
    int _top;

    void set(int i) {
        //a[i>>SHIFT] |= (1<<(i & MASK));
        // above is equivalent to the following code
        //a[i/32] |= (1<<(i % 32));
        int i_quotient_by_32 = i >> _SHIFT;
        int i_remainder_by_32 = i & _MASK;
        int get_1_position_by_remainder_shift = 1 << i_remainder_by_32;
        count_array[i_quotient_by_32] |= get_1_position_by_remainder_shift;
    }

    void clr(int i) {
        //a[i>>SHIFT] &= ~(1<<(i & MASK));
        // above is equivalent to the following code
        //a[i/32] &= ~(1<<(i % 32));
        int i_quotient_by_32 = i >> _SHIFT;
        int i_remainder_by_32 = i & _MASK;
        int get_1_position_by_remainder_shift_and_make_compliment  = ~(1 << i_remainder_by_32);
        count_array[i_quotient_by_32] &=  get_1_position_by_remainder_shift_and_make_compliment;
    }

    int tst(int i){
        //return a[i>>SHIFT] & (1<<(i & MASK));
        // above is equivalent to the following code
        //return a[i/32] & (1<<(i % 32));
        int i_quotient_by_32 = i >> _SHIFT;
        int i_remainder_by_32 = i & _MASK;
        int get_1_position_by_remainder_shift = 1 << i_remainder_by_32;
        int get_1_position_by_remainder_shift_at_relevant_position_of_array = count_array[i_quotient_by_32] & get_1_position_by_remainder_shift;
        return get_1_position_by_remainder_shift_at_relevant_position_of_array;
    }

    void check_valid_input(int input) {
        if ((input < 0) || (input >= _max_val)) {
            fprintf(stderr, "Out of range 0 >= %d < %d\n", input, _max_val);
            exit(1);
        }
        if (tst(input)) {
            fprintf(stderr, "Already passed %d\n", input);
            exit(1);
        }
    }

    bool is_member(int subscript) {
        return ((from[subscript] < _top) &&
                (to[from[subscript]] == subscript));
    }

public:
    bitCountSparseSet(int max_val): _max_val(max_val), _top(0) {
        _max_idx = 1 + _max_val / _BITSPERWORD;

        count_array = new int[_max_idx];
        from = new int[_max_idx];
        to = new int[_max_idx];
    }

    void init() {
        _top = 0;
    }

    void sort(int* a, int array_size){
        int subscript;

        for (int i = 0; i < array_size; i++) {
            subscript = (a[i]>>_SHIFT);

            if (!is_member(subscript)) {
                from[subscript] = _top;
                to[_top] = subscript;
                count_array[subscript] = 0;
                _top++;
            }

            set(a[i]);
        }

        int index=0;
        for (int i = 0; i < _max_val; i++) {
            subscript = (i>>_SHIFT);
            if (is_member(subscript)) {
                if (tst(i))
                    a[index++] = i;
            }
        }
    }
};
#endif //PROGRAMMING_PEARLS_COLUMN1_H
