#include <iostream>
#include <math.h>
#include "spiral.hpp"
#include <iomanip>

using namespace std;

int main() {

	const int side = 8;

	Memory * t = new Memory(side);
	
	// Fill with adjacent values
	int thres = 125000;
	cout << "Fill the spiral with adjacent values : " << endl;
	long ret = FillWithSumOfAdjacent(t, t->getCellById(1), thres);
	cout << "  First value larger than "<<thres<<" : " << ret << " (hex " << hex << ret << ")" << endl;
	
	//t->printGrid();
	
}