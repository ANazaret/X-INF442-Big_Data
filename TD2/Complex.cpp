#include "Complex.hpp"
#include <math.h>

using namespace std;

Complex::Complex() {

  a = 0.0;
  b = 0.0;

}

Complex::Complex(double a, double b){
  this->a = a;
  this->b = b;
}


double Complex::module(){
  return sqrt(a*a+b*b);
}


Complex::~Complex() {}





ostream& operator << (ostream& s, const Complex& c){
  s << c.a;
  
  if (c.b < 0)
    s << c.b << "*i";
  
  if (c.b > 0)
    s << "+" << c.b << "*i";
  
  
  return s;
}