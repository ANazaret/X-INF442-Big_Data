#include <iostream>
#include <vector>

int getHighestBit(int x){
  int i=-1;
  while (x){
    x >>= 1;
    i++;
  }
  
  return i;  
}


// messages are received from node with highest 1-bit flipped to 0
int computePredecessor(int node) {
  int hb = getHighestBit(node);
  int mask = 0;
  for (int i=0; i<hb; i++){
   mask <<= 1;
   mask += 1;
  }
  return node&mask;
}

// compute neighbors to communicate to
std::vector<int> computeOutNeighbors(int node, int numberNodes) {
  std::vector<int> neighbors;

  // first bit to flip
  int flipbit = (node - computePredecessor(node)) * 2;
  if (!flipbit)
    flipbit = 1;
  int next = node|flipbit;
  while(next < numberNodes){
    neighbors.push_back(next);
    flipbit <<= 1;
    next = node|flipbit;
  }

  return neighbors;
}

// print neighbor list for debugging
void printNeighbors(std::vector<int> neighbors) {
  for (std::vector<int>::iterator iter = neighbors.begin();
       iter != neighbors.end(); iter++) {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
}
