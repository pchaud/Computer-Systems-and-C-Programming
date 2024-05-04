#include "mathlib.h"

#include <stdio.h>

static double iteration = 0;

double pi_madhava(void) {
    double negative = -3;
    double sum = 1;
    double x = 1;
    iteration = 0;

    //summation with this for loop, EPSILON represents the infinity, utilzies local variables to simplify the formula
    for (double k = 1; absolute(x) > EPSILON; k += 1) {
        x = 1 / (((2 * k) + 1) * negative);
        sum += x;
        negative *= -3;
        iteration += 1;
    }

    //multiplies the entire right-hand side of the formula with the square root of 12 with a call to sqrt_newton
    sum *= sqrt_newton(12);
    return sum;
}

//once again, returns the number of terms computed with the madhava formula
int pi_madhava_terms(void) {
    return iteration;
}
