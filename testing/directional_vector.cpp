#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class gridVector {
    private:
    public: 
        int gridX;
        int gridY;
        int angle; // counterclockwise angle from the positive x axis in degrees
        gridVector();
        void turn(char direction);
        void forward();
        void print();
};

gridVector::gridVector() {
    this->gridX = 0;
    this->gridY = 0;
    this->angle = 0;
}

// turns angle by 90 using argument 'l' or 'r'. any other char input will do nothing
void gridVector::turn(char direction) {
    if(direction == 'l') {
        if(this->angle == 270) {
            this->angle = 0;
        }
        else {
            this->angle+= 90;
        }
    }
    else if(direction == 'r') {
        if(this->angle == 0) {
            this->angle = 270;
        }
        else {
            this->angle-= 90;
        }
    }
}

void gridVector::forward() {
    if(this->angle == 0) {
        this->gridX++;
    }
    else if(this->angle == 90) {
        this->gridY++;
    }
    else if(this->angle == 180) {
        this->gridX--;
    }
    else {
        this->gridY--;
    }
}

void gridVector::print() {
    cout << "(" << this->gridX << "," << this->gridY << ") facing " << angle << endl;
}

int main() {
    gridVector v;
    v.print();
    char c = ' ';
    while(c != 'q') {
        cout << "Input a command: ";
        cin >> c;

        if(c == 'r' || c == 'l') {
            v.turn(c);
        }
        else if(c == 'f') {
            v.forward();
        }
        v.print();
    }

    return 0;
}