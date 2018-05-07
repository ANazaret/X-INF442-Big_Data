/*
  Filename: randomsample.cpp
  Author: Leo Liberti
  Purpose: random sampling utilities for the JLL TD
  Source: GNU C++
  History:
    150419 work started
    150420 adapted to work as TD text
*/

// C library includes wrapped by STL
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <limits>

#include "randomsample.hpp"

// random integer between a and b
int randomInteger(int a, int b) {
  assert(a < b);
  // note the use of random() instead of rand(): random() uses a better
  //   pseudorandom number generators, and should always be preferred
  return random() % (b - a) + a;
}

// random double between a and b
double randomDouble(double a, double b) {
  assert(a < b);
  // note the use of random() instead of rand(): random() uses a better
  //   pseudorandom number generators, and should always be preferred
  return (random() / (double)RAND_MAX) * (b - a) + a;
}

// generate two Gaussian random samples (the Box-Muller algorithm)
void GaussianRandomPair(double& x1, double& x2) {
  // the algorithm is as follows: if you take two uniform samples in (0,1)
  //   then you treat them as if they were exponentials of sine and cosine,
  //   the inverse operation to retrieve such sine and cosine will yield
  //   two samples from a Normal distribution (which is a Gaussian
  //   distribution with mean 0 and variance 1) - see
  //   http://en.wikipedia.org/wiki/Box-Muller_transform
  const double about_zero = std::numeric_limits<double>::min();
  const double two_pi = 2.0 * 3.14159265358979323846;
  double v1, v2;
  do {
    v1 = randomDouble(0, 1);
    v2 = randomDouble(0, 1);
  } while (v1 <= about_zero);
  x1 = sqrt(-2.0 * log(v1)) * cos(two_pi * v2);
  x2 = sqrt(-2.0 * log(v1)) * sin(two_pi * v2);
}

// this version of the Box-Muller algorithm only returns one sample
double GaussianRandom(void) {
  double ret, tmp;
  GaussianRandomPair(ret, tmp);
  return ret;
}
