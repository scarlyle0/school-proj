#include "stats.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>

// Gaps calculates the gap that shell uses to calculate
// Returns the calculated gap
// Takes in an integer k as a parameter
uint32_t gaps(int k) {
    return floor((pow(3, k) - 1) / 2);
}

// Shell sort sorts an array using shell sorting method
// Returns nothing
// Takes in a stats struct, an array, and an integer which is the num_elements in the array.
void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t j = 0;
    uint32_t temp = 0;
    // Based on Assignment PDF
    for (uint32_t k = (log(3 + 2 * n) / log(3)); k > 0; k--) {
        uint32_t gap = gaps(k);
        for (uint32_t i = gap; i < n; i++) {
            j = i;
            temp = move(stats, A[i]);
            while ((j >= gap) && (cmp(stats, temp, A[j - gap]) == -1)) {
                A[j] = move(stats, A[j - gap]);
                j -= gap;
            }
            A[j] = move(stats, temp);
        }
    }
}
