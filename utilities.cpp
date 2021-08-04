#include <stdlib.h> // rand()
#include <cstdlib> // RAND_MAX
#include <math.h>

int gcd(int x, int y) {
    while (y != 0) {
        int r = x % y;
        x = y;
        y = r;
    }
    return x;
}

int inverse_modulo(int a, int b) {
    int s[2] = {1, 0};
    int t[2] = {0, 1};

    int x = a, y = b;

    while (y != 1) {
        int q = x / y, r = x % y;
        x = y;
        y = r;

        int newS = s[0] - q*s[1];
        int newT = t[0] - q*t[1];
        s[0] = s[1];
        t[0] = t[1];
        s[1] = newS;
        t[1] = newT;
    }

    int res = s[1] % b;
    if (res >= 0)
        return res;
    return res + b;
}

unsigned long power_modulo(unsigned long base, unsigned long exponent, unsigned long mod) {
    unsigned long res = 1;
    unsigned long power = base;
    while (exponent > 0) {
        if ((exponent & 1) == 1) {
            res = (res * power) % mod;
        }
        power = (power * power) % mod;
        exponent >>= 1;
    }
    return res;
}

unsigned long genPseudoRandomInt(unsigned long min, unsigned long max) {
    return round(((double)rand() / RAND_MAX) * (max - min) + min);
}
