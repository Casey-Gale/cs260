This program implements a Queue data structure through the use of a linked list. As a reminder,
a Queue models FIFO behavior-- first in, first out. This Queue is a template class; it must 
be declared by specifying a type:
    Queue<typename> example_queue;

The Queue class has three private member variables: Node* head, Node* tail, and int length.
All three of these variables are automatically changed after every function call:

Node* head:
    The head pointer always points at the first element in the Queue.
Node* tail:
    The tail pointer always points at the last element in the Queue.
int length:
    length tracks the total length of the Queue.

The Queue class also has five public member functions (excluding a default constructor and a 
destructor): get_length(), enqueue(), dequeue(), peek(), and print():

get_length():
    This function is a getter for the length member variable. It simply returns an integer
    with the value of length.
enqueue(<typename> val): 
    Enqueues a value of the desired type to the back of the linked list. It cannot be accessed 
    until the values in front of it are dequeued.

    Run-time complexity: O(1)
    Because the Queue class tracks the back of the linked list with a member variable, the 
    time required to access and add to the back of the list does not depend on the number of 
    elements in the list.
dequeue():
    Dequeues the front-most value in the linked list. This function deallocates the memory for 
    the node and returns the value stored in the node.

    Run-time complexity: O(1)
    As with the enqueue() member function, the Queue class tracks the beginning of the
    linked list with a member variable. This means that the dequeue() function may jump 
    straight to the beginning of the list and so does not depend on the number of elements
    in the list.
peek():
    this function returns the value stored in the front-most node without deallocating any
    memory.

    Run-time complexity: O(1)
    The peek() function is the same complexity as the dequeue() function because they do
    almost exactly the same thing. peek() simply does not delete the element, so it also 
    has the same run-time complexity as dequeue().
print():
    the print() function will iterate through the entire linked list and print the value
    stored in each node. It will separate each entry with a space character " ".
    In order for this function to properly work, the type stored in each node must be able
    to use the assignment operator without error.

    Run-time complexity: O(n)
    The print() function must iterate through the entire linked list and access the value 
    stored in each element, so the run-time scales linearly with the number of elements in 
    the queue.

Testing for this program is included in one function (do testing()) that calls two others:
test_queue_with_int() and test_queue_with_string(). Both of these functions run through tests 
with an integer and string queue respectively, attempting to enqueue, dequeue, peek, and 
print on a queue with 0 and >0 pre-existing entries.