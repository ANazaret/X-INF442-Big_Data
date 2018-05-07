/*
  Filename: mathtools.hpp
  Author: Leo Liberti
  Purpose: mathematical functions for the JLL TD
  Source: GNU C++
  History:
    150419 work started
*/

#ifndef MATHTOOLSH
#define MATHTOOLSH

#include <vector>

// compute the squared Euclidean distance between two vectors
double sqEuclideanDistance(std::vector<double>& x, std::vector<double>& y);

// compute the squared Euclidean distance matrix of a set of vectors
std::vector<std::vector<double> > sqEDM(std::vector<std::vector<double> >& S);

// sample a Gaussian d times k matrix
std::vector<std::vector<double> > JLProjectionMatrix(int d, int k);

// matrix product
std::vector<std::vector<double> > MatrixProduct(
    std::vector<std::vector<double> >& JL,
    std::vector<std::vector<double> >& X);
// #endif

// print a vector of vectors
void printData(std::vector<std::vector<double> >& data);

#endif
