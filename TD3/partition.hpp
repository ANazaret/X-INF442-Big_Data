/*
  Filename: partition.hpp
  Author: Leo Liberti
  Purpose: header file for the Partition class
  Source: GNU C++
  History:
    150418 work started
*/

// the #ifndef ... #endif is a C/C++ preprocessor block; its purpose
// is to allow users of the header file to include it many times from
// different files, while the actual inclusion is only carried out once
// to prevent compiler errors about declaring the same symbols more than
// once. This is achieved by #defining the tag IMAGEH only if it is not
// defined yet; this means that in a given compiler call, the inside
// of the #ifndef block is only read once, even if this file is referenced
// multiple times by many .cpp files
#ifndef PARTITIONH
#define PARTITIONH

// STL includes
#include <iostream>
#include <vector>
// C library includes wrapped by STL
#include <cstdlib>
#include <cmath>
#include <cassert>

class Partition {
  //// public methods&attributes can be accessed directly from calling methods
 public:
  // constructor
  Partition(std::vector<std::vector<double> >& X, int numClusters);
  // copy constructor
  Partition(Partition& P);
  // assignment overloading
  Partition& operator=(Partition& P);
  // print clusters
  void printClusters(void);
  //// methods for k-Means
  // Forgy's random centroid choice initialization method
  void Forgy(void);
  // best of s runs of Forgy's initialization
  void initialize(int s);
  // re-assign the points to the closest centroids
  void reassign(void);
  // update the centroids
  void updateCentroids(void);
  // sum of all inter-cluster distances
  double interClusterDistances(void);
  // Lloyd's iteration
  double iteration(void);

  //// simple get interface with private data
  int getDimension(void) const { return d; }
  int getNumberOfPoints(void) const { return n; }
  int getNumberOfClusters(void) const { return k; }
  std::vector<std::vector<double> >& getData(void) const { return point; }
  std::vector<std::vector<double> >& getCentroids(void) { return centroid; }
  std::vector<std::vector<int> >& getClusters(void) { return cluster; }

  //// most attributes are usually private, access through interface:
  ////   this allows decoupling of interface from actual implementation,
  ////   can make implementation more efficient without having to change
  ////   all calling code
 private:
  //// data structures for k-means
  // dimensionality of embedding space
  int d;
  // number of points in set
  int n;
  // number of clusters
  int k;
  // points, i.e. data; notice this is a reference, so there's no
  //   duplication of large amounts of data (see the constructor definition
  //   in partition.cpp::Partition::Partition() to see how to initialize
  //   a reference in a class)
  std::vector<std::vector<double> >& point;
  // centroids
  std::vector<std::vector<double> > centroid;
  // assignment cluster -> point index
  std::vector<std::vector<int> > cluster;
};

#endif
