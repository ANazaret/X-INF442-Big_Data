#include <iostream>
#include <stdexcept>
#include <map>
#include "graph.hpp"
#include "Isomorphism.hpp"

// Creation rapide de deux instances minimalistes pour tester
Graph createG1() {
  Graph G = Graph(3);
  G.insertEdge(2, 1);
  G.insertEdge(0, 2);

  return G;
}

Graph createH1() {
  Graph H = Graph(3);

  H.insertEdge(0, 1);
  H.insertEdge(1, 2);

  return H;
}

Graph createG2() {
  Graph G = Graph(4);

  G.insertEdge(2, 1);
  G.insertEdge(0, 2);
  G.insertEdge(2, 3);

  return G;
}

Graph createH2() {
  Graph H = Graph(4);

  H.insertEdge(0, 1);
  H.insertEdge(1, 2);
  H.insertEdge(2, 3);

  return H;
}

int main(int argc, char **argv) {
  // Creation de deux graphes, factices pour le moment, pour tester

  Graph G_1 = createG1();
  Graph H_1 = createH1();

  std::cout << "Test d'isomorphismes entre graphes G_1 et H_1 :" << std::endl;
  findIsomorphism(G_1, H_1);

  Graph G_2 = createG2();
  Graph H_2 = createH2();

  std::cout << "Test d'isomorphismes entre graphes G_2 et H_2 :" << std::endl;
  findIsomorphism(G_2, H_2);

  return 0;
}
