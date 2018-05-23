#pragma once
#include <string>

using namespace std;

class Cell {
	public:
		Cell(int i, int j);		// constructor
		~Cell();

		int read();				// returns the content (stored value) of this cell
		void set(int c);		// changes the content of this cell
		void setId(int id);		// sets the id of this cell
		int getId();			// returns the id this cell
   
		Cell * MoveRight();		// returns pointer to Cell on the right of calling cell
		Cell * MoveLeft();		//    "       "     "   "   "  "   left   "   "    "    
		Cell * MoveUp();		//    "       "     "   "   "  top        "   "    "
		Cell * MoveDown();  	//    "       "     "   "   "  the bottom "   "    "

		Cell * MoveToNext();	// returns pointer to next Cell (id+1) of calling cell 
		Cell * MoveToNext(string* direction);	
								// same, and writes in direction the movement to 
								//   reach it ("right", "left", "up", "down")

		void setNeighbors(Cell* up, Cell* down, Cell* left, Cell* right);

		int DistanceTo(Cell * b);

	private:
   		int id;
		int col;
		int row;
   		   
		unsigned long c;		// content
		
		Cell* up;
		Cell* down;
		Cell* left;
		Cell* right;
};