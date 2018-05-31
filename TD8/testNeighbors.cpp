#include <iostream>
#include <vector>

#include "computeNeighbors.hpp"

void textExpectedVector(int node, int numberNodes, std::vector<int> expected) {
  std::cout << "expected out-neighbors of " << node << " : ";
  printNeighbors(expected);

  std::cout << "computed out-neighbors are ";
  printNeighbors(computeOutNeighbors(node, numberNodes));
  std::cout << std::endl;
}

void textExpected(int node, int expectedPredecessor) {
  std::cout << "expected predecessor of " << node << " : "
            << expectedPredecessor << std::endl;
  std::cout << "computed predecessor is " << computePredecessor(node)
            << std::endl
            << std::endl;
}

int main(int argc, char *argv[]) {
  std::cout << "Testing some predecessors" << std::endl;
  textExpected(0, 0);
  textExpected(1, 0);
  textExpected(3, 1);
  textExpected(15, 7);
  textExpected(8, 0);

  std::cout << "Testing some out-neighbors" << std::endl;
  std::vector<int> expected;
  expected.push_back(1);
  expected.push_back(2);
  expected.push_back(4);
  expected.push_back(8);
  textExpectedVector(0, 16, expected);

  expected.clear();
  expected.push_back(3);
  expected.push_back(5);
  expected.push_back(9);
  textExpectedVector(1, 16, expected);

  expected.clear();
  expected.push_back(7);
  expected.push_back(11);
  textExpectedVector(3, 16, expected);

  expected.clear();
  textExpectedVector(8, 16, expected);
}
