#include <iostream>
#include <string>

using std::cout;
using std::endl;

//auto sorted list
//should automatically decide where to place objects based on the value stored in the object
//will likely have most operations be O(n)

class Node {
    private:
        
    public:
        int val;
        Node* next;
        Node();
        Node(int);
};

Node::Node() {
    this->val = 0;
    this->next = nullptr;
}
Node::Node(int val) {
    this->val = val;
    this->next = nullptr;
}


class List {
    private: 
        Node* head;
        int length;
    public:
        List();
        int get_length() const;
        void push(const int val); //pushes to the back of the List
        int search(const int index);
        
        void print() const;
};
List::List() {
    this->head = nullptr;
    this->length = 0;
}
int List::get_length() const {return this->length;}

//automatically pushes a value to a sorted list in a sorted position
void List::push(const int new_val) {
    //cout << "Pushing " << new_val << endl;
    //if list is empty
    Node* current = this->head;
    if(this->length == 0) {
        //cout << "length == 0" << endl;
        this->head = new Node(new_val); // new node->next is automatically nullptr
    }
    // checks if the value is less than the first 
    else if(new_val < this->head->val) {
        //cout << "current == head" << endl;
        current = new Node(new_val);
        current->next = this->head;
        this->head = current;
    }
    //else
    else {
        while(current->next != nullptr && new_val > current->next->val) {
            current = current->next;
        }
    
        // checks if current is at the end of the list
        if(current->next == nullptr) {
            //cout << "current->next == nullptr" << endl;
            current->next = new Node(new_val);
        }
        // now, we may assume that current is pointing to an object in the middle of the list
        else {
            //cout << "current is in the middle" << endl;
            Node* after = current->next;
            current->next = new Node(new_val);
            current->next->next = after;
        }
    }
    this->length++;
}

// searches for the value stored at specified index
// throws 1 if OUT OF BOUNDS and throws 2 if EMPTY LIST
int List::search(const int index) {
    Node* current = this->head;
    if(this->length == 0) {
        throw 2;
    }
    if(index < 0 || index >= this->length) {
        throw 1;
    }
    for(int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->val;
}


//prints out the entire List from the front to the back. assumes a valid value for length
void List::print() const {
    Node* current = this->head;
    for(int i = 0; i < this->length; i++) {
        cout << current->val << " ";
        current = current->next;
    }
    cout << endl << endl;
}

void do_testing() {
    List l;

    // testing insert
    cout << "TESTING INSERTING A VALUE INTO AN EMPTY LIST" << endl;
    l.push(0);
    cout << "Expected: 0" << endl;
    cout << "Actual:   ";
    l.print();

    cout << "TESTING INSERTING A VALUE BEHIND THE ONLY ELEMENT IN A LIST" << endl;
    l.push(1);
    cout << "Expected: 0 1" << endl;
    cout << "Actual:   ";
    l.print();

    cout << "TESTING INSERTING THE SAME VALUE AS THE LAST ELEMENT IN A LIST" << endl;
    l.push(1);
    cout << "Expected: 0 1 1" << endl;
    cout << "Actual:   ";
    l.print();

    cout << "TESTING INSERTING THE SAME VALUE AS THE FIRST ELEMENT IN A LIST" << endl;
    l.push(0);
    cout << "Expected: 0 0 1 1 " << endl;
    cout << "Actual:   ";
    l.print();

    cout << "TESTING INSERTING A VALUE TO THE END OF AN EXISTING LIST" << endl;
    l.push(3);
    cout << "Expected: 0 0 1 1 3" << endl;
    cout << "Actual:   ";
    l.print();

    cout << "TESTING INSERTING A VALUE TO THE BEGINNING OF AN EXISTING LIST" << endl;
    l.push(-2);
    cout << "Expected: -2 0 0 1 1 3" << endl;
    cout << "Actual:   ";
    l.print();

    cout << "TESTING INSERTING A VALUE AFTER THE BEGINNING OF AN EXISTING LIST" << endl;
    l.push(-1);
    cout << "Expected: -2 -1 0 0 1 1 3" << endl;
    cout << "Actual:   ";
    l.print();

    cout << "TESTING INSERTING A VALUE BEFORE THE END OF AN EXISTING LIST" << endl;
    l.push(2);
    cout << "Expected: -2 -1 0 0 1 1 2 3" << endl;
    cout << "Actual:   ";
    l.print();

    cout << "TESTING INSERTING A VALUE IN THE MIDDLE OF AN EXISTING LIST" << endl;
    l.push(0);
    cout << "Expected: -2 -1 0 0 0 1 1 2 3" << endl;
    cout << "Actual:   ";
    l.print();

    List l2;
    // testing search
    cout << "TESTING SEARCHING FOR A VALUE IN AN EMPTY LIST" << endl;
    cout << "Expected: EMPTY LIST" << endl;
    cout << "Actual:   ";
    try {
        cout << l2.search(0) << endl;
    }
    catch(int n) {
        if(n == 1) {
            cout << "OUT OF BOUNDS" << endl;
        }
        else if(n == 2) {
            cout << "EMPTY LIST" << endl;
        }
    }

    l2.push(1);
    cout << "TESTING SEARCHING FOR A VALUE IN A LIST WITH 1 ELEMENT" << endl;
    cout << "Expected: 1" << endl;
    cout << "Actual:   ";
    try {
        cout << l2.search(0) << endl;
    }
    catch(int n) {
        if(n == 1) {
            cout << "OUT OF BOUNDS" << endl;
        }
        else if(n == 2) {
            cout << "EMPTY LIST" << endl;
        }
    }

    cout << "TESTING SEARCHING FOR A VALUE AT INDEX -1" << endl;
    cout << "Expected: OUT OF BOUNDS" << endl;
    cout << "Actual:   ";
    try {
        cout << l2.search(-1) << endl;
    }
    catch(int n) {
        if(n == 1) {
            cout << "OUT OF BOUNDS" << endl;
        }
        else if(n == 2) {
            cout << "EMPTY LIST" << endl;
        }
    }

    cout << "TESTING SEARCHING FOR A VALUE AT INDEX 1 (OUT OF BOUNDS)" << endl;
    cout << "Expected: OUT OF BOUNDS" << endl;
    cout << "Actual:   ";
    try {
        cout << l2.search(1) << endl;
    }
    catch(int n) {
        if(n == 1) {
            cout << "OUT OF BOUNDS" << endl;
        }
        else if(n == 2) {
            cout << "EMPTY LIST" << endl;
        }
    }

    l2.push(-1);
    l2.push(2);
    l2.push(3);
    l2.push(4);
    cout << "TESTING SEARCHING FOR A VALUE AT END OF POPULATED LIST" << endl;
    cout << "Expected: 4" << endl;
    cout << "Actual:   ";
    try {
        cout << l2.search(4) << endl;
    }
    catch(int n) {
        if(n == 1) {
            cout << "OUT OF BOUNDS" << endl;
        }
        else if(n == 2) {
            cout << "EMPTY LIST" << endl;
        }
    }

    cout << "TESTING SEARCHING FOR A VALUE AT BEGINNING OF POPULATED LIST" << endl;
    cout << "Expected: -1" << endl;
    cout << "Actual:   ";
    try {
        cout << l2.search(0) << endl;
    }
    catch(int n) {
        if(n == 1) {
            cout << "OUT OF BOUNDS" << endl;
        }
        else if(n == 2) {
            cout << "EMPTY LIST" << endl;
        }
    }

    cout << "TESTING SEARCHING FOR A VALUE AT THE MIDDLE OF A POPULATED LIST" << endl;
    cout << "Expected: 2" << endl;
    cout << "Actual:   ";
    try {
        cout << l2.search(2) << endl;
    }
    catch(int n) {
        if(n == 1) {
            cout << "OUT OF BOUNDS" << endl;
        }
        else if(n == 2) {
            cout << "EMPTY LIST" << endl;
        }
    }
}


int main() {
    do_testing();

    return 0;
}