#include "Complex.hpp"
#include <iostream>

int main() {

	Complex c;
	
	c.a = 17.0;
	c.b = 8.0;

	std::cout << "Partie reelle: " << c.a << std::endl;
	std::cout << "Partie imaginaire: " << c.b << std::endl;

}

