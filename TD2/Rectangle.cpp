#include "Rectangle.hpp"


Rectangle::Rectangle() {

	this->xmin = 0.0;
	this->xmax = 0.0;
	this->ymin = 0.0;
	this->ymax = 0.0;

}

Rectangle::Rectangle(double xmin, double xmax, double ymin, double ymax) {

	this->xmin = xmin;
	this->xmax = xmax;
	this->ymin = ymin;
	this->ymax = ymax;

}

Rectangle::~Rectangle() {

}

bool Rectangle::intersects(const Rectangle& r) {

	if (xmax <= r.xmin) return false;
	if (xmin >= r.xmax) return false;
	if (ymax <= r.ymin) return false;
	if (ymin >= r.ymax) return false;

	return true;

}

bool Rectangle::contains(Atom* atom) {

	if (!atom) return false;

	if (atom->x < xmin) return false;
	if (atom->x >= xmax) return false;
	if (atom->y < ymin) return false;
	if (atom->y >= ymax) return false;

	return true;

}

Rectangle Rectangle::topLeftRectangle() const {

	double xm = 0.5*(xmin + xmax);
	double ym = 0.5*(ymin + ymax);

	return Rectangle(xmin,xm,ymin,ym);

}

Rectangle Rectangle::topRightRectangle() const {

	double xm = 0.5*(xmin + xmax);
	double ym = 0.5*(ymin + ymax);

	return Rectangle(xm, xmax, ymin, ym);

}


Rectangle Rectangle::bottomLeftRectangle() const {

	double xm = 0.5*(xmin + xmax);
	double ym = 0.5*(ymin + ymax);

	return Rectangle(xmin, xm, ym, ymax);

}


Rectangle Rectangle::bottomRightRectangle() const {

	double xm = 0.5*(xmin + xmax);
	double ym = 0.5*(ymin + ymax);

	return Rectangle(xm, xmax, ym, ymax);

}


