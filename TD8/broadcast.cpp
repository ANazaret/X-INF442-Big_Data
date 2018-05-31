#include <vector>

#include "mpi.h"
#include "computeNeighbors.hpp"

void broadcast() {
  const int root = 0;
  int myrank, size;
  MPI_Status status;

  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int round = 0;
  int tag = 0;

  // root does not have to wait for a message
  if (myrank != root) {
    // wait for message from predecessor and print out the round
    int pred = computePredecessor(myrank);
    MPI_Recv(&round, 1, MPI_INT, pred, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::cout << "node " << myrank << " received message from " << pred
              << " in round " << round << std::endl;
  }

  // now let's send

  // first compute neighbors to send to
  std::vector<int> neighbors = computeOutNeighbors(myrank, size);

  // iterate over neighbors and send
  for (int i=0; i<neighbors.size(); i++){
    round += 1;
    MPI_Send(&round, 1, MPI_INT, neighbors[i], 0, MPI_COMM_WORLD);
  }
}

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  broadcast();
  MPI_Finalize();
  return 0;
}
