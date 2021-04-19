/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Maxwell Metzner
 * Date        : September 19, 2020
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
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
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.

	const int max_prime_width = num_digits(max_prime_),
			primes_per_row = 80 / (max_prime_width + 1);
	bool nextLine = false;
	bool oneLiner = false;

	if (num_primes_ < primes_per_row) {
		oneLiner = true;
	}

	int indent = 0;
	int current_prime = 0; //keeps track of how many primes have been listed in a line

	for (int i = 1; i != limit_ + 1; i++) {
		if (current_prime % primes_per_row == 0 && nextLine == false) { //if the row is out of room, go to the next line
			cout << endl;
			indent = 1;
			nextLine = true;
		}

		if (is_prime_[i] == true) {
			if (oneLiner == true) {
				if (indent == true) {

				} else {
					cout << " ";
				}
			} else {
				for (int j = num_digits(i) + indent; j < max_prime_width + 1; j++) {
								cout << " "; //Sets the number of spaces preceding the prime to keep formatting
							}
			}
			current_prime++;
			nextLine = false;
			indent = 0;
			cout << i;
		}
	}
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found

	int tempCounter = 0;

	for (int i = 0; i != limit_ + 1; i++) { //All values are considered potentially prime
			if (is_prime_[i] == true) {
				tempCounter++;
			}
		}
    return tempCounter;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm

	for (int k = 0; k != limit_ + 1; k++) { //All values are considered potentially prime
		is_prime_[k] = true;
	}

	is_prime_[0] = false;// 0 and 1 are not counted as prime
	is_prime_[1] = false;

	for (int i = 2; i <= sqrt(limit_); i++) { //cycle through list of numbers up to sqrt of limit
		if (is_prime_[i] == true) { //if the number is prime, mark every multiple of it an non prime
			for (int j = 2; j <= limit_; j++) {
				is_prime_[i*j] = false;
			}
		}
	}
	for (int i = limit_; max_prime_ == 0; i--) { //Goes through primes list backwards checking for max prime
		if (is_prime_[i] == true) {
			max_prime_ = i;
		}
	}
	num_primes_ = count_num_primes();
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.

	int numDigits = 0;
	while (num != 0) { //if num < 10 then division truncates value to 0
		num = num / 10;
		numDigits++;
	}
    return numDigits;
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

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve* x = new PrimesSieve(limit);
    cout << endl;
    cout << "Number of primes found: " << x->num_primes() << endl;
    cout << "Primes up to " << limit << ":";
    x->display_primes();
    return 0;
}
