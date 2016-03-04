//
// Created by In Soo Oh on 3/4/16.
//

#ifndef PROGRAMMING_PEARLS_COLUMN1_H
#define PROGRAMMING_PEARLS_COLUMN1_H

#define SHIFT 5  // log2(BITSPERWORD); i.e. how many numbers we can
                 // store per element in the array[].
#define MASK 0x1F // i.e. 0001 1111 (5 bits) to mask of all but the contents.


void set(int a[], int i) {
    //a[i>>SHIFT] |= (1<<(i & MASK));
    // above is equivalent to the following code
    //a[i/32] |= (1<<(i % 32));
    int i_quotient_by_32 = i >> SHIFT;
    int i_remainder_by_32 = i & MASK;
    int get_1_position_by_remainder_shift = 1 << i_remainder_by_32;
    a[i_quotient_by_32] |= get_1_position_by_remainder_shift;
}

void clr(int a[], int i) {
    //a[i>>SHIFT] &= ~(1<<(i & MASK));
    // above is equivalent to the following code
    //a[i/32] &= ~(1<<(i % 32));
    int i_quotient_by_32 = i >> SHIFT;
    int i_remainder_by_32 = i & MASK;
    int get_1_position_by_remainder_shift_and_make_compliment  = ~(1 << i_remainder_by_32);
    a[i_quotient_by_32] &=  get_1_position_by_remainder_shift_and_make_compliment;
}

int tst(int a[], int i){
    //return a[i>>SHIFT] & (1<<(i & MASK));
    // above is equivalent to the following code
    //return a[i/32] & (1<<(i % 32));
    int i_quotient_by_32 = i >> SHIFT;
    int i_remainder_by_32 = i & MASK;
    int get_1_position_by_remainder_shift = 1 << i_remainder_by_32;
    int get_1_position_by_remainder_shift_at_relevant_position_of_array = a[i_quotient_by_32] & get_1_position_by_remainder_shift;
    return get_1_position_by_remainder_shift_at_relevant_position_of_array;
}

void count_bit_sort(int a[], int array_size, int max_val){
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

#endif //PROGRAMMING_PEARLS_COLUMN1_H
