/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Maxwell Metzner
 * Version : 1.0
 * Date    : Sep 2, 2020
 * Description : Computes the square root of a double using Newton's method.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std;

double sqrt(double num, double epsilon = 1e-7) {
	double nextGuess, lastGuess, temp;
	nextGuess = 0;
	lastGuess = num;
	temp = num;
	 if (num < 0) {
			return numeric_limits<double>::quiet_NaN();
	}
	if (num == 1) {
		return 1;
	}
	if (num == 0) {
		return 0;
	}
	while (abs(nextGuess - lastGuess) > epsilon) {	//loops according to formula, checking against epsilon
		lastGuess = temp;
		nextGuess = (lastGuess + num / lastGuess) / 2;
		temp = nextGuess;	//temp represents temporary storage for last guess for next loop
	}
	return nextGuess;
}

int main(int argc, char *argv[]) {
	istringstream iss;

	double num, epsilon;

	if (argc > 3 || argc < 2) {	//2 inputs with just number and 3 with provided epsilon
		cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
		return 1;
	}
	if (argc == 2) {	//epsilon case
			epsilon = 1e-7;
		}

	iss.str(argv[1]);	//makes sure str -> double goes smoothly
	if ( !(iss >> num) ) {
		cerr << "Error: Value argument must be a double." << endl;
		return 1;
	}
	iss.clear();
	if (argc == 3) { //makes sure str -> double goes smoothly (if epsilon provided)
		iss.str(argv[2]);
				if ( !(iss >> epsilon) ) {
					cerr << "Error: Epsilon argument must be a positive double." << endl;
					return 1;
				}
	}

	if (epsilon <= 0) {
		cerr << "Error: Epsilon argument must be a positive double." << endl;
		return 1;
	}

	cout << fixed << setprecision(8) << sqrt(num, epsilon) << endl;

	return 0;
}
