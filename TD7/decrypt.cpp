#include "codes.h"
#include "matrix.h"
#include <iostream>
#include <mpi.h>
#include <string>
#include <fstream>

std::string loadCiphertext(std::ifstream& file) {
  std::string s("");
  while (file.is_open( ) && ! file.eof( )) {
    char c = file.get( );
    if (c >= 'A' && c <= 'Z') {
      s += c;
    } else {
      // Silently ignore spurious characters
    }
  }
  return s;
}

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (argc < 2) {
    if (rank == 0) {
      std::cout << "Usage: " << argv[0] << " keyfile ciphertextfile" << std::endl;
    }
    MPI_Finalize( );
    return 1;
  }

  Matrix A(argv[1]);

  std::ifstream ciphertextfile(argv[2]);
  if (!ciphertextfile.is_open( )) {
    if (rank == 0) {
      std::cout << "Error: could not open ciphertext file '" << argv[2] << "'" << std::endl;
    }
    MPI_Finalize( );
    return 1;
  }

  std::string ciphertext = loadCiphertext(ciphertextfile);

  unsigned int len = ciphertext.length( );
  if ((len % A.n) != 0) {
    if (rank == 0) {
      std::cout << "Error: ciphertext length " << len << " is not a multiple of the matrix dimension " << A.n << std::endl;
    }
    MPI_Finalize( );
    return 1;
  }

  // TODO Exercise 4: 
  // Decipher using the matrix-vector product.
  // 
  unsigned int *b = new unsigned int[len];
  for (int i=0; i<len; i++)
    b[i] = charToCode(ciphertext[i]);
  
  for (int i=0; i*A.n < len; i++){
      unsigned int *c;
      
      c = A.vectorProduct(b+i*A.n);
      if (rank == 0) {
	for(int j=0; j<A.n; j++)
	  std::cout << codeToChar(c[j]);
      }
  }
  
  
  


  MPI_Finalize( );
  return 0;
}
