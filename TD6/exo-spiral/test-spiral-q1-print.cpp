#include <iostream>
#include <math.h>
#include "spiral.hpp"
#include <iomanip>

int main() {

	const int side = 5;

	Memory * t = new Memory(side);
	t->getCellById(2)->set(123467);
	t->getCellById(7)->set(5678654);
	t->getCellById(13)->set(987654);
	t->getCellById(21)->set(55555);
	
	// Show memory
	t->printGrid();
}