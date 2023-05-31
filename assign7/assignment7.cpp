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

        HashTable();
        HashTable(const int new_size);

        int hash(string new_val);
        void insert(string new_val);
        bool contains(string possible_val);
};

HashTable::HashTable() {
    this->size = 10;
    table_head = new Node*[10];
    for(int i = 0; i < this->size; i++) {
        table_head[i] = nullptr;
    }
}
HashTable::HashTable(const int new_size) {
    this->size = new_size;
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
    if(table_head[n] == nullptr) {
        cout << "wassup" << endl;
        table_head[n] = new Node(new_val);
    }
    else {
        cout << "oh snappa" << endl;
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

int main() {
    HashTable ht(5);
    // cout << ht.hash("") << endl;

    // Node n1("5");
    // n1.print();
    // cout << endl;
    // n1.insert("22");
    // n1.print();
    // cout << endl;
    // n1.insert("12905jasdklf");
    // n1.print();
    // cout << endl;

    ht.insert("hello");
    ht.insert("helll");
    cout << "DOES ht CONTAIN 'hello': " << ht.contains("hello") << endl;
    cout << "DOES ht CONTAIN 'helol': " << ht.contains("helol") << endl;
    cout << "DOES ht CONTAIN 'heyo' : " << ht.contains("heyo") << endl;
    cout << "DOES ht CONTAIN 'helll': " << ht.contains("helll") << endl;

    return 0;
}