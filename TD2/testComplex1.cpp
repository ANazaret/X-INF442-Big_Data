#include "Complex.hpp"
#include <iostream>

int main() {

	Complex c(17.0, 8.0);

	std::cout << "Partie reelle: " << c.a << std::endl;
	std::cout << "Partie imaginaire: " << c.b << std::endl;

}

