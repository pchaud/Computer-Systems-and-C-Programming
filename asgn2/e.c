#include "mathlib.h"

#include <stdio.h>

static double iteration = 0;

double e(void) {
    double fact = 1.0;
    double sum = 0;
    double addTerm = 1.0 / fact;
    //necessary to reset iteration to 0 in all functions to resolve an incorrect number of terms displaying
    iteration = 0;

    //this while loop stimulates the summation with EPSILON acting as infinity and 1 divided by not k
    while (absolute(addTerm) > EPSILON) {
        iteration += 1;
        sum += addTerm;
        fact *= iteration;
        addTerm = 1.0 / fact;
    }

    return sum;
}

//this function is responsible for returning the number of terms computed

int e_terms(void) {
    return iteration;
}
