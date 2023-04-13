#include <iostream>

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


class Queue {
    private: 
        Node* head;
        Node* tail;
        int length;
    public:
        Queue();
        int get_length() const;

        void push_back(const int val); //pushes to the back of the queue
        int pop_front(); //pops from the front of the queue
        
        void push_mid(const int val, const int i); //pushes to the middle of the queue, specified by the ith index from the front
        int pop_mid(const int i); //pops from the middle of the queue, specified by the ith index from the front

        void print() const;
};
Queue::Queue() {
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}
int Queue::get_length() const {return this->length;}

//pushes in a value to the back of the queue.
void Queue::push_back(const int val) {
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

//pops out the front value in the queue. 
int Queue::pop_front() {
    //if length == 0
    if(this->length == 0) {
        throw "There's nothing to pop!";
    }
    //if length >= 1
    //int pop_val = this->head->get_val();
    //Node* temp = this->head->get_next();
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

//pushes in a value to a specified location in the queue. doesn't assume a valid index
void Queue::push_mid(const int val, const int i) {
    //if length == 0

    //if length < i

    //if length == i

    //else
}

//pops out a value from a specified location in the queue. doesn't assume a valid index
int Queue::pop_mid(const int i) {
    //if length == 0

    //if length < i

    //if length == i

    //else
    return 0;
}

//prints out the entire queue from the front to the back. assumes a valid value for length
void Queue::print() const {
    Node* current = this->head;
    for(int i = 0; i < this->length; i++) {
        cout << current->get_val() << " ";
        current = current->get_next();
    }
    if(this->length == 0) {
        cout << "The queue is empty" << endl;
    }
    cout << endl;
}


int main() {
//    cout << "opening program" << endl;
    Queue q;
    q.print();
    for (int i = 0; i < 10; i++) {
        q.push_back(i);
    }
    q.print();
    for(int i = 0; i < 5; i++) {
        try {
            cout << "q.pop_front(" << i << "): " << q.pop_front() << endl;
        }
        catch (const std::string str) {
            cout << str << endl;
        }
    }
    q.print();
    for(int i = 0; i < 6; i++) {
        try {
            cout << "q.pop_front(" << i << "): " << q.pop_front() << endl;
        }
        catch (const std::string str) {
            cout << str << endl;
        }    }
    q.print();
    cout << "length is " << q.get_length() << endl;
    return 0;
}