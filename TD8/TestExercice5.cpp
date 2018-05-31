#include <iostream>
#include <stdexcept>
#include <map>
#include "graph.hpp"
#include "Isomorphism.hpp"
#include "mpi.h"

// Creation rapide d'une instance minimaliste pour tester
Graph createG1() {
  Graph G = Graph(3);

  G.insertEdge(2, 1);
  G.insertEdge(0, 2);
  G.insertEdge(1, 0);

  return G;
}

Graph createH1() {
  Graph H = Graph(5);

  H.insertEdge(0, 1);
  H.insertEdge(1, 2);
  H.insertEdge(0, 2);
  H.insertEdge(2, 3);
  H.insertEdge(3, 4);
  H.insertEdge(4, 2);

  return H;
}

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  Graph G_1 = createG1();
  Graph H_1 = createH1();

  findSubIsomorphismMPI(G_1, H_1);

  MPI_Finalize();
  return 0;
}
