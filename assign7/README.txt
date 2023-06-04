This program implements a simple hash table class. It stores strings in an array of linked lists; the hash function
chooses which index of the array to insert to by modding the string length by the array size. For example, if one were
to insert the string "12345678" into a hash table of size 5, it would be put into index 3 because 8 % 5 = 3.

The class contains 3 important functions:

int hash(string new_val) : O(1)
    This function is extremely simple; it mods the input string's length by the table's array size, then returns that value.
    Depending on the complexity of the string .size() method, this function could have a higher complexity than expected. However,
    provided that method is a O(1) operation, this function is as well.

void insert(string new_val) : O(n)
    This function inserts a new node into the hash table with a string as a value. After finding the array index to insert to, 
    a node is inserted to the end of a linked list pointed to by the array index. The hash function reduces the average complexity, 
    but in a worst-case situation a collision will happen every time and as such the run-time will still be O(n). 

    Though not implemented, this runtime could be reduced down to O(1) by inserting the node to the beginning of the linked list as
    opposed to the end. This theoretically wouldn't change any other functionalities of the hash table other than prioritizing later-inserted
    elements rather than earlier-inserted.

bool contains(string new_val) : O(n)
    This function returns whether or not a certain string is contained in the hash table. As with the implemented insert function, the worst-case
    scenario is that collisions have occurred in every insert. In this case, the run-time complexity is O(n) as the function must iterate through
    every single element.