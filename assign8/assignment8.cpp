#include <iostream>
#include <string>
#include <vector>
#include <set>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::set;

class GraphNode;

struct edge {
    GraphNode* source;
    GraphNode* destination;
    int weight;
    void print();
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
        Node* get_head();
        void push(edge* val); //pushes to a sorted location in the list
        edge* pop_front();
};
List::List() {
    this->head = nullptr;
    this->length = 0;
}
int List::get_length() const {return this->length;}
Node* List::get_head() {return this->head;}

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

void edge::print() {cout << "Edge between " << this->source->get_val() << " and " << this->destination->get_val() << " (Weight " << this->weight << ")" << endl;}

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
        // get nodes array
        vector<GraphNode*> get_nodes();
        // print all neighbors of all nodes
        void print_neighbors();
        // add node
        void add_node(string new_name);
        // add edge
        void add_edge(string source_name, string destination_name, int weight);
        // shortest path, return string representing shortest paths from source to each destination node
        string shortest_path(string source_name, string destination_name);
        // minimum spanning tree
        Graph* minimal_spanning_tree();
};

Graph::Graph() {
    // do nothing i guess
}
Graph::Graph(GraphNode* new_node) {this->nodes.push_back(new_node);}
Graph::~Graph() {
    // nothing so far
}
int Graph::get_size() {return this->nodes.size();}
vector<GraphNode*> Graph::get_nodes() {return this->nodes;}

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

struct sp_table {
    GraphNode* node;
    int cost;
    bool has_visited;
    sp_table* predecessor;
};

// assumes graph does not contain negative weight edges
string Graph::shortest_path(string source_name, string destination_name) {
    // make a string at the beginning of the function, then append path at the end
    string path = "";

    // algorithm: assume minimum weight to get to source node is 0, weight to get to all other nodes is infinity (-1 because this is unreachable without negative weights)
    // procedurally check lowest weighted edges to see if it would result in a lower weight path
    // we need to keep track of 4 things per node: node, path cost, has visited, shortest predecessor
    
    // set containing all nodes that have not been checked, but are connected in some way to the root node through a path of checked nodes
    set<GraphNode*> adjacent_nodes;
    // table containing all nodes in the graph, along with information about cost, whether or not the node has been visited, and its cheapest predecessor
    vector<sp_table*> table;


    for(GraphNode* node : this->nodes) {
        int c = -1;
        if(node->get_val() == source_name) {
            c = 0;
        }
        sp_table* entry = new sp_table;
        entry->node = node;
        entry->cost = c;
        entry->has_visited = false;
        entry->predecessor = nullptr;
        table.push_back(entry);
    }

    sp_table* final_destination_row = nullptr;
    // places the source node in the adjacent nodes set by itself. in future iterations edge->destinations will be inserted to this set
    bool s = false;
    bool d = false;
    for(auto row : table) {
        // cout << "row->node->get_val(): " << row->node->get_val() << endl;
        // cout << "destination_name:     " << destination_name << endl;
        if(row->node->get_val() == destination_name) {
            final_destination_row = row;
            d = true;
        }
        if(row->node->get_val() == source_name) {
            adjacent_nodes.insert(row->node);
            s = true;
        }
        if(s && d) {
            break;
        }
    }
    if(!s || !d) {
        return "No path can be found!";
    }

    // loop through every entry in the table. at each node, loop through every neighbor. at each neighbor of each node, 
    // calculate weight of path. place this in the proper cost entry, along with the direct predecessor
    bool is_finished = false;
    while(!is_finished) {
        is_finished = true;
        // cout << "troll " << endl;
        for(sp_table* row : table) {
            // cout << " viewing new row (" << row->node->get_val() << ")" << endl;
            // only looks at neighbors if node is contained in adjacent nodes
            if(adjacent_nodes.count(row->node)) {
                // cout << "  viewing adjacent node (" << row->node->get_val() << ")" << endl;
                adjacent_nodes.erase(row->node);
                for(edge* neighbor : row->node->get_neighbors()) {
                    // code that will run for every neighbor of every node
                    if(row->has_visited) {
                        break;
                    }
                    adjacent_nodes.insert(neighbor->destination);
                    sp_table* destination_row = nullptr;
                    // BELOW IS BAD! IT SHOULD NOT WORK! BAD COMPLEXITY!!
                    // it finds the destination of a given edge
                    for(int i = 0; i < table.size(); i++) {
                        // cout << "table.at(" << i << "): " << table.at(i)->node->get_val() << endl;
                        // cout << "neighbor:   " << neighbor->destination->get_val() << endl;
                        if(table.at(i)->node->get_val() == neighbor->destination->get_val()) {
                            destination_row = table.at(i);
                            break;
                        }
                    }
                    if(destination_row->has_visited) {
                        // cout << "node has been visited before" << endl;
                    }
                    // the meat of the algorithm. changes to the lower cost and sets cheapest predecessor
                    else {
                        // debug statement skips edges to already visited nodes
                        // cout << "   regarding (" << row->node->get_val() << ")" << ", (" << destination_row->node->get_val() << "): " << endl;
                        // cout << "    before destination_row->cost: " << destination_row->cost << endl;
                        // cout << "    before row->cost + neighbor->weight: " << row->cost + neighbor->weight << endl;
                        // cout << "    before destination_row->cost: " << destination_row->cost << endl;
                        // if(destination_row->predecessor != nullptr) {
                        //     cout << "    before destination_row->predecessor: " << destination_row->predecessor->node->get_val() << endl;
                        // }
                        // else {
                        //     cout << "    before destination_row->predecessor: " << destination_row->predecessor << endl;
                        // }
                        if(destination_row->cost > row->cost + neighbor->weight || destination_row->cost == -1) {
                            destination_row->cost = row->cost + neighbor->weight;
                            destination_row->predecessor = row;
                        }   
                        // cout << "    after destination_row->cost: " << destination_row->cost << endl;
                        // cout << "    after row->cost + neighbor->weight: " << row->cost + neighbor->weight << endl;
                        // cout << "    after destination_row->cost: " << destination_row->cost << endl;
                        // if(destination_row->predecessor != nullptr) {
                        //     cout << "    after destination_row->predecessor: " << destination_row->predecessor->node->get_val() << endl;
                        // }
                        // else {
                        //     cout << "    after destination_row->predecessor: " << destination_row->predecessor << endl;
                        // }
                    }
                }
                row->has_visited = true;
            }
            
            if(row->has_visited == false) {
                is_finished = false;
            }
        }
        if(adjacent_nodes.empty() && is_finished == false) {
            if(final_destination_row->cost == -1) {
                return "No path can be found!";
            }
            else {
                is_finished = true;
            }
        }
    }

    // cout << "finished with the logic!" << endl;

    //prints out the full table
    // for(auto row : table) {
    //     cout << row->node->get_val() << " | " << row->cost << " | " << row->has_visited << " | ";
    //     if(row->predecessor != nullptr) {
    //         cout << row->predecessor->node->get_val() << endl;
    //     }
    //     else {
    //         cout << row->predecessor << endl;
    //     }
    // }

    sp_table* current = final_destination_row;

    // cout << "address of final_destination_row: " << final_destination_row << endl;
    path = final_destination_row->node->get_val();
    // cout << path << endl;
    while(current->predecessor != nullptr) {
        current = current->predecessor;
        path = current->node->get_val() + "->" + path;
        // cout << path << endl;
    }
    // path = final_destination_row->node->get_val() + "->" + path;

    // cout << path << endl;

    return path;
}

Graph* Graph::minimal_spanning_tree() {
    // create an ascending list of edges in the whole graph
    // implemented using auto-sorted list from assignment 5
    Graph* mst = new Graph;
    // auto-sorted List of edges, sorted by ascending weight
    List edges;
    List confirmed_edges;
    vector<set<GraphNode*>> subsets;
    for(GraphNode* node : this->nodes) {
        mst->add_node(node->get_val());
        for(edge* e : node->get_neighbors()) {
            edges.push(e);
        }
        set<GraphNode*> s;
        s.insert(node);
        subsets.push_back(s);
    }
    // create a vector of subsets containing a single node each ^^

    // iterate through all edges (lowest weights first) and attempt to union sets
    // if possible edge would create a cycle, remove it


    Node* edge_current = edges.get_head();
    // iterates m times, where m is number of edges in graph
    while(edge_current != nullptr) {

        set<GraphNode*> source_set;
        set<GraphNode*> destination_set;
        int source_index = -1;
        int destination_index = -1;

        // iterates through all current sets to find the sets containing edge_current source and destination
        // for(auto subset : subsets) { // <- needed random access, so commented out
        for(int i = 0; i < subsets.size(); i++) {

            set<GraphNode*>& subset = subsets.at(i);
            // cout << "subsets[" << i << "]: " << &subsets.at(i) << endl;

            if(subset.count(edge_current->val->source)) {
                // if subset contains edge_current->val->source, make note of subset (subset ptr maybe?)
                source_set = subset;
                // cout << " address of source_set: " << &source_set << endl;
                source_index = i;
            }
            else {
                // cout << " source_set does not contain " << edge_current->val->source->get_val() << endl;
            }
            if(subset.count(edge_current->val->destination)) {
                // if subset contains edge_current->val->destination, make note of subset (subset ptr maybe?)
                destination_set = subset;
                // cout << " address of destination_set: " << &destination_set << endl;
                destination_index = i;
            }
            else {
                // cout << " destination_set does not contain " << edge_current->val->destination->get_val() << endl;
            }

            // cout << "source_index: " << source_index << " destination_index: " << destination_index << endl;
            if(source_index != -1 && destination_index != -1) {
                break;
            }
            
        }
        // vvvv I DONT KNOW HOW TO CHECK THIS WHEN THEYRE NOT POINTERS vvvv
        // if(source_set == nullptr || destination_set == nullptr) {
        //     cout << "SOMETHING BROKE : NEITHER OF THESE SHOULD BE NULLPTR" << endl;
        //     cout << "source_set == " << source_set << " | destination_set == " << destination_set << endl;
        // }

        // if edge_current->val->source set == edge_current->val->destination set, remove edge
        edge* e = edges.pop_front();
        // e->print();
        if(source_set == destination_set) {
            // remove edge
            // cout << "Edge would create a cycle" << endl << endl;
        }
        // now that source_set != destination_set AND neither == nullptr : 
        // we attempt to merge both sets and then delete one
        else {
            // cout << "Adding edge to mst" << endl;
            confirmed_edges.push(e);
            source_set.insert(destination_set.begin(), destination_set.end());
            if(source_index > destination_index) {
                subsets.erase(subsets.begin() + source_index);
                subsets.erase(subsets.begin() + destination_index);
            }
            else {
                subsets.erase(subsets.begin() + destination_index);
                subsets.erase(subsets.begin() + source_index);
            }

            subsets.push_back(source_set);


            // cout << "Whew! Through the scary clause" << endl << endl;
        }
        edge_current = edge_current->next;
    }

    // cout << "confirmed_edges.get_length() == " << confirmed_edges.get_length() << endl;
    int n = confirmed_edges.get_length();
    while(n > 0) {
        edge* e = confirmed_edges.pop_front();
        // e->print();
        mst->add_edge(e->source->get_val(), e->destination->get_val(), e->weight);
        // cout << "check" << endl;
        n--;
    }
    // cout << "zoo wee mama" << endl;

    return mst;
}

void Graph::print_neighbors() {
    for(int i = 0; i < this->get_size(); i++) {
        cout << "Neighbors of Node " << this->get_nodes()[i]->get_val() << ": " << endl;
        for(auto neighbor : this->get_nodes().at(i)->get_neighbors()) {
            cout << "  " << neighbor->destination->get_val() << " (" << neighbor->weight << ")" << endl;
        }
    }
} 

void do_testing() {
    Graph g1;
    Graph g2;
    Graph g3;
    Graph* min_g1;
    Graph* min_g2;
    Graph* min_g3;

    g1.add_node("A");
    g1.add_node("B");
    g1.add_node("C");
    g1.add_node("D");
    g1.add_node("E");
    g1.add_node("F");

    g1.add_edge("A", "B", 1);
    g1.add_edge("A", "D", 5);
    g1.add_edge("B", "D", 10);
    g1.add_edge("B", "C", 11);
    g1.add_edge("C", "E", 3);
    g1.add_edge("C", "F", 5);
    g1.add_edge("D", "E", 7);
    g1.add_edge("E", "F", 9);

    g2.add_node("A");
    g2.add_node("B");
    g2.add_node("C");
    g2.add_node("D");
    g2.add_node("E");
    g2.add_node("F");
    g2.add_node("G");
    g2.add_node("H");

    g2.add_edge("A", "B", 1);
    g2.add_edge("A", "D", 5);
    g2.add_edge("B", "D", 10);
    g2.add_edge("B", "C", 11);
    g2.add_edge("C", "E", 3);
    g2.add_edge("C", "F", 5);
    g2.add_edge("D", "E", 7);
    g2.add_edge("E", "F", 9);
    g2.add_edge("G", "H", 100);

    g3.add_node("A");
    g3.add_node("B");
    g3.add_node("C");
    g3.add_node("D");

    g3.add_edge("A", "B", 3);
    g3.add_edge("A", "D", 1);
    g3.add_edge("B", "C", 2);
    g3.add_edge("B", "D", 1);

    cout << "Testing functions on graph 1." << endl;

    cout << "Shortest Path... " << endl;
    cout << "Between nodes A and B: " << endl;
    cout << "EXPECTED: A->B" << endl;
    cout << "ACTUAL:   " << g1.shortest_path("A", "B") << endl;
    cout << "Between nodes A and F: " << endl;
    cout << "EXPECTED: A->B->C->F" << endl;
    cout << "ACTUAL:   " << g1.shortest_path("A", "F") << endl;
    cout << "Between nodes A and G (G not contained in Graph)" << endl;
    cout << "EXPECTED: No path can be found!" << endl;
    cout << "ACTUAL:   " << g1.shortest_path("A", "G") << endl;

    cout << "Minimum Spanning Tree..." << endl;
    cout << "EXPECTED: " << endl;
    cout << "Neighbors of Node A: " << endl << "  B (1)" << endl << "  D (5)" << endl;
    cout << "Neighbors of Node B: " << endl << "  A (1)" << endl;
    cout << "Neighbors of Node C: " << endl << "  E (3)" << endl << "  F (5)" << endl;
    cout << "Neighbors of Node D: " << endl << "  A (5)" << endl << "  E (7)" << endl;
    cout << "Neighbors of Node E: " << endl << "  C (3)" << endl << "  D (7)" << endl;
    cout << "Neighbors of Node F: " << endl << "  C (5)" << endl << endl;
    min_g1 = g1.minimal_spanning_tree();
    g1.print_neighbors();
    min_g1->print_neighbors();

    cout << "Testing functions on graph 2." << endl;

    cout << "Shortest Path..." << endl;
    cout << "Between nodes C and D: " << endl;
    cout << "EXPECTED: C->E->D" << endl;
    cout << "ACTUAL:   " << g2.shortest_path("C", "D") << endl;
    cout << "Between nodes E and G: " << endl;
    cout << "EXPECTED: No path can be found!" << endl;
    cout << "ACTUAL:   " << g2.shortest_path("E", "G") << endl;
    cout << "Between nodes G and H: " << endl;
    cout << "EXPECTED: G->H" << endl;
    cout << "ACTUAL:   " << g2.shortest_path("G", "H") << endl;

    cout << "Minimum Spanning Tree..." << endl;
    cout << "EXPECTED: " << endl;
    cout << "Neighbors of Node A: " << endl << "  B (1)" << endl << "  D (5)" << endl;
    cout << "Neighbors of Node B: " << endl << "  A (1)" << endl;
    cout << "Neighbors of Node C: " << endl << "  E (3)" << endl << "  F (5)" << endl;
    cout << "Neighbors of Node D: " << endl << "  A (5)" << endl << "  E (7)" << endl;
    cout << "Neighbors of Node E: " << endl << "  C (3)" << endl << "  D (7)" << endl;
    cout << "Neighbors of Node F: " << endl << "  C (5)" << endl;
    cout << "Neighbors of Node G: " << endl << "  H (100)" << endl;
    cout << "Neighbors of Node H: " << endl << "  G (100)" << endl << endl;
    cout << "ACTUAL: " << endl;
    min_g2 = g2.minimal_spanning_tree();
    g2.print_neighbors();
    min_g2->print_neighbors();

    

}

int main() {

    do_testing();

    // // create graph
    // Graph g1;
    // g1.add_node("A");
    // g1.add_node("B");
    // g1.add_node("C");
    // g1.add_node("D");
    // g1.add_node("E");
    // g1.add_node("F");
    // // g1.add_node("G");
    // // g1.add_node("H");

    // g1.add_edge("A", "B", 1);
    // g1.add_edge("A", "D", 5);
    // g1.add_edge("B", "D", 10);
    // g1.add_edge("B", "C", 11);
    // g1.add_edge("C", "E", 3);
    // g1.add_edge("C", "F", 5);
    // g1.add_edge("D", "E", 7);
    // g1.add_edge("E", "F", 9);

    // // g1.add_edge("G", "H", 1);

    // Graph* min_g1 = g1.minimal_spanning_tree();

    // g1.print_neighbors();
    // min_g1->print_neighbors();

    // cout << "Shortest path between A and B: " << endl;
    // cout << "Expected: A->B" << endl;
    // cout << "Actual:   " << endl;
    
    // cout << g.shortest_path("G", "H") << endl;
    // g.shortest_path("B", "E");

    return 0;
}