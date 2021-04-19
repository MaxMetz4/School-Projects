/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Maxwell Metzner and Savnick Patel
 * Date        : October 18, 2020
 * Description : Water jug puzzle solved using BST
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>

using namespace std;
int capA_;
int capB_;
int capC_;
int goalA_;
int goalB_;
int goalC_;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *current;

    State(int _a, int _b, int _c, string _directions) :
        a{_a}, b{_b}, c{_c}, directions{_directions}, current{nullptr} { }

    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

bool canPour(State *current, int instruction) {

//  instruction represents pouring operation:
//	1 == "CtoA"
//	2 == "BtoA"
//	3 == "CtoB"
//	4 == "AtoB"
//	5 == "BtoC"
//	6 == "AtoC"

switch(instruction) {
   	case 1 :
		if (current->a == capA_ || current->c == 0) {//Error out if recipient is full or donor is empty
			return false;
		} else {
			return true;
		}
		break;

	case 2 :
		if (current->a == capA_ || current->b == 0) {//Error out if recipient is full or donor is empty
			return false;
		} else {
			return true;
		}
		break;

	case 3 :
		if (current->b == capB_ || current->c == 0) {//Error out if recipient is full or donor is empty
			return false;
		} else {
			return true;
		}
		break;

	case 4 :
		if (current->b == capB_ || current->a == 0) {//Error out if recipient is full or donor is empty
			return false;
		} else {
			return true;
		}
		break;

	case 5 :
		if (current->c == capC_ || current->b == 0) {//Error out if recipient is full or donor is empty
			return false;
		} else {
			return true;
		}
		break;

	case 6 :
		if (current->c == capC_ || current->a == 0) {//Error out if recipient is full or donor is empty
			return false;
		} else {
			return true;
		}
		break;

   	default://In the case that an incorrect instruction is given, return 0
   			return false;
   	}
}

State pour(State *current, int instruction) {//returns current modified in the specified way

//  instruction represents pouring operation:
//	1 == "CtoA"
//	2 == "BtoA"
//	3 == "CtoB"
//	4 == "AtoB"
//	5 == "BtoC"
//	6 == "AtoC"

switch(instruction) {
	case 1 :
		if ((capA_ - current->a) < (current->c)) {//If the recipient cannot fit a full pour
			current->directions += "Pour " + to_string(capA_ - current->a) + " gallon";
			if(capA_ - current->a != 1){ current->directions += "s"; }
			current->directions += " from C to A. ";
			current->c = current->c - (capA_ - current->a);
			current->a = capA_;
			current->directions += current->to_string();
			current->directions += "\n";
		} else {
			current->directions += "Pour " + to_string(current->c) + " gallon";
			if(current->c != 1){ current->directions += "s"; }
			current->directions += " from C to A. ";
			current->a = current->a + current->c;
			current->c = 0;
			current->directions += current->to_string();
			current->directions += "\n";
		}
		break;

	case 2 :
		if ((capA_ - current->a) < (current->b)) {//If the recipient cannot fit a full pour
			current->directions += "Pour " + to_string(capA_ - current->a) + " gallon";
			if(capA_ - current->a != 1){ current->directions += "s"; }
			current->directions += " from B to A. ";
			current->b = current->b - (capA_ - current->a);
			current->a = capA_;
			current->directions += current->to_string();
			current->directions += "\n";
		} else {
			current->directions += "Pour " + to_string(current->b) + " gallon";
			if(current->b != 1){ current->directions += "s"; }
			current->directions += " from B to A. ";
			current->a = current->a + current->b;
			current->b = 0;
			current->directions += current->to_string();
			current->directions += "\n";
		}
		break;

	case 3 :
		if ((capB_ - current->b) < (current->c)) {//If the recipient cannot fit a full pour
			current->directions += "Pour " + to_string(capB_ - current->b) + " gallon";
			if(capB_ - current->b != 1){ current->directions += "s"; }
			current->directions += " from C to B. ";
			current->c = current->c - (capB_ - current->b);
			current->b = capB_;
			current->directions += current->to_string();
			current->directions += "\n";
		} else {
			current->directions += "Pour " + to_string(current->c) + " gallon";
			if(current->c != 1){ current->directions += "s"; }
			current->directions += " from C to B. ";
			current->b = current->b + current->c;
			current->c = 0;
			current->directions += current->to_string();
			current->directions += "\n";
		}
		break;

   	case 4 :
		if ((capB_ - current->b) < (current->a)) {//If the recipient cannot fit a full pour
			current->directions += "Pour " + to_string(capB_ - current->b) + " gallon";
			if(capB_ - current->b != 1){ current->directions += "s"; }
			current->directions += " from A to B. ";
			current->a = current->a - (capB_ - current->b);
			current->b = capB_;
			current->directions += current->to_string();
			current->directions += "\n";
		} else {
			current->directions += "Pour " + to_string(current->a) + " gallon";
			if(current->a != 1){ current->directions += "s"; }
			current->directions += " from A to B. ";
			current->b = current->b + current->a;
			current->a = 0;
			current->directions += current->to_string();
			current->directions += "\n";
		}
		break;

   	case 5 :
		if ((capC_ - current->c) < (current->b)) {//If the recipient cannot fit a full pour
			current->directions += "Pour " + to_string(capC_ - current->c) + " gallon";
			if(capC_ - current->c != 1){ current->directions += "s"; }
			current->directions += " from B to C. ";
			current->b = current->b - (capC_ - current->c);
			current->c = capC_;
			current->directions += current->to_string();
			current->directions += "\n";
		} else {
			current->directions += "Pour " + to_string(current->b) + " gallon";
			if(current->b != 1){ current->directions += "s"; }
			current->directions += " from B to C. ";
			current->c = current->c + current->b;
			current->b = 0;
			current->directions += current->to_string();
			current->directions += "\n";
		}
		break;

   	case 6 :
		if ((capC_ - current->c) < (current->a)) {//If the recipient cannot fit a full pour
			current->directions += "Pour " + to_string(capC_ - current->c) + " gallon";
			if(capC_ - current->c != 1){ current->directions += "s"; }
			current->directions += " from A to C. ";
			current->a = current->a - (capC_ - current->c);
			current->c = capC_;
			current->directions += current->to_string();
			current->directions += "\n";
		} else {
			current->directions += "Pour " + to_string(current->a) + " gallon";
			if(current->a != 1){ current->directions += "s"; }
			current->directions += " from A to C. ";
			current->c = current->c + current->a;
			current->a = 0;
			current->directions += current->to_string();
			current->directions += "\n";
		}
		break;
   	default://In the case that an incorrect instruction is given, return 0
		cerr << "Unexpected error, instruction not valid in pour function" << endl;
		return *current;
   	}
   	return *current;
}

vector<State *> q;
void createTree(int a, int b, int c) {
	bool done = false;
	vector<State *> objectList;
	State *z = new State(a, b, c, "Initial state. ");
	z->directions += z->to_string();
	z->directions += "\n";
	q.push_back(z);

	vector<vector<int>> visited;
	for (int i = 0; i < capA_+1; i++) {
		vector<int> v1;
		for (int j = 0; j < capB_+1; j++) {
			v1.push_back(-1);
		}
		visited.push_back(v1);
	}

	while (q.empty() == false) {								    		//PSEUDOCODE: while (queue not empty)
		State *current = q.front();													//current <- front of queue &
		q.erase(q.cbegin());																	//pop from queue
		if (current->a == goalA_ && current->b == goalB_ && current->c == goalC_) {	//if current equals goal state
			//Print function here													  return the backtracked solution
			cout << current->directions << endl;
			done = true;
			break;
		}
		if (visited[current->a][current->b] == current->c) {						//if current has already been seen
			continue;
		} else {																	//continue
			visited[current->a][current->b] = current->c;							//mark current as having been visited

			State *s = new State(current->a, current->b, current->c, current->directions);	//create a new State
			if (canPour(s, 1) == true) {													//check if a valid State can be created
				*s = pour(s, 1);															//use pour function to rewrite the state
				q.push_back(s);																	//add to the queue
				objectList.insert(objectList.cbegin(), s);									//add to the objectList
			} else {
				delete s;																	//if pour is not possible, get rid of object
			}

			State *p = new State(current->a, current->b, current->c, current->directions);
			if (canPour(p, 2) == true) {
				*p = pour(p, 2);
				q.push_back(p);
				objectList.insert(objectList.cbegin(), p);
			} else {
				delete p;
			}

			State *e = new State(current->a, current->b, current->c, current->directions);
			if (canPour(e, 3) == true) {
				*e = pour(e, 3);
				q.push_back(e);
				objectList.insert(objectList.cbegin(), e);
			} else {
				delete e;
			}

			State *r = new State(current->a, current->b, current->c, current->directions);
			if (canPour(r, 4) == true) {
				*r = pour(r, 4);
				q.push_back(r);
				objectList.insert(objectList.cbegin(), r);
			} else {
				delete r;
			}

			State *t = new State(current->a, current->b, current->c, current->directions);
			if (canPour(t, 5) == true) {
				*t = pour(t, 5);
				q.push_back(t);
				objectList.insert(objectList.cbegin(), t);
			} else {
				delete t;
			}

			State *n = new State(current->a, current->b, current->c, current->directions);
			if (canPour(n, 6) == true) {
				*n = pour(n, 6);
				q.push_back(n);
				objectList.insert(objectList.cbegin(), n);
			} else {
				delete n;
			}
		}
	}
	if(!done){
		//Print no solution statement here
		cout << "No solution." << endl;
	}
	for(auto obj: objectList){
		delete obj;
	}
	delete z;
}


int main(int argc, char * const argv[]) {
	istringstream iss;
	int capA;
	int capB;
	int capC;
	int goalA;
	int goalB;
	int goalC;

	//Case 0: too many or too little arguments
	if(argc != 7){
		cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>";

		return 1;
	}

	//Case 1: non integer inputs
	iss.str(argv[1]);
	if ( !(iss >> capA) ) {
		cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
		return 1;
	}
	iss.clear();

	iss.str(argv[2]);
	if ( !(iss >> capB) ) {
		cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
		return 1;
	}
	iss.clear();

	iss.str(argv[3]);
	if ( !(iss >> capC) ) {
		cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
		return 1;
	}
	iss.clear();

	iss.str(argv[4]);
	if ( !(iss >> goalA) ) {
		cerr << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
		return 1;
	}
	iss.clear();

	iss.str(argv[5]);
	if ( !(iss >> goalB) ) {
		cerr << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
		return 1;
	}
	iss.clear();

	iss.str(argv[6]);
	if ( !(iss >> goalC) ) {
		cerr << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
		return 1;
	}
	iss.clear();

	//Case 2: Negative inputs
	if(capA < 0){
		cerr << "Error: Invalid capacity '" << capA << "' for jug A." << endl;
		return 1;
	}
	if(capB < 0){
		cerr << "Error: Invalid capacity '" << capB << "' for jug B." << endl;
		return 1;
	}
	if(capC < 1){ //capC can't be 0 because it shows the total amount of gallons we have
		cerr << "Error: Invalid capacity '" << capC << "' for jug C." << endl;
		return 1;
	}
	if(goalA < 0){
		cerr << "Error: Invalid goal '" << goalA << "' for jug A." << endl;
		return 1;
	}
	if(goalB < 0){
		cerr << "Error: Invalid goal '" << goalB << "' for jug B." << endl;
		return 1;
	}
	if(goalC < 0){
		cerr << "Error: Invalid goal '" << goalC << "' for jug C." << endl;
		return 1;
	}

	//Case 3: Goal exceeding capacity
	if(capA < goalA){
		cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
		return 1;
	}
	if(capB < goalB){
		cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
		return 1;
	}
	if(capC < goalC){
		cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
		return 1;
	}

	//Case 4: The gallons in goal exceed capC
	if(goalA + goalB + goalC != capC){
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}

	//Set global variables to command line arguments
	capA_ = capA;
	capB_ = capB;
	capC_ = capC;
	goalA_ = goalA;
	goalB_ = goalB;
	goalC_ = goalC;

    createTree(0,0,capC);//the main branching method
    return 0;
}
