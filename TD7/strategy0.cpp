#include "matrix.h"

unsigned int *Matrix::vectorProduct(unsigned int *b) {
  // assumes the argument b has the correct length n.
  // creates a new unsigned int *, which must be deleted by the user.

  unsigned int *c = new unsigned int[n];

  for (unsigned int i = 0; i < n; ++i) {
    unsigned int s = 0;
    for (unsigned int j = 0; j < n; ++j) {
      s += (data[i][j] * b[j]) % 26;
    }
    c[i] = s % 26;
  }
  return c;
}
