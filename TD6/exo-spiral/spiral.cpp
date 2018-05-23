#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "spiral.hpp"
#include "Cell.hpp"
#include "Memory.hpp"
#include <iomanip>

using namespace std;

Cell* WalkByNext(Cell * src, int dest) {
	// TODO, Q2 : implement this function (and return the corresponding pointer)
	string * dir = new string();
	cout << "[" << src->getId() << "]";
	while( src->getId() < dest){
	    src = src->MoveToNext(dir);
	    cout << " " << (*dir) << " [" << src->getId() << "]";
	}
	cout << "\n";
	return src;
}

Cell* WalkTo(Cell * src, int &dist, Cell * dst) {
	// TODO, exercise Q3  : implement this function (and return the corresponding pointer)
	if (src->getId() != dst->getId()){
	    dist += 1;
	    int d = src->DistanceTo(dst);
	    Cell* next;
	    next = src->MoveRight();
	    if (next != NULL)
	      if (next->DistanceTo(dst) < d){
		cout << "[" << src->getId() << "] " << "right ";
		return WalkTo(next, dist, dst);
	      }
	    
	    next = src->MoveUp();
	    if (next != NULL)
	      if (next->DistanceTo(dst) < d){
		cout << "[" << src->getId() << "] " << "up ";
		return WalkTo(next, dist, dst);
	      }
	      
	      
	    next = src->MoveLeft();
	    if (next != NULL)
	      if (next->DistanceTo(dst) < d){
		cout << "[" << src->getId() << "] " << "left ";
		return WalkTo(next, dist, dst);
	      }
	      
	    next = src->MoveDown();
	    if (next != NULL)
	      if (next->DistanceTo(dst) < d){
		cout << "[" << src->getId() << "] " << "down ";
		return WalkTo(next, dist, dst);
	      }
	
	}
	
	cout << "[" << dst->getId() << "]\n";
	return dst;
}

int distanceBetween(int id_a, int id_b, int side) {
	// TODO, Q4 : implement this function (and return the corresponding value)

	return 0;
}

int FillWithSumOfAdjacent(Memory * m, Cell * cell, int thres) {
	// TODO, Q5 : implement this function (and return the corresponding value)
	
	//Fill with 0
	Cell * c = m->getCellById(1);
	while (c != NULL){
	  c->set(0); c=c->MoveToNext();
	}
	
	cell->set(1);
	c = cell->MoveToNext();
	while(c != NULL){
	  int tmp = 0;
	  Cell* ct;
	  
	  ct = c->MoveRight();
	  if (ct != NULL){
	    tmp += ct->read();
	    Cell * ct2;
	    ct2 = ct->MoveUp();
	    if (ct2 != NULL){
	      tmp += ct2->read();	      
	    }
	    ct2 = ct->MoveDown();
	    if (ct2 != NULL){
	      tmp += ct2->read();	      
	    }	    
	  }
	  
	  ct = c->MoveLeft();
	  if (ct != NULL){
	    tmp += ct->read();
	    Cell * ct2;
	    ct2 = ct->MoveUp();
	    if (ct2 != NULL){
	      tmp += ct2->read();	      
	    }
	    ct2 = ct->MoveDown();
	    if (ct2 != NULL){
	      tmp += ct2->read();	      
	    }	    
	  }
	  
	
	 
	  ct = c->MoveUp();
	  if (ct != NULL){
	    tmp += ct->read();	      
	  }
	  ct = c->MoveDown();
	  if (ct != NULL){
	    tmp += ct->read();	
	  }
	    
	  c->set(tmp);
	  
	  if (tmp > thres)
	    return tmp;
	  
	  c = c->MoveToNext();
	    
	  
	}
      
	return -1;
}
