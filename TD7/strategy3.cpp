#include "matrix.h"
#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <math.h>

unsigned int *Matrix::vectorProduct(unsigned int *b) {
  // assumes the argument b has the correct length n.
  // creates a new unsigned int *, which must be deleted by the user.

  int rank, size;

  unsigned int *c = new unsigned int[n];
  for (unsigned int i = 0; i < n; ++i) {
    c[i] = 0;
  }

  MPI_Status status;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // TODO Exercise 3:
  // Matrix-vector product c = Ab with parallel decomposition by blocks.
  // Each of the p processors handles the matrix entries in a contiguous rectangle of side-lengths floor(n/p) or ceil(n/p).
  // The vectors b and c are both decomposed into blocks for each processor.

  // total # processors must be a perfect square.

  // don't forget to reduce the result modulo 26!

  return c;
}
