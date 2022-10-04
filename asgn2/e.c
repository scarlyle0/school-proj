#include "mathlib.h"

#include <stdio.h>

static int term_count = 0;

// e calculates e using taylor series
// Returns the value summation of terms which are close to e
// Accepts no parameters
double e(void) {
    double e_value = 0;
    double factorial = 1;
    int i = 0;
    // Loop until the term being added is less than epsilon
    while ((1 / factorial) >= EPSILON) {
        if (i != 0) {
            factorial *= i; // Instead of calculating factorial we multiply by i+1 every term
        }
        i++;
        term_count++;
        e_value += (1 / factorial); // Add terms to the sum
    }
    return e_value;
}

// e_terms returns the number of terms for e to calculate e
// Returns the number of terms for e to calculate e
// Accepts no parameters
int e_terms(void) {
    return term_count;
}
