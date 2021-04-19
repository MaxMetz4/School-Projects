/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Maxwell Metzner and Savnick Patel
 * Version     : 1.0
 * Date        : 12/6/20
 * Description : Displays the matrix on the screen formatted as a table.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/


#include <iostream>
#include <sstream>
#include <fstream>	//I'm using this to read .txt files
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip> //for setw

using namespace std;
int num_vertices, INF = -1;	//INF needs replacement

int len(int x) {	//gives length of an int
	string temp = to_string(x);
	return temp.length();
}
int len(long x) {	//gives length of a long (overloaded)
	string temp = to_string(x);
	return temp.length();
}

void display_table(vector<vector<long>> const matrix, const string &label, const bool use_letters = false) {	//given in assignment sheet
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			long cell = matrix.at(i).at(j);
			if (cell != INF && cell > max_val) {
				max_val = matrix.at(i).at(j);
			}
		}
	}
	int max_cell_width = use_letters ? len(max_val) : len(max(static_cast<long>(num_vertices), max_val));
	cout << ' ';
	for(int j = 0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for(int i = 0; i < num_vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for(int j = 0; j < num_vertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix.at(i).at(j) == INF) {
				cout << "-";
			} else if   (use_letters) {
				cout << static_cast<char>(matrix.at(i).at(j) + 'A');
			} else {
				cout << matrix.at(i).at(j);
			}
		}
		cout << endl;
	}
	cout << endl;
}

string print_path(vector<vector<long>> matrix, int first, int second){
	if(matrix[first][second] == INF){
		return string(1,static_cast<char>(second + 'A'));
	} else {
		return print_path(matrix, first, matrix[first][second]) + " -> " + print_path(matrix, matrix[first][second], second);
	}

}

string check_length_one(string line){
	for (string::size_type i = 0; i < line.size(); i++) {
		if(line[i] == ' '){
			return line.substr(0,i);
		}
	}
	return " ";
}

string check_length_two(string line){
	for (string::size_type i = 2; i < line.size(); i++) {
		if(line[i] == ' '){
			return line.substr(2,i-2);
		}
	}
	return " ";
}

int shortestPath(vector<string> instructions) {
	vector<vector<long>> distance_matrix, path_matrix, intermediate_matrix;	//Initialize Matrix, indexes represent letter with A=0 to Z=25

	vector<long> temp(num_vertices, -1);				//-1 represents INF
	for (int i = 0; i < num_vertices; i++) {			//all spaces of matrix are initialized to INF/-1
		distance_matrix.push_back(temp);
		path_matrix.push_back(temp);
		intermediate_matrix.push_back(temp);
	}


	int line_num = 2;									//used to represent line number of txt in error
	for (string x : instructions) {						//this fills out the distances matrix, x is in the format 'A B 123'
		//checks for correct number of inputs
		if (x.length() < 4) {
			cerr << "Error: Invalid edge data '" << x << "' on line " << line_num << "." << endl;
			return 1;
		}
		//checks that the vertices and distance are proper
		if(x.at(1) != ' '){
			cerr << "Error: Starting vertex '" << check_length_one(x) << "' on line " << line_num << " is not among valid values " << "A-"
					<< (char)(65 + num_vertices - 1) << "." << endl;
			return 1;
		}
		if(x.at(3) != ' '){
			cerr << "Error: Ending vertex '" << check_length_two(x) << "' on line " << line_num << " is not among valid values " << "A-"
					<< (char)(65 + num_vertices - 1) << "." << endl;
			return 1;
		}
		long dist;
		stringstream sst(x.substr(4,x.length()));
		if(!(sst >> dist) ){
			cerr << "Error: Invalid edge weight '" << x.substr(4,x.length()) << "' on line " << line_num << "." << endl;
			return 1;
		}

		char a = x.at(0);
		char b = x.at(2);
		if (x.at(0) > 65 + num_vertices || x.at(0) < 65) {
			cerr << "Error: Starting vertex '" << x.at(0) << "' on line " << line_num << " is not among valid values " << "A-"
					<< (char)(65 + num_vertices - 1) << "." << endl;
			return 1;
		}
		if (x.at(2) > 65 + num_vertices || x.at(2) < 65) {
			cerr << "Error: Ending vertex '" << x.at(2) << "' on line " << line_num << " is not among valid values " << "A-"
					<< (char)(65 + num_vertices - 1) << "." << endl;
			return 1;
		}

		if (a < 65 || a > 90 || b < 65 || a > 90) {
			cerr << "Error: Invalid edge data '" << a << " " << b << "'on line " << line_num << "." << endl;
			return 1;
		}
		if (dist <= 0) {
			cerr << "Error: Invalid edge weight '" << dist << "' on line " << line_num << "." << endl;
			return 1;
		}


		distance_matrix[a-65][b-65] = dist;				//A is 65 in ASCII, the matrix inserts at correct index by subtracting this
		++line_num;
	}


	for (int x = 0; x < num_vertices; ++x) {			//set the diagonal of paths to 0
		for(int y = 0; y < num_vertices; ++y){
			if(x == y){
				path_matrix[x][y] = 0;
				distance_matrix[x][y] = 0;
			} else {
				path_matrix[x][y] = distance_matrix[x][y];
			}
		}
	}

	for(int k=0; k<num_vertices; ++k){
		for(int j=0; j<num_vertices; ++j){
			for(int i=0; i<num_vertices; ++i){
				if(path_matrix[i][k] != INF && path_matrix[k][j] != INF) {
					long value = path_matrix[i][k]+path_matrix[k][j];
					if(path_matrix[i][j] == -1 || path_matrix[i][j] > value) {
						path_matrix[i][j] = value;
						intermediate_matrix[i][j] = k;
					}
				}
			}
		}
	}
	//print matrices
	display_table(distance_matrix, "Distance matrix:", false);
	display_table(path_matrix, "Path lengths:", false);
	display_table(intermediate_matrix, "Intermediate vertices:", true);

	//print all edges
	for (int x = 0; x < num_vertices; ++x) {
		for(int y=0; y < num_vertices; ++y){
			if(path_matrix[x][y] == -1){
				cout << static_cast<char>(x + 'A') << " -> " << static_cast<char>(y + 'A') << ", distance: infinity, path: none" << endl;
			} else {
				cout << static_cast<char>(x + 'A') << " -> " << static_cast<char>(y + 'A') << ", distance: " << path_matrix[x][y];
				cout << ", path: ";
				if(x == y){
					cout << string(1,static_cast<char>(x + 'A')) << endl;
				} else {
					cout << string(1,static_cast<char>(x + 'A')) << " -> ";
					cout << print_path(intermediate_matrix, x, y) << endl;
				}
			}
		}
	}
	return 0;
}


int main(int argc, char *argv[]) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <filename>" << endl;
		return 1;
	}
	ifstream input_file(argv[1]);
	if (!input_file) {
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		return 1;
	}
	input_file.exceptions(ifstream::badbit);
	vector<string> instructions;
	string line;

	try {
		unsigned int line_number = 1;
		getline(input_file, line);
		stringstream sst(line);
		if(!(sst >> num_vertices) ){
			cerr << "Error: Invalid number of vertices '" << line <<"' on line 1." << endl;
			return 1;
		}
		if (num_vertices <= 0 || num_vertices > 26) {
			cerr << "Error: Invalid number of vertices '" << num_vertices <<"' on line 1." << endl;
			return 1;
		}
		++line_number;
		while (getline(input_file, line)) {
			stringstream sst(line);
			instructions.push_back(line);
			++line_number;
		}

		input_file.close();
	} catch (const ifstream::failure &f) {
		cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
		return 1;
	}

	int result = shortestPath(instructions);
	if (result == 1) {	//shortestPath returns 1 with error
		return 1;
	}
	return 0;
}
