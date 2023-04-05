#include "helper_functions.h"
#include <iostream>

int main() {
    srand(time(NULL));
    Node* head = nullptr;
    int length = 0;
    do {

        int choice;
        cout << "1-Add a marble" << endl;
        cout << "2-Draw a marble" << endl;
        cout << "3-Count all marbles" << endl;
        cout << "Anything else-end program" << endl;
        cout << "Which do you want to do?: ";
        cin >> choice;
        if(choice == 1) {
            add_marble(head, length);
        }
        else if(choice == 2) {
            draw_marble(head, length);
        }
        else if(choice == 3) {
            count_marbles(head, length);
        }
        else {
            break;
        }

    } while(true);
    return 0;
}