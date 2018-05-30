#include "matrix.h"
#include <mpi.h>
#include <math.h>
using namespace std;
unsigned int *Matrix::vectorProduct(unsigned int *b) {
  // assumes the argument b has the correct length n.
  // creates a new unsigned int *, which must be deleted by the user.

  unsigned int *c = new unsigned int[n];
  for (unsigned int i = 0; i < n; ++i) {
    c[i] = 0;
  }

  int rank, size;

  MPI_Status status;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // TODO Exercise 2:
  // Matrix-vector product c = Ab with parallel decomposition by columns.
  // Each of the p processors handles a contiguous group of floor(n/p) or ceil(n/p) columns of the matrix.
  // The vector b is decomposed into blocks, one for each processor.
  
  // don't forget to reduce the result modulo 26!
   int k;
  int start;
  
  if (rank >= n%size)
    k = n/size;    
  else 
    k = n/size + 1;
  start = (n*rank)/size + min((int) (n%size), rank);
  
  //cout << "Processor " << rank << " : " << start << " + " << k; 
    
  for (int i=0; i<n; i++){
   int tmp = 0;
   for (int j=start; j<start+k; j++){
      tmp += (data[i][j]*b[j]) %26;
      tmp %= 26;
   }
   c[i] = tmp;    
  }
  
  
  
  
  if (rank == 0){
    unsigned int *temp = new unsigned int[n];
    for (int i=1; i<size; i++){
      int tmp_start = (n*i)/size + min((int) (n%size), i);
      int tmp_k = n/size + ( (rank > n%size) ? 0 : 1);
      MPI_Recv(temp, n, MPI_UNSIGNED, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
      for (int i=0; i<n; i++) 
	c[i] = ( c[i] + temp[i]) % 26;
    }
    
    delete[] temp;
    
  } else {
    MPI_Send(c, n, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD);
    delete[] c;
  }
  

  return c;
}
