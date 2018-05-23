#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "spiral.hpp"
#include "Memory.hpp"
#include <iomanip>

using namespace std;

Cell::Cell(int i, int j) {
	this->col=i;
	this->row=j;
}

void Cell::setNeighbors(Cell* up, Cell* down, Cell* left, Cell* right) {
	this->up=up;
	this->down=down;
	this->left=left;
	this->right=right;
}

void Cell::setId(int id) { this->id = id; }

int Cell::getId() { return id; }

void Cell::set(int c) { this->c = c; }

int Cell::read() { return this->c; }

int Cell::DistanceTo(Cell * b) { return abs(b->col-col) + abs(b->row-row); }

Cell* Cell::MoveToNext(string* direction) {

	if (col+row>0) { // right or up
		if (row>=col) {	// right
			//cout << "Next=Right" << endl;
			if (direction) *direction = "right";
			return MoveRight();
		} else { 		// up
			//cout << "Next=Up" << endl;
			if (direction) *direction = "up";
			return MoveUp();
		}
	}
	if (col+row<0) { // down or left
		if (row>=col) {	// down
			//cout << "Next=Down" << endl;
			if (direction) *direction = "down";	
			return MoveDown();
		} else {		// left
			//cout << "Next=Left" << endl;			
			if (direction) *direction = "left";
			return MoveLeft();
		}
	}
	if (col+row==0) {
		if (row>=0) {	// right
			//cout << "Next=Right" << endl;
			if (direction) *direction = "right";			
			return MoveRight();
		} else { 		// left
			//cout << "Next=Left" << endl;
			if (direction) *direction = "left";			
			return MoveLeft();
		}
	}
	
	cout << "Something went wrong..." << endl;
	return NULL;
}

Cell* Cell::MoveToNext() { return MoveToNext(NULL); }

Cell* Cell::MoveRight() { return right; }
Cell* Cell::MoveLeft() { return left; }
Cell* Cell::MoveUp() { return up; }
Cell* Cell::MoveDown() { return down; }
