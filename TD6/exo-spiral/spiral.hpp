#include <map>
#include "Cell.hpp"
#include "Memory.hpp"

Cell* WalkByNext(Cell * src, int dest);								// TODO: exo2.2
Cell * WalkTo(Cell * src, int &dist, Cell * dst);					// TODO: exo2.3
int distanceBetween(int id_a, int id_b, int side);				// TODO: exo2.4
int FillWithSumOfAdjacent(Memory * m, Cell * cell, int thres);	// TODO: exo2.5