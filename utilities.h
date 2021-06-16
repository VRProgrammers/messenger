// GCD of two positive integers using Euclidian algorithm
int gcd(int x, int y) {
    while (y != 0) {
        int r = x % y;
        x = y;
        y = r;
    }
    return x;
}

// Compute and return a^(-1) mod b using extended Euclidian algorithm.
// Precondition: a and b must be positive integers that are relatively prime and b > 1.
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
