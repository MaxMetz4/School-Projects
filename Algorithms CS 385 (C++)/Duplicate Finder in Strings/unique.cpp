/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Maxwell Metzner
 * Date        : 9/20/20
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
	for (char c : s) {
		if (islower(c) == false) {
			return false;
		}
	}
	return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.

	unsigned int vector = 0; //Initialize list of letters already seen to none
	unsigned int setter; //Used to input letters into vector and check for repeated characters

	for (char c : s) {
		setter = 1 << (c - 'a'); 			//Setter is 1 shifted over by this many bits
		if ((vector & setter) != 0) {			//if there is a match in one of the bits, duplicate is found
			return false;
		} else {							// otherwise add the char representative to the vector
			vector = vector | setter;
		}
	}

	return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
	if (argv[1] == NULL || argv[2] != NULL) {
		cerr << "Usage: ./unique <string>" << endl;
		return 1;
	}
	if (is_all_lowercase(argv[1]) == false) {
		cerr << "Error: String must contain only lowercase letters." << endl;
		return 1;
	}

	if (all_unique_letters(argv[1]) == true) {
		cout << "All letters are unique." << endl;
	} else {
		cout << "Duplicate letters found." << endl;
	}
	return 0;
}
