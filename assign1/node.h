#ifndef NODE
#define NODE

class Node
{
private:
    marble m;
    Node* next;
public:
    Node();
};

Node::Node() {
    this->m = 0;
    this->next = nullptr;
}