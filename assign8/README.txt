This program models a Graph data structure. It stores data in two ways: nodes, which have a string value, and edges between nodes, 
which have an integer weight assigned between them. A higher weight assigned to an edge models a higher 'difficulty' or 'resistance'
associated with moving between nodes. 

A few thoughts to begin: 

I made this project much longer than it needed to be. For the minimum spanning tree, I decided to use the auto-sorted list from assignment 5.
Because I haven't figured out how to compile using multiple files on VSCode, this decision practically doubled the length of the file and so it
seems a lot longer than it is. 

The graphs that I use for testing are drawn out on my design PDF, so refer to that to make sense of what each function is expecting. 

One application of graphs can be found in printed circuit board design, or any other design where efficient space usage is paramount. The board
being designed can be modeled as a collection of nodes in a square grid, with weighted edges proportional to the euclidian distance between nodes. 
The shortest path can be applied to this concept as well; if a wire trace is to be placed on the board between two nodes, it might be best to 
lead it through the shortest path possible. If a component is in the way, then the nodes colliding with that component can be excluded from the 
shortest path algorithm, thus routing around it. 

The program has four functions:

void add_node(string new_name) : O(1)
    This function adds a new node to the vector stored in the member variable nodes. It makes use of std::vector::push_back(), which 
    has a time complexity of O(1). Apart from that, nothing else takes longer than constant time. 

void add_edge(string source_name, string destination_name) : O(n), n = number of nodes
    This function adds an edge between two existing nodes. It will not add an edge if either argument is not a valid name of an existing
    node in the graph. To connect the node names to node addresses, the program iterates through the entire vector of nodes. As such, the 
    time complexity of this function is O(n), where n is the number of nodes in the graph.

string shortest_path(string source_name, string destination_name) : O(n^3*e), n = number of nodes, e = number of edges
    This function applies Dijkstra's algorithm to find the shortest path (lowest weight path) between two specified nodes. Due to poor 
    planning and implementation, the time complexity is much worse than Dijkstra's algorithm can be. This function could be optimized a great deal;
    that goes without saying when four embedded for loops exist.

    An issue is known about a certain edge case, exemplified by graph g3. Due to the ordering of the nodes in the vector, some paths can be found
    that the implementation believes to be optimal when it isn't. The function works for most graphs, however. 

Graph* minimal_spanning_tree() : O(n*e), n = number of nodes, e = number of edges
    This function implements Kruskal's algorithm to find the minimum spanning tree of a given graph. It iterates through all edges of all 
    nodes, so the time complexity is nodes * edges, O(n*e)

    A glaring issue with this function is a memory issue with pointers. The testing function may not line up with what we would expect from the 
    minimal spanning tree. The issue of memory corruption gets really difficult to troubleshoot because the program ceases to be deterministic.
    I asked ChatGPT on a place to start and it suggested that the issue might be in the section where I determine whether a given string is in a set.
    (This is around line 362)

Line numbers:
    add_node() : Line 179
    add_edge() : Line 184
    shortest_path() : Line 212
    minimal_spanning_tree() : Line 326