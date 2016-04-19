#ifndef PROGRAMMING_PEARLS_COLUMN9_H
#define PROGRAMMING_PEARLS_COLUMN9_H

/* bitcount: count 1 bits in x
 * K&R P.50 */

int bitcount_simple(unsigned x) {
    int count;

    for (count = 0; x != 0; x >>= 1)
        if (x & 0b1)
            count++;
    return count;
}

unsigned removeRightMostBit(unsigned &x) {
    x &= x -1;
    return x;
}

int bitcount_rightmostbit(unsigned x) {
    int count;

    for (count = 0; x > 0; count++)
        x = removeRightMostBit(x);
    return count;
}

/* K&R p.49
 * getbits: get n bits from position p
 * Example: x= 10010100 getbits(x, 4, 3)
 * A: x >> (p-n+1): 00100101
 *    ~0          : 11111111
 *    ~0 << n     : 11111000
 * B: ~(~0 << n)  : 00000111
 * A & B          : 00000101 */
unsigned getbits(unsigned x, const int p, const int n) {
    return (x >> (p-n+1)) & ~(~0 << n);
}

#endif //PROGRAMMING_PEARLS_COLUMN9_H
