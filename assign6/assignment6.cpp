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

class BST {
    public: 
        Node* root;
        BST();
        ~BST();

        void add(int new_val);
        void remove(const int index);
        Node* find_highest_descendant(Node* current, Node* maximum);
        Node* move_in_order(Node* current, int& index);

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

    //while loop takes current to the parent of where we want to insert
    // the parameters of this while loop are bad and WRONG !!! (low tier god)
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

// should walk through in-order traversal 'index' times to arrive at desired node
void BST::remove(const int index) {
    int n = index;
    move_in_order(root, n);
}

// Node* BST::find_highest_descendant(Node* current, Node* maximum) {
//     // always compare current node to maximum, then return the greater of the two
//     if(current != nullptr) {
//         Node* temp_right = find_highest_descendant(current->right);
//     }
// }

Node* BST::move_in_order(Node* current, int& index) {
    if(index > 0) {
        if(current != nullptr) {
            move_in_order(current->left, index);
            index--;
            move_in_order(current->right, index);
        }
    }
    else {
        return current;
    }
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

int main() {

    BST tree;
    tree.add(4);
    tree.add(5);
    tree.add(2);
    tree.add(3);
    tree.add(8);
    tree.add(6);
    tree.add(5);


    tree.print_in_order();

    cout << "Ending program :)" << endl;
    return 0;
}