#include "batcher.h"
#include "gaps.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "aishqbr:n:p:H"

int main(int argc, char **argv) {
    Set S = set_empty();
    Stats stats = (Stats) { 0, 0 };
    int op = 0;
    uint32_t seed = 13371453;
    srandom(seed);
    uint32_t size = 100;
    uint32_t elements = 100;

    while ((op = getopt(argc, argv, OPTIONS)) != -1) {
        switch (op) {
        case 'a': {
            S = set_insert(S, 1);
            break;
        }

        case 'h': {
            S = set_insert(S, 2);
            break;
        }
        case 'b': {
            S = set_insert(S, 3);
            break;
        }
        case 's': {
            S = set_insert(S, 4);
            break;
        }
        case 'q': {
            S = set_insert(S, 5);
            break;
        }
        case 'i': {
            S = set_insert(S, 6);
            break;
        }
        case 'r': {
            seed = (uint32_t) strtoul(optarg, NULL, 10);
            srandom(seed);
            break;
        }
        case 'n': {
            size = (uint32_t) strtoul(optarg, NULL, 10);
            break;
        }
        case 'p': {
            elements = (uint32_t) strtoul(optarg, NULL, 10);
            break;
        }

        case 'H': {
            printf("sorting - \n -a: Employs all sorting algorithms. \n -i: Enables Insertion "
                   "Sort. \n -h: Enables Heap Sort.\n "
                   "-b: Enables Batcher Sort.\n -s: Enables Shell Sort.\n -q: Enables Quicksort. "
                   "\n -r seed: Set the random seed to seed\n -n size: Set the array size to size. "
                   "\n -p elements: Print out elements number of elements from.\n -H: prints out "
                   "program usage.\n");
            break;
        }
        }
    }

    if (S == 0) {
        printf("Select at least one sort to perform.\n");
        printf("sorting - \n -a: Employs all sorting algorithms. \n -i: Enables Insertion "
               "Sort. \n -h: Enables Heap Sort.\n "
               "-b: Enables Batcher Sort.\n -s: Enables Shell Sort.\n -q: Enables Quicksort. "
               "\n -r seed: Set the random seed to seed\n -n size: Set the array size to size. "
               "\n -p elements: Print out elements number of elements from.\n -H: prints out "
               "program usage.\n");
        return EXIT_FAILURE;
    }

    if (elements > size) {
        elements = size;
    }

    uint32_t *batcher_array = (uint32_t *) calloc(size, sizeof(uint32_t));
    uint32_t *shell_array = (uint32_t *) calloc(size, sizeof(uint32_t));
    uint32_t *heap_array = (uint32_t *) calloc(size, sizeof(uint32_t));
    uint32_t *quick_array = (uint32_t *) calloc(size, sizeof(uint32_t));
    uint32_t *insert_array = (uint32_t *) calloc(size, sizeof(uint32_t));

    if (set_member(S, 1)) {
        srandom(seed);
        for (uint32_t x = 0; x < size; x++) {
            insert_array[x] = random() & ((1 << 30) - 1);
        }
        insertion_sort(&stats, insert_array, size);
        print_stats(&stats, "Insertion Sort", size);
        for (uint32_t i = 0; i < elements; i++) {
            if (i != 0 && i % 5 == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, insert_array[i]);
        }
        printf("\n");

        srandom(seed);
        for (uint32_t x = 0; x < size; x++) {
            heap_array[x] = random() & ((1 << 30) - 1);
        }
        heap_sort(&stats, heap_array, size);
        print_stats(&stats, "Heap Sort", size);
        for (uint32_t i = 0; i < elements; i++) {
            if (i != 0 && i % 5 == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, heap_array[i]);
        }
        printf("\n");

        srandom(seed);
        for (uint32_t x = 0; x < size; x++) {
            shell_array[x] = random() & ((1 << 30) - 1);
        }
        shell_sort(&stats, shell_array, size);
        print_stats(&stats, "Shell Sort", size);
        for (uint32_t i = 0; i < elements; i++) {
            if (i != 0 && i % 5 == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, shell_array[i]);
        }
        printf("\n");

        srandom(seed);
        for (uint32_t x = 0; x < size; x++) {
            quick_array[x] = random() & ((1 << 30) - 1);
        }
        quick_sort(&stats, quick_array, size);
        print_stats(&stats, "Quick Sort", size);
        for (uint32_t i = 0; i < elements; i++) {
            if (i != 0 && i % 5 == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, quick_array[i]);
        }

        printf("\n");

        srandom(seed);
        for (uint32_t x = 0; x < size; x++) {
            batcher_array[x] = random() & ((1 << 30) - 1);
        }
        batcher_sort(&stats, batcher_array, size);
        print_stats(&stats, "Batcher Sort", size);
        for (uint32_t i = 0; i < elements; i++) {
            if (i != 0 && i % 5 == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, batcher_array[i]);
        }
        printf("\n");
    }

    if (set_member(S, 2)) {
        srandom(seed);
        for (uint32_t x = 0; x < size; x++) {
            heap_array[x] = random() & ((1 << 30) - 1);
        }

        //reset(&stats);
        heap_sort(&stats, heap_array, size);
        print_stats(&stats, "Heap Sort", size);
        for (uint32_t i = 0; i < elements; i++) {
            if (i != 0 && i % 5 == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, heap_array[i]);
        }
        printf("\n");
    }
    if (set_member(S, 3)) {
        srandom(seed);
        for (uint32_t x = 0; x < size; x++) {
            batcher_array[x] = random() & ((1 << 30) - 1);
        }

        //reset(&stats);
        batcher_sort(&stats, batcher_array, size);
        print_stats(&stats, "Batcher Sort", size);
        for (uint32_t i = 0; i < elements; i++) {
            if (i != 0 && i % 5 == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, batcher_array[i]);
        }
        printf("\n");
    }
    if (set_member(S, 4)) {
        srandom(seed);
        for (uint32_t x = 0; x < size; x++) {
            shell_array[x] = random() & ((1 << 30) - 1);
        }

        //reset(&stats);
        shell_sort(&stats, shell_array, size);
        print_stats(&stats, "Shell Sort", size);
        for (uint32_t i = 0; i < elements; i++) {
            if (i != 0 && i % 5 == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, shell_array[i]);
        }
        printf("\n");
    }
    if (set_member(S, 5)) {
        srandom(seed);
        for (uint32_t x = 0; x < size; x++) {
            quick_array[x] = random() & ((1 << 30) - 1);
        }

        //reset(&stats);
        quick_sort(&stats, quick_array, size);
        print_stats(&stats, "Quick Sort", size);
        for (uint32_t i = 0; i < elements; i++) {
            if (i != 0 && i % 5 == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, quick_array[i]);
        }
        printf("\n");
    }
    if (set_member(S, 6)) {
        srandom(seed);
        for (uint32_t x = 0; x < size; x++) {
            insert_array[x] = random() & ((1 << 30) - 1);
        }

        //reset(&stats);
        insertion_sort(&stats, insert_array, size);
        print_stats(&stats, "Insertion Sort", size);
        for (uint32_t i = 0; i < elements; i++) {
            if (i != 0 && i % 5 == 0) {
                printf("\n");
            }
            printf("%13" PRIu32, insert_array[i]);
        }
        printf("\n");
    }

    free(batcher_array);
    free(shell_array);
    free(heap_array);
    free(quick_array);
    free(insert_array);

    return 0;
}
