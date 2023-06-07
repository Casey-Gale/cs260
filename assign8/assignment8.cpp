#include <iostream>
#include <string>
#include <vector>
#include <set>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class GraphNode;

struct edge {
    GraphNode* source;
    GraphNode* destination;
    int weight;
};

// auto sorted list from assignment 5!
class Node {
    private:
        
    public:
        edge* val;
        Node* next;
        Node();
        Node(edge*);
};

Node::Node() {
    this->val = nullptr;
    this->next = nullptr;
}
Node::Node(edge* val) {
    this->val = val;
    this->next = nullptr;
}

class List {
    private: 
        Node* head;
        int length;
    public:
        List();
        int get_length() const;
        void push(edge* val); //pushes to a sorted location in the list
        edge* pop_front();
};
List::List() {
    this->head = nullptr;
    this->length = 0;
}
int List::get_length() const {return this->length;}

//automatically pushes a value to a sorted list in a sorted position
void List::push(edge* new_val) {
    //cout << "Pushing " << new_val << endl;
    //if list is empty
    Node* current = this->head;
    if(this->length == 0) {
        //cout << "length == 0" << endl;
        this->head = new Node(new_val); // new node->next is automatically nullptr
    }
    // checks if the value is less than the first 
    else if(new_val->weight < this->head->val->weight) {
        //cout << "current == head" << endl;
        current = new Node(new_val);
        current->next = this->head;
        this->head = current;
    }
    //else
    else {
        while(current->next != nullptr && new_val->weight > current->next->val->weight) {
            current = current->next;
        }
    
        // checks if current is at the end of the list
        if(current->next == nullptr) {
            //cout << "current->next == nullptr" << endl;
            current->next = new Node(new_val);
        }
        // now, we may assume that current is pointing to an object in the middle of the list
        else {
            //cout << "current is in the middle" << endl;
            Node* after = current->next;
            current->next = new Node(new_val);
            current->next->next = after;
        }
    }
    this->length++;
}

// pops out the front (smallest) value from the list
// ASSUMES THE LIST CONTAINS SOMETHING
edge* List::pop_front() {
    edge* e = this->head->val;
    Node* current = this->head->next;
    delete this->head;
    this->head = current;
    return e;
}





class GraphNode {
    private: 
        string val;
        vector<edge*> neighbors;
    public:
        GraphNode();
        ~GraphNode();
        GraphNode(string new_val);
        void add_edge(GraphNode* destination, int weight);
        string get_val();
        vector<edge*> get_neighbors();
};

GraphNode::GraphNode() {
    this->val = "";
}
GraphNode::GraphNode(string new_val) {
    this->val = new_val;
}
GraphNode::~GraphNode() {
    for(auto neighbor : neighbors) {
        delete neighbor;
    }
}
void GraphNode::add_edge(GraphNode* destination, int weight) {
    edge* new_edge = new edge{this, destination, weight};
    neighbors.push_back(new_edge);
    //okay!
}
string GraphNode::get_val() {return this->val;}
vector<edge*> GraphNode::get_neighbors() {return neighbors;}

class Graph {
    private:
        // way of storing data
        vector<GraphNode*> nodes;
    public:
        Graph();
        Graph(GraphNode* new_node);
        ~Graph();
        // get size of graph nodes list
        int get_size();
        // add node
        void add_node(string new_name);
        // add edge
        void add_edge(string source_name, string destination_name, int weight);
        // shortest path, return string representing shortest paths from source to each destination node
        string shortest_path(string source_name);
        // minimum spanning tree
        Graph* mst();
};

Graph::Graph() {
    // do nothing i guess
}
Graph::Graph(GraphNode* new_node) {
    this->nodes.push_back(new_node);
}

Graph::~Graph() {

}

int Graph::get_size() {
    return nodes.size();
}

void Graph::add_node(string new_name) {
    GraphNode* new_node = new GraphNode(new_name);
    this->nodes.push_back(new_node);
}

void Graph::add_edge(string source_name, string destination_name, int weight) {
    GraphNode* source_node = nullptr;
    GraphNode* destination_node = nullptr;
    // find source location AND destination location
    for(auto node : nodes) {
        if(source_name == node->get_val()) {
            source_node = node;
        }
        if(destination_name == node->get_val()) {
            destination_node = node;
        }
    }
    // make edge between source and destination
    if(source_node != nullptr && destination_node != nullptr) {
        source_node->add_edge(destination_node, weight);
        destination_node->add_edge(source_node, weight);
    }

}

string shortest_path(string source_name, string destination_name) {
    return ":)";
}

Graph* Graph::mst() {
    // create an ascending list of edges in the whole graph
    // implemented using auto-sorted list from assignment 5
    List edges;
    vector<set<GraphNode*>> subsets;
    for(GraphNode* node : this->nodes) {
        for(edge* e : node->get_neighbors()) {
            edges.push(e);
        }
        subsets.insert(node);
    }
    // create a vector of subsets containing a single node each ^^

    // iterate through all edges (lowest weights first) and attempt to union sets
    // if possible edge would create a cycle, remove it

    for(edge* e : edges) {
        for(auto subset : subsets) {
            if(subset.count(e->source)) {
                // if subset contains e->source, make note of subset (subset ptr maybe?)
            }
            if(subset.count(e->destination)) {
                // if subset contains e->destination, make note of subset (subset ptr maybe?)
            }
            
        }
        // if e->source set == e->destination set, remove edge
    }

    return nullptr;
}


int main() {
    // create an edge to test :)
    edge *new_edge = new edge{nullptr, nullptr, 42};
    cout << "new_edge->source: " << new_edge->source << endl << "new_edge->destination: " << new_edge->destination << endl << "new_edge->weight: " << new_edge->weight << endl << endl;

    // create a simple node to test :)
    GraphNode* new_node = new GraphNode("Corvallis"); // default constructor
    cout << "new_node->get_val(): " << new_node->get_val() << endl << "new_node->get_neighbors().size(): " << new_node->get_neighbors().size() << endl << endl;

    // add edge to node :)
    new_node->add_edge(new_node, 1);
    cout << "new_node->get_val(): " << new_node->get_val() << endl << "new_node->get_neighbors().at(0)->destination->get_val(): " << new_node->get_neighbors().at(0)->destination->get_val() << endl << endl;

    // create graph

    return 0;
}