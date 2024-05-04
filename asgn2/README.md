# Purpose of My Program

This program contains 7 mathematical functions (including e, BBP, Madhava, Euler, Vi‘ete, Wallis, Newton) without using a math library that allows us to compute the major math functions e and Pi. These functions are supposed to mimic the math.h library without exactly utilizing it within our function files other than comparing our results with the math library’s. We will have an additional test harness file named mathlib-test that will execute the outputs and their formats of the function files.

# How to Use My Program

In order to use my program, the user must first run the command "make" within the terminal. Next ./mathlib-test (with a command-line option) should be entered into the terminal. Of course, the user must input a specific command line which should either be an a, e, b, r, v, w, n, m, s, or h (purposes specified below) and if neither of the options is inputted, the default will be the help message. If the user wants to see the terms and statistics alongside the tests the -s command line should be followed with whatever specific formula they want to see. 

	-a: Runs all tests.
	-e: Runs e approximation test.
	-b: Runs Bailey-Borwein-Plouffe PI approximation test.
	-m: Runs Madhava PI approximation test.
	-r: Runs Euler sequence PI approximation test.
	-w: Runs Wallis PI approximation test.
	-v : Runs Viète PI approximation test.
	-n: Runs Newton-Raphson square root approximation tests.
	-s: Enable printing of statistics to see computed terms and factors for each tested function.
	-h: Display a help message detailing program usage.



