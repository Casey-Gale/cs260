#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void add_marble(int& r, int& g, int& b);
string draw_marble(int& r, int& g, int& b);
int count_marbles(int r, int g, int b);

int main() {
    srand(time(NULL));
    int r = 0;
    int g = 0;
    int b = 0;

    do {
        cout << "1-Add a marble" << endl;
        cout << "2-Draw a marble" << endl;
        cout << "3-Count marbles" << endl;
        cout << "Anything else-End program" << endl;
        cout << "Choice: ";
        string choice;
        getline(cin, choice);
        cin.clear();
        cout << endl;
        string str;
        if(choice.length() == 1) {
            switch(choice[0]) {
                case '1':
                    add_marble(r, g, b);
                    break;
                case '2':
                    str = draw_marble(r, g, b);
                    if(str != "There aren't any marbles in the bag!") {
                        cout << "You drew a " << str << " marble from the bag!" << endl;
                    }
                    else {
                        cout << str << endl;
                    }
                    break;
                case '3':
                    cout << "There are " << count_marbles(r, g, b) << " marbles in the bag!" << endl;
                    break;
                default:
                    return 0;
            }
        }
        else {
            break;
        }
    } while(true);

    return 0;
}

//prompts a user for the color of a marble and increments that marble color
void add_marble(int& r, int& g, int& b) {
    cout << "Which color do you want to add?" << endl;
    cout << "r-Add a red marble" << endl;
    cout << "g-Add a green marble" << endl;
    cout << "b-Add a blue marble" << endl;
    cout << "Choice: ";
    string c;
    getline(cin, c);
    cin.clear();
    cout << endl;
    if(c == "r") { //r
        r++;
    }
    else if(c == "g") { //g
        g++;
    }
    else if(c == "b") { //b
        b++;
    }
    else {
        cout << "There is no color by that name!" << endl;
    }
}

//randomly draws a marble (that hopefully has the proper chances), returns the color, and decrements the marble color
string draw_marble(int& r, int& g, int& b) {
    int n = count_marbles(r, g, b);
    if(!n) {
        return "There aren't any marbles in the bag!";
    }
    int prob = rand() % n + 1; //random number from 1 to number of marbles
    if(prob <= r) {
        r--;
        return "red";
    }
    else if(prob <= r + g) {
        g--;
        return "green";
    }
    else {
        b--;
        return "blue";
    }
}

//adds the three integers together
int count_marbles(int r, int g, int b) {
    return r + g + b;
}