#include "stats.h"

#include <stdint.h>
#include <stdio.h>

// This function does insertion sort on an array
// Returns nothing
// Accepts parameters as stat struct, array and number of elements in array
void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t j;
    uint32_t temp;
    // Based on assignment PDF
    for (uint32_t i = 1; i < n; i++) {
        j = i;
        temp = move(stats, A[i]);
        // Check if any number before is greater, if it is swap them
        // Keep doing this until array is sorted
        while ((j > 0) && (cmp(stats, temp, A[j - 1]) == -1)) {
            A[j] = move(stats, A[j - 1]);
            j -= 1;
        }
        A[j] = move(stats, temp);
    }
}
