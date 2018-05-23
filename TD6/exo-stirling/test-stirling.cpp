#include <iostream>
#include "stirling.hpp"

using namespace std;

int main() {

	cout << "Test numbers of Stirling, Q1 and Q2" << endl;

	cout << " Factorials n!" << endl;
	for (int n=0; n<7; n++) {
		cout << "  " << n << "! = " << Factorial(n) << endl;
	}
	
	cout << " Binomials (n, k)" << endl;
	for (int n=4; n<6; n++) {
		for (int k=2; k<6; k ++) {
			cout << "  (" << n << ", " << k << ") = " << Binomial(n, k) << endl;
		}
	}

	cout << " Stirling numbers of 2nd kind {n, k}" << endl;
	for (int n=4; n<6; n++) {
		for (int k=2; k<6; k ++) {
			int ncalls = 0;
			int expl = Stirling2kind_Explicit(n, k);
			int recur = Stirling2kind_Recurrence(n, k, ncalls);
			cout << "  {" << n << ", " << k << "} = " << expl << " (explicit) = " << recur << " (recursive, in " << ncalls << " calls)" << endl;
		}
	}
}