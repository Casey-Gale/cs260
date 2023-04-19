#include <iostream>
#include <ctime>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using std::cout;
using std::cin;
using std::endl;



int main() {
    while(true) {
        cout << "time: " << time(nullptr) << endl;
    }
    return 0;
}
