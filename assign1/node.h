#ifndef NODE
#define NODE

class Node
{
public:
    Marble m;
    Node* next;
    Node();
};

Node::Node() {
    this->m.set_color("N/A");
    this->next = nullptr;
}

#endif