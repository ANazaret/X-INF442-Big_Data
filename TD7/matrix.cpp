#include "matrix.h"
#include "codes.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

// Trivial default constructor: constructs a 0x0 matrix.
Matrix::Matrix() : n(0), data(0) { }

// Creates a new nxn matrix object.
// The memory for the entries is allocated, but they are not initialised.
Matrix::Matrix(unsigned int dimension) : n(dimension), data((dimension > 0) ? new unsigned int *[dimension]() : 0) {
  for (unsigned int i = 0; i < n; ++i) {
    data[i] = new unsigned int[n];
  }
}

// Copy constructor.
Matrix::Matrix(const Matrix &M) : n(M.n), data((M.n > 0) ? new unsigned int*[M.n]() : 0) {
  for (unsigned int i = 0; i < n; ++i) {
    data[i] = new unsigned int[n];
    std::copy(M.data[i],M.data[i]+n,data[i]);
  }
}

// Move constructor.
// Matrix::Matrix(Matrix && other) : Matrix( ) { swap(*this,other) }

// Assignment operator.
Matrix& Matrix::operator=(const Matrix& other) {
  Matrix temp(other);
  swap(*this,temp);
  return *this;
}

// Constructor for testing: read in a matrix from a text file.
// Assumes that the file is in the correct format...
Matrix::Matrix(const char *filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cout << "Error: could not open matrix file '" << filename << "'"
              << std::endl;
    std::exit(1);
  }
  file >> n;
  data = new unsigned int *[n];
  for (unsigned int i = 0; i < n; ++i) {
    data[i] = new unsigned int[n];
    for (unsigned int j = 0; j < n; ++j) {
      file >> data[i][j];
    }
  }
  file.close();
}

// Unsurprising destructor: delete internal arrays.
Matrix::~Matrix() {
  for (unsigned int i = 0; i < n; ++i) {
    delete[] data[i];
  }
  if (data != 0) {
    delete[] data;
  }
}

// Subscripting so that we can use M[i][j] in a familiar way.
unsigned int *&Matrix::operator[](unsigned int i) { return data[i]; }

// Matrix transpose.
Matrix Matrix::transpose( ) {
  Matrix res(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      res[j][i] = data[i][j];
    }
  }
  return res;
}

// Over-write all entries of this matrix to 0.
void Matrix::zeroFill( ) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      data[i][j] = 0;
    }
  }
}

// Over-write entries of this matrix to create a uniformly random-sampled
// lower-triangular invertible matrix over ZZ/26ZZ.
void Matrix::randomLowerTriangularInvertibleFill( ) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      data[i][j] = randomCode( );
    }
    data[i][i] = randomInvertibleCode( );
    for (int j = i+1; j < n; ++j) {
      data[i][j] = 0;
    }
  }
}


// Printing functions
void printVector(std::ostream &os, unsigned int *v, unsigned int n) {
  os << "[";
  for (unsigned int i = 0; i < n; ++i) {
    if (v[i] < 10) {
      os << " ";
    }
    os << v[i];
    if (i != n - 1) {
      os << " ";
    }
  }
  os << "]";
}
std::ostream &operator<<(std::ostream &os, Matrix &M) {
  os << "[" << std::endl;
  for (unsigned int i = 0; i < M.n; ++i) {
    os << " ";
    printVector(os, M[i], M.n);
    os << std::endl;
  }
  os << "]";
}

// loading "vectors" from a text file
unsigned int *loadVector(const char *filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cout << "Error: could not open vector file '" << filename << "'"
              << std::endl;
    std::exit(1);
  }
  unsigned int n;
  file >> n;
  unsigned int *vec = new unsigned int[n];
  for (unsigned int i = 0; i < n; ++i) {
    file >> vec[i];
  }
  file.close();
  return vec;
}


