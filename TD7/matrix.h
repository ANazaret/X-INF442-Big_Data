#pragma once
#include <iostream>
#include <algorithm>

class Matrix {
 public:
  unsigned int **data;
  unsigned int n;

  // Default: a 0x0 matrix.
  Matrix();

  // Creates an *uninitialized* square matrix.
  Matrix(unsigned int);

  // Creates a matrix with entries in a text file (for testing).
  Matrix(const char *);

  // Copy constructor.
  Matrix(const Matrix &);

  // Move constructor.
  // Matrix(Matrix &&);

  // Assignment
  Matrix & operator=(const Matrix &);

  // Destruction.
  ~Matrix();

  // Allows us to use M[i][j] to access the (i,j)-th entry
  unsigned int *&operator[](unsigned int);

  // Matrix-vector product: argument is viewed as a column vector,
  // to be multiplied on the right, and the result reduced modulo 26.
  // Allocates new memory for the result, which must be deleted by the user.
  // (To be implemented in Exercises 1, 2, 3.)
  unsigned int *vectorProduct(unsigned int *);

  // Returns the transpose of this matrix.
  Matrix transpose( );

  // Replaces entries of this matrix with zeroes.
  void zeroFill( );

  // Replaces entries of this matrix to create a uniformly random-sampled lower-triangular invertible matrix.
  // Warning: over-writes all current entries of this matrix!
  void randomLowerTriangularInvertibleFill( );

  // Exchange two matrices (for use in assignment operator).
  friend void swap(Matrix& first, Matrix& second) {
    using std::swap;
    swap(first.n,second.n);
    swap(first.data,second.data);
  }
};

// to print "vectors" (and rows of matrices)
void printVector(std::ostream &, unsigned int *, unsigned int);

// to load vectors from a file (for testing)
unsigned int *loadVector(const char *filename);

// to print out matrices (eg. std::cout << M << std::endl;)
std::ostream &operator<<(std::ostream &, Matrix &);
