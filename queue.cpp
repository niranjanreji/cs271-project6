#pragma once

#include "queue.h"
#include <sstream>

using namespace std;

template <class T>
queue<T>::queue(int n) {
    q = new T[n + 1];
    head = 0;
    tail = 0;
    size = n;
}

template <class T>
bool queue<T>::empty() {
    return head == tail;
}

template <class T>
void queue<T>::enqueue(T x) {
    if (tail + 1 != head && (tail + 1) % size != head) {
        q[tail] = x;
        tail++;
    }
    if (tail > size) tail = 1;
}

template <class T>
T queue<T>::dequeue() {
    if (!empty()) {
        T temp = q[head];
        head++;
        if (head > size) head = 1;
        return temp;
    }
    return T();
}

template <class T>
string queue<T>::printq() {
    stringstream out;
    if (tail < head) {
        for (int i = head; i < size + 1; i++) {
            out << q[i] << " ";
        }
        for (int i = 0; i < tail; i++) {
            out << q[i] << " ";
        }
    }
    else {
        for (int i = head; i < tail; i++) {
            out << q[i] << " ";
        }
    }
    out << endl;
    return out.str();
}