#include <iostream>
#include <string>
#include <vector>

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

class GraphNode {
    private: 
        string val;
        vector<edge*> neighbors;
    public:
        GraphNode();
        ~GraphNode();
        GraphNode(string new_val);
        void add_edge(GraphNode* destination, int weight);
        string get_value();
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
string GraphNode::get_value() {return this->val;}
vector<edge*> GraphNode::get_neighbors() {return neighbors;}

class Graph {
    private:
        // way of storing data
        vector<GraphNode*> nodes;
    public:
        Graph();
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
};

Graph::Graph() {
    // do nothing i guess
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
    if(source_node != nullptr && destination_name != nullptr) {
        source_node->add_edge(destination_node, weight);
        destination_node->add_edge(source_node, weight);
    }

}

string shortest_path(string source_name) {

}


int main() {
    // create an edge to test :)
    edge *new_edge = new edge{nullptr, nullptr, 42};
    cout << "new_edge->source: " << new_edge->source << endl << "new_edge->destination: " << new_edge->destination << endl << "new_edge->weight: " << new_edge->weight << endl << endl;

    // create a simple node to test :)
    GraphNode* new_node = new GraphNode("Corvallis"); // default constructor
    cout << "new_node->get_value(): " << new_node->get_value() << endl << "new_node->get_neighbors().size(): " << new_node->get_neighbors().size() << endl << endl;

    // add edge to node :)
    new_node->add_edge(new_node, 1);
    cout << "new_node->get_value(): " << new_node->get_value() << endl << "new_node->get_neighbors().at(0)->destination->get_value(): " << new_node->get_neighbors().at(0)->destination->get_value() << endl << endl;

    // create graph

    return 0;
}