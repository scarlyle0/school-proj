#include "mathlib.h"

#include <stdio.h>

static int iters = 0;

// Based on pseudo sqrt() from assignment PDF
// sqrt_newton approximates the square root of a number
// Returns the approximates square root of a number
// Accepts a double x which is the number that is to be square rooted
double sqrt_newton(double x) {
    double z = 0.0;
    double y = 1.0;
    iters = 0;
    while (absolute(y - z) > EPSILON) { // Iterate until new value is within an epsilon of old value
        iters++;
        z = y;
        y = 0.5 * (z + x / z); // Find new value
    }
    return y;
}

// sqrt_newton_iters returns the number of iterations to find sqrt
// Returns the number of iterations it takes sqrt_newton to find sqrt
// Accepts no parameters
int sqrt_newton_iters(void) {
    return iters;
}
