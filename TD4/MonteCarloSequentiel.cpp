#include "Molecule.h"
#include <iostream>
#include <cstdlib>
#include <limits>

unsigned long monteCarlo(unsigned long e, std::vector<Boule> mol,
		double BB[3][2]) {
	
	unsigned long ePrime = 0;
	double rp[3];
	bool contains = false;
	
	for(unsigned long i=0; i<e; i++){
	  randomPoint(rp, BB);
	  contains = false;
	  
	  for(int k=0; k< mol.size(); k++){
	    Boule b = mol[k];
	    if (b.contains(rp)){
	      contains = true;
	      break;
	    }
	  }
	  if (contains)
	    ePrime ++;
	}
	
	return ePrime;
}

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cerr << "Usage : " << argv[0]
			<< " e moleculefile (where e = # Monte Carlo trials)"
			<< std::endl;
		return 1;
	}

	const long e = atol(argv[1]);
	if (e <= 0) {
		std::cerr << "Argument must be an integer > 0" << std::endl;
		return 1;
	}

	// In the spirit of reproducibility, explicit initialisation of seed
	srand(0);

	// Load molecule.
	std::vector<Boule> molecule = readMolecule(argv[2]);
	// Bounding box.
	double BB[3][2];
	boundingBox(BB, molecule);

	// Compute volume.
	unsigned long ePrime = monteCarlo(e, molecule, BB);
	
	//std::cout << "ePrime : " << ePrime << std::endl;
	
	double BBvol = (BB[0][1]-BB[0][0])*(BB[1][1]-BB[1][0])*(BB[2][1]-BB[2][0]);
	double vol = -1.0;
	vol = (double)ePrime*BBvol/(double)e;

	// Set maximal precision when printing doubles.
	std::cout.precision(std::numeric_limits<double>::digits10 + 1);
	std::cout << "volume : " << vol << std::endl;

	return 0;
}
