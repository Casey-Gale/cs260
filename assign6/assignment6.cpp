#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Node {
    public: 
        int val;
        int weight;
        Node* left;
        Node* right;
        Node();
        Node(int new_val);
        void print_info();
};
Node::Node() {
    val = 0;
    weight = 0;
    left = nullptr;
    right = nullptr;
}
Node::Node(int new_val) {
    val = new_val;
    weight = 0;
    left = nullptr;
    right = nullptr;
}
void Node::print_info() {
    cout << "current: " << this << endl;
    if(this != nullptr) {
        cout << "val: " << this->val << endl;
        cout << "left:  " << this->left << endl;
        cout << "right: " << this->right << endl;
    }
}

class BST {
    public: 
        Node* root;
        BST();
        ~BST();

        void add(int new_val);
        void add(Node* new_ptr);
        int remove(int old_val);

        void print_in_order();
        void in_order_traversal(Node* current);
        
};
BST::BST() {
    root = nullptr;
}
BST::~BST() {
    // cout << "bst destructor" << endl;
}

// function adds a node with val = 'new_val' to the BST 
void BST::add(int new_val) {
    Node* current = root;
    if(current == nullptr) {
        root = new Node(new_val);
        return;
    }

    // while loop takes current to the parent of where we want to insert
    while(true) {
        if(new_val <= current->val) {
            if(current->left != nullptr) {
                current = current->left;
            }
            else {
                current->left = new Node(new_val);
                return;
            }
        }
        else {
            if(current->right != nullptr) {
                current = current->right;
            }
            else {
                current->right = new Node(new_val);
                return;
            }
        }
    }
}

// function adds a ptr to an existing node to the BST
void BST::add(Node* new_ptr) {
    if(new_ptr == nullptr) {
        return;
    }
    if(root == nullptr) {
        root = new_ptr;
        return;
    }

    Node* current = root;
    // while loop takes current to the parent of where we want to insert
    while(true) {

        if(new_ptr->val <= current->val) {
            if(current->left != nullptr) {
                current = current->left;
            }
            else {
                current->left = new_ptr;
                return;
            }
        }
        else {
            if(current->right != nullptr) {
                current = current->right;
            }
            else {
                current->right = new_ptr;
                return;
            }
        }
    }
}

// should walk through in-order traversal 'index' times to arrive at desired node
// returns integer '0' if successfully removed object, returns '1' if object not found
int BST::remove(int old_val) {

    if(root == nullptr) {
        return 1;
    }

    Node* current = root;
    Node* previous;

    // while loop hopefully takes current to the node that will be deleted
    // this happens by looping until current->val == old_val
    // if current->left < old_val and current->right > old_val, but current->val != old_val, return an integer for error
    while(current->val != old_val) {
        previous = current;
        if(current->val > old_val) {
            if(current->left != nullptr) {
                current = current->left;
            }
            else {
                // in this scenario, current->val > old_val. however, current->left is nullptr. this means that the value we're looking for cant be found
                return 1;
            }
        }
        else {
            if(current->right != nullptr) {
                current = current->right;
            }
            else {
                // in this scenario, current->val <= old_val. however, current->right is nullptr. this means that the value we're looking for cant be found
                return 1;
            }
        }
    }

    // if removing root node
    if(current == nullptr) {
        // the tree is empty, so there is nothing to be removed from it
        return 1;
    }
    
    Node* p_left = current->left;
    Node* p_right = current->right;

    if(current == root) {
        delete current;
        root = p_left;
        add(p_right);
    }

    // if not removing root node
    else {
        // this if/else tries to sever the connection between the previous node and the node we are deleting
        if(previous->left == current) {
            previous->left = nullptr;
        }
        else {
            previous->right = nullptr;
        }
        delete current;
        add(p_left);
        add(p_right);
    }

    return 0;
}

void BST::print_in_order() {
    in_order_traversal(root);
    cout << endl;
}

void BST::in_order_traversal(Node* current) {
    if(current != nullptr) {
        in_order_traversal(current->left);
        cout << current->val << " ";
        in_order_traversal(current->right);
    }
}

void do_testing() {
    BST t;

    t.add(10);
    cout << "TESTING ADD TO AN EMPTY TREE" << endl;
    cout << "EXPECTED: 10" << endl;
    cout << "ACTUAL:   ";
    t.print_in_order();

    t.add(15);
    cout << "TESTING ADD TO THE RIGHT OF THE ROOT NODE" << endl;
    cout << "EXPECTED: 10 15" << endl;
    cout << "ACTUAL:   ";
    t.print_in_order();

    t.add(5);
    cout << "TESTING ADD TO THE LEFT OF THE ROOT NODE" << endl;
    cout << "EXPECTED: 5 10 15" << endl;
    cout << "ACTUAL:   ";
    t.print_in_order();

    t.add(9);
    cout << "TESTING ADD TO A BALANCED TREE" << endl;
    cout << "EXPECTED: 5 9 10 15" << endl;
    cout << "ACTUAL:   ";
    t.print_in_order();

    t.add(14);
    cout << "TESTING ADD TO A BALANCED TREE" << endl;
    cout << "EXPECTED: 5 9 10 14 15" << endl;
    cout << "ACTUAL:   ";
    t.print_in_order();

    for(int i = 0; i < 10; i++) {
        t.add(i);
    }
    cout << "TESTING ADDING VALUES 0 THROUGH 9 TO AN EXISTING TREE" << endl;
    cout << "EXPECTED: 0 1 2 3 4 5 5 6 7 8 9 9 10 14 15" << endl;
    cout << "ACTUAL:   ";
    t.print_in_order();


    cout << endl << endl;

    cout << "TESTING REMOVING THE VALUE 5 FROM A TREE CONTAINING MULTIPLE 5s" << endl;
    cout << "EXPECTED RETURN VALUE: 0" << endl;
    cout << "ACTUAL:                " << t.remove(5) << endl;
    cout << "EXPECTED: 0 1 2 3 4 5 6 7 8 9 9 10 14 15" << endl;
    cout << "ACTUAL:   ";
    t.print_in_order();

    cout << "TESTING REMOVING THE VALUE 15 FROM A TREE CONTAINING ONE 15" << endl;
    cout << "EXPECTED RETURN VALUE: 0" << endl;
    cout << "ACTUAL:                " << t.remove(15) << endl;
    cout << "EXPECTED: 0 1 2 3 4 5 6 7 8 9 9 10 14" << endl;
    cout << "ACTUAL:   ";
    t.print_in_order();

    cout << "TESTING REMOVING A VALUE THAT DOES NOT EXIST IN A TREE" << endl;
    cout << "EXPECTED RETURN VALUE: 1" << endl;
    cout << "ACTUAL:                " << t.remove(100) << endl;
    cout << "EXPECTED: 0 1 2 3 4 5 6 7 8 9 9 10 14" << endl;
    cout << "ACTUAL:   ";
    t.print_in_order();

    cout << "TESTING REMOVING 10 VALUES THAT EXIST IN A TREE" << endl;
    cout << "EXPECTED RETURN VALUES: 0 0 0 0 0 0 0 0 0 0" << endl;
    cout << "ACTUAL:                 ";
    for(int i = 0; i < 10; i++) {
        cout << t.remove(i) << " ";
    }
    cout << endl;
    cout << "EXPECTED: 9 10 14" << endl;
    cout << "ACTUAL:   ";
    t.print_in_order();

    t.remove(9);
    t.remove(10);
    cout << "TESTING REMOVING A VALUE FROM A TREE WITH A SINGLE NODE" << endl;
    cout << "EXPECTED RETURN VALUE: 0" << endl;
    cout << "ACTUAL:                " << t.remove(14) << endl;
    cout << "EXPECTED: " << endl;
    cout << "ACTUAL:   ";
    t.print_in_order();

    cout << "TESTING REMOVING A VALUE FROM AN EMPTY TREE" << endl;
    cout << "EXPECTED RETURN VALUE: 1" << endl;
    cout << "ACTUAL:                " << t.remove(1) << endl;
    cout << "EXPECTED: " << endl;
    cout << "ACTUAL:   ";
    t.print_in_order();
}

int main() {

    do_testing();

    return 0;
}