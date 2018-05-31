#include <iostream>
#include <stdexcept>
#include <map>
#include "graph.hpp"

void Graph::insertEdge(int nidFrom, int nidTo) {
  //    std::cout << "ajout de " << nidFrom << " a " << nidTo << std::endl;
  inAdjacencyList[nidTo].insert(nidFrom);
  outAdjacencyList[nidFrom].insert(nidTo);
}

bool Mapping::areMappable(int nidg, int nidh) {
  // do the two vertices violate the conditions for a valid mapping?
  // check several conditions

  // is one of the vertices already mapped ?
  if (currentMatchGH.count(nidg) != 0 || currentMatchHG.count(nidh) != 0) {
    //            std::cout << "alpha " << nidg << " , " << nidh << std::endl;
    return false;
  }

  // is the degree of the first vertex too high?
  if (G.inNeighborCount(nidg) > H.inNeighborCount(nidh) ||
      G.outNeighborCount(nidg) > H.outNeighborCount(nidh)) {
    //        std::cout << "beta " << nidg << " , " << nidh << std::endl;
    return false;
  }

  // do the neighbors fit?
  //    std::cout << "gamma " << nidg1 << " , " << nidg2 << std::endl;
  for (std::map<int, int>::iterator pair = currentMatchGH.begin();
       pair != currentMatchGH.end(); pair++) {
    if (G.isEdge(pair->first, nidg) != H.isEdge(pair->second, nidh) ||
        G.isEdge(nidg, pair->first) != H.isEdge(nidh, pair->second)) {
      return false;
    }
  }
  return true;
}

void Mapping::addToMap(int nidg, int nidh) {
  currentMatchGH[nidg] = nidh;
  currentMatchHG[nidh] = nidg;
}

void Mapping::deleteFromMap(int nidg) {
  std::map<int, int>::iterator tmp = currentMatchGH.find(nidg);
  int second = tmp->second;  // on sauve la valeur puisqu'on va effacer la
                             // memoire pointee par l'iterateur
  currentMatchGH.erase(tmp);
  tmp = currentMatchHG.find(second);
  currentMatchHG.erase(tmp);
  // std::cout << "unmatching de " << tmp->first << " et " << tmp->second <<
  // std::endl;
}

bool Mapping::isFull() { return currentMatchGH.size() == G.vertexCount(); }
std::ostream &operator<<(std::ostream &os, Mapping &m) {
  for (std::map<int, int>::iterator i = m.currentMatchGH.begin();
       i != m.currentMatchGH.end(); ++i) {
    os << '[' << i->first << " => " << i->second << ']' << ' ';
  }
  return os;
}
