/*
  Filename: mathtools.cpp
  Author: Leo Liberti
  Purpose: mathematical functions for the JLL TD
  Source: GNU C++
  History:
    150419 work started
*/

#include <iostream>
#include <vector>
// C library includes wrapped by STL
#include <cstdlib>
#include <cmath>
#include <cassert>

#include "randomsample.hpp"
#include "mathtools.hpp"

extern bool debug;

// compute the squared Euclidean distance between two vector<double>
double sqEuclideanDistance(std::vector<double>& x, std::vector<double>& y) {
  using namespace std;
  assert(x.size() == y.size());
  double sqDist = 0;
  // WARNING: a for loop with index access (x[i]-y[i])
  //   would yield O(n log n), since each vector [] access is O(log n)
  //   The iterator-baed loop below is O(n)
  vector<double>::iterator xi(x.begin());
  vector<double>::iterator yi(y.begin());
  while (xi != x.end()) {
    // don't get confused between the unary dereference operator * and
    //   the binary arithmetic product operator with the same symbol.
    //   C++ can tell them apart - if the computer can, so should you!
    sqDist += (*xi - *yi) * (*xi - *yi);
    xi++;
    yi++;
  }
  return sqDist;
}

// compute the squared Euclidean distance matrix of a set of vectors
std::vector<std::vector<double> > sqEDM(std::vector<std::vector<double> >& S) {
  using namespace std;
  // size of S (set of n column vectors of size d
  int n = S.size();
  int d = S[0].size();
  // we use both iterators and indices
  int i = 0;
  int j = 0;
  // this holds the output squared EDM
  vector<vector<double> > EDM(n);
  // initialize EDM to zero
  for (vector<vector<double> >::iterator ei = EDM.begin(); ei != EDM.end();
       ++ei) {
    for (j = 0; j < n; j++) {
      ei->push_back(0.0);
    }
  }
  // loop over the vectors twice
  for (vector<vector<double> >::iterator vi = S.begin(); vi != S.end(); ++vi) {
    j = 0;
    for (vector<vector<double> >::iterator vj = S.begin(); vj != S.end();
         ++vj) {
      if (i < j) {
        EDM[i][j] = sqEuclideanDistance(*vi, *vj);
      } else {
        EDM[i][j] = EDM[j][i];
      }
      j++;
    }
    i++;
  }
  return EDM;
}

// sample Gaussian projd x d matrix
//   sequential computation
std::vector<std::vector<double> > JLProjectionMatrix(int d, int projd) {
  using namespace std;
  vector<vector<double> > JL;
  // we are going to store the matrix by rows (since the data matrix
  //   is stored by columns, this is like storing the transpose)
  double sqrtp = sqrt(projd);

  if (debug) {
    cerr << "JLProjectionMatrix(): using sequential";
  }

  // create the Gaussian matrix component by component
  //// TODO: JL must contain projd vectors of length d, each component
  ////       of which is sampled by a Gaussian distribution with mean 0
  ////       and standard deviation 1 / sqrtp
  
  for (int i=0; i<projd; ++i){
   vector<double> row;
   for (int j=0; j<d;++j){
     double val = GaussianRandom()/sqrtp;
    row.push_back(val); 
   }
   
   JL.push_back(row);
    
  }

  if (debug) {
    cerr << "JLProjectionMatrix(): JL is " << JL.size() << " x " << JL[0].size()
         << endl;
  }

  // about returning a large object on the stack: all modern C++ compilers
  //   will NOT copy them, but rather just use the original storage. See
  //   http://stackoverflow.com/questions/753312/
  return JL;
}

// matrix product
//   sequential implementation
std::vector<std::vector<double> > MatrixProduct(
    std::vector<std::vector<double> >& JL,
    std::vector<std::vector<double> >& X) {
  using namespace std;
  if (debug) {
    cerr << "MatrixProduct(): using sequential" << endl;
  }
  // this will hold the product of JL and X
  vector<vector<double> > projX;
  // matrix dimensions
  int projd = JL.size();
  int n = X.size();
  int d = X[0].size();
  // as matrices, JL is (projd x d) and X is (d x n)
  //   as a vector of vectors, JL holds projd vectors of length d
  //   as a vector of vectors, X holds n vectors of length d
  for (int j=0; j<n; ++j){
    vector<double> col;
    
    for (int i=0; i<projd; ++i){    
      double val=0.0;
      for (int k=0; k<d; ++k){
	val += JL[i][k]*X[j][k];
      }
      col.push_back(val);
      
    }
    projX.push_back(col);
  }
  
  
  //// TODO: projX must be the scalar product of JL by X, meaning
  ////       component (i,j) of projX is the scalar product of the
  ////       i-th row of JL by j-th column of X (recall that JL
  ////       is stored as a vector of rows, whereas X is stored as
  ////       a vector of columns)

  return projX;
}

// print a vector<vector<double> >
void printData(std::vector<std::vector<double> >& data) {
  using namespace std;
  // loop over rows
  // WARNING: when using iterators, NEVER EVER write
  //   iterator_name < container_name.end(), always use "!=" instead of "<"
  //   (an iterator is like a pointer, elements of the container
  //    could be stored beyond the end() address)
  for (vector<vector<double> >::iterator vvd = data.begin(); vvd != data.end();
       ++vvd) {
    // loop over columns
    for (vector<double>::iterator vd = vvd->begin(); vd != vvd->end(); ++vd) {
      // separate fields using spaces
      cout << " " << *vd;
    }
    cout << endl;
  }
}
