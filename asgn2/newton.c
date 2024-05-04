#include "mathlib.h"

#include <stdio.h>

static double iteration = 0;

double sqrt_newton(double x) {
    //translated provided pseudocode from the assignment's pdf to C
    double z = 0.0;
    double y = 1.0;
    iteration = 0;

    //"force while condition to be true initially"
    while (absolute(y - z) > EPSILON) {
        z = y;
        y = 0.5 * (z + x / z);
        iteration += 1;
    }
    return y;
}

//returns terms
int sqrt_newton_iters(void) {
    return iteration;
}
