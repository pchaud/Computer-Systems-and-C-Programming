#include "shell.h"

#include "gaps.h"
#include "stats.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    //for loop "for gap in gaps"
    for (uint32_t gap = 0; gap < GAPS; gap += 1) {
        uint32_t x = gaps[gap];
        //for loop "for i in range"
        for (uint32_t i = x; i < n; i += 1) {
            uint32_t j = i;
            //might have to put move
            uint32_t temp = A[i];

            while (j >= x && cmp(stats, temp, A[j - x]) == -1) {
                A[j] = move(stats, A[j - x]);
                j -= x;
            }
            A[j] = move(stats, temp);
        }
    }
}
