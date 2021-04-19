/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Maxwell Metzner
 * Version     : 1.0
 * Date        : 12/12/20
 * Description : Reads the graph representation from a file and computes the minimum set of roads on which to install power lines.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;
int num_streets;
vector<int> cap;

bool is_cycle (vector<vector<bool>> path, vector<int> visited, int from, int to, int parent = 0){
	vector<bool> recursiveQueue;
	visited.push_back(from);												//first mark the "from" intersection as being visited
	if (count(visited.cbegin(), visited.cend(), to) && to != parent) {		//if visited contains the intersection we are travelling to, a cycle has been detected
		return true;
	}
	if (to == parent) {
		return false;
	}
	for (size_t i = 0; i < path[to].size(); i++) {							//look through all paths from the intersection "to" to find the next paths
		if (path[to][i] == true) {
			recursiveQueue.push_back(is_cycle(path, visited, to, i, from));	//test if following a path creates a cycle recursively, adding result to a vector
			//to/i ordering may be source of error
		}
	}
	if (count(recursiveQueue.cbegin(), recursiveQueue.cend(), true)) {		//look through the vector, if any recursive calls returned true, then there is a cycle
		return true;
	} else {
		if (visited.size() > cap.size()) {
			cap = visited;
		}
		return false;
	}
}

int powerGrid(vector<string> input) {
	vector<vector<int>> streets;
	vector<vector<string>> names;												//A matrix containing all street names is initialized to ""
	vector<string> ready(num_streets+1, "");
	for (int i = 0; i < num_streets+1; i++) {
		names.push_back(ready);
	}
	vector<vector<bool>> path;													//A matrix containing the path of the power lines, initialized to false
	vector<bool> fill2(num_streets+1, false);
	for (int i = 0; i < num_streets+1; i++) {
		path.push_back(fill2);
	}
	vector<int> street;
	int num_start = 0;										//num_start assists substring
	int arg = 0;											//temp assists stoi
	int name = 0;											//arg tracks # of commas
	int lineNum = 1;										//name tracks location of street name
	for (string line : input) {
		lineNum++;
		arg = 0;
		for (size_t i = 0; i < line.length(); i++) {
			if (line.at(i) == ',') {
				arg++;
			}
		}
		if (arg < 3) {
			cerr << "Error: Invalid edge data '" << line << "' on line " << lineNum << "." << endl;
			return 1;
		}
		num_start = 0;
		arg = 0;
		name = 0;
		street.clear();
		for (size_t current = 0; current < line.length(); ++current) {
			if (arg == 3) {														//comma count == 3 since loop only collects (start,end,weight,)
				name = current;
				streets.push_back(street);
				break;
			}
			if (line.at(current) == ',') {
				string temp = line.substr(num_start, current-num_start);
				try {
					street.push_back(stoi(temp));								//street contains: start[0],end[1],weight[2]
				} catch(...) {

					if (arg == 0) {
						cerr << "Error: Starting vertex '" << temp <<"' on line " << lineNum << " is not among valid values 1-" << num_streets << "." << endl;
					} else if (arg == 1) {
						cerr << "Error: Ending vertex '" << temp <<"' on line " << lineNum << " is not among valid values 1-" << num_streets << "." << endl;
					} else {
						cerr << "Error: Invalid edge weight '" << temp << "' on line " << lineNum << "." << endl;
					}
					return 1;
				}
				if (street[0] < 1 || street[0] > num_streets) {
					cerr << "Error: Starting vertex '" << temp <<"' on line " << lineNum << " is not among valid values 1-" << num_streets << "." << endl;
					return 1;
				}
				if (street[0] > num_streets) {
					cerr << "Error: Ending vertex '" << temp <<"' on line " << lineNum << " is not among valid values 1-" << num_streets << "." << endl;
					return 1;
				}
				if (arg > 0) {
					if (street[1] < 1 || street[1] > num_streets) {
						cerr << "Error: Ending vertex '" << temp <<"' on line " << lineNum << " is not among valid values 1-" << num_streets << "." << endl;
						return 1;
					}
				}
				if (arg > 1) {
					if (street[2] < 1) {
						cerr << "Error: Invalid edge weight '" << temp <<"' on line " << lineNum << "." << endl;
						return 1;
					}
				}
				num_start = current+1;
				arg++;
			}
		}
		names[street[0]][street[1]] = line.substr(name, line.length()-name);	//street name from x to y is named inside matrix @ location [x][y]
	}
	if (lineNum < num_streets-1) {												//to have n vertices connect, you need at least n-1 edges
		cerr << "No solution." << endl;
		return 1;
	}

	for (size_t i = 0; i < streets.size()-1; i++) {								//prep streets vertex for kruskal by sorting (shortest to longest)
		for (size_t j = i; j < streets.size(); j++) {
			if (streets[i][2] > streets[j][2]) {
				swap(streets[i],streets[j]);
			}
		}
	}
	bool done;
	int edgeNumber = 1;
	vector<vector<int>> save = streets;											//store streets so that it can be used for the printing & streets can be modified freely
	path[streets[0][0]][streets[0][1]] = true;									//put in the initial edge to get started

	streets.erase(begin(streets));
	if (streets.size() != 0) {													//whenever a street is removed, check to make sure there are no streets left
		done = false;
	} else {
		done = true;
	}
	while (done == false) {														//done signifies streets vertex is empty
		path[streets[0][0]][streets[0][1]] = true;								//Insert the edge
		path[streets[0][1]][streets[0][0]] = true;								//since the graph is undirected, insert the reverse too
		vector<int> visited;
		if (is_cycle(path, visited, streets[0][0], streets[0][1]) == true || is_cycle(path, visited, streets[0][1], streets[0][0]) == true) {//REMOVE not sure if both are needed
			//If the graph now contains a cycle, remove it from path and streets
			path[streets[0][0]][streets[0][1]] = false;
			path[streets[0][1]][streets[0][0]] = false;
			streets.erase(begin(streets));
			if (streets.size() != 0) {
				done = false;
			} else {
				done = true;
			}
		} else {																//otherwise only remove it from streets
			streets.erase(begin(streets));
			edgeNumber++;
			if (streets.size() != 0) {
				done = false;
			} else {
				done = true;
			}
		}
	}
	if (edgeNumber < num_streets - 1) {
		cerr << "No solution." << endl;
		return 1;
	}
	vector<vector<int>> takenPath;
	string streetOutput;
	int totalLength = 0;
	for (size_t i = 0; i < path.size(); i++) {
		for (size_t j = 0; j < path[i].size(); j++) {
			if (path[i][j] == true) {
				for (size_t k = 0; k < save.size(); k++) {
					if (save[k][0] == (int)i && save[k][1] == (int)j) {
						totalLength += save[k][2];
						takenPath.push_back(save[k]);
					}
				}
			}
		}
	}
	vector<int> intersections;
	for (size_t i = 0; i < takenPath.size(); i++) {										//make sure there are numbers 1 up to num_streets in either [0] or [1] of each taken path
		intersections.push_back(takenPath[i][0]);
		intersections.push_back(takenPath[i][1]);

	}
	for (size_t i = 1; i < (size_t)(num_streets+1); i++) {
		if (count(intersections.cbegin(),intersections.cend(), i) == 0) {			//also make sure the graph is connected
			cerr << "No solution." << endl;
			return 1;
		}
	}

	for (size_t i = 0; i < takenPath.size()-1; i++) {									//put streets in alphabetical order in takenPath
		for (size_t j = i; j < takenPath.size(); j++) {
			if (names[takenPath[i][0]][takenPath[i][1]] > names[takenPath[j][0]][takenPath[j][1]]) {
				swap(takenPath[i],takenPath[j]);
			}
		}
	}
	cout << "Total wire length (meters): " << totalLength << endl;
	for (vector<int> street : takenPath) {											//print name and weights of sorted path taken
		cout << names[street[0]][street[1]] << " [" << street[2] << "]" << endl;
	}
	return 0;
}
int main(int argc, char *argv[]) {
	if (argc != 2) {											//check input txt file for errors (given from Borowski)
		cerr << "Usage: " << argv[0] << " <input file>" << endl;
		return 1;
	}
	ifstream input_file(argv[1]);
	if (!input_file) {
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		return 1;
	}
	input_file.exceptions(ifstream::badbit);
	vector<string> input;
	string line;

	try {
		unsigned int line_number = 1;
		getline(input_file, line);
		stringstream sst(line);
		if(!(sst >> num_streets) ){
			cerr << "Error: Invalid number of vertices '" << line <<"' on line 1." << endl;
			return 1;
		}
		if (num_streets == 1) {
			cerr << "No solution." << endl;
						return 1;
		}
		if (num_streets < 1 || num_streets > 1000) {
			cerr << "Error: Invalid number of vertices '" << num_streets <<"' on line 1." << endl;
			return 1;
		}
		++line_number;
		while (getline(input_file, line)) {
			stringstream sst(line);
			input.push_back(line);
			++line_number;
		}

		input_file.close();
	} catch (const ifstream::failure &f) {
		cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
		return 1;
	}
	return powerGrid(input) == 1? 1 : 0;										//return false if error occurs in powerGrid
}
