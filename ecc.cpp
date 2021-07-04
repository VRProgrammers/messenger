#include "ecc.h"

int main(){
	/*
	 * Currently, ECC functions are mostly based on the following sources:
	 *   https://cryptobook.nakov.com/asymmetric-key-ciphers/elliptic-curve-cryptography-ecc
	 *   https://cyberleninka.org/article/n/436686
	 *   https://stackoverflow.com/questions/56815398/implementation-of-elliptic-curve-cryptography-in-c
	 */

	ECC ecc;
	ecc.encode();
	ecc.decode();
}
