#ifndef MOLECULE_H
#define MOLECULE_H
#include <vector>

// A "molecule" is a std::vector of Boules.
//
// A Boule is a sphere in RR^3, defined by
//   - its centre (an array of 3 doubles);
//   - its radius (a double)
//
// All points in RR^3 are arrays of three doubles.

class Boule {
	public:
		double centre[3];
		double radius;  // should be non-negative, though we don't check this.
		Boule(const double[3], const double);
		bool contains(const double[3]);  // true iff the argument is within the boule
};

// the (squared) Euclidean distance between two points
double squaredDistance(const double[3], const double[3]);

// reads in a molecule from a text file
std::vector<Boule> readMolecule(const char *);

// defines a bounding box around a given molecule
void boundingBox(double[3][2], std::vector<Boule>);

// generates a random point in a given bounding box
void randomPoint(double[3], const double[3][2]);

#endif
