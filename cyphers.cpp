#include <cstdio>
#include <iostream>
#include <string>
#include "ecc.h"
#include "rsa.h"
#include "elgamal.h"

using namespace std;

void ecc_example(){
	ECC ecc;
    cout << "Public Key: " << ecc.PubKey[0] << " : " << ecc.PubKey[1] << endl << endl;

    int message = 312;
    cout << "Initial message: " << message << endl;

	int * encoded = ecc.encodeMessage(message);
    cout << "Encoded message: ";
    printf("(%i, %i), (%i, %i)\n", *encoded, *(encoded+1), *(encoded+2), *(encoded+3));

	int decoded = ecc.decodeMessage(encoded);
    cout << "Decoded message: " << decoded << endl;
}

void rsa_example() {
    RSA rsa(17, 101);

    cout << "p is " << rsa.p << endl;
    cout << "q is " << rsa.q << endl;
    cout << "n is " << rsa.n << endl;
    cout << "e is " << rsa.e << endl;
    cout << "d is " << rsa.d << endl << endl;

    long unsigned int initial = 1312;
    cout << "Initial message: " << initial << endl;

    long unsigned int encoded = rsa.encodeMessage(initial);
    cout << "Encoded message: " << encoded << endl;

    long unsigned int decoded = rsa.decodeMessage(encoded);
    cout << "Decoded message: " << decoded << endl;
}

void elgamal_example(){

    Receiver rec = Receiver();
    Sender sen = Sender(rec);

    int message = 284;
    cout << "Initial message: " << message << endl;

    unsigned long *encoded = Elgamal::encodeMessage(message, sen.key, sen.shared, sen.q, sen.g);
    cout << "Encoded message: " << encoded[0] << " : " << encoded[1] << endl;

    unsigned long decoded = Elgamal::decodeMessage(encoded, rec.key, rec.q);
    cout << "Decoded message: " << decoded << endl;

}

void test_key_generation(){

    unsigned long q, g, B, receiver_key;

    unsigned long *keys = Elgamal::generate_receiver_keys();
    q = keys[0];
    g = keys[1];
    B = keys[2];
    receiver_key = keys[3];

    unsigned long shared;
    unsigned long sender_key;

    keys = Elgamal::generate_sender_keys(q, B);
    sender_key = keys[0];
    shared = keys[1];

    cout << "q, g, gcd: " << q << ", " << g << ", " << gcd(q, g) << "\n";
    cout << "shared: " << shared << "\n";
}


int main(){
    cout << "RSA" << endl;
    rsa_example();
    cout << endl << endl << "ECC" << endl;
    ecc_example();
    cout << endl << endl << "ElGamal" << endl;
    elgamal_example();

    return 0;
}
