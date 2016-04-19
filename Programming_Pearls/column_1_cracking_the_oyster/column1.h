#ifndef PROGRAMMING_PEARLS_COLUMN1_H
#define PROGRAMMING_PEARLS_COLUMN1_H

#include <set>
#include <stdbool.h>

/*
#define SHIFT 5  // log2(BITSPERWORD); i.e. how many numbers we can
                 // store per element in the array[].
#define MASK 0x1F // i.e. 0001 1111 (5 bits) to mask of all but the contents.
*/

enum {SHIFT=5, MASK=0b11111};


void set(int *a, const int i) {
    //a[i>>SHIFT] |= (1<<(i & MASK));
    // above is equivalent to the following code
    //a[i/32] |= (1<<(i % 32));
    int get_index_in_array = i >> SHIFT;
    int remainder_devide_by_32 = i & MASK;
    int get_set_bit_position_in_entry = 1 << remainder_devide_by_32;
    a[get_index_in_array] |= get_set_bit_position_in_entry;
}

void clr(int* a, const int i) {
    //a[i>>SHIFT] &= ~(1<<(i & MASK));
    // above is equivalent to the following code
    //a[i/32] &= ~(1<<(i % 32));
    int get_index_in_array = i >> SHIFT;
    int remainder_devide_by_32 = i & MASK;
    int complement_bit_position_in_entry = ~(1 << remainder_devide_by_32);
    a[get_index_in_array] &= complement_bit_position_in_entry;
}

int tst(const int* a, const int i){
    //return a[i>>SHIFT] & (1<<(i & MASK));
    // above is equivalent to the following code
    //return a[i/32] & (1<<(i % 32));
    int get_index_in_array = i >> SHIFT;
    int remainder_devide_by_32 = i & MASK;
    int get_set_bit_position_in_entry = 1 << remainder_devide_by_32;
    int check_target_bit = a[get_index_in_array] & get_set_bit_position_in_entry;
    return check_target_bit;
}

void init_count_array(int* &count_array, const int max_val) {
    enum { BITS_PER_INT_TYPE = 32 }; /* sizeof(int) = 4 byte -> 32 bit*/

    int count_array_size = 1 + max_val / BITS_PER_INT_TYPE;

    count_array = new int[count_array_size];

    for (int i = 0; i < count_array_size; i++)
        count_array[i] = 0;
}

void check_input_data(int* &a, int index, int* &count_array, const int max_val){
    if ((a[index] < 0) || (a[index] >= max_val)) {
        fprintf(stderr, "Out of range 0 >= %d < %d\n", a[index], max_val);
        exit(1);
    }
    if (tst(count_array, a[index])) {
        fprintf(stderr, "Already passed %d\n", index);
        exit(1);
    }
}

void set_count_array(int* &a, int* &count_array, const int array_size, const int max_val){
    for (int i = 0; i < array_size; i++) {
        check_input_data(a, i, count_array, max_val);
        set(count_array, a[i]);
    }
}

void sort_array_using_count_array(int * &a, const int max_val, const int *count_array) {
    int index=0;
    for (int i = 0; i < max_val; i++) {
        if (tst(count_array,i))
            a[index++] = i;
    }
}

void count_bit_sort(int* a, const int array_size, const int max_val){
    int* count_array;

    init_count_array(count_array, max_val);

    set_count_array(a, count_array, array_size, max_val);

    sort_array_using_count_array(a, max_val, count_array);
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
    enum { _BITSPERWORD = 32, _SHIFT = 5, _MASK = 0b11111 };
    int* count_array;
    int _max_val;
    int _count_ary_size;

    void set(int i) {
        count_array[i>>_SHIFT] |= (1<<(i & _MASK));
    }

    void clr(int i) {
        count_array[i>>_SHIFT] &= ~(1<<(i & _MASK));
    }

    int tst(int i){
        return count_array[i>>_SHIFT] & (1<<(i & _MASK));
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
        _count_ary_size = 1 + _max_val / _BITSPERWORD;

        count_array = new int[_count_ary_size];
    }

    void init() {
        for (int i = 0; i < _count_ary_size; i++)
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

/*
 * Exercise 1.9.
 * See: http://research.swtch.com/sparse
 */
class bitCountSparseSet {
private:
    enum { _BITSPERWORD = 32, _SHIFT = 5, _MASK = 0b11111 };
    int* count_array;
    int* from;
    int* to;
    int _max_val;
    int _max_idx;
    int _top;

    void set(int i) {
        count_array[i>> _SHIFT] |= (1<<(i & _MASK));
    }

    int tst(int i){
        return count_array[i>> _SHIFT] & (1<<(i & _MASK));
    }

    bool is_member(int subscript) {
        return ((from[subscript] < _top) &&
                (to[from[subscript]] == subscript));
    }

    void set_bit_with_from_to_data(int* &a, const int array_size) {
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
    }

    void sort_by_count_arry(int* &a) {
        int index=0;
        int subscript;
        for (int i = 0; i < _max_val; i++) {
            subscript = (i>>_SHIFT);
            if (is_member(subscript)) {
                if (tst(i))
                    a[index++] = i;
            }
        }
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

    void sort(int* a, const int array_size){
        set_bit_with_from_to_data(a, array_size);

        sort_by_count_arry(a);
    }
};
#endif //PROGRAMMING_PEARLS_COLUMN1_H
