/**
 * Implements ElGamal encryption system
 * @file elgamal.h
 */

#include "utilities.h"

/**
 * Struct with functions to generate keys and
 * encode/decode message.
 * @see Receiver
 * @see Sender
 */
struct Elgamal
{
    /**
     * Generate keys for message receiver.
     * @return Pointer to array with keys for receiver.
     * @see Receiver
     */
    static unsigned long *generate_receiver_keys()
    {
        unsigned long q, g;
        // if g and q are coprime, s = g ^ (a * b) and q are coprime, too
        // in this way precondition, needed to decrypt message, is satisfied
        do
        {
            q = genPseudoRandomInt(pow(10, 5), pow(10, 7));
            g = genPseudoRandomInt(2, q);
        } while (gcd(g, q) != 1);
        unsigned long key = genPseudoRandomInt(2, q);
        unsigned long B = power_modulo(g, key, q);
        static unsigned long keys[] = {q, g, B, key};
        return keys;
    }
    
    /**
     * Generate keys for message sender
     * @return Pointer to array with keys for sender
     * @see Sender
     */
    static unsigned long *generate_sender_keys(unsigned long q, unsigned long B)
    {
        unsigned long key = genPseudoRandomInt(2, q);
        unsigned long shared = power_modulo(B, key, q);
        static unsigned long keys[] = {key, shared};
        return keys;
    }
    
    /**
     * Encode message
     * @param msg A number we want to encode
     * @param sender_key Private sender's key
     * @param shared So called "shared" between sender and receiver key.
     * @param q Order of cyclic group used in algorithm
     * @param g Random number from this group
     * @return Two numbers that represent encoded message
     * \pre q and g are coprime. Otherwise, message can't be decrypted
     */
    static unsigned long *encodeMessage(unsigned long msg, unsigned long sender_key, unsigned long shared, unsigned long q, unsigned long g)
    {
        unsigned long A = power_modulo(g, sender_key, q);
        unsigned long X = (msg * shared) % q;
        static unsigned long encoded_parts[] = {A, X};
        return encoded_parts;
    }

    /**
     * Decode message
     * @param encoded_parts Two numbers that represent encoded message
     * @param receiver_key Private receiver's key
     * @param q Order of cyclic group used in current run of algorithm
     * @return A number that is decrypted message
     */
    static unsigned long decodeMessage(unsigned long encoded_parts[], unsigned long receiver_key, unsigned long q)
    {
        unsigned long A = encoded_parts[0], X = encoded_parts[1];
        unsigned long shared = power_modulo(A, receiver_key, q);
        unsigned long inverse_s = inverse_modulo(shared, q);
        unsigned long M = (X * inverse_s) % q;
        return M;
    }
};

/**
 * Holds receiver's public and private keys
 * q - Order of cyclic group used in current run of algorithm
 * g - Random number from this group
 * B - receiver's part of "shared" secret key
 * key - Private receiver's key
 */
struct Receiver
{
    Receiver()
    {
        unsigned long *keys = Elgamal::generate_receiver_keys();
        q = keys[0];
        g = keys[1];
        B = keys[2];
        key = keys[3];
    }

    unsigned long q, g, B;
    unsigned long key;
};

/**
 * Holds sender's public and private keys
 * q - Order of cyclic group used in current run of algorithm
 * g - Random number from this group
 * B - receiver's part of "shared" secret key
 * shared - "Shared" secret key
 * key - Sender's private key
 */
struct Sender
{
    Sender(Receiver receiver)
    {
        q = receiver.q, g = receiver.g, B = receiver.B;
        unsigned long *keys = Elgamal::generate_sender_keys(q, B);
        key = keys[0];
        shared = keys[1];
    }

    unsigned long q, g, B;
    unsigned long shared;
    unsigned long key;
};
