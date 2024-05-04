#include "mathlib.h"

#include <stdio.h>

static double iteration = -1;

double pi_bbp(void) {

    double numerator = 0;
    double denominator = 0;
    double answer = 0;
    double term = 1;
    iteration = 0;

    //the for loop mimicks summation and EPSILON represents infinity
    for (double k = 0; absolute(term) > EPSILON; k += 1) {
        //calculates the bbp formula with the least number of multiplications (formula on page 6 of asgn pdf)
        numerator = (k * ((120 * k) + 151) + 47);
        denominator = (k * (k * (k * ((512 * k) + 1024) + 712) + 194) + 15);
        //combines the right-hand side of the formula
        answer += term * (numerator / denominator);
        //is the 1/16^k of th formula
        term /= 16;
        iteration += 1;
    }

    return answer;
}

//responsible for returning number of terms computed with the bbp formula
int pi_bbp_terms(void) {
    return iteration;
}
