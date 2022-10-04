#include "stats.h"

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// This function finds the max child from a mother in a heap
// Returns the greater child as a uint32_t
// Takes parameters stats, the array, and the mother index/last index
// Functions based off Assignment PDF python pseudo
uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = (2 * first);
    uint32_t right = (left + 1);
    if ((right <= last) && ((cmp(stats, A[right - 1], A[left - 1])) == 1)) {
        return right;
    }
    return left;
}

// This function fixes the heap to follow max heap standards
// Returns nothing
// Takes parameters, stats, the array, the heap index  be fixed and the last index
void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t mother = first;
    uint32_t great = max_child(stats, A, mother, last); // Find biggest child
    while ((mother <= floor(last / 2)) && (!found)) {
        if (cmp(stats, A[mother - 1], A[great - 1])
            == -1) { // If mother is less than greatest child swap them
            swap(stats, &A[mother - 1], &A[great - 1]);
            mother
                = great; // Make mother the greatest child and keep going to make sure heap is in order
            great = max_child(stats, A, mother, last); // Find max child of new mother
        } else {
            found = true;
        }
    }
}

// This function builds heap by inputting all heap mothers to be fixed
// Returns nothing
// Takes parameters as first index, last index, stats and the array
void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t i = floor(last / 2); i > first - 1; i--) {
        fix_heap(stats, A, i, last);
    }
}
// This functions sorts the heap and then swaps first
// and last array values then forgets about the last value
// it keeps doing this until array is sorted
// Returns nothing
// Takes parameters stats, the array, and num_elements in array
void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(stats, A, first, last); // Fix the max heap
    for (uint32_t i = n; i > first; i--) { // Swap first and last then forget about last
        swap(stats, &A[first - 1], &A[i - 1]);
        fix_heap(stats, A, first, i - 1);
    }
}
