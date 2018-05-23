#include <iostream>
#include <math.h>
#include "spiral.hpp"
#include <iomanip>

using namespace std;

void displayDistance(int idsrc, int iddst, int side) {
	int dist = distanceBetween(idsrc, iddst, side);
	if (dist!=-1) {
		cout << "  From position id " << idsrc << " to position id " << iddst << ", distance is " << dist << endl;
	} else {
		cout << "  From position id " << idsrc << " to position id " << iddst << ", requested position(s) not found in the grid." << endl;
	} 
}

int main() {
	const int side = 5;

	Memory * t = new Memory(side);
	
	int idsrc, iddst;
	int dist;

	cout << "Distances on a " << side << "x" << side << " grid:" << endl;
	displayDistance(1, 23, side);
	displayDistance(2, 14, side);
	displayDistance(3, 21, side);
	displayDistance(5, 11, side);
	displayDistance(13, 9, side);
	displayDistance(15, 28, side);	
}