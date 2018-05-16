#include <iostream>
#include <limits>
#include "knn.h"

using namespace std;

void printArray(int k, int* array) {
      for(int i = 0; i < k; i++) {
        cout <<" " <<array[i];
      }
      cout <<endl;
}

void printLabelsDistances(int k, int* labels, int* distances) {
  cout <<"labels:      ";
  printArray(k, labels);
  cout <<"distances:   ";
  printArray(k, distances);
}

int main(int argc, char* argv[]) {

  int k = 5;
  int labels_0[] =    { 0, 0, 0, 0, 1 };
  int distances_0[] = { 1, 3, 5, 7, 8 };
  int labels_1[] =    { 1, 1, 1, 0, -1 };
  int distances_1[] = { 2, 3, 5, 9, numeric_limits<int>::max() };
  int labels_ref[] =    {0, 1, 0, 1, 0};
  int distances_ref[] = {1, 2, 3, 3, 5};

  cout <<endl <<"%%%%%%%%%%%%%%%%%";
  cout <<endl <<"%%%%% INPUTS %%%%";
  cout <<endl <<"%%%%%%%%%%%%%%%%%";
  cout <<endl <<"Local:" <<endl;
  printLabelsDistances(k, labels_0, distances_0);
  cout <<endl <<"Other:" <<endl;
  printLabelsDistances(k, labels_1, distances_1);
 
  cout <<endl <<"%%%%%%%%%%%%%%%%%";
  cout <<endl <<"%%%% OUTPUTS %%%%";
  cout <<endl <<"%%%%%%%%%%%%%%%%%";
  Knn knn(NULL, k);
  knn.Merge(labels_0, distances_0, labels_1, distances_1);
  cout <<endl <<"Local:" <<endl;
  printLabelsDistances(k, labels_0, distances_0);
  cout <<endl <<"Other:" <<endl;
  printLabelsDistances(k, labels_1, distances_1);

  return 0;
}
