#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void add_marble(int& color, char c);
char draw_marble(int& r, int& g, int& b);
int count_marbles(int r, int g, int b);

int main() {
    srand(time(NULL));
    int r = 0;
    int g = 0;
    int b = 0;

    return 0;
}

void add_marble(int& r, int& g, int& b, char c) {
    if(c == 114) { //r
        r++;
    }
    else if(c == 103) { //g
        g++;
    }
    else if(c == 98) { //b
        b++;
    }
}

char draw_marble(int& r, int& g, int& b) {
    int n = count_marbles(r, g, b);
    if(!n) {
        cout << "There aren't any marbles in the bag!" << endl;
        return 'x';
    }
    int prob = rand() % n + 1; //random number from 1 to number of marbles
    if(prob <= r) {
        r--;
        return 'r';
    }
    else if(prob r + g) {
        g--;
        return 'g';
    }
    else {
        b--;
        return 'b';
    }
}

//adds the three integers together
int count_marbles(int& r, int& g, int& b) {
    return r + g + b;
}