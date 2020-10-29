/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : James Labayna
 * Version : 1.0
 * Date    : September 2, 2020
 * Description : Calculates the square root of a double using Newton's method.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

/**
 * Calculates the square root of a double using Newton's method.
 */
double sqrt(double num, double epsilon) {
	if (num < 0) {
		return numeric_limits<double>::quiet_NaN();
	}

	if (num == 0 || num == 1) {
		return num;
	}

	double last_guess = num;
	double next_guess = (last_guess + num/last_guess) / 2;

	while ( !( abs(last_guess - next_guess) <= epsilon) ) {
		last_guess = next_guess;
		next_guess = (last_guess + num/last_guess) / 2;
	}

	return next_guess;
}


int main(int argc, char *argv[]) {
	double value, epsilon;
	istringstream iss;

	/*
	 * If the number of arguments is not 2 and not 3,
	 * then sqrt is not being used with proper syntax.
	 * sqrt requires one value and optionally a given epsilon.
	 */
	/*
	 * Additional note: from here (line 50) to line 83 is largely based on practice.cpp and 9/2 lecture:
	 * https://sit.instructure.com/courses/38971/files/6434887/download?download_frd=1
	 */
	if (argc != 2 && argc != 3) {
		cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
		/* Note to self: changed this back to argv[0] after I realized that
		 *               it puts the "./" in front of the filename.
		 */
		return 1;
	}


	iss.str(argv[1]);
	/* Note to self: conversion returns a null pointer (implicitly convertible to bool)
	 *               if fail() is true.
	 *               else if no error on conversion, returns !fail().
	 * Refer to https://en.cppreference.com/w/cpp/io/basic_ios/operator_bool for details.
	 */
	if( !(iss >> value) ) {
		cerr << "Error: Value argument must be a double." << endl;
		return 1;
	}

	if (argc == 3) {
		iss.clear();
		iss.str(argv[2]);
		if( !(iss >> epsilon) || (epsilon <= 0) ) {
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		}
	}

	cout << fixed << setprecision(8) << sqrt(value, epsilon) << endl;

	return 0;
}

