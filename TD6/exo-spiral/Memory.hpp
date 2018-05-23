#pragma once

#include <map>
#include "Cell.hpp"

class Memory {
	public:
		Cell* getCellById(int id);		// returns pointer to cell with id "id"
		Cell* getCellByCoords(int col, int row);
										// returns pointer to cell with coords (col, row)
		
		void printGrid();							// TODO: exo2.1
		
		Memory(int size);	// constructor
		~Memory();

		int offx;
		int offy;	
   		int side;						// side of the memory grid (nbr of cells: side*side)

	private:
		std::map <int, Cell *> cells;

		Cell *** mem;		// the internal 2D-array of Cell*
   		Cell * p;
};