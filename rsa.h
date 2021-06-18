#include "utilities.h" // inverse_modulo, gcd, power_modulo, genPseudoRandomInt

class RSA {
    private:
        void init(unsigned long int p, unsigned long int q, unsigned long int e) {
            this->p = p;
            this->q = q;
            this->n = p * q;
            this->e = e;
            this->d = inverse_modulo(e, (p-1)*(q-1));
        }

    public:
        long unsigned int p, q; // two prime numbers
        long unsigned int n; // product of two prime numbers p and q
        long unsigned int e, d; // e*d = 1 (mod (p-1)*(q-1))

        // p and q must be prime and e must be relatively prime with (p-1)*(q-1) and 1 < e < (p-1)*(q-1)
        RSA(unsigned long int p, unsigned long int q, unsigned long int e) {
            init(p, q, e);
        }

        // p and q must be prime
        RSA(unsigned long int p, unsigned long int q) {
            unsigned long int e;
            while (true) {
                e = genPseudoRandomInt(2, (p-1)*(q-1)-1);
                if (gcd(e, (p-1)*(q-1)) == 1) {
                    break;
                }
            }
            init(p, q, e);
        }

        unsigned long encodeMessage(unsigned long message) {
            return power_modulo(message, this->e, this->n);
        }

        unsigned long decodeMessage(unsigned long message) {
            return power_modulo(message, this->d, this->n);
        }

};
