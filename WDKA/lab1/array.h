#ifndef ARRAY_H
#define ARRAY_H

#include <memory.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Array {
    size_t size;
    long double buf[];
} Array;

Array *array_init(size_t size);
void array_delete(Array *arr);
void array_print(Array const *const arr);

Array *array_init(size_t size) {

    if (size == 0)
        return NULL;

    Array *arr = (Array*)malloc(sizeof(Array) + size * sizeof(long double));

    arr->size = size;

    return arr;
}

void array_delete(Array * arr) {
    if (arr != NULL)
        free(arr);
}

void array_print(Array const *const arr) {
    for (size_t i = 0; i < arr->size; i++)
        printf("%Lf\t", arr->buf[i]);
    puts("");
}

#endif
