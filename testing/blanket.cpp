#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Node {
    public: 
        int x;
        int height;
        Node* next;
        Node();
        Node(int, int);
        Node(int, int, Node*);
};
Node::Node() {this->x = 0; this->height = 0; this->next = nullptr;}
Node::Node(int new_x, int new_height) {this->x = new_x; this->height = new_height; this->next = nullptr;}
Node::Node(int new_x, int new_height, Node* new_node) {this->x = new_x; this->height = new_height; this->next = new_node;}

class Blanket {
    public:
        Node* head;
        
        Blanket() {this->head = nullptr;}
        void add_node(int new_x, int new_height);
        void remove_node(int index);
        void print();
};

void Blanket::add_node(int new_x, int new_height) {
    if(this->head == nullptr) {
        this->head = new Node(new_x, new_height);
        // cout << "head nullptr" << endl;
    }
    
    else if(new_x < this->head->x) {
        // add to front
        this->head = new Node(new_x, new_height, this->head->next);
    }
    else {
        Node* current = this->head;
        // while not at the end of the list:
        while(current->next != nullptr) {
            if(new_x < current->next->x) {
                current = current->next;
            }
            else {
                // add in the middle
                current->next = new Node(new_x, new_height, current->next);
            }
        }
        // at the end of the list: 
        // add to end
        current->next = new Node(new_x, new_height);
    }
    return;
}

void Blanket::print() {
    if(this->head == nullptr) {
        cout << endl << endl;
        return;
    }
    Node* current = this->head;
    while(current != nullptr) {
        for(int i = 0; i < current->height; i++) {
            cout << "-";
        }
        cout << endl;
        current = current->next;
    }
    return;
}

int main() {
    // make a linked list which stores locations and heights 
    // when adding to the linked list, sort by increasing location (higher x means further in the list)
    Blanket b;
    string input;
    while(1) {
        cout << "Input x: ";
        getline(cin, input);
        int x = stoi(input);
        cout << "Input height: ";
        getline(cin, input);
        int height = stoi(input);
        b.add_node(x, height);
        cout << endl;

        b.print();

    }
    return 0;
}