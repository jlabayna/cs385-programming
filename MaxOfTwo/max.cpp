/*
 * max.cpp
 *
 *  Created on: Sep 2, 2020
 *      Author: user
 */

// Note: The program itself is an argument as a character array!
// Each string in argv ends in \0

// Note: werror turns warnings into errors

#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;


/**
 * Returns the max of two integers
 */
int max(int m, int n) {
	return m > n ? m : n;
}

int main(int argc, char *argv[]) {
	int m, n;
	istringstream iss;

	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
		return 1;
	}

	iss.str(argv[1]);
	if( !(iss >> m) ) {
		cerr << "Error: The first argument is not a valid integer." << endl;
		return 1;
	}

	iss.clear();
	iss.str(argv[2]);
	if( !(iss >> n) ) {
		cerr << "Error: The second argument is not a valid integer." << endl;
		return 1;
	}

	cout << "max(" << m << ", " << n << ") = " << max(m, n) << endl;

	// Demonstration of floating point precision
	double d = 22.0 / 7;
	cout << fixed << setprecision(8) << d << endl;
	return 0;
}
