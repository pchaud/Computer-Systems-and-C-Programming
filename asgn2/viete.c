#include "mathlib.h"

#include <stdio.h>

static double factors = 0;

double pi_viete(void) {
    double total = 1;
    factors = 0;

    //for loop stimulates a product operator
    for (double term = sqrt_newton(2); absolute(2 - term) > EPSILON; factors += 1) {
        //total is a with the subscript of term (k)
        total *= (term / 2);
        term = sqrt_newton((2 + term));
    }

    return (2 / total);
}

//returns factors calculated in the Viete formula
int pi_viete_factors(void) {
    return factors;
}
