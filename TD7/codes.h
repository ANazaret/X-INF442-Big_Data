#pragma once

// Conversion between characters (assumed to be in {A,...,Z})
// and unsigned ints (assumed to be in {0,...,25})
// (A <-> 0, B <-> 1, ..., Z <-> 25).
char codeToChar(unsigned int);
unsigned int charToCode(char);

// For exercise 5: random sampling of unsigned ints in {0..25}
unsigned int randomCode( );

// random sampling of unsigned ints in {0..25} prime to 26
unsigned int randomInvertibleCode( );

// inversion of codes mod 26 (returns 0 if not invertible)
unsigned int inverse(unsigned int);
