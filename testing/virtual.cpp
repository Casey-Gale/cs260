// the ultimate goal of this project is to implement a fully compliant 32-bit risc-v virtual computer
// i am entirely new to the idea of virtual machines, risc, and have only taken a rudimentary course
// on computer organization. my hope is that by developing this project, i will learn invaluable information
// about the development and architecture of computers.


#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <bitset>
#include <cmath>

// instead of using a million #define statements, lets use enum!

#define ffffffff add(1, 2);
#define eeeeeeee ldi(1, 200);
#define dddddddd ldi(2, 123);

using namespace std;

const int word_size = 32;
const int pm_size = 256;
const string pm = "0f12feab ffffffff";
unsigned int program_memory[pm_size] = {0};
unsigned int registers[32] = {0};
int num_registers = 32;

// class cpu {
//     public: 
//         const short word_size = 32;
//         const short pm_size = 256;
//         int program_counter;
//         int program_memory[pm_size];
// }
void initialize_program_memory();
void print_pm(bool);
void print_registers();
void add(int, int);
void ldi(int d, int i) {registers[d] = i;}

unsigned int my_atoi(char* cstring, int base = 10) {
    int slen = 0;
    while(cstring[slen] != '\0') {
        slen++;
    }
    unsigned int num = 0;
    // cout << "strlen: " << slen << endl;
    for(int i = 0; i < slen; i++) {
        char a = cstring[i];
        if(a >= 48 && a <= 57) {
            a -= 48;
        }
        else if(a >= 97 && a <= 102) {
            a -= 87;
        }
        num += (a) * pow(base, slen - i - 1);
        // cout << "a is: " << (int)a << endl;
        // cout << "power is: " << slen - i - 1 << endl;
        // cout << "   num: " << num << endl;
        // char hex_string[9];
        // sprintf(hex_string, "%x", num);
        // cout << "   hex: " << hex_string << endl;
    }
    return num;
}

int main() {
    int program_counter = 0;

    // char test[100] = "bfffef18";
    // cout << bitset<32>(my_atoi(test, 16)) << endl;

    // cout << "pm.size() == " << pm.size();
    // int x = 0b1111010101;
    // cout << "x == " << x << endl << "bitset(x) == " << bitset<8*sizeof(x)>(x) << endl;
    initialize_program_memory();
    // program_memory[0] = 0b01100111111111111111111111111111;
    print_pm(false);
    dddddddd;
    eeeeeeee;
    print_registers();
    ffffffff;
    print_registers();

    return 0;

}

// parses from an external string into program memory
void initialize_program_memory() {
//    for(int i = 0; i < pm_size; i++) {
        // parse pm into program_memory[i]
        int i = 0;
        int j = 0;
        char word_string[(word_size / 4) + 1];
        word_string[(word_size / 4)] = '\0';
        while(j < pm.size()) {
            for(int k = 0; k < (word_size / 4); k++) {
                word_string[k] = pm[k+j];
                // cout << word_string[k];
                // move word to program memory here
            }
            // cout << endl << endl;
            // cout << word_string[0] << endl;
            // cout << word_int << endl;
            // cout << bitset<word_size>(word_int) << endl;
            program_memory[i] = my_atoi(word_string, 16);

            j += ((word_size / 4) + 1);
            i++;
        }
//   }
}


void print_pm(bool with_line_nums) {
    char hex_word[9];
    for(int i = 0; i < 10; i++) { // replace 10 with pm_size
        if(with_line_nums) {
            cout << (i+1) << " ";
        }
        sprintf(hex_word, "%x", program_memory[i]);
        cout << hex_word << endl;
    }
}

void print_registers() {
    char hex_word[9];
    cout << "REGISTERS: " << endl;
    for(int i = 0; i < num_registers; i++) {
        sprintf(hex_word, "%x", registers[i]);
        cout << hex_word << " ";
        if(i % 8 == 7) {
            cout << endl;
        }
    }
    cout << endl;
    return;
}

// adds r to d, stores in d
// d and r must be on [0, 31]
void add(int d, int r) {
    if (d < 0 || r < 0 || d > 31 || r > 31) {
        return;
    }
    registers[d] += registers[r];
    return;
}