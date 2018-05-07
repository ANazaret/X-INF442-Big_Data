/*
  Filename: main.cpp
  Author: Leo Liberti
  Purpose: the main() driver function for the JLL TD
  Source: GNU C++
  History:
    150418 work started
*/

/******* user-configurable parameters *******/

// output some debug messages on cerr
bool debug = 1;

// we'll rescale all images to small squares in RGB colors
static int NEW_SIZE = 300;    // new size for horizontal/vertical
static int KEEP_SIZE = -100;  // don't change the depth (no 3D images)
static int NEW_COLORS = 3;    // make BW into colors

// number of clusters
static int numberOfClusters = 3;

// infinity
double infinity = 1E+30;

// tolerance
double zero = 0;

// number of multistart Forgy initializations
int multiStartForgy = 300;

// JL epsilon
static double JLepsilon = 0.15;

// JL constant
static double JLconstant = 4;

/******* includes *******/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <sys/time.h>

#include "CImg.h"
#include "randomsample.hpp"
#include "mathtools.hpp"
#include "partition.hpp"

/******* main() code *******/
int main(int argc, char** argv) {
  // read in all symbols from STL and CImg library
  using namespace std;
  using namespace cimg_library;

  // time tasks: tic is the start, toc is the end, time is (toc-tic)
  clock_t tic, toc, globtic, globtoc;

  // initialize randomizer with time of the day seed
  // (don't try to understand this code snippet, just accept it...)
  struct timeval theTV;
  struct timezone theTZ;
  gettimeofday(&theTV, &theTZ);
  srandom(theTV.tv_usec);

  // start the global clock
  globtic = clock();

  // this is the return code we pass back to the operating system on exit
  int ret = 0;

  // the dimensionality of the full space
  int d;

  // the dimensionality of the projected space
  int projd;

  // the data set X: images as (3 x #pixels)-dimensional vectors
  vector<vector<double> > X;

  // examine calling command line
  if (argc < 2) {
    cout << argv[0] << ": syntax error: syntax is:" << endl;
    cout << "   " << argv[0] << " imgfile1.jpg imgfile2.jpg ..." << endl;
    ret = 1;
    exit(ret);
  }
  
  
  // store the image vectors corresponding to filenames passed on command line
  for (int c = 1; c < argc; ++c) {
    try {
      // try reading the image
      CImg<unsigned char> img(argv[c]);
      // if we're here, reading was successful: resize
      img.resize(NEW_SIZE, NEW_SIZE, KEEP_SIZE, NEW_COLORS);
      // transform into vector of doubles
      vector<double> Xcol;
      for (CImg<unsigned char>::iterator pixIt = img.begin();
           pixIt != img.end(); ++pixIt) {
        Xcol.push_back(((double)*pixIt) / 255.0);
      }
      X.push_back(Xcol);
    } catch (CImgException& e) {
      // some errors in reading the image
      cerr << argv[0] << ": CImg error while reading " << argv[c] << endl;
      ret = 2;
      exit(ret);
    }
  }

  // output configuration
  cout << argv[0] << ": configuration for this run:" << endl;
  cout << "  images rescaled to " << NEW_SIZE << " x " << NEW_SIZE << endl;
  cout << "  number of clusters: " << numberOfClusters << endl;
  cout << "  number of multistart runs of Forgy's initialization: "
       << multiStartForgy << endl;
  cout << "  JL epsilon: " << JLepsilon << ", JL factor: " << JLconstant
       << endl;

  // run k-means in high dimension
  d = X[0].size();  // dimension of the original image vector space
  cout << argv[0] << ": k-means clustering in " << d << " dimensions" << endl;
  tic = clock();
  Partition P(X, numberOfClusters);
  double cost = P.iteration();
  toc = clock();
  P.printClusters();
  cout << "sum of intra-cluster distances = " << cost << endl;
  cout << argv[0] << ": elapsed CPU (original k-means) = "
       << (toc - tic) / ((float)(CLOCKS_PER_SEC)) << "s" << endl;

  //// Johnson-Lindenstrauss lemma
  projd = d;
  // dimension of the projected space: projd is O(eps^-2 * log(n))
  projd = (int)round(JLconstant * log(X.size()) / (JLepsilon * JLepsilon));
  if (projd >= d) {
    cout << argv[0] << ": cannot run JL: proj dim = " << projd
         << " > dim = " << d << endl;
    exit(3);
  }

  tic = clock();

  // sample JL projection matrix
  // compute the matrix
  vector<vector<double> > JL = JLProjectionMatrix(d, projd);

  // actions of the master process (or only proc if sequential code)
  toc = clock();
  cout << argv[0] << ": elapsed CPU (JLL sampling)  = "
       << (toc - tic) / ((float)(CLOCKS_PER_SEC)) << "s" << endl;

  // matrix product: project data set in lower dimensional space
  tic = clock();
  vector<vector<double> > projX = MatrixProduct(JL, X);
  toc = clock();
  cout << argv[0] << ": elapsed CPU (matrix product)  = "
       << (toc - tic) / ((float)(CLOCKS_PER_SEC)) << "s" << endl;

  // run k-means in projected dimension
  cout << argv[0] << ": k-means clustering in " << projd << " dimensions"
       << endl;
  tic = clock();
  Partition projP(projX, numberOfClusters);
  double JLcost = projP.iteration();
  toc = clock();
  projP.printClusters();
  cout << "sum of intra-cluster distances = " << JLcost << endl;
  cout << argv[0] << ": elapsed CPU (projected k-means)  = "
       << (toc - tic) / ((float)(CLOCKS_PER_SEC)) << "s" << endl;

  // are distances well-approximated?
  vector<vector<double> > EDM = sqEDM(X);
  vector<vector<double> > projEDM = sqEDM(projX);
  int n = EDM.size();
  double avgerr = 0;
  double maxerr = 0;
  double currerr = 0;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      currerr = fabs(EDM[i][j] / projEDM[i][j] - 1);
      if (currerr > maxerr) {
        maxerr = currerr;
      }
      avgerr += currerr;
    }
  }
  avgerr /= n * n;
  cout << argv[0] << ": JL epsilon = " << JLepsilon << "; max err = " << maxerr
       << "; avg err = " << avgerr << endl;

  // total (real) CPU time
  globtoc = clock();
  cout << argv[0] << ": total CPU time = "
       << (globtoc - globtic) / ((float)(CLOCKS_PER_SEC)) << endl;

  return ret;
}
