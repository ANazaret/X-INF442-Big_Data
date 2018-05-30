#include "codes.h"
#include <cstdlib>

static const unsigned int invertibles[12] = {
  1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25
};

static const unsigned int inverses[26] = {
  0, 1, 0, 9, 0, 21, 0, 15, 0, 3, 0, 19, 0, 0, 0, 7, 0, 23, 0, 11, 0, 5, 0, 17, 0, 25 
};

unsigned int charToCode(const char x) {
  return ((unsigned int)(x - 'A')) % 26;
}

char codeToChar(unsigned int s) {
  return 'A' + (char)s;
}

unsigned int randomCode( ) {
  return std::rand( ) % 26;
}

unsigned int randomInvertibleCode( ) {
  return invertibles[std::rand( ) % 12];
}

unsigned int inverse(unsigned int c) {
  return inverses[c % 26];
}
