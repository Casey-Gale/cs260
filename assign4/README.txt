This program implements a linked list which supports arbitrary operations. 
In particular, it is able to insert and remove from anywhere in the list by specifying a position.
In addition, it is able to view the value at a position without removing it from the list.

push(int val, int index) : O(n)
    This function will insert a specified value in front of the index passed in. For example, 
    push(1, 5) would push the integer 1 into the 5th position of the list.

    Supporting functions:
        push_front(val) : O(1)
            This function inserts a value to the beginning of the list.
        push_back(val) :  O(1)
            This function inserts a value to the very end of the list.

pop(int index) : O(n)
    This function will remove the value from the specified index which is passed into the function.
    For example, pop(3) will remove the 3rd item from the list and return the value stored.

    Supporting functions:
        pop_front() : O(1)
            This function removes and returns a value from the beginning of the list.
        pop_back() : O(n)
            This function removes and returns a value from the very end of the list.

peek(int index) : O(n)
    This function will return the value stored at a specified index without removing it from the list.
    For example, peek(3) will return the 3rd item from the list without removing it.

    Supporting functions: 
        peek_front() : O(1)
            This function returns the value stored at the beginning of the list.
        peek_back() : O(1)
            This function returns the value stored at the very end of the list.

Line numbers:

push() : Line 123
pop() : Line 154
peek() : Line 203
tests : Line 285