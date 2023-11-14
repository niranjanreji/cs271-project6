#pragma once

template <class T>
class queue {
    private:
        T* q;
        int head;
        int tail;
        int size;
    public:
        queue(int n);
        bool empty();
        void enqueue(T x);
        T dequeue();
};