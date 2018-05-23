#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "spiral.hpp"
#include <iomanip>

using namespace std;

int main() {

	const int side = 5;

	Memory * t = new Memory(side);
	
	Cell * src, * current;

	// Shortest with Move() methods
	cout << "Walk within shortest path :" << endl;
	src = t->getCellById(2);
	if (not src) {
		cout << "Error ! getCellById() failed." << endl;
		exit(-1);	
	}

	Cell* dest = t->getCellById(14);
	if (not dest) {
		cout << "Error ! getCellById() failed." << endl;
		exit(-1);	
	}

	current = src;
	int dist = 0;
	cout << "  Starting position id is " << src->getId() << endl;
	cout << "  Path : ";
	Cell* endpath = WalkTo(current, dist, dest);
	if (not endpath) {
		cout << endl << "  Error ! WalkTo() failed." << endl;
		exit(-1);
	}
	cout << "  Arrived to " << endpath->getId() << endl;
	cout << "  Total distance: " << dist << endl;
}