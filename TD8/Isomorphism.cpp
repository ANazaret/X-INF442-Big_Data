#include <iostream>
#include <stdexcept>
#include <map>
#include "Isomorphism.hpp"
#include "mpi.h"
using namespace std;

// Exercice 3
void extendInjection(Mapping &m) {
  // The argument m is (a reference to) a partially-defined injective
  // function G -> H : it may only have images defined for a subset of G.
  // This procedure recursively attempts to extend m to the whole of G,
  // using a backtracking approach.

  if (m.isFull()) {
    return;
  }
  for (int nidg = 0; nidg < m.getSizeG(); nidg++) {
    for (int nidh = 0; nidh < m.getSizeH(); nidh++) {
       if (m.areMappable(nidg, nidh) ){
	  m.addToMap(nidg, nidh);
	  extendInjection(m);
	  if (m.isFull()) {
	    return;
	  }
	  m.deleteFromMap(nidg);
       }
    }
  }
  return;
}

void findIsomorphism(Graph G, Graph H) {
  if (G.vertexCount() != H.vertexCount()) {
    std::cout << "Pas d'isomorphisme" << std::endl;
    return;
  }
  Mapping candidate(G, H);
  extendInjection(candidate);
  if (candidate.isFull())
    std::cout << candidate << std::endl;
  else
    std::cout << "Pas d'isomorphisme" << std::endl;
}

// Exercice 4
void findSubIsomorphism(Graph G, Graph H) {
  Mapping candidate(G, H);
  extendInjection(candidate);
  if (candidate.isFull())
    std::cout << candidate << std::endl;
  else
    std::cout << "Pas de sous-isomorphisme" << std::endl;
}




// Exercice 5
void findSubIsomorphismMPI(Graph G, Graph H) {
  int myrank, size;
  int n = H.vertexCount();

  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Status status;
  
  int imgh;
  if (myrank == 0) {
    // On lance plusieurs recherches r_i mappant chacune 0_g -> i_h
    std::vector<MPI_Request> requests;    
    std::vector<int> to_send;
    for (int i=n-1; i>=n; i--)
      to_send.push_back(i);
    
    
    
    //std::vector<int*> subisomorphisms;
    
    int reponse;
    //On envoie initialement aux esclaves
    for (int dest=1; dest<std::min(size,n+1); dest++){
      int h0 = to_send.pop_back();
      MPI_Send(&h0, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
      //int* res = new int[n];
      MPI_Request req;
      //subisomorphisms.push_back(res);
      //MPI_Irecv(res, n, MPI_INT, dest, 0, MPI_COMM_WORLD, req);
      
      MPI_Irecv(&reponse, 1, MPI_INT, dest, 0, MPI_COMM_WORLD, req);
      
      requests.push_back(req);
    }
    
    bool notfinished = true;
    while (notfinished){
      notfinished = false;
      //On check les r2ponses et on renvoie si ils ont repondu
      for (int i=0; i<requests.size(); i++){
	int flag;
	MPI_Test(&requests[i], &flag, &status);
	if (flag){
	  // Le processus i+1 a repondu
	  //
	  
	  //Si il reste des trucs a faire, on renvoie
	  if (to_send.size()){
	    int h0 = to_send.pop_back();
	    MPI_Send(&h0, 1, MPI_INT, i+1, 0, MPI_COMM_WORLD);
	    //MPI_Irecv(&subisomorphisms[i], n, MPI_INT, i+1, 0, MPI_COMM_WORLD, &requests[i]);
	    MPI_Irecv(&reponse, 1, MPI_INT, i+1, 0, MPI_COMM_WORLD, &requests[i]);
	    notfinished = true;
	  }
	  
	} else {
	    notfinished = true;	  
	}
      }
    
      
    }
    
  } else {
    int* res = new int[n];
    while (true){
      MPI_Recv(&imgh, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
      
      res[0] = -1;
      Mapping candidate(G, H);
      
      if (candidate.areMappable(0, imgh) ){
	  candidate.addToMap(0, imgh);
	  extendInjection(candidate);
	  if (candidate.isFull()) {
	    std::cout << candidate << std::endl;
	  }
      }
      MPI_Send(res, n, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    
    delete [] res;
  }
  return;
}
