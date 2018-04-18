#include "QuadTree.hpp"
#include <iostream>

using namespace std;

QuadTree::QuadTree(std::vector<Atom*>& v, Rectangle& r) {

	rectangle = r;

	if (v.size() == 0) {

		topLeft = 0;
		topRight = 0;
		bottomLeft = 0;
		bottomRight = 0;

		atom = 0;

	}
	else if (v.size() == 1) {

		topLeft = 0;
		topRight = 0;
		bottomLeft = 0;
		bottomRight = 0;

		atom = v[0];

	}
	else {

		atom = 0;
		
		Rectangle rtl = r.topLeftRectangle();
		Rectangle rtr = r.topRightRectangle();
		Rectangle rbl = r.bottomLeftRectangle();
		Rectangle rbr = r.bottomRightRectangle();
		
		vector<Atom*> vtl, vtr, vbl, vbr;
		
		//for (Atom* patom : v){
		for (vector<Atom*>::iterator it = v.begin(); it != v.end(); ++it){
		  Atom* atom = *it;
		  if (rtl.contains(atom))
		    vtl.push_back(atom);
		  if (rtr.contains(atom))
		    vtr.push_back(atom);
		  if (rbl.contains(atom))
		    vbl.push_back(atom);
		  if (rbr.contains(atom))
		    vbr.push_back(atom);
		}
		
			
		topLeft = new QuadTree(vtl,  rtl);
		topRight = new QuadTree(vtr,  rtr);
		bottomLeft = new QuadTree(vbl,  rbl);
		bottomRight = new QuadTree(vbr,  rbr);
		
		
	}

}

void QuadTree::print(unsigned int offset) const {

	if (topLeft) {

		for (unsigned int i = 0; i < offset; i++) std::cout << "\t";
		std::cout << "topLeft";
		std::cout << std::endl;
		topLeft->print(offset + 1);

		for (unsigned int i = 0; i < offset; i++) std::cout << "\t";
		std::cout << "topRight";
		std::cout << std::endl;
		topRight->print(offset + 1);

		for (unsigned int i = 0; i < offset; i++) std::cout << "\t";
		std::cout << "bottomLeft";
		std::cout << std::endl;
		bottomLeft->print(offset + 1);

		for (unsigned int i = 0; i < offset; i++) std::cout << "\t";
		std::cout << "bottomRight";
		std::cout << std::endl;
		bottomRight->print(offset + 1);

	}
	else if (atom) {

		for (unsigned int i = 0; i < offset; i++) std::cout << "\t";
		std::cout << "Atom = " << atom->x << " " << atom->y << std::endl;

	}

}

QuadTree::~QuadTree() {

	if (topLeft) delete topLeft;
	if (topRight) delete topRight;
	if (bottomLeft) delete bottomLeft;
	if (bottomRight) delete bottomRight;

}

void QuadTree::rangeSearch(std::vector<Atom*>& v, Rectangle& r) {

	if (atom && r.contains(atom) ){
	  v.push_back(atom);
	  return;
	}
	
	if (topLeft && r.intersects(topLeft->rectangle))
	  topLeft->rangeSearch(v, r);
	if (topRight && r.intersects(topRight->rectangle))
	  topRight->rangeSearch(v, r);
	if (bottomLeft && r.intersects(bottomLeft->rectangle))
	  bottomLeft->rangeSearch(v, r);
	if (bottomRight && r.intersects(bottomRight->rectangle))
	  bottomRight->rangeSearch(v, r);
	

}