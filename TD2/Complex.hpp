#include <iostream>

class Complex {

public:

	Complex();
	Complex(double a, double b);
	~Complex();

	double module();
	
	double a;
	double b;

};

std::ostream& operator<<(std::ostream& s, const Complex& c);