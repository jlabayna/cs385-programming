/*
 * pointers.cpp
 *
 *  Created on: Sep 4, 2020
 *      Author: user
 */
#include <iostream>

using namespace std;

void display_array(int array[], const int length) {
	cout << "[";
	if (length >= 1) {
		cout << array[0];
	}
	for (int i = 1; i < length; ++i) {
		/* Inefficient. Better way is the move the if statement outside of the loop, as seen above.
		if (i != 0) {
			cout << << ",";
		}
		*/
		cout << "," << array[i];
	}

	cout << "]" << endl;
}

// Modified array printer using pointers.
void display_array_ptr(int array[], const int length) {
    cout << "[";
	if (length >= 1) {
		cout << *array;
	}
	// Set the iterator (*prt) to the start of the array plus 1. Also set the end pointer.
	// Stop when the pointer exceeds the end.
	// Increment the pointer variable. DO NOT DEREFERENCE USING *prt.
	// We want the address to increment, so we access elements of the array.
    for (int *ptr = array + 1, *end = array + length; ptr < end; ++ptr) {
        cout << ", " << *ptr;
    }
    cout << "]" << endl;
}

void pass_by_value(int x) {
	x = 10;
}

// UNSAFE
void pass_by_pointer(int *x) {
	*x = 15;
}

// SAFER
void pass_by_reference(int &x) {
	x = 1;
}

// TODO: STUDY THIS AND EXPLAIN WHAT HAPPENS
int main() {
	int x = 5, *z = &x;					// Pointer z (specified by *) gets address (specified by &) of x.
	cout << &x << " " << z << endl; 	// Prints ADDRESSES of both (the addresses)
	cout << x << " " << *z << endl; 	// Prints VALUES of both (* dereferences z, using z to point to it's specified address)
	*z = 7; 							// This modifies x! We go to the address specified by *z and modify the value there.
	cout << &x << " " << *z << endl; 	// Prints address of x (via &), and we get the value at the address specified by z.
	int y= 6;
	z = &y;
	cout << x << " " << *z << endl;		// z now the address of y.

	*z = 7;
	cout << x << " " << *z << endl;

	cout << &x << " " << &y << " " << z << endl;
	z--;								// Decrement by 4 bytes (the size of an int);
	cout << &x << " " << &y << " " << z << endl;
	z++;
	z++;
	cout << *z << endl;

	/* BAD IDEA
	z += 30000;
	cout << *z << endl;					// Segmentation fault!!!! Referenced memory outside of your segment
	*/

	int *values = new int[y];
	for (int i = 0; i < y; i++) {
		//values[i] = i;
		*(values + i) = i;
	}
	display_array(values, y);
	display_array_ptr(values, y);
	delete [] values;


	//TODO: EXPLAIN ME
	x = 5;
	y = 6;
	pass_by_value(x);
	cout << x << endl;

	pass_by_pointer(&x);
	cout << x << endl;

	pass_by_reference(x);
	cout << x << endl;

	return 0;
}



