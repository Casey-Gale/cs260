#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int num_iterations = 157680000; // number of seconds in 5 years
    long double chance = .9999999975; // chance to survive every second
    // __float128 chance = .99;

    cout << scientific; // set cout to use scientific notation

    cout << "Initial chance: " << chance << "\n";
    double cap = log2(num_iterations);

    for(long i = 0; i < cap; i++) { // approximate chance by squaring the current chance and halving the number of iterations left. results in log2 iterations

        chance = chance * chance;
        cout << "Intermediate chance: [" << i << "] " << chance << "\n";
    }

    cout << "Final chance: " << chance << "\n"; // final chance to be alive after 5 years

    return 0;
}