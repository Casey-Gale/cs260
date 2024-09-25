#include <iostream>

using namespace std;

int recursive(int n) {
    if(n == 5) {
        return 0;
    }
    int result = recursive(n-1) + 2000 * (n - 5);
    return result;
}

int main() {
    int sum = 0;
    int j = 0;
    for(int i = 5; i <= 26; i++) {
        j = recursive(i);
        cout << "a_" << i << " == " << j << endl;
        sum += j;
    }
    cout << "total cost: " << sum << endl;
    return 0;
}