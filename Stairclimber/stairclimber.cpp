/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : James Albert P. Labayna
 * Date        : 2020-09-30
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

/*
 * def get_ways_1(num_stairs):
 * 		ways = []
 * 		if num_stairs <= 0:
 * 			ways.append([])
 * 		else:
 * 			for i in range(1, 4):
 * 				if num_stairs >= i:
 * 					result = get_ways_1(num_stairs - i)
 * 					for j in range(len(result)):
 * 						result[j].insert(0, i)
 * 					ways += result
 * 		return ways
 *
 *
 * def get_ways_2(num_stairs):
 * 		if num_stairs <= 0:
 * 				return [[]]
 * 		ways = []
 * 		for i in range(1, 4):
 * 		    if num_stairs >= i:
 * 		    	result = get_ways_2(num_stairs - i)
 * 		        for j in range(len(result)):
 * 		        	result[j] = [i] + result[j]
 * 		        ways.extend(result)
 * 		return ways
 */

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
	vector<vector<int>> ways(0);
	vector<vector<int>> result(0);
	if(num_stairs <= 0) {
		return vector<vector<int>>(1);
	} else {
		for(int i = 1; i < 4; i++) {
			if(num_stairs >= i) {
				result = get_ways(num_stairs - i);
				for(vector<int> &vec : result) {
					vec.insert(vec.begin(),i);
				}
				ways.insert(ways.end(), result.begin(), result.end());
			}
		}
	}
	return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	int size = (int) ways.size();
	int tempSize = size;
	int digits = 1;
	while (tempSize >= 10) {
		tempSize /= 10;
		digits++;
	}

	for (int i = 0; i < size; i++) {
		cout << setw(digits) << i+1 << ". [";
		if (ways[i].size() == 1) {
			cout << ways[i][0] <<  "]" << endl;
		} else {
			cout << ways[i][0] << ",";
			for (int j = 1; j < (int) ways[i].size() - 1; j++) {
				cout << " " << ways[i][j] << ",";
			}
			cout << " " << ways[i][(int) ways[i].size() - 1] << "]" << endl;
		}
	}
}

int main(int argc, char * const argv[]) {
	int stairs;
	istringstream iss;

	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
		return 1;
	}

	iss.str(argv[1]);
	if (!(iss >> stairs)) {
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}

	if (stairs < 1) {
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}

	vector<vector<int>> ways = get_ways(stairs);

	if((int)ways.size() == 1) {
		cout << "1 way to climb " << stairs << " stair." << endl;
	} else {
		cout << (int)ways.size() << " ways to climb " << stairs << " stairs." << endl;
	}

	display_ways(ways);
}
