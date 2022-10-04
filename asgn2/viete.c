#include "mathlib.h"

#include <stdio.h>

static int factor_count = 0;

// pi_viete finds pi using the viete formula
// Returns the approximates pi
// Accepts no paramters
double pi_viete(void) {
    double product = 1;
    double numerators = sqrt_newton(2);
    // Keep looping until the numerator is within an epsilon of 2
    while ((numerators) < 2 - EPSILON) {
        product *= numerators / 2;
        numerators += 2;
        numerators = sqrt_newton(numerators);
        factor_count++;
    }
    return (2 / product); // since formula finds 2/pi, find 2/2/pi to find pi
}

// pi_viete_factors returns how many factors it took to find pi
// Returns how many factors it took viete to find pi
// Accepts no parameters
int pi_viete_factors(void) {
    return factor_count;
}
