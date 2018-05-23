#include <iostream>
#include <math.h>
#include "stirling.hpp"

using namespace std;

long Factorial(int n) {
	// , exercise stirling : implement this function (and return the corresponding value)
	if (n<=1)
	  return (long) 1;
	else
	  return (long) n*Factorial(n-1);
	
}

long Binomial(int n, int k) {
	return Factorial(n)/(Factorial(n-k)*Factorial(k));
}

long Stirling2kind_Explicit(int n, int k) {
	// , exercise stirling : implement this function (and return the corresponding value)
	long somme = 0;
	for (int j=0; j<=k; j++){
	    if ( (k-j)%2 )
	      somme -= Binomial(k,j)*pow(j,n);
	    else
	      somme += Binomial(k,j)*pow(j,n);
	}
	
	long f = Factorial(k);
	
	return somme/f;
}

long Stirling2kind_Recurrence(int n, int k, int& ncalls) {
	// , exercise stirling : implement this function (and return the corresponding value)
	ncalls ++;
	
	if (n==0 && k==0)
	  return 1L;
	
	if (n==0 || k==0)
	  return 0L;
	
	return Stirling2kind_Recurrence(n-1,k, ncalls)*(long)k + Stirling2kind_Recurrence(n-1,k-1,ncalls);
	
	return -1;
}
