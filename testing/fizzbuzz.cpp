#include <iostream>
#include <string>

using namespace std;

int main() {
    bool skip_num;
    int arr_len = 4;    
    int mod_arr[arr_len] = {3, 4, 5, 7};    // array containing integers of every single modulo of a given rule
    string string_arr[arr_len] = {"Fizz", "Bizz", "Buzz", "Bazz"};  // array containing strings of every name of a given rule

    for(int i = 1; i < 106; i++) {
        skip_num = false;   // clear flag at beginning of each iteration i
                            // if cleared at the end of iteration, the 
                            // number i will be printed to the terminal
        // iterate over all rules
        for(int j = 0; j < arr_len; j++) {
            // modulo i with the jth entry in mod_arr. if == 0, then i is divisible by mod_arr[j]
            if(i % (mod_arr[j]) == 0) {
                cout << string_arr[j];  // print the jth rule to the terminal
                skip_num = true;    // sets flag showing that a rule has been satisfied
            }
        }
        // prints i if no rules are satisfied (i.e. no Fizz, Buzz, etc)
        if(!skip_num) {
            cout << i;
        }
        cout << endl;
    }
}