#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <tgmath.h>
#include <assert.h>
#include <stdbool.h>
#include <memory.h>

void FisherYates(size_t n, size_t arr[n]);
size_t fixed_point_num(size_t n, size_t arr[n]);
size_t cycles_num(size_t n, size_t arr[n]);

/* Funkcje pomocnicze */
void swap(size_t *a, size_t *b);
size_t factorial(size_t n);
void print_arr(size_t n, size_t arr[n]);
void fill_arr(size_t n, size_t arr[n]);

size_t factorial(size_t n) {
    size_t f = 1;
    for (size_t i = 2; i <= n; i++)
        f *= i;

    return f;
}

void swap(size_t *a, size_t *b) {
    size_t temp = *a;
    *a = *b;
    *b = temp;
}

void FisherYates(size_t n, size_t arr[n]) { // implementation of Fisher
    size_t j = 0;
    for (size_t i = n - 1; i > 0; i--) { // for loop to shuffle
        j = (size_t)rand() % (i + 1);     // randomise j for shuffle with Fisher Yates
        // printf("j = %zu\n", j);
        swap(&arr[i], &arr[j]);
    }
}

size_t fixed_point_num(size_t n, size_t arr[n]) {

    size_t counter = 0;
    for (size_t i = 0; i < n; i++) {
        if (arr[i] == i) 
            ++counter;
    }
    return counter;
}

void print_arr(size_t n, size_t arr[n]) {
    printf("{ ");
    for (size_t i = 0; i < n; i++) {
        printf(" %zu,", arr[i]);
    }
    printf(" }\n");
}

void fill_arr(size_t n, size_t arr[n]) {
    for (size_t i = 0; i < n; i++)
        arr[i] = i;
}

size_t cycles_num(size_t n, size_t arr[n]) {

    bool visited[n];
    memset(visited, 0, n);
    size_t counter = 0;

    for (size_t i = 0; i < n; i++) {
        
        if (visited[i] == true)
            continue;
        
        if (arr[i] != i)
        {
            size_t index = i;
            while (visited[index] == false) {
                // printf("%zu, ", index);
                visited[index] = true;
                index = arr[index];
            }
        }
        // puts("");
        visited[i] = true;
        counter++;
    }
    return counter;
}

void test(void) {
    size_t arr[] = { 1, 3, 4, 0, 2, 6, 5, };
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t correct = 3;

    // printf("answer: %zu\n", cycles_num(size, arr));
    assert(cycles_num(size, arr) == correct);
}

int main(void) {

    test();

    // #define REPETITIONS_NUM 100
    #define SAMPLES_NUM 100000UL
    #define N 20UL

    size_t one_fixp_counter = 0;
    size_t null_fixp_counter = 0;
    size_t cycles_sum = 0;

    srand(time(NULL));

    printf("SAMPLES_NUM: %zu\tN_MAX: %zu\n", SAMPLES_NUM, N);
    printf("n\tavg_0_fixp\tmean_0_fixp\tavg_1_fixp\tmean_1_fixp\tavg_cycles_num\tcycles_mean\n");

    for (size_t n = 1; n <= N; n++) {

        size_t* const arr = malloc(sizeof(size_t[n]));
        fill_arr(n, arr);

        for (size_t i = 0; i < SAMPLES_NUM; i++) {
            FisherYates(n, arr);
            size_t fixp = fixed_point_num(n, arr);
            size_t cycles = cycles_num(n, arr);

            if (fixp == 0)
                ++null_fixp_counter;
            else if (fixp == 1)
                ++one_fixp_counter;

            cycles_sum += cycles;
        }

        double null_fixp_mean = ((double)null_fixp_counter / SAMPLES_NUM);
        double one_fixp_mean = ((double)one_fixp_counter / SAMPLES_NUM);
        double cycles_mean = ((double)cycles_sum / SAMPLES_NUM);

        size_t fact_n = factorial(n);
        double avg_null_fixp_num = (null_fixp_mean * fact_n);
        double avg_one_fixp_num = (one_fixp_mean * fact_n);
        double avg_cycles_num = (cycles_mean * fact_n);

        printf("%zu\t%.5f\t\t%.5f\t\t%.5f\t\t%.5f\t\t%.5f\t\t%.5f\n",
               n,
               avg_null_fixp_num, null_fixp_mean,
               avg_one_fixp_num, one_fixp_mean,
               avg_cycles_num, cycles_mean);

        null_fixp_counter = 0;
        one_fixp_counter = 0;
        cycles_sum = 0;

        free(arr);
    }

    return EXIT_SUCCESS;
}
