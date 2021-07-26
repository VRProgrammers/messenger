#include <iostream>
#include <string>
#include "rsa.h" // RSA
#include "biginteger.h" // BigInteger

using namespace std;

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

void biginteger_example() {
    string strNum1, strNum2;
    cin >> strNum1;
    cin >> strNum2;
    BigInteger* integer1 = new BigInteger(strNum1);
    BigInteger* integer2 = new BigInteger(strNum2);
    BigInteger* res = integer1->add(integer2);
    cout << res->toStringBin() << endl;
}

int main() {
    biginteger_example();
    return 0;
}
