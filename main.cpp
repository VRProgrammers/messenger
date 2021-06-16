#include <iostream>
#include "utilities.h"

using namespace std;

int main() {
    int x, y;
    cin >> x >> y;
    cout << inverse_modulo(x, y) << endl;
}
