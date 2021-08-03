#include <cstdio>
#include <iostream>
#include <string>
#include "ecc.h"
#include "rsa.h"
//#include "elgamal.h"

using namespace std;

void ecc_example(){
    int message = 155;
	ECC ecc;
    printf("\nThe Public Key is (%d,%d)\n", ecc.PubKey[0], ecc.PubKey[1]);

    printf("Message: %i\n", message);

	int * encoded = ecc.encodeMessage(message);
    printf("Encoded: %i\n", *encoded);

	int * decoded = ecc.decodeMessage(encoded);
    printf("Decoded: %i\n", *decoded);
}

void rsa_example() {
    RSA rsa(17, 101);

    cout << "p is " << rsa.p << endl;
    cout << "q is " << rsa.q << endl;
    cout << "n is " << rsa.n << endl;
    cout << "e is " << rsa.e << endl;
    cout << "d is " << rsa.d << endl << endl;

    long unsigned int initial = 1312;
    cout << "Initial message is " << initial << endl;
    long unsigned int encoded = rsa.encodeMessage(initial);
    cout << "Encoded message is " << encoded << endl;
    long unsigned int decoded = rsa.decodeMessage(encoded);
    cout << "Decoded message is " << decoded << endl;
}
/*
void elgamal_example(){
    int msg = 384;

    Receiver rec = Receiver();
    Sender sen = Sender(rec);

    cout << "message: " << msg << "\n";
    unsigned long *encoded_parts = Elgamal::encodeMessage(msg, sen.key, sen.shared, sen.q, sen.g);
    cout << "encoded parts: " << encoded_parts[0] << " : " << encoded_parts[1] << "\n";
    unsigned long decoded_msg = Elgamal::decodeMessage(encoded_parts, rec.key, rec.q);
    cout << "decoded message: " << decoded_msg << "\n";


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
*/

int main(){
    rsa_example();
    ecc_example();

    return 0;
}
