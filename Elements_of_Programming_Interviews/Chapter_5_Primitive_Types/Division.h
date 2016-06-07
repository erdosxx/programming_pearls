#ifndef ALGORITHM_ANALYSIS_DIVISION_H
#define ALGORITHM_ANALYSIS_DIVISION_H

// Alternative solution.
unsigned DivideBsearch(unsigned x, unsigned y) {
    if (x < y) {
        return 0;
    }

    int power_left = 0;
    // sizeof(unsigned) =4,   power_right = 4*2^3 = 32
    int power_right = sizeof(unsigned) << 3;
    int power_mid = -1;

    while (power_left < power_right) {
        int old_power_mid = power_mid;
        power_mid = power_left + ((power_right - power_left) / 2);
        if (old_power_mid == power_mid) {
            break;
        }

        // yshift = y * 2^power_mid
        // if overflow is occurred, y << power_mid > x, so power_right = power_mid
        unsigned yshift = y << power_mid;
        if ((yshift >> power_mid) != y) {
            // yshift overflowed, use a smaller shift.
            power_right = power_mid;
            continue;
        }

        if ((y << power_mid) > x) {
            power_right = power_mid;
        } else if ((y << power_mid) < x) {
            power_left = power_mid;
        } else {
            return (1U << power_mid);
        }
    }
    unsigned part = 1U << power_left;
    return part | DivideBsearch(x - (y << power_left), y);
}

// @include
// x/y = 2^k + (x - 2^k * y)/y
unsigned Divide(unsigned x, unsigned y) {
    unsigned result = 0;
    int power = 32;
    // y_power = y * 2^32
    unsigned long long y_power = static_cast<unsigned long long>(y) << power;
    while (x >= y) {
        while (y_power > x) {
            y_power >>= 1;
            --power;
        }

        result += 1U << power;
        x -= y_power;
    }
    return result;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_DIVISION_H
