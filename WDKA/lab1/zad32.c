#include <stdio.h>
#include <stdlib.h>
#include "array.h"

static int formal_inverse(long double(f)(size_t), Array *A, Array *B);
static void double_print(Array const *const restrict A, Array const *const restrict B);

static long double f1(size_t n);
static long double f2(size_t n);
static long double f3(size_t n);
static long double f4(size_t n);

static long double f1(size_t n) {
    return 1;
}

static long double f2(size_t n) {
    return 1UL << n;
}

static long double f3(size_t n) {
    size_t f = 1;
    for (size_t i = 2; i <= n; i++)
        f *= i;
    return f;
}

static long double f4(size_t n) {
    return 1.0L / f3(n);
}

static int formal_inverse(long double(f)(size_t), Array *A, Array *B) {

    if (A == NULL || B == NULL)
        return -1;

    if (A->size != B->size)
        return -2;

    size_t n = A->size;

    for (size_t i = 0; i < n; i++) {
        A->buf[i] = f(i);
        B->buf[i] = 0.0L;
    }

    B->buf[0] = 1.0L / A->buf[0];

    for (size_t i = 1; i < n; i++)
    {
        for (size_t k = 1; k <= i; k++)
            B->buf[i] += (A->buf[k] * B->buf[i - k]);
        B->buf[i] *= (-1.0L) / A->buf[0];
    }

    return 0;
}

static void double_print(Array const * const restrict A, Array const * const restrict B) {

    size_t n = A->size;
    puts("n\tA[n]\t\t\tB[n]");
    for (size_t i = 0; i < n; i++)
        printf("%zu\t%.10Lf\t\t%.10Lf\n", i, A->buf[i], B->buf[i]);
    
}

int main(void) {

    #define N 10

    Array* A = array_init(N);
    Array* B = array_init(N);

    puts("f(n) = 1");
    formal_inverse(f1, A, B);
    double_print(A, B);

    puts("f(n) = 2^n");
    formal_inverse(f2, A, B);
    double_print(A, B);

    puts("f(n) = n!");
    formal_inverse(f3, A, B);
    double_print(A, B);

    puts("f(n) = 1 / n!");
    formal_inverse(f4, A, B);
    double_print(A, B);

    array_delete(A);
    array_delete(B);

    return EXIT_SUCCESS;
}
