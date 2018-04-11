#include <iostream>

using namespace std;

int** lireMatrice(int& n, int &m){
  cin >> n;
  cin >> m;
  
  int** matrice = 0;
  matrice = new int*[n];
  
  for (int i=0; i<n; i++){
    matrice[i] = new int[m];
    for (int j=0; j<m; j++){
      std::cin >> matrice[i][j];
    }      
  }
  
  return matrice;  
}

int main(int argc, char** argv)
{
   
  // lecture de la matrice
  int nA, mA;
  int** A = lireMatrice(nA, mA);
 
  int nB, mB;
  int** B = lireMatrice(nB, mB);
  
  for (int i=0; i<nA; i++){
    for (int j=0; j<mB; j++){
      int temp = 0;
      for (int k=0; k<mA; k++)
	temp += A[i][k]*B[k][j];
      
      
      std::cout << temp;
      if (j<mB-1)
	std::cout << " ";
    }      
    std::cout << std::endl;
  }
  
  return 0;
}
