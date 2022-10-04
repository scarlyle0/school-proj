#include "mathlib.h"

#include <stdio.h>

static int term_count = 0;

// pi_euler finds pi using the euler formula
// Returns final_pi which is an approximation of pi based on the summation in the formula
// Accepts no parameters
double pi_euler(void) {
    double i = 1;
    double summation = 0;
    double final_pi = 0;
    // Loops until a single term being added is less then epsilon
    while ((1 / (i * i)) >= EPSILON) {
        summation += 1 / (i * i); // Add each term to the summation
        i++;
        term_count++;
    }
    // Finish the formula
    final_pi = sqrt_newton(6 * summation);
    return final_pi;
}

// pi_euler_terms counts the number of terms it took to approximate pi
// Returns the number of terms it took to approximate pi
// Accepts no parameters
int pi_euler_terms(void) {
    return term_count;
}
