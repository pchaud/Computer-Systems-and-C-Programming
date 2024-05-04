#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#define OPTIONS "aebrvwnmsh"

// At the very top are my math and style libraries needed
// Within my main file I am initializing the commands as "false" or 0 since they have not been called yet.

int main(int argc, char *argv[]) {

    int opt = 0;
    //double newton_op = 49;
    int a = 0;
    int e1 = 0;
    int b = 0;
    int r = 0;
    int v = 0;
    int w = 0;
    int n = 0;
    int m = 0;
    int s = 0;

    // I am creating a while loop here which will create my switch cases and am listing that the command is true or 1 when the respective case is called.
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': {
            e1 = 1;
            b = 1;
            m = 1;
            r = 1;
            v = 1;
            w = 1;
            n = 1;
            break;
        }

        case 'e': {
            e1 = 1;
            break;
        }
        case 'b': {
            b = 1;
            break;
        }
        case 'm': {
            m = 1;
            break;
        }
        case 'r': {
            r = 1;
            break;
        }
        case 'v': {
            v = 1;
            break;
        }
        case 'w': {
            w = 1;
            break;
        }
        case 'n': {
            n = 1;
            break;
        }
        case 's': {
            s = 1;
            break;
        }

        //This is the help message that is printed and lists all the commands the user needs to run my program.
        case 'h': {
            printf("\n");
            printf("mathlib-test command-line options: \n");
            printf("	-a: runs all tests.\n");
            printf("	-e: computes e using Taylor series.\n");
            printf("	-b: computes pi using Bailey-Borwein-Plouffe formula.\n");
            printf("	-m: computes pi using Madhava series.\n");
            printf("        -w: computes Wallis pi approximation.\n");
            printf("	-r: computes pi using Euler's approximation. \n");
            printf("	-v: run Viete pi approximation.\n");
            printf("	-n: compute square root using Newton-Raphson method. \n");

            printf("	-s: prints statistics.\n");
            printf("	-h: prints help message.\n");
            break;
        }

        //The defaulted output if a user inputs an invalid option
        default: {

            printf("\n");
            printf("mathlib-test command-line options: \n");
            printf("	-a: runs all tests.\n");
            printf("	-e: computes e using Taylor series.\n");
            printf("	-b: computes pi using Bailey-Borwein-Plouffe formula.\n");
            printf("	-m: computes pi using Madhava series.\n");
            printf("        -w: computes Wallis pi approximation.\n");
            printf("	-r: computes pi using Euler's approximation. \n");
            printf("	-v: run Viete pi approximation.\n");
            printf("	-n: compute square root using Newton-Raphson method. \n");

            printf("	-s: prints statistics.\n");
            printf("	-h: prints help message.\n");

            break;
        }

            return 0;
        }
    }

    if (argc < 2) {
        printf("\n");
        printf("mathlib-test command-line options: \n");
        printf("	-a: runs all tests.\n");
        printf("	-e: computes e using Taylor series.\n");
        printf("	-b: computes pi using Bailey-Borwein-Plouffe formula.\n");
        printf("	-m: computes pi using Madhava series.\n");
        printf("        -w: computes Wallis pi approximation.\n");
        printf("	-r: computes pi using Euler's approximation. \n");
        printf("	-v: run Viete pi approximation.\n");
        printf("	-n: compute square root using Newton-Raphson method. \n");

        printf("	-s: prints statistics.\n");
        printf("	-h: prints help message.\n");
    }
    // This specific if statement will print every function's output including the terms.
    if (a == 1) {
        printf("e() = %16.15lf,", e());
        printf(" M_E = %16.15lf,", M_E);
        printf(" diff = %16.15lf\n,", absolute(M_E - e()));
        printf("e() terms = %d\n", e_terms());

        printf("pi_bbp() = %16.15lf, ", pi_bbp());
        printf("M_PI = %16.15lf,", M_PI);
        printf(" diff = %16.15lf\n,", absolute(M_PI - pi_bbp()));
        printf("pi_bbp() terms = %d\n", pi_bbp_terms());

        printf("pi_madhava() = %16.15lf, ", pi_madhava());
        printf("M_PI = %16.15lf,", M_PI);
        printf(" diff = %16.15lf\n,", absolute(M_PI - pi_madhava()));
        printf("pi_madhava() terms = %d\n", pi_madhava_terms());

        printf("pi_euler() = %16.15lf, ", pi_euler());
        printf("M_PI = %16.15lf,", M_PI);
        printf(" diff = %16.15lf\n,", absolute(M_PI - pi_euler()));
        printf("pi_euler() terms = %d\n", pi_euler_terms());

        printf("pi_viete() = %16.15lf, ", pi_viete());
        printf("M_PI = %16.15lf,", M_PI);
        printf(" diff = %16.15lf,", absolute(M_PI - pi_viete()));
        printf("pi_viete() terms = %d\n", pi_viete_factors());

        printf("pi_wallis() = %16.15lf, ", pi_wallis());
        printf("M_PI = %16.15lf,", M_PI);
        printf(" diff = %16.15lf,", absolute(M_PI - pi_wallis()));
        printf("pi_wallis() terms = %d\n", pi_wallis_factors());

        printf("sqrt_newton() = %16.15lf\n", sqrt_newton(49.0));
        printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
    }

    // The rest are within this format which prints my function's output, the math library's
    // output, and the difference between them. And there is another if statement
    // if -s is printed alongside then the number of terms will also print.
    if (e1 == 1) {

        printf("e() = %16.15lf,", e());
        printf(" M_E = %16.15lf,", M_E);
        printf(" diff = %16.15lf\n", (M_E - e()));

        if (s > 0) {
            printf("e() terms = %d\n", e_terms());
        }
    }
    if (b == 1) {
        printf("pi_bbp() = %16.15lf, ", pi_bbp());
        printf("M_PI = %16.15lf,", M_PI);
        printf(" diff = %16.15lf\n", absolute(M_PI - pi_bbp()));

        if (s > 0) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
    }

    if (m == 1) {
        printf("pi_madhava() = %16.15lf, ", pi_madhava());
        printf("M_PI = %16.15lf,", M_PI);
        printf(" diff = %16.15lf\n", (M_PI - pi_madhava()));

        if (s > 0) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }

    if (r == 1) {
        printf("pi_euler() = %16.15lf, ", pi_euler());
        printf("M_PI = %16.15lf,", M_PI);
        printf(" diff = %16.15lf\n", absolute(M_PI - pi_euler()));

        if (s > 0) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    }

    if (v == 1) {
        printf("pi_viete() = %16.15lf, ", pi_viete());
        printf("M_PI = %16.15lf,", M_PI);
        printf(" diff = %16.15lf\n", absolute(M_PI - pi_viete()));

        if (s > 0) {
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
    }

    if (w == 1) {
        printf("pi_wallis() = %16.15lf, ", pi_wallis());
        printf("M_PI = %16.15lf,", M_PI);
        printf(" diff = %16.15lf\n", absolute(M_PI - pi_wallis()));

        if (s > 0) {
            printf("pi_wallis() terms = %d\n", pi_wallis_factors());
        }
    }

    //If the case where the square root option is called, the following print statements are displayed on terminal
    if (n == 1) {
        for (double i = 0; i < 9.90; i += 0.1) {

            printf("sqrt_newton(%.2f) = %16.15lf,", i, sqrt_newton(i));
            printf(" sqrt(%.2f) = %16.15lf,", i, sqrt(i));
            printf(" diff = %16.15lf\n", (sqrt(i) - sqrt_newton(i)));

            if (s > 0) {
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }
        }
    }

    return 0;
}
