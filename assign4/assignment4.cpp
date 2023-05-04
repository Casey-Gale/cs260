#include <iostream>
#include <string>

using std::cout;
using std::endl;

class Node {
    private:
        int val;
        Node* next;
    public:
        Node();
        Node(int);
        int get_val() const;
        void set_val(const int);
        Node* get_next();
        void set_next(Node*);
};

Node::Node() {
    this->val = 0;
    this->next = nullptr;
}
Node::Node(int val) {
    this->val = val;
    this->next = nullptr;
}
int Node::get_val() const {return this->val;}
void Node::set_val(const int val) {this->val = val;}
Node* Node::get_next() {return this->next;}
void Node::set_next(Node* next) {this->next = next;}


class List {
    private: 
        Node* head;
        Node* tail;
        int length;
    public:
        List();
        ~List();
        int get_length() const;
        Node* get_head() const;
        Node* get_tail() const;
        void print_ends() const;

        void push_back(const int val); //pushes to the back of the list
        void push_front(const int val); //pushes to the front of the list
        int pop_back(); //pops from the back of the list
        int pop_front(); //pops from the front of the list

        void push(const int val, const int i); //pushes to index i of list
        int pop(const int i); //pops from index i of list
        
        void print() const;
};
// O(1)
List::List() {
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}
// O(n)
List::~List() {
    int n = this->length; //exists so that it doesnt get modified during the for loop
    for (int i = 0; i < n; i++) {
        this->pop_front();
    }
}
int List::get_length() const {return this->length;}
Node* List::get_head() const {return this->head;}
Node* List::get_tail() const {return this->tail;}
void List::print_ends() const {
    // cout << "head: " << head << endl;
    // if(head != nullptr) {
    //     cout << "  head->val: " << head->get_val() << ", head->next: " << head->get_next() << endl;
    // }
    // cout << "tail: " << tail << endl;
    // if(tail != nullptr) {
    //     cout << "  tail->val: " << tail->get_val() << ", tail->next: " << tail->get_next() << endl;
    // }
    // cout << "length: " << length << endl << endl;
}

// O(1)
//pushes in a value to the back of the list.
void List::push_back(const int val) {
    //if length == 0
    if(this->length == 0) {
        this->head = new Node(val);
        this->tail = this->head;
    }
    //else
    else {
        this->tail->set_next(new Node(val));
        this->tail = this->tail->get_next();
    }
    this->length++;
    print_ends();
}

// O(1)
//pushes in a value to the front of the list
void List::push_front(const int val) {
    if(this->length == 0) {
        this->head = new Node(val);
        this->tail = this->head;
    }
    else {
        Node* new_node = new Node(val);
        new_node->set_next(this->head);
        this->head = new_node;
    }
    this->length++;
    print_ends();
}

// O(n)
//pushes to index i of list
void List::push(const int val, const int i) {
    //if i is out of bounds
    if(i < 0 || i > this->length) {
        return;
    }
    //if inserting to the beginning of the list
    else if(i == 0) {
        push_front(val);
        return;
    }
    //if inserting to the end of the list
    else if(i == this->length) {
        push_back(val);
        return;
    }
    else {
        Node* current = this->head; //node ptr to iterate through list
        for(int j = 0; j < i - 1; j++) {
            current = current->get_next();
        }
        Node* new_node = new Node(val);
        new_node->set_next(current->get_next());
        current->set_next(new_node);
        this->length++;
    }
    print_ends();
}

// O(n)
//pops out the back value in the list
//throws 2 if the list is empty
int List::pop_back() {
    if(this->length == 0) {
        throw 2;
    }
    Node temp = *(this->tail);
    delete this->tail;
    if(this->length == 1) {
        this->head = nullptr;
        this->tail = nullptr;
    }
    else {
        Node* current = this->head;
        for(int i = 0; i < this->length - 2; i++) {
            current = current->get_next();
        }
        current->set_next(nullptr);
        this->tail = current;
    }
    this->length--;
    print_ends();
    return temp.get_val();

}

// O(1)
//pops out the front value in the list. 
//throws 2 if the list is empty
int List::pop_front() {
    //if length == 0
    if(this->length == 0) {
        throw 2;
    }
    Node temp = *(this->head);
    delete this->head;
    if(this->length == 1) {
        this->head = nullptr;
        this->tail = nullptr;
    }
    else {
        this->head = temp.get_next();
    }
    this->length--;
    print_ends();
    return temp.get_val();
}

// O(n)
// pops an item from the ith index of the list
//throws 1 if out of bounds, throws 2 if the list is empty
int List::pop(int i) {
    //checking if empty list
    if(this->length == 0) {
        throw 2;
    }
    //checking OUT OF BOUNDS
    else if(i < 0 || i >= this->length) {
        throw 1;
    }
    //check if popping from beginning
    else if(i == 0) {
        return pop_front();
    }
    //check if popping from end
    else if(i == this->length - 1) {
        return pop_back();
    }
    //otherwise pop from middle
    else {
        Node* current = this->head;
        Node* prev = current;
        for (int j = 0; j < i; j++)
        {
            prev = current;
            current = current->get_next();
        }
        prev->set_next(current->get_next());
        int val = current->get_val();
        delete current;
        this->length--;
        return val;
    }
}

// O(n)
//prints out the entire list from the front to the back. assumes a valid value for length
void List::print() const {
    Node* current = this->head;
    for(int i = 0; i < this->length; i++) {
        cout << current->get_val() << " ";
        current = current->get_next();
    }
    cout << endl;
}

// returns a list that has had a variety of integer values pushed onto it
// returned list: 3 1 0 5 2 4
List* test_push() {
    List* l = new List;
    cout << "Attempting to push the value 0 into position 0 (in bounds)..." << endl;
    l->push(0, 0);
    cout << "Expected: 0" << endl;
    cout << "Actual:   ";
    l->print();
    cout << "Attempting to push the value 1 into position 0 (in bounds)..." << endl;
    l->push(1, 0);
    cout << "Expected: 1 0" << endl;
    cout << "Actual:   ";
    l->print();
    cout << "Attempting to push the value 2 into position 2 (in bounds)..." << endl;
    l->push(2, 2);
    cout << "Expected: 1 0 2" << endl;
    cout << "Actual:   ";
    l->print();
    cout << "Attempting to push the value 3 into position 0 (in bounds)..." << endl;
    l->push(3, 0);
    cout << "Expected: 3 1 0 2" << endl;
    cout << "Actual:   ";
    l->print();
    cout << "Attempting to push the value 4 into position 4 (in bounds)..." << endl;
    l->push(4, 4);
    cout << "Expected: 3 1 0 2 4" << endl;
    cout << "Actual:   ";
    l->print();
    cout << "Attempting to push the value 5 into position 3 (in bounds)..." << endl;
    l->push(5, 3);
    cout << "Expected: 3 1 0 5 2 4" << endl;
    cout << "Actual:   ";
    l->print();
    cout << "Attempting to push the value 6 into position 7 (out of bounds)..." << endl;
    l->push(6, 7);
    cout << "Expected: 3 1 0 5 2 4" << endl;
    cout << "Actual:   ";
    l->print();
    cout << "Attempting to push the value 7 into position -1 (out of bounds)..." << endl;
    l->push(7, -1);
    cout << "Expected: 3 1 0 5 2 4" << endl;
    cout << "Actual:   ";
    l->print();
    return l;
}
// takes in a specific list from test_push() and tries to pop various values off
// required list: 3 1 0 5 2 4
void test_pop(List* l) {
    cout << "Attempting to pop the value stored at position 4 (in bounds)..." << endl;
    cout << "Expected value: 2" << endl;
    cout << "Actual value:   ";
    try {
        cout << l->pop(4) << endl;
    }
    catch(int n) {
        if(n == 1) {
            cout << "OUT OF BOUNDS!" << endl;
        }
        else if(n == 2) {
            cout << "EMPTY LIST!" << endl;
        }
    };
    cout << "Expected remaining list: 3 1 0 5 4" << endl;
    cout << "Actual remaining list:   ";
    l->print();

    cout << "Attempting to pop the value stored at position 2 (in bounds)..." << endl;
    cout << "Expected value: 0" << endl;
    cout << "Actual value:   ";
    try {
        cout << l->pop(2) << endl;
    }
    catch(int n) {
        if(n == 1) {
            cout << "OUT OF BOUNDS!" << endl;
        }
        else if(n == 2) {
            cout << "EMPTY LIST!" << endl;
        }
    };
    cout << "Expected remaining list: 3 1 5 4" << endl;
    cout << "Actual remaining list:   ";
    l->print();

    cout << "Attempting to pop the value stored at position 6 (out of bounds)..." << endl;
    cout << "Expected value: OUT OF BOUNDS!" << endl;
    cout << "Actual value:   ";
    try {
        cout << l->pop(6) << endl;;
    }
    catch(int n) {
        if(n == 1) {
            cout << "OUT OF BOUNDS!" << endl;
        }
        else if(n == 2) {
            cout << "EMPTY LIST!" << endl;
        }
    }
    cout << "Expected remaining list: 3 1 5 4" << endl;
    cout << "Actual remaining list:   ";
    l->print();

    cout << "Attempting to pop the value stored at position 1 (in bounds)..." << endl;
    cout << "Expected value: 1" << endl;
    cout << "Actual value:   ";
    try {
        cout << l->pop(1) << endl;;
    }
    catch(int n) {
        if(n == 1) {
            cout << "OUT OF BOUNDS!" << endl;
        }
        else if(n == 2) {
            cout << "EMPTY LIST!" << endl;
        }
    };
    cout << "Expected remaining list: 3 5 4" << endl;
    cout << "Actual remaining list:   ";
    l->print();

    cout << "Attempting to pop the value stored at position 0 (in bounds)..." << endl;
    cout << "Expected value: 3" << endl;
    cout << "Actual value:   ";
    try {
        cout << l->pop(0) << endl;;
    }
    catch(int n) {
        if(n == 1) {
            cout << "OUT OF BOUNDS!" << endl;
        }
        else if(n == 2) {
            cout << "EMPTY LIST!" << endl;
        }
    };
    cout << "Expected remaining list: 5 4" << endl;
    cout << "Actual remaining list:   ";
    l->print();

    cout << "Attempting to pop the value stored at position 1 (in bounds)..." << endl;
    cout << "Expected value: 4" << endl;
    cout << "Actual value:   ";
    try {
        cout << l->pop(1) << endl;;
    }
    catch(int n) {
        if(n == 1) {
            cout << "OUT OF BOUNDS!" << endl;
        }
        else if(n == 2) {
            cout << "EMPTY LIST!" << endl;
        }
    };
    cout << "Expected remaining list: 5" << endl;
    cout << "Actual remaining list:   ";
    l->print();

    cout << "Attempting to pop the value stored at position 0 (in bounds)..." << endl;
    cout << "Expected value: 5" << endl;
    cout << "Actual value:   ";
    try {
        cout << l->pop(0) << endl;;
    }
    catch(int n) {
        if(n == 1) {
            cout << "OUT OF BOUNDS!" << endl;
        }
        else if(n == 2) {
            cout << "EMPTY LIST!" << endl;
        }
    };
    cout << "Expected remaining list: " << endl;
    cout << "Actual remaining list:   ";
    l->print();

    cout << "Attempting to pop the value stored at position 0 (out of bounds)..." << endl;
    cout << "Expected value: EMPTY LIST!" << endl;
    cout << "Actual value:   ";
    try {
        cout << l->pop(0) << endl;;
    }
    catch(int n) {
        if(n == 1) {
            cout << "OUT OF BOUNDS!" << endl;
        }
        else if(n == 2) {
            cout << "EMPTY LIST!" << endl;
        }
    };
    cout << "Expected remaining list: " << endl;
    cout << "Actual remaining list:   ";
    l->print();
}

// tests the arbitrary push() and pop() functions in the list
void test_all() {
    List* l_ptr;
    l_ptr = test_push();
    test_pop(l_ptr);
    cout << endl;
}


int main() {

    test_all();
    cout << "Exiting program gracefully..." << endl;

    return 0;
}