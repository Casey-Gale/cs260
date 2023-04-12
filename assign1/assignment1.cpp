#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void add_marble(int& r, int& g, int& b);
string draw_marble(int& r, int& g, int& b);
int count_marbles(int r, int g, int b);
void do_free_test(int& r, int& g, int& b);
void do_default_test(int& r, int& g, int& b);

int main() {
    srand(time(NULL));
    int r = 0; //integer representing the number of red marbles contained in the bag
    int g = 0; //integer representing the number of green marbles contained in the bag
    int b = 0; //integer representing the number of blue marbles contained in the bag

    cout << "Do you want to run through hard-coded tests or manually test?" << endl;
    cout << "1-Default tests" << endl;
    cout << "Anything else-Manual test" << endl;
    cout << "Choice: ";
    string choice;
    getline(cin, choice);
    cin.clear();

    if(choice == "1") {
        do_default_test(r, g, b);
    }
    else {
        do_free_test(r, g, b);

        cout << "Ending program..." << endl << endl;
    }

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


//asks the user to do testing manually to test for more cases than those hard-coded
void do_free_test(int& r, int& g, int& b) {
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
                    return;
            }
        }
        else {
            break;
        }
    } while(true);
}


//hard-coded test cases for the program
void do_default_test(int& r, int& g, int& b) {
    cout << endl;
//tests if count_marbles works on 0
    cout << "TEST 1: count_marbles() -- TESTING WITH EMPTY BAG" << endl;
    cout << "EXPECTED: 0" << endl;
    cout << "ACTUAL  : " << count_marbles(r, g, b) << endl << endl;

//tests if r is drawn if it is the only marble in there
    r = 1;
    cout << "TEST 2.1.1: count_marbles() -- TESTING WITH ONLY RED IN BAG" << endl;
    cout << "EXPECTED: 1" << endl;
    cout << "ACTUAL  : " << count_marbles(r, g, b) << endl << endl;

    cout << "TEST 2.1.2: draw_marble()" << endl;
    cout << "EXPECTED: red" << endl;
    cout << "ACTUAL  : " << draw_marble(r, g, b) << endl << endl;

    cout << "TEST 2.1.3: count_marbles()" << endl;
    cout << "EXPECTED: 0" << endl;
    cout << "ACTUAL  : " << count_marbles(r, g, b) << endl << endl;

//tests if g is drawn if it is the only marble in there
    g = 1;
    cout << "TEST 2.2.1: count_marbles() -- TESTING WITH ONLY GREEN IN BAG" << endl;
    cout << "EXPECTED: 1" << endl;
    cout << "ACTUAL  : " << count_marbles(r, g, b) << endl << endl;

    cout << "TEST 2.2.2: draw_marble()" << endl;
    cout << "EXPECTED: green" << endl;
    cout << "ACTUAL  : " << draw_marble(r, g, b) << endl << endl;

    cout << "TEST 2.2.3: count_marbles()" << endl;
    cout << "EXPECTED: 0" << endl;
    cout << "ACTUAL  : " << count_marbles(r, g, b) << endl << endl;

//tests if b is drawn if it is the only marble in there
    b = 1;
    cout << "TEST 2.3.1: count_marbles() -- TESTING WITH ONLY BLUE IN BAG" << endl;
    cout << "EXPECTED: 1" << endl;
    cout << "ACTUAL  : " << count_marbles(r, g, b) << endl << endl;

    cout << "TEST 2.3.2: draw_marble()" << endl;
    cout << "EXPECTED: blue" << endl;
    cout << "ACTUAL  : " << draw_marble(r, g, b) << endl << endl;

    cout << "TEST 2.3.3: count_marbles()" << endl;
    cout << "EXPECTED: 0" << endl;
    cout << "ACTUAL  : " << count_marbles(r, g, b) << endl << endl;

//tests if draw_marble works with 0 marbles
    cout << "TEST 3.1: draw_marble() -- TESTING WITH EMPTY BAG" << endl;
    cout << "EXPECTED: There aren't any marbles in the bag!" << endl;
    cout << "ACTUAL  : " << draw_marble(r, g, b) << endl << endl;

//tests if count_marbles and draw_marble work with almost integer overflow marbles
    r = 2147483647;
    g = 0;
    b = 0;
    cout << "TEST 3.2.1: count_marbles() -- TESTING NEAR OVERFLOW" << endl;
    cout << "EXPECTED: 2147483647" << endl;
    cout << "ACTUAL  : " << count_marbles(r, g, b) << endl << endl;

    cout << "TEST 3.2.2: draw_marble()" << endl;
    cout << "EXPECTED: red" << endl;
    cout << "ACTUAL  : " << draw_marble(r, g, b) << endl << endl;

    cout << "TEST 3.2.3: count_marbles()" << endl;
    cout << "EXPECTED: 2147483646" << endl;
    cout << "ACTUAL  : " << count_marbles(r, g, b) << endl << endl;

//tests if count_marbles and draw_marble work with integer overflow marbles
    r = 0;
    g = 2147483648;
    b = 0;
    cout << "TEST 3.2.1: count_marbles() -- TESTING PAST OVERFLOW" << endl;
    cout << "EXPECTED: 2147483648" << endl;
    cout << "ACTUAL  : " << count_marbles(r, g, b) << endl << endl;

    cout << "TEST 3.2.2: draw_marble()" << endl;
    cout << "EXPECTED: green" << endl;
    cout << "ACTUAL  : " << draw_marble(r, g, b) << endl << endl;

    cout << "TEST 3.2.3: count_marbles()" << endl;
    cout << "EXPECTED: 2147483647" << endl;
    cout << "ACTUAL  : " << count_marbles(r, g, b) << endl << endl;
}