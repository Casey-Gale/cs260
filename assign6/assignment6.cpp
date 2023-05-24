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
    cout << "bst destructor" << endl;
}

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
    // cout << endl << "attempting to add existing node to the tree..." << endl;
    // cout << "node details: " << endl;
    // new_ptr->print_info();
    // cout << endl;
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

        // cout << "new_ptr address == " << new_ptr << endl;
        // // cout << "new_ptr->val == " << new_ptr->val << endl;
        // cout << "current->val == " << current->val << endl;
        // cout << endl;

        // current->print_info();
        // cout << endl;
        // cout << "we did not get this far" << endl;
        if(new_ptr->val <= current->val) {
            // cout << "moving to the left... (line 107)" << endl;
            if(current->left != nullptr) {
                current = current->left;
            }
            else {
                current->left = new_ptr;
                return;
            }
        }
        else {
            // cout << "moving to the right... (line 117)" << endl;
            if(current->right != nullptr) {
                current = current->right;
            }
            else {
                current->right = new_ptr;
                return;
            }
        }
    }

    // print_in_order();
}

// should walk through in-order traversal 'index' times to arrive at desired node
// returns integer '0' if successfully removed object, returns '1' if object not found
int BST::remove(int old_val) {
    Node* current = root;
    Node* previous;

    // while loop hopefully takes current to the node that will be deleted
    // this happens by looping until current->val == old_val
    // if current->left < old_val and current->right > old_val, but current->val != old_val, return an integer for error
    while(current->val != old_val) {
        // cout << "wuh oh" << endl;
        previous = current;
        if(current->val > old_val) {
            if(current->left != nullptr) {
                // cout << "moving to the left (line 133)" << endl;
                current = current->left;
            }
            else {
                // cout << "value not found (current->left == nullptr) (line 137)" << endl;
                // in this scenario, current->val > old_val. however, current->left is nullptr. this means that the value we're looking for cant be found
                return 1;
            }
        }
        else {
            if(current->right != nullptr) {
                // cout << "moving to the right (line 144)" << endl;
                current = current->right;
            }
            else {
                // cout << "value not found (current->right == nullptr) (line 148)" << endl;
                // in this scenario, current->val <= old_val. however, current->right is nullptr. this means that the value we're looking for cant be found
                return 1;
            }
        }
    }

    // if removing root node
    if(current == nullptr) {
        // cout << "the tree is empty" << endl;
        // the tree is empty, so there is nothing to be removed from it
        return 1;
    }
    
    Node* p_left = current->left;
    Node* p_right = current->right;

    if(current == root) {
        // cout << "deleting the root..." << endl;
        // cout << "node details: " << endl;
        // current->print_info();
        // cout << endl;
        delete current;
        root = p_left;
        add(p_right);
    }

    // if not removing root node
    else {
        // cout << endl << "deleting an intermediate node..." << endl;
        // cout << "node details: " << endl;
        // current->print_info();
        // cout << endl;

        // this if/else tries to sever the connection between the previous node and the node we are deleting
        if(previous->left == current) {
            // cout << "severing the left of node with val = " << previous->val << endl;
            previous->left = nullptr;
        }
        else {
            // cout << "severing the right of node with val = " << previous->val << endl;
            previous->right = nullptr;
        }
        delete current;
        add(p_left);
        add(p_right);
    }

    return 0;
}

// Node* BST::find_highest_descendant(Node* current, Node* maximum) {
//     // always compare current node to maximum, then return the greater of the two
//     if(current != nullptr) {
//         Node* temp_right = find_highest_descendant(current->right);
//     }
// }

// Node* BST::move_in_order(Node* current, int& index) {
//     if(index > 0) {
//         if(current != nullptr) {
//             move_in_order(current->left, index);
//             index--;
//             move_in_order(current->right, index);
//         }
//     }
//     else {
//         return current;
//     }
// }



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

int main() {

    BST tree;
    tree.add(4);
    tree.add(5);
    tree.add(2);
    tree.add(3);
    tree.add(8);
    tree.add(6);
    tree.add(5);

    // Node* n1 = new Node(100);
    // n1->left = new Node(99);
    // n1->right = new Node(1500);

    // tree.add(n1);

    // BST tree2;
    // tree2.add(nullptr);

    tree.print_in_order();

    tree.remove(8);

    tree.print_in_order();

    cout << "Ending program :)" << endl;
    return 0;
}