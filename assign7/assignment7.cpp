#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Node {
    public:
        string val;
        Node* next;

        Node();
        Node(string new_val);
        // recursive insert function??
        void insert(string new_val);
        // recursive print function
        void print();
};

Node::Node() {
    this->val = "NULL";
    this->next = nullptr;
}
Node::Node(string new_val) {
    this->val = new_val;
    this->next = nullptr;
}

void Node::insert(string new_val) {
    if(this->next == nullptr) {
        this->next = new Node(new_val);
    }
    else {
        this->next->insert(new_val);
    }
}

void Node::print() {
    cout << this->val << " ";
    if(this->next != nullptr) {
        this->next->print();
    }
}

class HashTable {
    public: 
        int size;
        Node** table_head;
        int num_collisions;
        int num_elements;

        HashTable();
        HashTable(const int new_size);

        int hash(string new_val);
        void insert(string new_val);
        bool contains(string possible_val);
};

HashTable::HashTable() {
    this->size = 10;
    this->num_collisions = 0;
    this->num_elements = 0;
    table_head = new Node*[10];
    for(int i = 0; i < this->size; i++) {
        table_head[i] = nullptr;
    }
}
HashTable::HashTable(const int new_size) {
    this->size = new_size;
    this->num_collisions = 0;
    this->num_elements = 0;
    table_head = new Node*[new_size];
    for(int i = 0; i < this->size; i++) {
        table_head[i] = nullptr;
    }
}

// very bad hash function, but it gets the job done:
// sets hash value equal to the length of the string mod table size
int HashTable::hash(string new_val) {
    return new_val.size() % this->size;
}

// inserts a new string into the hash table
// if there's a collision, add string to a linked list at that location
void HashTable::insert(string new_val) {
    // when inserting, we need to keep track of whether or not the string is empty
    int n = hash(new_val);
    this->num_elements++;
    if(table_head[n] == nullptr) {
        table_head[n] = new Node(new_val);
    }
    else {
        this->num_collisions++;
        table_head[n]->insert(new_val);
    }
}

// checks to see if the given string is contained in the hash table
// returns a 1 if true and a 0 if false
bool HashTable::contains(string new_val) {
    int n = hash(new_val);
    Node* current = this->table_head[n];
    while(current != nullptr) {
        if(current->val == new_val) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void do_testing() {
    HashTable h1;
    h1.insert("hello");
    // test insert to an empty table
    cout << "TESTING INSERT TO AN EMPTY TABLE AND CONTAINS ON THE INSERTED VALUE" << endl;
    cout << "EXPECTED: Does h1 contain 'hello': 1" << endl;
    cout << "ACTUAL:   Does h1 contain 'hello': " << h1.contains("hello") << endl << endl;

    // test contains on 
    cout << "TESTING CONTAINS ON A TABLE NOT CONTAINING DESIRED VALUE" << endl;
    cout << "EXPECTED: Does h1 contain 'hi': 0" << endl;
    cout << "ACTUAL:   Does h1 contain 'hi': " << h1.contains("hi") << endl << endl;

    // test collision with an object
    h1.insert("5char");
    cout << "TESTING INSERT TO A COLLISION AND CONTAINS ON THE INSERTED VALUE" << endl;
    cout << "EXPECTED: Does h1 contain '5char': 1" << endl;
    cout << "ACTUAL:   DOES h1 contain '5char': " << h1.contains("5char") << endl << endl;

    // test contains something that doesnt exist in table
    h1.insert("hhhhh");
    cout << "TESTING INSERT TO ANOTHER COLLISION AND CONTAINS ON THE INSERTED VALUE" << endl;
    cout << "EXPECTED: Does h1 contain 'hhhhh': 1" << endl;
    cout << "ACTUAL:   Does h1 contain 'hhhhh': " << h1.contains("hhhhh") << endl << endl;
    
    // test insert to another empty location
    h1.insert("testing!");
    cout << "TESTING INSERT TO ANOTHER EMPTY LOCATION AND CONTAINS ON THE INSERTED VALUE" << endl;
    cout << "EXPECTED: Does h1 contain 'testing!': 1" << endl;
    cout << "ACTUAL:   Does h1 contain 'testing!': " << h1.contains("testing!") << endl << endl;

    // test insert "nullptr"
    h1.insert("nullptr");
    cout << "TESTING INSERT 'nullptr'" << endl;
    cout << "EXPECTED: Does h1 contain 'nullptr': 1" << endl;
    cout << "ACTUAL:   Does h1 contain 'nullptr': " << h1.contains("nullptr") << endl << endl;

    cout << "TOTAL ELEMENTS IN TABLE: " << h1.num_elements << endl;
    cout << "TOTAL COLLISIONS:        " << h1.num_collisions << endl;

}

int main() {
    // HashTable ht(5);

    // ht.insert("hello");
    // ht.insert("helll");
    // cout << "DOES ht CONTAIN 'hello': " << ht.contains("hello") << endl;
    // cout << "DOES ht CONTAIN 'helol': " << ht.contains("helol") << endl;
    // cout << "DOES ht CONTAIN 'heyo' : " << ht.contains("heyo") << endl;
    // cout << "DOES ht CONTAIN 'helll': " << ht.contains("helll") << endl << endl;

    // cout << "NUMBER OF COLLISIONS: " << ht.num_collisions << endl;
    // cout << "NUMBER OF ELEMENTS:   " << ht.num_elements << endl;

    do_testing();

    return 0;
}