#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Node {
    public: 
        int val;
        Node* left;
        Node* right;
        Node();
        Node(int new_val);
};
Node::Node() {
    val = 0;
    left = nullptr;
    right = nullptr;
}
Node::Node(int new_val) {
    val = new_val;
    left = nullptr;
    right = nullptr;
}

class BST {
    public: 
        Node* root;
        Node* current;
        BST();
        ~BST();

        void add(int new_val);
        
};
BST::BST() {
    root = nullptr;
    current = nullptr;
}
BST::~BST() {
    cout << "bst destructor" << endl;
}

void BST::add(int new_val) {
    current = root;
    if(current == nullptr) {
        root = new Node(new_val);
        return;
    }

    //while loop takes current to the parent of where we want to insert
    while(current->left != nullptr && current->right != nullptr) {
        if(current->left
    }
}

int main() {
    cout << "Ending program :)" << endl;
    return 0;
}