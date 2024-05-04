#include "mathlib.h"

#include <stdio.h>

static double factors = 0;

double pi_wallis(void) {

    double total = 1;
    double k = 1;
    factors = 0;

    //conducts the product operator of 4k squared divided by 4k^2 - 1
    for (double term = 0; absolute(1 - term) > EPSILON; factors += 1) {
        //computes 4k^2
        double numerator = (4 * (k * k));
        //computes 4k^2 - 1
        double denominator = (numerator - 1);
        //term divides both and then total is multiplied to this and then k is iterated
        term = (numerator / denominator);
        total *= term;
        k += 1;
    }

    //2 is multiplied with the total
    return (2 * total);
}

//returns the number of factors calculated with the wallis formula
int pi_wallis_factors(void) {
    return factors;
}
