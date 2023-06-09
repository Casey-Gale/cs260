This program implements a simple Binary Search Tree (BST). It is automatically sorted in the following manner:
If a new value is less than or equal to the current node's value, the value is attempted to be inserted into the left node location.
If a new value is greater than the current node's value, the value is attempted to be inserted into the right node location. 
This continues until the desired location is currently nullptr, after which a new node is created and inserted into the tree.

This program includes four main functions: 

add(int new_val) : O(log(n))
    This function attempts to add a specified value to the BST. This is done according to the rules stated above, and once a proper
    location is found a node is inserted. Because the tree doubles in size each layer, the worst-possible number of iterations is log(n).
    
    If this tree were unordered, the run-time complexity would not change. Again, because the binary tree doubles in size at each depth, 
    the most that any algorithm would have to iterate is log(n) times, so time complexity is unchanged at O(log(n)).

add(Node* new_ptr) : O(log(n))
    This function attempts to add an existing node to the tree. This is mostly a helper function for the removal function, as it allows
    for easy reordering of the tree. The logic is exactly the same as the other add, so it has the same run-time complexity of O(log(n)).
    
    This function would also have the same run-time complexity if the tree were unordered, for the same reasons as specified above. 

remove(int old_val) : O(log(n))
    This function attempts to remove a node from the tree. It returns a 0 if the value is found and successfully removed and returns a 1
    if no value is found. It also passes through a maximum of log(n) nodes.
    
    If this tree were unordered, this function would have to be O(n). This is because the program would not know where any value was stored, so 
    without any organization in the tree the worst case is that the program has to iterate through the entire tree to locate the desired node.

print_in_order() : O(n)
    This function recursively traverses the entire BST. Since it accesses every node, the run-time complexity is O(n).
    
    No part of this algorithm would be changed if the tree were unordered.

Locations in code: 
add(int) : Line 60
add(Node*) : Line 91
remove(int) : Line 127
print_in_order() : Line 193
