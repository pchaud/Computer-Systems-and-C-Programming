#include "mathlib.h"

#include <stdio.h>

static double iteration = 0;

double pi_euler(void) {
    double term = 1.0;
    double ans = 0;
    iteration = 0;

    //works through the summation of 1 divided by k squared with k equal to 1 and EPSILON = infinity
    for (double k = 1; absolute(term) > EPSILON; k += 1) {
        term = 1 / (k * k);
        ans += term;
    }

    //multiplies 6 with the calculated answer and then square roots this entire portion
    iteration += 1;
    return sqrt_newton(6 * ans);
}

//returns the amount of terms computed
int pi_euler_terms(void) {
    return iteration;
}
