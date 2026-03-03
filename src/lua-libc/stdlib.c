#include <string.h>
#include <errno.h>
#include <float.h>

#define NAN (__builtin_nanf(""))
#define INFINITY (__builtin_inff())

extern double pow(double base, double exponent);

#define isdigit(c) ((c) >= '0' && (c) <= '9')
#define tolower(c) ((c) >= 'A' && (c) <= 'Z' ? (c) + 32 : (c))

int isfinite(double x) {
    unsigned long long bits;
    memcpy(&bits, &x, sizeof(bits));

    unsigned long long exponent = (bits >> 52) & 0x7FFULL;
    unsigned long long fraction = bits & 0xFFFFFFFFFFFFFULL;

    return (exponent == 0x7FFULL) && (fraction == 0);
}

double strtod(const char *nptr, char **endptr) {
    const char *s = nptr;
    double result = 0.0;
    int sign = 1;
    int exp_sign = 1;
    long exponent = 0;
    int any_digits = 0;

    while (*s == ' ') {
        s++;
    }

    if (*s == '+' || *s == '-') {
        if (*s == '-') sign = -1;
        s++;
    }

    // Handle special values: inf / infinity
    if ((tolower(s[0]) == 'i') &&
        (tolower(s[1]) == 'n') &&
        (tolower(s[2]) == 'f')) {
        s += 3;
        if ((tolower(s[0]) == 'i') &&
            (tolower(s[1]) == 'n') &&
            (tolower(s[2]) == 'i') &&
            (tolower(s[3]) == 't') &&
            (tolower(s[4]) == 'y')) {
            s += 5;
        }
        if (endptr) *endptr = (char *)s;
        return sign * INFINITY;
    }

    // Handle NaN
    if ((tolower(s[0]) == 'n') &&
        (tolower(s[1]) == 'a') &&
        (tolower(s[2]) == 'n')) {
        s += 3;
        if (endptr) *endptr = (char *)s;
        return NAN;
    }

    // Integer part
    while (isdigit((unsigned char)*s)) {
        any_digits = 1;
        result = result * 10.0 + (*s - '0');
        s++;
    }

    // Fractional part
    if (*s == '.') {
        s++;
        double fraction = 0.0;
        double base = 0.1;

        while (isdigit((unsigned char)*s)) {
            any_digits = 1;
            fraction += (*s - '0') * base;
            base *= 0.1;
            s++;
        }
        result += fraction;
    }

    // Exponent
    if ((*s == 'e' || *s == 'E') && any_digits) {
        const char *exp_start = s;
        s++;

        if (*s == '+' || *s == '-') {
            if (*s == '-') exp_sign = -1;
            s++;
        }

        if (isdigit((unsigned char)*s)) {
            while (isdigit((unsigned char)*s)) {
                exponent = exponent * 10 + (*s - '0');
                s++;
            }
        } else {
            s = exp_start; // rollback if invalid exponent
            exponent = 0;
        }
    }

    if (!any_digits) {
        if (endptr) *endptr = (char *)nptr;
        return 0.0;
    }

    exponent *= exp_sign;
    if (exponent != 0) {
        result *= pow(10.0, exponent);
    }

    if (endptr) {
        *endptr = (char *)s;
    }

    result *= sign;

    return result;
}
