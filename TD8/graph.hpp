#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <stdexcept>
#include <map>
#include <vector>
#include <set>

class Graph {
 public:
  // Constructor that creates a graph with numVertices vertices and no edges.
  
  // The vertex set of a graph is always implicitly assumed to be {0, 1, ..., numVertices - 1} and
  // thus not encoded explicitly.
  // Consequently, when one wants to iterate over the vertices of a graph, one can simply iterate over the 
  // integers from 0 to vertexCount()
  Graph(int numVertices)
      : n(numVertices),
        inAdjacencyList(std::vector<std::set<int> >(numVertices)),
        outAdjacencyList(std::vector<std::set<int> >(numVertices)){};

  // returns the number of vertices in the graph
  int vertexCount() { return n; };

  // return the number in- resp. out-neighbors of the vertex nid
  int inNeighborCount(int nid) { return inAdjacencyList[nid].size(); }
  int outNeighborCount(int nid) { return outAdjacencyList[nid].size(); }

  // inserts a directed edge from nidFrom to nidTo
  void insertEdge(int nidFrom, int nidTo);

  // returns true if and only if there is an edge from nidFrom to nidTo
  bool isEdge(int nidFrom, int nidTo) {
    return inAdjacencyList[nidTo].count(nidFrom) != 0;
  }

 private:
  // number of vertices in the graph
  int n;

  // adjacency lists for in- resp. out-neighbors of the vertices
  std::vector<std::set<int> > inAdjacencyList;
  std::vector<std::set<int> > outAdjacencyList;
};

class Mapping {
 public:
  // constructor that just initializes the graphs to map
  // want to find a (sub)isomorphism from G to H
  Mapping(Graph G, Graph H) : G(G), H(H){};

  // return number of vertices in G resp. H
  int getSizeG() { return G.vertexCount(); }
  int getSizeH() { return H.vertexCount(); }

  // checks if adding mapping nidg to nidh would be valid
  // checks that neither of the vertices is already mapped and that they satisfy
  // the neighbor condition for the vertices already mapped
  bool areMappable(int nidg, int nidh);

  // adds the nidg -> nidh to the mapping without any sanity checks
  void addToMap(int nidg, int nidh);

  // deletes nidg and the vertex it is mapped to from the mapping
  void deleteFromMap(int nidg);

  bool isFull();

  // used for printing the mapping, eg. std::cout << m << std::endl;
  friend std::ostream& operator<<(std::ostream&, Mapping&);

 private:
  // the considered graphs
  Graph G;
  Graph H;

  // the mapping, for technical reasons in both directions
  std::map<int, int> currentMatchGH;
  std::map<int, int> currentMatchHG;
};

#endif
