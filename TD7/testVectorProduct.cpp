#include "matrix.h"
#include <iostream>
#include <mpi.h>

struct Test {
  const char *name, *matrixfile, *vectorfile, *resultfile;
};

int main(int argc, char **argv) {
  const unsigned int printLimit = 20;
  MPI_Init(&argc, &argv);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  const unsigned int ntests = 5;
  const Test tests[ntests] = {
      {"2x2", "tests/test.matrix.2", "tests/test.vector.2",
       "tests/result.vector.2"},
      {"5x5", "tests/test.matrix.5", "tests/test.vector.5",
       "tests/result.vector.5"},
      {"20x20", "tests/test.matrix.20", "tests/test.vector.20",
       "tests/result.vector.20"},
      {"200x200", "tests/test.matrix.200", "tests/test.vector.200",
       "tests/result.vector.200"},
      {"1000x1000", "tests/test.matrix.1000", "tests/test.vector.1000",
       "tests/result.vector.1000"}};

  for (unsigned int i = 0; i < ntests; i++) {
    Test test = tests[i];
    if (rank == 0) {
      //std::cout << "== Test " << test.name << " ==" << std::endl;
    }
    Matrix A(test.matrixfile);
    if (rank == 0) {
      std::cout << "A = " ;
      if (A.n <= printLimit) {
        std::cout << A ;
      } else {
        std::cout << "[ " << A.n << "x" << A.n << " matrix ]";
      }
      std::cout << std::endl;
    }
    unsigned int *b = loadVector(test.vectorfile);
    if (rank == 0) {
      std::cout << "b = ";
      if (A.n <= printLimit) {
        printVector(std::cout, b, A.n);
      } else {
        std::cout << "[ " << A.n << "-dimensional vector ]";
      }
      std::cout << std::endl;
    }
    unsigned int *c = A.vectorProduct(b);
    if (rank == 0 && A.n <= printLimit) {
      std::cout << "c = Ab =  ";
      printVector(std::cout, c, A.n);
      std::cout << std::endl;
    }
    unsigned int *e = loadVector(test.resultfile);
    if (rank == 0) {
      if (A.n <= printLimit) {
        std::cout << "(expected ";
        printVector(std::cout, e, A.n);
        std::cout << ")" << std::endl;
      }
      bool pass = true;
      for (unsigned int i = 0; i < A.n; ++i) {
        if (c[i] != e[i]) {
          if (pass) {
            pass = false;
            std::cout << "Bad entries at indices: ";
          }
          std::cout << i << " ";
        }
      }
      if (!pass) {
        std::cout << std::endl;
        std::cout << "== Test " << test.name << " FAILED ==" << std::endl;
      } else {
        std::cout << "== Test " << test.name << " PASSED ==" << std::endl;
      } 
    }
    delete[] b, c, e;
  }

  MPI_Finalize();
  return 0;
}
