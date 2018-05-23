#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "spiral.hpp"
#include <iomanip>

using namespace std;

Cell* sendWalk(Cell * src, int iddst) {
	cout << "  Starting position id is " << src->getId() << ", intended destination " << iddst << endl;
	cout << "  Path : ";
	Cell * current = WalkByNext(src, iddst);	
	if (current) {
		cout << "  Position in dest is : " << current->getId() << endl;
		return current;
	} else {
		cout << "  Error ! WalkByNext() failed." << endl;
		return NULL;
	}
}

int main() {

	const int side = 5;

	Memory * t = new Memory(side);
	
	int idsrc = 1, iddst = 23;
	Cell * src, * current;
	// Walk through the spiral
	cout << "Walking through the spiral :" << endl;
	
	src = t->getCellById(idsrc);
	if (not src) {
		cout << "Error ! getCellById() failed." << endl;
		exit(-1);	
	}
	if (not t->getCellById(iddst)) {
		cout << "Error ! Intended destination " << iddst << " does not exist." << endl;
		exit(-1);
	}
	current = sendWalk(src, 23);
	if (not current) {
		cout << "Error ! sendWalk() failed." << endl;
		exit(-1);
	}
	
	cout << endl;

	src = t->getCellById(6);
	if (not src) {
		cout << "Error ! getCellById() failed." << endl;
		exit(-1);	
	}
	current = sendWalk(src, 10);
	if (not current) {
		cout << "Error ! sendWalk() failed." << endl;
		exit(-1);
	}
}