#include <iostream>
#include <string>

using std::cout;
using std::endl;

template <class T> class Node {
    private:
        T val;
        Node<T>* next;
    public:
        Node<T>();
        Node<T>(T);
        T get_val() const;
        void set_val(T);
        Node<T>* get_next();
        void set_next(Node<T>*);
};

template <class T> Node<T>::Node() {
    this->val = 0; //probably doesnt work with templates
    this->next = nullptr;
}
template <class T> Node<T>::Node(T val) {
    this->val = val;
    this->next = nullptr;
}
template <class T> T Node<T>::get_val() const {return this->val;}
template <class T> void Node<T>::set_val(T val) {this->val = val;}
template <class T> Node<T>* Node<T>::get_next() {return this->next;}
template <class T> void Node<T>::set_next(Node* next) {this->next = next;}

template <class T> class Queue {
    private: 
        Node<T>* head;
        Node<T>* tail;
        int length;
    public:
        Queue();
        ~Queue();
        int get_length() const;

        void enqueue(T val); //pushes to the back of the queue
        T dequeue(); //pops from the front of the queue
        T peek(); //returns the value from the front of the queue without removing it
        
        void print() const;
};
template <class T> Queue<T>::Queue() {
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}
template <class T> Queue<T>::~Queue() {
    int n = this->length; //exists so that it doesnt get modified during the for loop
    for (int i = 0; i < n; i++) {
        this->dequeue();
    }
}
template <class T> int Queue<T>::get_length() const {return this->length;}

//pushes in a value to the back of the queue.
template <class T> void Queue<T>::enqueue(T val) {
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
//throws int 1 if length == 0
template <class T> T Queue<T>::dequeue() {
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

//returns the value from the front of the queue without removing it
//throws int 2 if length == 0
template <class T> T Queue<T>::peek() {
    if(this->length == 0) {
        throw 2;
    }
    return this->head->get_val();
}

//prints out the entire queue from the front to the back. assumes a valid value for length
template <class T> void Queue<T>::print() const {
    Node<T>* current = this->head;
    for(int i = 0; i < this->length; i++) {
        cout << current->get_val() << " ";
        current = current->get_next();
    }
    if(this->length == 0) {
        cout << "The queue is empty" << endl;
    }
    cout << endl;
}

void test_queue_with_int() {
    Queue<int> q_int;
    q_int.enqueue(1);
    cout << "TEST NUMBER 1: Queue<int>::enqueue()" << endl;
    cout << "TEST 1.1: enqueue() when there is 0 in the queue:" << endl;
    cout << "Expected: 1" << endl;
    cout << "Actual: ";
    q_int.print();
    cout << endl;

    q_int.enqueue(2);
    q_int.enqueue(3);
    q_int.enqueue(4);
    cout << "TEST 1.2: enqueue() when there is >0 in the queue:" << endl;
    cout << "Expected: 1 2 3 4" << endl;
    cout << "Actual: ";
    q_int.print();
    cout << endl;


    cout << "TEST NUMBER 2: Queue<int>::dequeue() and peek()" << endl;
    cout << "TEST 2.1: peek() when there is >0 in the queue:" << endl;
    cout << "Expected: 1" << endl;
    cout << "Actual: " << q_int.peek() << endl;
    cout << "TEST 2.2: print() after peek():" << endl;
    cout << "Expected: 1 2 3 4" << endl;
    cout << "Actual: ";
    q_int.print();
    cout << endl;

    cout << "TEST 2.3: dequeue() when there is >0 in the queue:" << endl;
    cout << "Expected: 1" << endl;
    cout << "Actual: " << q_int.dequeue() << endl;
    cout << "TEST 2.4: print() after dequeue():" << endl;
    cout << "Expected: 2 3 4" << endl;
    cout << "Actual: ";
    q_int.print();
    cout << endl;

    q_int.dequeue();
    q_int.dequeue();
    q_int.dequeue();
    try {
        cout << "TEST 2.5: peek() when there is 0 in the queue:" << endl;
        cout << "Expected: There is nothing to peek at!" << endl;
        cout << "Actual: " << q_int.peek() << endl;
        cout << "TEST 2.6: print() after peek():" << endl;
        cout << "Expected: " << endl;
        cout << "Actual: ";
        q_int.print();
        cout << endl;
    }
    catch(int n) {
        if(n == 1) {
            cout << "There's nothing to dequeue!" << endl;
        }
        else if(n == 2) {
            cout << "There's nothing to peek at!" << endl;
        }
    }
    try {
        cout << "TEST 2.7: dequeue() when there is 0 in the queue:" << endl;
        cout << "Expected: There is nothing to dequeue!" << endl;
        cout << "Actual: " << q_int.dequeue() << endl;
        cout << "TEST 2.8: print() after dequeue():" << endl;
        cout << "Expected: " << endl;
        cout << "Actual: ";
        q_int.print();
        cout << endl;
    }
    catch(int n) {
        if(n == 1) {
            cout << "There's nothing to dequeue!" << endl;
        }
        else if(n == 2) {
            cout << "There's nothing to peek at!" << endl;
        }
    }
}
void test_queue_with_string() {
    
    Queue<std::string> q_int;
    q_int.enqueue("string 1 ");
    cout << "TEST NUMBER 3: Queue<std::string>::enqueue()" << endl;
    cout << "TEST 3.1: enqueue() when there is 0 in the queue:" << endl;
    cout << "Expected: string 1 " << endl;
    cout << "Actual: ";
    q_int.print();
    cout << endl;

    q_int.enqueue("string 2 ");
    q_int.enqueue("string 3 ");
    q_int.enqueue("string 4 ");
    cout << "TEST 3.2: enqueue() when there is >0 in the queue:" << endl;
    cout << "Expected: string 1  string 2  string 3  string 4" << endl;
    cout << "Actual: ";
    q_int.print();
    cout << endl;


    cout << "TEST NUMBER 4: Queue<std::string>::dequeue() and peek()" << endl;
    cout << "TEST 4.1: peek() when there is >0 in the queue:" << endl;
    cout << "Expected: string 1 " << endl;
    cout << "Actual: " << q_int.peek() << endl;
    cout << "TEST 4.2: print() after peek():" << endl;
    cout << "Expected: string 1  string 2  string 3  string 4" << endl;
    cout << "Actual: ";
    q_int.print();
    cout << endl;

    cout << "TEST 4.3: dequeue() when there is >0 in the queue:" << endl;
    cout << "Expected: string 1 " << endl;
    cout << "Actual: " << q_int.dequeue() << endl;
    cout << "TEST 4.4: print() after dequeue():" << endl;
    cout << "Expected: string 2  string 3  string 4" << endl;
    cout << "Actual: ";
    q_int.print();
    cout << endl;

    q_int.dequeue();
    q_int.dequeue();
    q_int.dequeue();
    try {
        cout << "TEST 4.5: peek() when there is 0 in the queue:" << endl;
        cout << "Expected: There is nothing to peek at!" << endl;
        cout << "Actual: " << q_int.peek() << endl;
        cout << "TEST 4.6: print() after peek():" << endl;
        cout << "Expected: " << endl;
        cout << "Actual: ";
        q_int.print();
        cout << endl;
    }
    catch(int n) {
        if(n == 1) {
            cout << "There's nothing to dequeue!" << endl;
        }
        else if(n == 2) {
            cout << "There's nothing to peek at!" << endl;
        }
    }
    try {
        cout << "TEST 4.7: dequeue() when there is 0 in the queue:" << endl;
        cout << "Expected: There is nothing to dequeue!" << endl;
        cout << "Actual: " << q_int.dequeue() << endl;
        cout << "TEST 4.8: print() after dequeue():" << endl;
        cout << "Expected: " << endl;
        cout << "Actual: ";
        q_int.print();
        cout << endl;
    }
    catch(int n) {
        if(n == 1) {
            cout << "There's nothing to dequeue!" << endl;
        }
        else if(n == 2) {
            cout << "There's nothing to peek at!" << endl;
        }
    }
}

//runs through a number of hard-coded test cases
void do_testing() {
    test_queue_with_int();
    cout << endl << endl << endl;
    test_queue_with_string();

    cout << endl << "Ending testing..." << endl;
}


int main() {
    do_testing();
    // Queue<std::string> q;
    // q.print();
    // for (int i = 0; i < 10; i++) {
    //     q.enqueue("hello");
    // }
    // q.print();
    // for(int i = 0; i < 5; i++) {
    //     try {
    //         cout << "q.dequeue(" << i << "): " << q.dequeue() << endl;
    //     }
    //     catch (int n) {
    //         if(n == 1) {
    //             cout << "There's nothing to dequeue!" << endl;
    //         }
    //         else if(n == 2) {
    //             cout << "There's nothing to peek at!" << endl;
    //         }
    //     }
    // }
    // q.print();
    // for(int i = 0; i < 6; i++) {
    //     try {
    //         cout << "q.dequeue(" << i << "): " << q.dequeue() << endl;
    //     }
    //     catch (int n) {
    //         if(n == 1) {
    //             cout << "There's nothing to dequeue!" << endl;
    //         }
    //         else if(n == 2) {
    //             cout << "There's nothing to peek at!" << endl;
    //         }
    //     }
    // }
    // q.print();
    // cout << endl << endl;

    return 0;
}