#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <tgmath.h>
#include <stdbool.h>
#include <string.h>

static size_t rand_n_bit_num(size_t n);
static void printBits(size_t num, size_t bits);
static bool is_subseq(size_t num, size_t bits, const char *seq);

static size_t rand_n_bit_num(size_t n) {

    if(n > 50) {
        return 0;
    }

    if (n < 32) {
        return rand() % ((size_t)pow(2, n));
    }

    size_t a = n / 2;
    size_t b = n - a;

    size_t r1 = rand() % ((size_t)pow(2, a));
    size_t r2 = rand() % ((size_t)pow(2, b));
    size_t r = (r1 << b) + r2;

    // printf("%zX | %zX = %zX\n", r1, r2, r);
    // printBits(r1, a);
    // printBits(r2, b);
    // printBits(r, n);

    return r;
}

static void printBits(size_t num, size_t bits) {

    size_t mask = 1 << (--bits);

    do {
        printf("%zu", (num & mask) >> (bits--));
        mask >>= 1;
    } while (mask > 0);
    puts("");
}

static bool is_subseq(size_t num, size_t bits, const char* seq) {

    size_t seqlen = strlen(seq);
    size_t counter = 0;
    int last_id = seqlen - 1;
    for (int b = 0; b < (int)(bits - seqlen + 1); b++)
    {
        uint8_t bit = num & 0x1;
        num >>= 1;
        if (bit == seq[last_id] - '0') 
        {
            counter++;
            size_t temp_num = num;
            for (int i = last_id - 1; i >= 0; --i) {
                bit = temp_num & 0x1;
                // printf("%hhu", bit);
                temp_num >>= 1;
                if (bit == seq[i] - '0') {
                    counter++;
                } else {
                    counter = 0;
                    break;
                }
            }
        }
        if (counter == seqlen) {
            return true;
        }
        // puts("");
    }
    return false;
}

int main(void) {

    #define SAMPLE_NUM 1000000
    #define N 50

    /* {a, b} = {0, 1} */
    /*
        ciagów o długości n <= 50 jest 2^50
        liczby [0, 1, ..., 2^n - 1] to wszytskie ciągi o długości 2^50
    */

    size_t counter_aaa = 0;
    size_t counter_abb = 0;

    char* aaa = "000";
    char* abb = "011";

    srand(time(NULL));

    // printf("n\taaa count\taaa mean\tabb count\t abb mean\n");

    // for (size_t n = 1; n <= 30; n++) {
        
    //     for (size_t i = 0; i < (1 << n); i++) {
    //         counter_aaa += is_subseq(i, n, aaa);
    //         counter_abb += is_subseq(i, n, abb);
    //     }

    //     size_t nums = 1UL << n;

    //     double aaa_mean = (double)counter_aaa / nums;
    //     double abb_mean = (double)counter_abb / nums;

    //     printf("%zu\t%zu\t\t%f\t\t%zu\t\t%f\n", n, counter_aaa, aaa_mean, counter_abb, abb_mean);

    //     counter_aaa = 0;
    //     counter_abb = 0;
    // }

    printf("n\tAPX. aaa count\taaa mean\tAPX. abb count\t abb mean\n");

    for (size_t n = 31; n <= N; n++) {
        for (size_t i = 0; i < SAMPLE_NUM; i++) {
            size_t rand_seq = rand_n_bit_num(n);
            counter_aaa += is_subseq(rand_seq, n, aaa);
            counter_abb += is_subseq(rand_seq, n, abb);
        }

        size_t nums = 1UL << n;

        double aaa_mean = (double)counter_aaa / SAMPLE_NUM;
        double abb_mean = (double)counter_abb / SAMPLE_NUM;

        printf("%zu\t%f\t\t%f\t\t%f\t\t%f\n", 
                n, 
                aaa_mean * nums, 
                aaa_mean, 
                abb_mean * nums, 
                abb_mean
                );

        counter_aaa = 0;
        counter_abb = 0;
    }

    return EXIT_SUCCESS;
}
