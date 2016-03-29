#ifndef PROGRAMMING_PEARLS_COLUMN8_H
#define PROGRAMMING_PEARLS_COLUMN8_H

void sprinkle(int* x, int n) /* Fill x[n] with reals uniform on [-1,1] */ {
    for (int i = 0; i < n; i++)
        x[i] = 1 - 2*( (float) rand()/RAND_MAX);
}

/* naive algorithm*/
float alg1(int* x, int n) {
    int i, j, k;
    float sum, maxsofar = 0;
    for (i = 0; i < n; i++)
        for (j = i; j < n; j++) {
            sum = 0;
            for (k = i; k <= j; k++)
                sum += x[k];
            if (sum > maxsofar)
                maxsofar = sum;
        }
    return maxsofar;
}

float alg2(int* x, int n) {
    int i, j;
    float sum, maxsofar = 0;
    for (i = 0; i < n; i++) {
        sum = 0;
        for (j = i; j < n; j++) {
            sum += x[j];
            if (sum > maxsofar)
                maxsofar = sum;
        }
    }
    return maxsofar;
}

#define MAXN 10000000
float cumvec[MAXN+1];

float alg2b(int* x, int n) {
    int i, j;
    float *cumarr, sum, maxsofar = 0;

    /* to access cumarr[-1], see problem 8.5 */
    cumarr = cumvec+1;
    cumarr[-1] = 0;

    for (i = 0; i < n; i++)
        cumarr[i] = cumarr[i-1] + x[i];

    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
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

/* divide and conquer algorithm */
float recmax(int* x, int l, int u) {
    int i, m;
    float lmax, rmax, sum;

    if (l > u)  /* zero elements */
		return 0;

    if (l == u)  /* one element */
		return maxval(0, x[l]);

    m = (l+u) / 2;

	/* find max crossing to left */
    lmax = sum = 0;
    for (i = m; i >= l; i--) {
		sum += x[i];
		if (sum > lmax)
			lmax = sum;
    }

	/* find max crossing to right */
    rmax = sum = 0;
    for (i = m+1; i <= u; i++) {
		sum += x[i];
		if (sum > rmax)
			rmax = sum;
    }

    return maxval(lmax + rmax, maxval(recmax(x, l, m), recmax(x, m+1, u)));
}

float alg3(int* x, int n) {
    return recmax(x, 0, n-1);
}

float alg4(int* x, int n) {
    int i;
    float maxsofar = 0, maxendinghere = 0;

    for (i = 0; i < n; i++) {
        maxendinghere += x[i];

        if (maxendinghere < 0)
            maxendinghere = 0;

        if (maxsofar < maxendinghere)
            maxsofar = maxendinghere;
    }
    return maxsofar;
}

float alg4b(int* x, int n) {
    int i;
    float maxsofar = 0, maxendinghere = 0;

    for (i = 0; i < n; i++) {
        maxendinghere += x[i];
        maxendinghere = maxmac(maxendinghere, 0);
       	maxsofar = maxmac(maxsofar, maxendinghere);
    }
    return maxsofar;
}

float alg4c(int* x, int n) {
    int i;
    float maxsofar = 0, maxendinghere = 0;
    for (i = 0; i < n; i++) {
        maxendinghere += x[i];
        maxendinghere = maxfun(maxendinghere, 0);
       	maxsofar = maxfun(maxsofar, maxendinghere);
    }
    return maxsofar;
}

#endif //PROGRAMMING_PEARLS_COLUMN8_H