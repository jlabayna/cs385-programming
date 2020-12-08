/*******************************************************************************
 * Name    : shortestpaths.cpp
 * Author  : James Albert P. Labayna
 * Version : 1.0 (bad)
 * Date    : 2020-12-07
 * Description : Finds shortest paths
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <exception>
#include <cmath>
#include <iomanip>
#include <limits>		// Eh, decided not to use.
#include <climits>


struct edge {
	std::string start, end, weight;

	edge() :
			start(""), end(""), weight("") {
	}

	edge(std::string _start, std::string _end, std::string _weight) :
			start(_start), end(_end), weight(_weight) {
	}
};

std::string buildPath(long **i_matrix, int start, int end) {
	std::string output = "";
	if(i_matrix[start][end] == LONG_MAX) {
		output += (char)('A' + start);
		output += (char)('A' + end);
		return output;
	} else {
		// Obtain start -> intermediate & intermediate -> end
		// Remove duplicate intermediate.
		std::string left = buildPath(i_matrix,start,i_matrix[start][end]);
		std::string right = buildPath(i_matrix,i_matrix[start][end],end);
		output += left;
		output += right.substr(1);
		return output;
	}
}

// Is there even a faster way to do this?
int len(long x) {
	int length = 0;
	do {
		length++;
		x /= 10;
	} while (x > 0);
	return length;
}

void display_table(long** const matrix, const std::string &label,
		const bool use_letters, int num_vertices) {
	long INF = LONG_MAX;
	std::cout << label << std::endl;
	long max_val = 0;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			long cell = matrix[i][j];
			if (cell < INF && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}

	int max_cell_width = use_letters ? len(max_val) :
			len(std::max(static_cast<long>(num_vertices),max_val));
	std::cout << ' ';
	for (int j = 0; j < num_vertices; j++) {
		std::cout << std::setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	std::cout << std::endl;
	for(int i = 0; i < num_vertices; i++) {
		std::cout << static_cast<char>(i + 'A');
		for (int j = 0; j < num_vertices; j++) {
			std::cout << " " << std::setw(max_cell_width);
			if(matrix[i][j] == INF) {
				std::cout << "-";
			} else if (use_letters) {
				std::cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				std::cout << matrix[i][j];
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void deleteMatrix(long **matrix, int size) {
	for (int i = 0; i < size; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

int main(int argc, char *argv[]) {

	// Argument validation
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
		return 1;
	}

	// Declare input file stream
	std::ifstream ifs;

	ifs.open(argv[1]);
	// Check if file exists
	// Should be open if it doesn't exist.
	if (!ifs) {
		std::cerr << "Error: Cannot open file '" << argv[1] << "'."
				<< std::endl;
		return 1;
	}

	// Declare line counter
	int lineNum = 1;

	// Declare vertex count
	int numVertices;

	// Declare temp string for general use
	std::string temp;

	getline(ifs, temp);

//	// This is very dumb. But preserving just in case.
//	// ifs -> iss -> s -> int... all so I can preserve the original string.
//	// Maybe replace with a try block or whatever it'temp called.
//	if (!(iss >> numVertices) || (numVertices < 1 || numVertices > 26)) {
//		std::cerr << "Error: Invalid number of vertices '" << temp << "' on line "
//				<< lineNum << "." << std::endl;
//		return 1;
//	}
//
//	//std::cout << (char)(64 + numVertices) << std::endl;

	// Feels more elegant. Dunno if it's faster
	try {
		numVertices = std::stoi(temp);
		if (numVertices < 1 || numVertices > 26) {
			throw std::invalid_argument("Invalid number of vertices");
		}
	} catch (...) {
		std::cerr << "Error: Invalid number of vertices '" << temp
				<< "' on line " << lineNum << "." << std::endl;
		return 1;
	}


	// Declare edge and matrix
	edge e = edge();
	// Is it faster to set all to inf, then fix diagonal,
	// or set all to zero and initialize via if-statement.
	long **d_matrix = new long*[numVertices];
	for (int i = 0; i < numVertices; i++) {
		d_matrix[i] = new long[numVertices];
		for(int j = 0; j < numVertices; j++) {
			d_matrix[i][j] = LONG_MAX;
		}
		d_matrix[i][i] = 0;
	}

	std::istringstream iss;
	std::string line;
	int weight;

	/*
	 * Notes: Is there a better way than ifs -> string -> iss?
	 * - getline advances to nextline
	 * 		- Must preserve line
	 */


	// TODO Refactor this garbage into a nice try and catch blocks.
	while (std::getline(ifs, line)) {
		lineNum++;

		iss.clear();
		iss.str(line);
		// Place input into edge
		if (!(iss >> temp)) {
			std::cerr << "Error: Invalid edge data '" << line << "' on line "
					<< lineNum << "." << std::endl;
			deleteMatrix(d_matrix, numVertices);
			return 1;
		}
		// Shallow copies don't matter here.
		e.start = temp;
		if (!(iss >> temp)) {
			std::cerr << "Error: Invalid edge data '" << line << "' on line "
					<< lineNum << "." << std::endl;
			deleteMatrix(d_matrix, numVertices);
			return 1;
		}
		e.end = temp;
		if (!(iss >> temp)) {
			std::cerr << "Error: Invalid edge data '" << line << "' on line "
					<< lineNum << "." << std::endl;
			deleteMatrix(d_matrix, numVertices);
			return 1;
		}
		e.weight = temp;
		// Check for excess:
		if ((iss >> temp)) {
			std::cerr << "Error: Invalid edge data '" << line << "' on line "
					<< lineNum << "." << std::endl;
			deleteMatrix(d_matrix, numVertices);
			return 1;
		}

		// Check start
		if (e.start.length() > 1
				|| (e.start[0] < 'A' || e.start[0] > (64 + numVertices))) {
			std::cerr << "Error: Starting vertex '" << e.start << "' on line "
					<< lineNum << " is not among valid values A-"
					<< char(64 + numVertices) << "." << std::endl;
			deleteMatrix(d_matrix, numVertices);
			return 1;
		}

		// Check end
		if (e.end.length() > 1
				|| (e.end[0] < 'A' || e.end[0] > (64 + numVertices))) {
			std::cerr << "Error: Ending vertex '" << e.end << "' on line "
					<< lineNum << " is not among valid values A-"
					<< char(64 + numVertices) << "." << std::endl;
			deleteMatrix(d_matrix, numVertices);
			return 1;
		}

		// Check edge weight. This is disgusting. Duped strings.
		try {
			weight = std::stol(e.weight);
			if (weight <= 0) {
				throw std::invalid_argument("Invalid edge weight");
			}
		} catch (...) {
			std::cerr << "Error: Invalid edge weight '" << e.weight
					<< "' on line " << lineNum << "." << std::endl;
			deleteMatrix(d_matrix, numVertices);
			return 1;
		}

		// Place edge in matrix.
		d_matrix[(int)e.start[0]-'A'][(int) e.end[0]-'A'] = weight;
	}
	ifs.close();

	/*
	 * Is it better to make a struct with both distance and intermediary?
	 * Without struct, two matrices.... worse or no?
	 */

	long **i_matrix = new long*[numVertices];
	for (int i = 0; i < numVertices; i++) {
		i_matrix[i] = new long[numVertices];
		for (int j = 0; j < numVertices; j++) {
			i_matrix[i][j] = LONG_MAX;
		}
	}


	display_table(d_matrix, "Distance matrix:", false, numVertices);

	for(int i = 0; i < numVertices; i++) {
		for(int r = 0; r < numVertices; r++) {
			for(int c = 0; c < numVertices; c++) {
				if(i != r && i != c && r != c) {
					// Do not add infinities together
					if(d_matrix[i][c] != LONG_MAX && d_matrix[r][i] != LONG_MAX) {
						if(d_matrix[r][c] > d_matrix[r][i] + d_matrix[i][c]) {
							d_matrix[r][c] = d_matrix[r][i] + d_matrix[i][c];
							i_matrix[r][c] = i;
						}
					}
				}
			}
		}
	}

	display_table(d_matrix, "Path lengths:", false, numVertices);
	display_table(i_matrix, "Intermediate vertices:", true, numVertices);

	long distance;
	std::string path = "";


	for (int i = 0; i < numVertices; i++) {
		for (int j = 0; j < numVertices; j++) {
			distance = d_matrix[i][j];
			path = "";
			if (i != j && d_matrix[i][j] == LONG_MAX) {
				std::cout << (char) ('A' + i) << " -> " << (char) ('A' + j)
						<< ", distance: infinity, path: none" << std::endl;
			} else if (i == j) {
				path = (char) ('A' + i);
				std::cout << (char) ('A' + i) << " -> " << (char) ('A' + j)
						<< ", distance: " << distance << ", path: " << path
						<< std::endl;
			} else {
				path = buildPath(i_matrix, i, j);
				std::cout << (char) ('A' + i) << " -> " << (char) ('A' + j)
						<< ", distance: " << distance << ", path: " << path[0];
				for(unsigned int k = 1; k < path.length(); k++) {
					std::cout << " -> " << path[k];
				}
				std::cout << std::endl;
			}
		}

	}

	deleteMatrix(d_matrix,numVertices);
	deleteMatrix(i_matrix,numVertices);
	return 0;
}
