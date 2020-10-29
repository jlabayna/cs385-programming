/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : James Labayna
 * Date        : 2020-09-12
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

// TODO Read the style guide.
// TODO Make code more semantically intuitive.

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
        	for (int i = 0; i <= limit; i++){
        		is_prime_[i] = true;
        	}
    sieve();
}

void PrimesSieve::display_primes() const {
	// Given width and primes_per_row calculation
	const int max_prime_width = num_digits(max_prime_),
			  primes_per_row = 80 / (max_prime_width + 1);

	int current_prime_count = 0;	// Current number of primes printed.
	int current_num = 2;			// Current number to test for primality.

	// Newline (requirements doc) before printing number of primes and limit.
	cout << endl;
	cout << "Number of primes found: " << num_primes_ << endl;
	cout << "Primes up to " << limit_ << ":" << endl;

	if(num_primes_ <= primes_per_row) {
		// Case 1: number of primes to print is less than max primes per row.

		/*
		 * Print the first prime number.
		 * This makes formatting easier because I don't need to worry about a space at the end of the line.
		 * In case you're wondering why I use a while loop, I'm assuming we don't know 2 is prime.
		 * This is a bad idea in my book. I might change it later.
		 */
		while (!is_prime_[current_num]) {
			current_num++;
		}
		cout << current_num;
		// Don't forget to increment the prime_count! We printed a number!
		current_prime_count++;
		// Also don't forget to increment the current_number, or we reprint 2.
		current_num++;
		/*
		 * Used a while loop because I'm not sure exactly how long the printing process takes.
		 * It's somewhere between num_primes_ and limit_
		 * By the way, we go until right before num_primes_ == current_prime_count
		 * because current_prime_count (or printed primes) reaches num_primes_ within the loop.
		 */
		while (current_prime_count < num_primes_) {
			if (is_prime_[current_num]) {
				/*
				 * Print a space before current_num to prevent having to check if we are going to print
				 * the last prime next.
				 * The check is necessary because we don't want to print an extra space at the end.
				 * I feel that printing 2 at the start is simpler.
				 */
				cout << " " << current_num;
				current_prime_count++;
			}
			current_num++;
		}
		// This endl is necessary to prevent the command line prompt from spawning right after the last prime.
		cout << endl;
	} else {
		int current_row_size = 0;	// The current number of primes printed in the current row.
		while (current_prime_count < num_primes_) {

			// This loop finds the first prime of a row.
			while (!is_prime_[current_num]) {
				current_num++;
			}
			// Print the current_num as a string the same size as the max_prime_width.
			cout << setw(max_prime_width) << current_num;

			/*
			 * Don't forget to increment the:
			 * current_num to check for primality,
			 * the current number of printed primes,
			 * and the current number of primes printed in the current row! We printed the first prime of a row!
			 */
			current_num++;
			current_prime_count++;
			current_row_size++;

			/*
			 * This inner loop prints every remaining prime in the current row (after the first prime).
			 * The loop ends when the prime count reaches the total number of primes to prevent printing
			 * numbers not checked for primality. Although these numbers are not in the is_prime_ array,
			 * current_num may be incremented above limit_ to reach a multiple of primes_per_row.
			 */
			while(current_row_size < primes_per_row && current_prime_count < num_primes_) {
				if (is_prime_[current_num]) {
					/*
					 * Instead of printing a space, why not set the field width to max_prime_width plus 1?
					 * This adds a space to the left of a number and seems effectively identical to printing " "
					 */
					cout << setw(max_prime_width + 1) << current_num;
					current_prime_count++;
					current_row_size++;
				}
				current_num++;
			}
			current_row_size = 0;
			// End lines after printing all primes in a given row. Also prevents the command line spawnning issue.
			cout << endl;
		}
	}
}

int PrimesSieve::count_num_primes() const {
	int prime_count = 0;

	/*
	 * For loop used because I don't know a better estimate for the max number of primes other than limit_
	 */
	// TODO Find the upper limit of prime numbers in a given range [2,limit_]
	for(int i = 2; i <= limit_; i++) {
		if(is_prime_[i]) {
			prime_count++;
		}
	}
    return prime_count;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm

	for(int i = 2; i <= sqrt(limit_); i++) {
		if(is_prime_[i]) {
			for(int j = pow(i,2); j <= limit_; j+= i) {
				is_prime_[j] = false;
			}
		}
	}

	// Here, I set other important variables, like the number of primes and the max_prime_

	num_primes_ = count_num_primes();
	int current_prime_count = 0;
	int current_num = 0;

	/*
	 * Uhg, I feel really bad for doing this.
	 * I use a duplicate of the count_num_primes() code to find the last prime, since the template
	 * suggests that that method shouldn't modify instance variables. (and semantically, it seems
	 * like it should only find the number of primes, not the max prime as well).
	 */
	while(current_prime_count < num_primes_) {
		if(is_prime_[current_num]) {
			current_prime_count++;
		}
		current_num++;
	}
	max_prime_ = current_num;
}

int PrimesSieve::num_digits(int num) {
	/* Just divide a number until it has less than 2 digits.
	 * Equivalently, divide until the number is less than 10.
	 * Total digits starts at 1, since each possible division increases the possible order of magnitude.
	 */
	int digits = 1;
	while(num >= 10) {
		num /= 10;
		digits++;
	}
    return digits;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }

    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // Code that uses your class to produce the desired output.
    PrimesSieve *sieve = new PrimesSieve(limit);
    sieve -> display_primes();
    delete sieve;
    return 0;
}
