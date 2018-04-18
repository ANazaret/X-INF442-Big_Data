#include "QuadTree.hpp"
#include <math.h>
#include <iostream>
#include <stdlib.h>

int main() {

    // create the atoms

    std::vector<Atom*> atomVector;

    double x[10] = {
       0.840188 , 
       0.783099 , 
       0.911647 , 
       0.335223 , 
       0.277775 , 
       0.477397 , 
       0.364784 , 
       0.95223  , 
       0.635712 , 
       0.141603
    };
    double y[10] = {
       0.394383 , 
       0.79844  , 
       0.197551 , 
       0.76823  , 
       0.55397  , 
       0.628871 , 
       0.513401 , 
       0.916195 , 
       0.717297 , 
       0.606969
    };
    for (unsigned int i = 0; i < 10; i++) {
        atomVector.push_back(new Atom(x[i], y[i]));
    }

    // create the quad tree

    Rectangle r0(0.0, 1.0, 0.0, 1.0);
    QuadTree* quadTree = new QuadTree(atomVector, r0);
    quadTree->print();

    return 0;

}

