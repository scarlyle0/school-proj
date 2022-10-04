#include "stats.h"

#include <stdint.h>
#include <stdio.h>

// This function places elements less than pivot on left, more than pivot on right
// Accepts stats, array, lo value in partition, hi value in partitian
// Returns the index indicated the division of partitioned parts
// Functions based off Assignment PDF python pseudo
uint32_t partition(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    uint32_t i = lo - 1;
    for (uint32_t k = lo; k < hi; k++) {
        if (cmp(stats, A[k - 1], A[hi - 1]) == -1) {
            i += 1;
            swap(stats, &A[i - 1], &A[k - 1]);
        }
    }
    swap(stats, &A[i], &A[hi - 1]); // Swap pointer with pivot
    return i + 1; // Returns index that divides partition
}

// This function applies quicksort recursively on itself until the partitions are singular
// Returns nothing
// Takes paramaters stats, the array, the lo value and the hi value of partition
void quick_sorter(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    if (lo < hi) {
        uint32_t p = partition(stats, A, lo, hi); // Find partition
        quick_sorter(stats, A, lo, p - 1); // Call recursively to top of partition
        quick_sorter(stats, A, p + 1, hi); // Call recursively to bottom of partition
    }
}

// This function just calls the quick_sorter function
// Takes parameters stats, the array, and num of array elements
// Returns nothing
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n);
}
