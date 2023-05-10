This program implements an auto-sorted linked list.
The primary class is List, which contains 3 critical functions:

void push(int val) : O(n)
    This function pushes a given value into the list and places it in ascending order.
    It will automatically loop through the list and compare the given value to the entire list,
    stopping once it finds the correct location to insert to.

int search(int index) : O(n)
    This function returns the value stored at the requested index. It will throw a 1
    if the index is out of bounds, and throw a 2 if the list is empty.

void print() : O(n)
    This function prints out all elements of the list. It loops through every elements
    and prints it to the terminal, separating each element with a single space character " "

