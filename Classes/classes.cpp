/*
 * classes.cpp
 *
 *  Created on: Sep 9, 2020
 *      Author: user
 */
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class MyPoint {

public:
	// Constructor that uses an initializer list
	// All vars must be initialized by the end of this constructor.
	// Last curly brace thing is the body of the constructor.
	MyPoint(short x, int y, float z) : x_{x}, y_{y}, z_{z} { }

	// Methods that don't modify vars should be declared const (for efficiency)
	void print_coords() const {

	}

	// Mutator.
	void set_x(short x) {
		x_ = x;
	}

	// Accessor.
	short get_x() const {
		return x_;
	}



private:
	// Member variables (fields). Use trailing_ for these according to style guide.
	// Note on size: object size is probably going to be the size of the member variables combined.
	// BE CAREFUL WITH STACK SIZE.
	short x_;
	int y_;
	float z_;
};

void display_points(const vector<MyPoint> &points) {
	// cbegin gives constant iterator
	for(auto it = points.cbegin(); it != points.cend(); ++it) {

	}
}

int main() {
	int x,y;

	// Know that this syntax places the object in the stack
	MyPoint point1(10000, 7.2, 22);

	// To place on the heap (use for big stuff)
	MyPoint *heap_point = new MyPoint(2, 3, 4);
	// To reference now
	heap_point->print_coords();
	// To free up heap:
	delete heap_point;


	vector<MyPoint> points;


	// for each loop
	// const means not modifying the poitns as we loop
	// auto means we don't need to specify type we loop over. Deduces type is MyPoint
	// We're going by reference here so we don't copy over each element.
	for (const auto &point : points) {

	}
}
