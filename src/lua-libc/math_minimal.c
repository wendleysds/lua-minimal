#include <stdint.h>
#include <limits.h>

// Simple minimal math.c, expects the kernel support FPU

int abs(int x) {
    return x < 0 ? (x == INT_MIN ? INT_MIN : -x) : x;
}

double floor(double x) {
    long long i = (long long)x;
    if ((double)i > x)
        return (double)(i - 1);
    return (double)i;
}

double ldexp(double x, int exp) {
    while (exp > 0) {
        x *= 2.0;
        exp--;
    }
    while (exp < 0) {
        x *= 0.5;
        exp++;
    }
    return x;
}

double frexp(double x, int *exp) {
    if (x == 0.0) {
        *exp = 0;
        return 0.0;
    }

    int e = 0;
    double ax = x > 0 ? x : -x;

    while (ax >= 1.0) {
        ax *= 0.5;
        e++;
    }

    while (ax < 0.5) {
        ax *= 2.0;
        e--;
    }

    *exp = e;
    return x > 0 ? ax : -ax;
}

double fmod(double x, double y) {
    if (y == 0.0)
        return 0.0/0.0;

    long long q = (long long)(x / y);
    return x - (double)q * y;
}

double pow(double base, double exponent) {
    if (exponent == 0.0)
        return 1.0;

    if ((long long)exponent == exponent) {
        long long e = (long long)exponent;
        int neg = 0;
        if (e < 0) {
            neg = 1;
            e = -e;
        }

        double result = 1.0;

        while (e) {
            if (e & 1)
                result *= base;
            base *= base;
            e >>= 1;
        }

        return neg ? 1.0 / result : result;
    }

    // fallbacks
    return 0.0;
}