/*
 * Header file with prototypes of userful functions.
 * Definition of that function can be found in utilities.cpp
 *
 */


// GCD of two positive integers using Euclidian algorithm
int gcd(int x, int y);

// Compute and return a^(-1) mod b using extended Euclidian algorithm.
// Precondition: a and b must be positive integers that are co-prime and b > 1.
int inverse_modulo(int a, int b);

// compute and return base^exponent % mod.
// Parameters base, exponent and mod must be positive whole numbers.
unsigned long power_modulo(unsigned long base, unsigned long exponent, unsigned long mod);

// generate pseudorandom positive integer from range [min, max] (min and max are included).
// Parameters min and max must be positive whole numbers.
unsigned long genPseudoRandomInt(unsigned long min, unsigned long max);

