#include <iostream>

int main(int argc, char** argv)
{
  // lecture de la taille de la matrice
    
  int n = 0;
  int m = 0;
  
  std::cin >> n;
  std::cin >> m;

  
  // lecture de la matrice
    
  int** matrice = 0;
  matrice = new int*[n];
  
  for (int i=0; i<n; i++){
    matrice[i] = new int[m];
    for (int j=0; j<m; j++){
      std::cin >> matrice[i][j];
    }      
  }
  
  for (int j=0; j<m; j++){
    for (int i=0; i<n; i++){
      std::cout << matrice[i][j];
      if (i<n-1)
	std::cout << " ";
    }      
    if (j<n-1)
	std::cout << std::endl;
  }
  
  return 0;
}
