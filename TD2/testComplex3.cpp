#include "Complex.hpp"
#include <iostream>

int main() {
    
    Complex a(17.0, 0.0);
    Complex b(3, -4);
    
    std::cout << a.module() << std::endl;
    std::cout << b.module() << std::endl;
    
}

