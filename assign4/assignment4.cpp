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

        void push_back(const int val); //pushes to the back of the list
        int pop_front(); //pops from the front of the list

        void push(const int val, const int i); //pushes to index i of list
        int pop(const int i); //pops from index i of list
        
        void print() const;
};
List::List() {
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}
List::~List() {
    int n = this->length; //exists so that it doesnt get modified during the for loop
    for (int i = 0; i < n; i++) {
        this->pop_front();
    }
}
int List::get_length() const {return this->length;}

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
}

//pushes to index i of list
void List::push(const int val, const int i) {
    //if i = 0
    if(i == 0) {
        if(this->length == 0) {
            cout << "push is pushing back" << endl;
            push_back(val);
            return;
        }
        cout << "push is pushing front" << endl;
        Node* new_node = new Node(val);
        cout << "new_node->set_next(this->head->get_next());" << endl;
        new_node->set_next(this->head->get_next());
        cout << "this->head = new_node;" << endl;
        this->head = new_node;
        this->length++;
    }
    //if i is out of bounds
    else if(i < 0 || i >= this->length) {
        cout << "OUT OF BOUNDS" << endl;
        return;
    }
    //if i = length
    else if(i == this->length - 1) {
        cout << "push is pushing back" << endl;
        push_back(val);
    }
    else {
        cout << "push is pushing to index i" << endl;
        Node* current = this->head; //node ptr to iterate through list
        for(int j = 0; j < i - 1; j++) {
            current = current->get_next();
        }
        Node* new_node = new Node(val);
        new_node->set_next(current->get_next());
        current->set_next(new_node);
        this->length++;
    }
}

//pops out the front value in the list. 
int List::pop_front() {
    //if length == 0
    if(this->length == 0) {
        throw 1;
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
    return temp.get_val();
}

//prints out the entire list from the front to the back. assumes a valid value for length
void List::print() const {
    Node* current = this->head;
    for(int i = 0; i < this->length; i++) {
        cout << current->get_val() << " ";
        current = current->get_next();
    }
    if(this->length == 0) {
        cout << "The list is empty" << endl;
    }
    cout << endl;
}


int main() {
    List l;
    l.push(1, 0);
    l.print();
    l.push(2, 0);
    cout << "l.get_length: " << l.get_length() << endl;
    l.print();
    return 0;
}