#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS          "haeisqn:p:r:"
#define DEFAULT_PRINT    100
#define DEFAULT_ELEMENTS 100
#define DEFAULT_SEED     13371453
#define MASK             0x3fffffff

enum { HELP, ALL, HEAP, INSERTION, SHELL, QUICK };

void fill_array(uint32_t *A, uint32_t num_elements, uint32_t mask, int seed);
// Main function that acts as a test harness for sorting functions
// Returns 0
// Accepts command line arguments as input
int main(int argc, char **argv) {
    int opt = 0;
    uint32_t mask = MASK;
    uint32_t num_elements = DEFAULT_ELEMENTS;
    uint32_t num_print = DEFAULT_PRINT;
    int seed = DEFAULT_SEED;
    Stats stats;
    Set arguments = empty_set();
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': // All
            arguments = insert_set(INSERTION, arguments);
            arguments = insert_set(SHELL, arguments);
            arguments = insert_set(HEAP, arguments);
            arguments = insert_set(QUICK, arguments);
            break;
        case 'i': arguments = insert_set(INSERTION, arguments); break; // Insertion Sort
        case 's': arguments = insert_set(SHELL, arguments); break; // Shell Sort
        case 'r': seed = atoi(optarg); break; // Seed
        case 'e': arguments = insert_set(HEAP, arguments); break; // Heap Sort
        case 'q': arguments = insert_set(QUICK, arguments); break; // Quick Sort
        case 'n': // Length
            num_elements = atoi(optarg);
            break;
        case 'p': // Print
            num_print = atoi(optarg);
            break;
        case 'h': // Help
            arguments = empty_set();
            arguments = insert_set(HELP, arguments);
            break;
        }
    }

    // If no sorting algorithm is called, print help
    if ((!(member_set(HEAP, arguments))) && (!(member_set(SHELL, arguments)))
        && (!(member_set(INSERTION, arguments))) && (!(member_set(QUICK, arguments)))) {
        arguments = empty_set();
        arguments = insert_set(HELP, arguments);
    }

    // This makes sure the program isn't trying to print more elements than there are
    if (num_elements < num_print) {
        num_print = num_elements;
    }
    // This array declarations is based off of eugenes section video
    uint32_t *A = (uint32_t *) calloc(num_elements, sizeof(uint32_t));

    // Each if statement does a seperate command
    // Sorting if statements fill the array, reset stats
    // Sort then print sorting results
    if (member_set(HEAP, arguments)) {
        fill_array(A, num_elements, mask, seed);
        reset(&stats);
        heap_sort(&stats, A, num_elements);
        printf("Heap Sort, %d elements, %lu moves, %lu compares\n", num_elements, stats.moves,
            stats.compares);
        for (uint32_t i = 0; i < num_print; i++) {
            printf("%13" PRIu32, A[i]);
            if ((i + 1) % 5 == 0) {
                printf("\n");
            }
        }
        if (num_print % 5 != 0) {
            printf("\n");
        }
    }
    if (member_set(SHELL, arguments)) {
        fill_array(A, num_elements, mask, seed);
        reset(&stats);
        shell_sort(&stats, A, num_elements);
        printf("Shell Sort, %d elements, %lu moves, %lu compares\n", num_elements, stats.moves,
            stats.compares);
        for (uint32_t i = 0; i < num_print; i++) {
            printf("%13" PRIu32, A[i]);
            if ((i + 1) % 5 == 0) {
                printf("\n");
            }
        }
        if (num_print % 5 != 0) {
            printf("\n");
        }
    }
    if (member_set(INSERTION, arguments)) {
        fill_array(A, num_elements, mask, seed);
        reset(&stats);
        insertion_sort(&stats, A, num_elements);
        printf("Insertion Sort, %d elements, %lu moves, %lu compares\n", num_elements, stats.moves,
            stats.compares);
        for (uint32_t i = 0; i < num_print; i++) {
            printf("%13" PRIu32, A[i]);
            if ((i + 1) % 5 == 0) {
                printf("\n");
            }
        }
        if (num_print % 5 != 0) {
            printf("\n");
        }
    }
    if (member_set(QUICK, arguments)) {
        fill_array(A, num_elements, mask, seed);
        reset(&stats);
        quick_sort(&stats, A, num_elements);
        printf("Quick Sort, %d elements, %lu moves, %lu compares\n", num_elements, stats.moves,
            stats.compares);
        for (uint32_t i = 0; i < num_print; i++) {
            printf("%13" PRIu32, A[i]);
            if ((i + 1) % 5 == 0) {
                printf("\n");
            }
        }
        if (num_print % 5 != 0) {
            printf("\n");
        }
    }
    if (member_set(HELP, arguments)) {
        printf("SYNOPSIS\n   A collection of comparison-based sorting algorithms.\n\n");
        printf("USAGE\n   ./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n\n");
        printf("OPTIONS\n   -h              display program help and usage.\n   -a              "
               "enable all sorts.\n   -e              enable Heap Sort.\n   "
               "-i              enable Insertion Sort.\n   -s              enable Shell Sort.\n   "
               "-q              enable Quick Sort."
               "\n   -n length       specify number of array elements (default: 100).\n   -p "
               "elements     specify number of elements to print (default: 100).\n   "
               "-r seed         specify random seed (default: 13371453).\n");
    }
    // Free the allocated mem
    free(A);
    return 0;
}

// This function fills the array with random masked uint32_t
// Returns nothing
// Accepts the array, number of elements, the mask, and seed
void fill_array(uint32_t *A, uint32_t num_elements, uint32_t mask, int seed) {
    srandom(seed);
    for (uint32_t i = 0; i < num_elements; i++) {
        A[i] = random() & mask;
    }
}
