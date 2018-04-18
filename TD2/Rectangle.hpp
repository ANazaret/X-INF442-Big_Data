#pragma once

#include "Atom.hpp"

class Rectangle {

public:

	Rectangle();
	Rectangle(double xmin, double xmax, double ymin, double ymax);
	~Rectangle();

	bool intersects(const Rectangle& r);			///< Cette fonction renvoie true si et seulement si l'intersection de *this et r est non vide
	bool contains(Atom* atom);						///< Cette fonction renvoie true si et seulement si *this contient *atom

	Rectangle topLeftRectangle() const;				///< Cette fonction renvoie un rectangle correspondant a la partie top-left de *this
	Rectangle topRightRectangle() const;			///< Cette fonction renvoie un rectangle correspondant a la partie top-right de *this
	Rectangle bottomLeftRectangle() const;			///< Cette fonction renvoie un rectangle correspondant a la partie bottom-left de *this
	Rectangle bottomRightRectangle() const;			///< Cette fonction renvoie un rectangle correspondant a la partie bottom-right de *this

private:

	double xmin;
	double xmax;
	double ymin;
	double ymax;

};

