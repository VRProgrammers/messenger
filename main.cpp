#include <iostream>
#include "rsa.h" // RSA

using namespace std;

int main() {
    long unsigned int x = (long long unsigned)-1;
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
