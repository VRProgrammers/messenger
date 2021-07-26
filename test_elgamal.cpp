#include <elgamal.h>
#include <iostream>

using namespace std;

void test_send(unsigned long msg);
void test_key_generation();

int main()
{
    srand(time(0));

    unsigned long msg = 102;
    test_send(msg);

    test_key_generation();
}

void test_send(unsigned long msg)
{
    Receiver rec = Receiver();
    Sender sen = Sender(rec);

    cout << "message: " << msg << "\n";
    unsigned long *encoded_parts = Elgamal::encodeMessage(msg, sen.key, sen.shared, sen.q, sen.g);
    cout << "encoded parts: " << encoded_parts[0] << " : " << encoded_parts[1] << "\n";
    unsigned long decoded_msg = Elgamal::decodeMessage(encoded_parts, rec.key, rec.q);
    cout << "decoded message: " << decoded_msg << "\n";
}

void test_key_generation()
{
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