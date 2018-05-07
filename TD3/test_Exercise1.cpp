/* test_Exercise1.cpp
 *
 * author: Sameh Mohamed
 * date: 7/02/2016
 * Uses k-means code from partition.cpp to cluster the iris dataset.
 */
// STL includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
// C library includes wrapped by STL
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <climits>
// C library includes
#include <time.h>
#include <sys/time.h>

#include "mathtools.hpp"
#include "partition.hpp"

/***** user-configurable data *****/

// output some debug messages on cerr
bool debug = 1;

// maximum number of fields read from CSV records
static int maxCsvFld = 4;

// number of clusters
static int numberOfClusters = 3;

// infinity
double infinity = 1E+30;

// tolerance
double zero = 0;

// number of multistart Forgy initializations
int multiStartForgy = 300;

/***** the main() driver *****/
int main(int argc, char** argv) {
  using namespace std;
  int ret = 0;

  // initialize randomizer with time of the day seed
  // (don't try to understand this code snippet, just accept it...)
  struct timeval theTV;
  struct timezone theTZ;
  gettimeofday(&theTV, &theTZ);
  srandom(theTV.tv_usec);

  vector<vector<double> > irisData;
  //// read the iris CSV file
  ifstream irisFile("data/Iris.csv");
  while (!irisFile.eof()) {
    // read one record at a time
    string record;
    getline(irisFile, record);
    stringstream inputStringStream(record);
    vector<double> irisRecord;
    // read the first maxCsvFld fields from record
    for (int field = 0; field < maxCsvFld; ++field) {
      string value;
      getline(inputStringStream, value, ',');
      if (!inputStringStream.good()) {
        break;
      }
      // convert the field value from string to double
      stringstream typeConvertor(value);
      double dValue;
      typeConvertor >> dValue;
      // save the value in the record
      irisRecord.push_back(dValue);
    }
    if (!irisRecord.empty()) {
      // if record not empty, save in database
      irisData.push_back(irisRecord);
    }
  }

  // create the Partition object
  Partition P(irisData, numberOfClusters);

  double cost = P.iteration();
  P.printClusters();
  cout << "sum of intra-cluster distances = " << cost << endl;

  return ret;
}
