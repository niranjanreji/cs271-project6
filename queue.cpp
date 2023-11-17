#pragma once

#include "queue.h"
#include <sstream>

using namespace std;

// Constructor for queue class
// Preconditions:
//   - 'n' should be a non-negative integer representing the maximum size of the queue.
// Postconditions:
//   - Initializes a queue with a maximum size of 'n'.
//   - The queue is initially empty.
template <class T>
queue<T>::queue(int n)
{
    q = new T[n + 1]; // Allocate memory for the queue
    head = 0;         // Initialize head pointer
    tail = 0;         // Initialize tail pointer
    size = n;         // Set the size of the queue
}

// Check if the queue is empty
// Preconditions: None
// Postconditions:
//   - Returns true if the queue is empty.
//   - Returns false otherwise.
template <class T>
bool queue<T>::empty()
{
    return head == tail; // Queue is empty if head and tail are at the same position
}

// Enqueue an element to the queue
// Preconditions:
//   - The queue should not be full.
// Postconditions:
//   - Adds the element 'x' to the tail of the queue if the queue is not full.
//   - If the tail reaches the end of the queue array, it wraps around to the beginning.
template <class T>
void queue<T>::enqueue(T x)
{
    if (tail + 1 != head && (tail + 1) % size != head)
    {
        q[tail] = x; // Place the element at the current tail
        tail++;      // Increment the tail pointer
    }
    if (tail > size)
        tail = 1; // Wrap around if tail exceeds the size
}

// Dequeue an element from the queue
// Preconditions:
//   - The queue should not be empty.
// Postconditions:
//   - Removes and returns the element at the head of the queue.
//   - If the head reaches the end of the queue array, it wraps around to the beginning.
//   - If the queue is empty, returns a default-initialized value of type T.
template <class T>
T queue<T>::dequeue()
{
    if (!empty())
    {
        T temp = q[head]; // Store the head element
        head++;           // Increment the head pointer
        if (head > size)
            head = 1; // Wrap around if head exceeds the size
        return temp;  // Return the dequeued element
    }
    return T(); // Return a default-initialized value if the queue is empty
}

// Print the contents of the queue
// Preconditions: None
// Postconditions:
//   - Returns a string representation of the queue's contents.
//   - The contents are presented in the order from the head to the tail of the queue.
template <class T>
string queue<T>::printq()
{
    stringstream out;
    // Print the queue contents depending on the relative positions of head and tail
    if (tail < head)
    {
        // If the tail has wrapped around, print the two segments
        for (int i = head; i < size + 1; i++)
        {
            out << q[i] << " ";
        }
        for (int i = 0; i < tail; i++)
        {
            out << q[i] << " ";
        }
    }
    else
    {
        // If the tail is after the head, print the single segment
        for (int i = head; i < tail; i++)
        {
            out << q[i] << " ";
        }
    }
    out << endl;
    return out.str(); // Return the string representation
}
