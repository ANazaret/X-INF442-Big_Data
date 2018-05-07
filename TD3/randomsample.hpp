/*
  Filename: randomsample.hpp
  Author: Leo Liberti
  Purpose: random sampling utilities for the JLL TD
  Source: GNU C++
  History:
    150419 work started
*/

#ifndef RANDOMSAMPLEH
#define RANDOMSAMPLEH

#include <vector>

// cast a uniformly randomly chosen integer in {a,...,b}
int randomInteger(int a, int b);
// cast a uniformly randomly chosen double in [a,b]
double randomDouble(double a, double b);
// generate two Gaussian random samples (the Box-Muller algorithm)
void GaussianRandomPair(double& X1, double& X2);
// this version of the Box-Muller algorithm only returns one sample
double GaussianRandom(void);

#endif
