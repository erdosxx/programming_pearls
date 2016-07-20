#ifndef PROGRAMMING_PEARLS_COLUMN8_H
#define PROGRAMMING_PEARLS_COLUMN8_H

void sprinkle(int* x, int n) /* Fill x[n] with reals uniform on [-1,1] */ {
    for (int i = 0; i < n; i++)
        x[i] = 1 - 2*( (float) rand()/RAND_MAX);
}

/* naive algorithm*/
float maxsum_simple(const int *x, const int size_ary) {
    float sum, maxsofar = 0;

    for (int i = 0; i < size_ary; i++)
        for (int j = i; j < size_ary; j++) {
            sum = 0;

            for (int k = i; k <= j; k++)
                sum += x[k];

            if (sum > maxsofar)
                maxsofar = sum;
        }
    return maxsofar;
}

float maxsum_simple2(const int *x, const int size_ary) {
    float sum, maxsofar = 0;

    for (int i = 0; i < size_ary; i++) {
        sum = 0;

        for (int j = i; j < size_ary; j++) {
            sum += x[j];
            if (sum > maxsofar)
                maxsofar = sum;
        }
    }
    return maxsofar;
}

float maxsum_cumarr(const int *x, const int size_ary) {
    float sum, maxsofar = 0;

    enum {MAXN=10000000};
    float* cumvec = new float[MAXN+1];

    /* to access cumarr[-1], see problem 8.5 */
    float* cumarr = cumvec+1;
    cumarr[-1] = 0;

    for (int i = 0; i < size_ary; i++)
        cumarr[i] = cumarr[i-1] + x[i];

    for (int i = 0; i < size_ary; i++) {
        for (int j = i; j < size_ary; j++) {
            sum = cumarr[j] - cumarr[i-1];
            if (sum > maxsofar)
                maxsofar = sum;
        }
    }
    return maxsofar;
}

/* MS VC++ has a max macro, and therefore a perf bug */

//#ifdef max
//#undef max
//#endif

#define maxmac(a, b) ((a) > (b) ? (a) : (b) )

float maxfun(float a, float b) {
    return a > b ? a : b;
}

#define maxval(a, b) maxfun(a, b)

float recmax(const int* x, int low, int high);

float maxsum_divide_n_conquer(const int *x, const int n) {
    return recmax(x, 0, n-1);
}

/* divide and conquer algorithm */
float recmax(const int* x, int low, int high) {
    if (low > high)  /* zero elements */
		return 0;

    if (low == high)  /* one element */
		return maxval(0, x[low]);

    int middle = (low + high) / 2;

	/* find max crossing to left */
    float lmax = 0;
    float sum = 0;
    for (int i = middle; i >= low; i--) {
		sum += x[i];
		if (sum > lmax)
			lmax = sum;
    }

	/* find max crossing to right */
    float rmax = 0;
    sum =0;
    for (int i = middle + 1; i <= high; i++) {
		sum += x[i];
		if (sum > rmax)
			rmax = sum;
    }

    return maxval(lmax + rmax, maxval(recmax(x, low, middle), recmax(x, middle + 1, high)));
}

float maxsum_fast(const int *x, const int size_ary) {
    float maxsofar = 0;
    float maxendinghere = 0;

    for (int i = 0; i < size_ary; i++) {
        maxendinghere += x[i];

        if (maxendinghere < 0)
            maxendinghere = 0;

        if (maxsofar < maxendinghere)
            maxsofar = maxendinghere;
    }
    return maxsofar;
}

float maxsum_fast2(const int *x, const int size_ary) {
    float maxsofar = 0;
    float maxendinghere = 0;

    for (int i = 0; i < size_ary; i++) {
        maxendinghere += x[i];
        maxendinghere = maxmac(maxendinghere, 0);
       	maxsofar = maxmac(maxsofar, maxendinghere);
    }
    return maxsofar;
}

float maxsum_fast3(const int *x, const int size_ary) {
    float maxsofar = 0;
    float maxendinghere = 0;

    for (int i = 0; i < size_ary; i++) {
        maxendinghere += x[i];
        maxendinghere = maxfun(maxendinghere, 0);
       	maxsofar = maxfun(maxsofar, maxendinghere);
    }
    return maxsofar;
}

//see EPI p.274

// Problem 8.8.
// Ref: http://codinghighway.com/2013/09/28/on-programming-perls-exercise-8-column-8-and-the-power-of-conceptual-blocks/
struct solution {
    int maxlow;
    int maxhigh;
    int total;
    int maxsum;
};

void maxsum_aux(const int *x, int low, int high, solution *s);

float maxsum_dnc_linear(const int *x, const int size_ary) {
    solution s;
    maxsum_aux(x, 0, size_ary-1, &s);
    return s.maxsum;
}

void maxsum_aux(const int *x, int low, int high, solution *s) {
    solution left;
    solution right;

    if (low >= high) {
        s->maxsum = s->maxhigh = s->maxlow = (low > high ? 0: maxmac(x[low], 0));
        s->total = (low > high ? 0 : x[low]);
        return;
    }

    int m = (low+high)/2;
    maxsum_aux(x, low, m, &left);
    maxsum_aux(x, m+1, high, &right);

    s->maxlow = maxmac(left.total+right.maxlow, left.maxlow);
    s->maxhigh = maxmac(right.total+left.maxhigh, right.maxhigh);
    s->total = left.total + right.total;
    s->maxsum = maxmac(maxmac(left.maxsum, right.maxsum), left.maxhigh + right.maxlow);
}

#endif //PROGRAMMING_PEARLS_COLUMN8_H
