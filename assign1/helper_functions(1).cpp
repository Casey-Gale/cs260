#include "helper_functions.h"
#include <iostream>

using namespace std;

//adds a marble based on user inputs to the end of the marble bag (linked list)
void add_marble(Node* head, int& length) {

    if(head == nullptr) {
        head = new Node;
        head->m = *(get_marble());
        length++;
        return;
    }
    Node* current = head;
    while(current != nullptr) {
        current = current->next;
    }
    current = new Node;
    current->m = *(get_marble());
    length++;

}

//this function prints and removes a marble from the marble bag (linked list)
void draw_marble(Node*& head, int& length) {
//checks if the length is zero
    if(length == 0) {
        cout << "There are zero marbles in the bag" << endl;
        return;
    }
//assumes length is not zero below this
//code runs if marble drawn is the first in the list
    int x = rand() % length;
    if(x == 0) {
        head->m.print();
        Node* temp = head->next;
        delete head;
        head = temp;
    }
//code runs if marble drawn is not the first in the list
    Node* current = head->next;
    Node* prev = head;
    for (int i = 0; i < x; i++) {
        prev = current;
        current = current->next;
    }
    current->m.print();
    delete current;
    prev->next = current->next;
//probably OOB errors with last member of the list but will fix that when I get to it   
}
//returns length lol why do i have this
int count_marbles(int length) {
    return length;
}
//initializes a marble to be added to the bag from user inputs
Marble* get_marble() {
    string temp;
    cout << "What color marble do you want?: ";
    cin >> temp;
    Marble* m = new Marble(temp);
    return m;
}