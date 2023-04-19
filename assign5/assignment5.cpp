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


class Queue {
    private: 
        Node* head;
        Node* tail;
        int length;
    public:
        Queue();
        ~Queue();
        int get_length() const;

        void enqueue(const int val); //pushes to the back of the queue
        int dequeue(); //pops from the front of the queue
        
        void print() const;
};
Queue::Queue() {
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}
Queue::~Queue() {
    int n = this->length; //exists so that it doesnt get modified during the for loop
    for (int i = 0; i < n; i++) {
        this->dequeue();
    }
}
int Queue::get_length() const {return this->length;}

//pushes in a value to the back of the queue.
void Queue::enqueue(const int val) {
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
int Queue::dequeue() {
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

    return 0;
}