#pragma once

#include "Atom.hpp"
#include "Rectangle.hpp"
#include <vector>

class QuadTree {

public:

	QuadTree(std::vector<Atom*>& v, Rectangle& r);
	~QuadTree();

	void rangeSearch(std::vector<Atom*>& v, Rectangle& r);
	void print(unsigned int offset = 0) const;

private:

	QuadTree* topLeft;
	QuadTree* topRight;
	QuadTree* bottomLeft;
	QuadTree* bottomRight;

	Atom* atom;
	Rectangle rectangle;
	
};

