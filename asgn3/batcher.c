#include "batcher.h"

#include "stats.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void comparator(Stats *stats, uint32_t *A, uint32_t x, uint32_t y) {
    //doing the comparison A[x] > A[y]
    if (cmp(stats, A[x], A[y]) == 1) {
        //swaps A[x] and A[y]
        swap(stats, &A[x], &A[y]);
    }
}

uint32_t n_bit_length(uint32_t x) {
    uint32_t n = 0;
    while (x != 0) {
        x >>= 1;
        n += 1;
    }
    return n;
}

void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    if (n == 0) {
        return;
    }

    //setting n.bit_length() to 0
    uint32_t t = n_bit_length(n);
    uint32_t p = 1 << (t - 1);

    while (p > 0) {
        uint32_t q = 1 << (t - 1);
        uint32_t r = 0;
        uint32_t d = p;
        while (d > 0) {
            for (uint32_t i = 0; i < (n - d); i += 1) {
                if ((i & p) == r) {
                    comparator(stats, A, i, i + d);
                }
            }
            d = (q - p);
            q >>= 1;
            r = p;
        }
        p >>= 1;
    }
}
