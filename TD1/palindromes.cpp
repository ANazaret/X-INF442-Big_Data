#include <iostream>
#include <string>

using namespace std;

bool estUnPalindrome(string& mot)
{
  unsigned int nombreDeLettres = (unsigned int) mot.length();
  
  for (unsigned int i = 0; i <= nombreDeLettres / 2; i++)
    {
      // comparons les lettres a des positions symétriques
      if (mot[i] != mot[nombreDeLettres - i - 1])
	return false;
      
    }
  return true; // le mot est un palindrome
}

int main(int argc, char** argv)
{
  unsigned int nombreDeMots = 0;
	
  std::cin >> nombreDeMots;
  for (unsigned int i = 0; i < nombreDeMots; i++)
    {
      std::string mot;
      std::cin >> mot;
      
      bool resultat = estUnPalindrome(mot);
      if (resultat)
	std::cout << "Le mot est un palindrome" << std::endl;
      else
	std::cout << "Le mot n'est pas un palindrome" << std::endl;
    }
  return 0;
}
