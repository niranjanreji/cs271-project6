#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include "graph.h"
#include "queue.h"

using namespace std;

template <class D, class K>
Graph<D, K>::Graph(vector<K> key, vector<D> data, vector<vector<K>> edges) {
    vertices = key.size();
    V = new vertex*[vertices];
    keys = new K[vertices];

    for (int i = 0; i < vertices; i++) {
        int adjSize = edges[i].size();
        K* adj = new K[adjSize];
        for (int j = 0; i < adjSize; j++) {
            adj[j] = edges[i][j];
        }
        vertex* curr = new vertex(data[i], key[i], adj);
        V[i] = curr;
        keys[i] = key[i]
    }
}

template <class D, class K>
Graph<D, K>::vertex* Graph<D, K>::get(K key) {
    for (int i = 0; i < keys.length(); i++) {
        if (keys[i] == key) return V[i];
    }
    return nullptr;
}

template <class D, class K>
bool Graph<D, K>::reachable(K start, K end) {
    bfs(start);
    if (get(end)->pi != nullptr) return true;
    return false;
}

template <class D, class K>
void Graph<D, K>::bfs(K start, bool print) {
    for (int i = 0; i < vertices; i++) {
        V[i]->color = false;
        V[i]->pi = nullptr;
        V[i]->d = -1;
    }
    queue<vertex*> curr(vertices);
    vertex* ptr = get(start);
    if (ptr != nullptr) {
        ptr->color = false;
        ptr->d = 0;
        curr.enqueue(ptr);
        int level = 0;
        stringstream out;
        while (!processing.empty()) {
            vertex* z = curr.dequeue();
            if (print) {
                if (level + 1 == z->d) {
                    level++;
                    out << endl << z->key;
                }
                else {
                    out << " " << z->key;
                }
            }  
            for (int i = 0; i < z->adjSize, i++) {
                if (adj[i]->color) {
                    adj[i]->color = false;
                    adj[i]->d = z.d + 1;
                    adj[i]->pi = z;
                    curr.enqueue(adj[i]);
                }
            }
        }
        if (print) {
            cout << out.str() << endl;
        }
    }
}

template <class D, class K>
void Graph<D, K>::print_path(K start, K end) {
    bfs(end);
    vertex* ptr = get(start);
    stringstream out;
    if (ptr != nullptr) {
        out << ptr->pi;
        ptr = ptr->pi;
    }
    while (ptr != nullptr) {
        out << " -> " << ptr->key;
        ptr = ptr->pi;
    }
    cout << out.str() << endl;
}

template <class D, class K>
string Graph<D, K>::edge_class(K start, K end) {

}

template <class D, class K>
void Graph<D, K>::bfs_tree(K start) {
    bfs(start, true);
}