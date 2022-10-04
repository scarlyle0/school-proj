#include "mathlib.h"

#include <stdio.h>

static int term_count = 0;

// pi_bbp calculates pi using the bbp formula
// The return value is the summation of the formula which is close to pi
// Accepts no parameters
double pi_bbp(void) {
    double sixteen_power = 1;
    double i = 0;
    double summation = 0;
    // This while continuously sums the terms until the summation is within an epsilon of pi
    while (((1 / sixteen_power) * (i * (120 * i + 151) + 47)
               / (i * (i * (i * (512 * i + 1024) + 712) + 194) + 15))
           >= EPSILON) {
        summation += (1 / sixteen_power) * (i * (120 * i + 151) + 47)
                     / (i * (i * (i * (512 * i + 1024) + 712) + 194) + 15);
        sixteen_power
            *= 16; // Instead of calculating 16 to the power i, we multiply by 16 every term
        i++;
        term_count++;
    }
    return summation;
}

// pi_bbp_terms returns the number of terms it took for bbp to calculate pi
// The return value is the number of terms it took for bbp to calculate pi
// Accepts no parameters
int pi_bbp_terms(void) {
    return term_count;
}
