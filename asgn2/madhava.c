#include "mathlib.h"

#include <stdio.h>

static int term_count = 0;

// pi_madhava approximates the value of pi based on the madhava formula
// Returns the approximated value of pi based on the summation
// Accepts no parameters
double pi_madhava(void) {
    double i = 0;
    double final_pi = 0;
    double three_power = 1;
    double summation = 0;
    // Keeps looping until a single term is between +/- epsilon
    while (((1 / ((2 * i + 1) * (three_power))) > EPSILON)
           || ((1 / ((2 * i + 1) * (three_power))) < -EPSILON)) {
        summation += (1 / ((2 * i + 1) * (three_power)));
        three_power *= -3; // Instead of calculating -3^k, multiply by -3 every term
        i++;
        term_count++;
    }
    double sqrt_twelve = sqrt_newton(12); // Finish the formula
    final_pi = (sqrt_twelve * summation);
    return final_pi;
}

// pi_madhava_terms counts the number of terms to approximate pi
// Returns the number of terms to approximate pi
// Accepts no parameters
int pi_madhava_terms(void) {
    return term_count;
}
