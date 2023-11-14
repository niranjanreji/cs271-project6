#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include "graph.h"
#include "queue.cpp"

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
        vertex* curr = new vertex(data[i], key[i], adj, adjSize);
        curr->adjPtr = new vertex*[adjSize];
        V[i] = curr;
        keys[i] = key[i];
    }

    for (int i = 0; i < vertices; i++) {
        vertex* curr = V[i];
        vertex** adjPtrs = curr->adjPtr;
        K* adj = curr->adj;
        for (int j = 0; j < curr->adjSize; j++) {
            adjPtrs[j] = get(adj[j]); 
        }
    }
}

template <class D, class K>
typename Graph<D, K>::vertex* Graph<D, K>::get(K key) {
    for (int i = 0; i < vertices; i++) {
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
        V[i]->distance = -1;
    }
    queue<vertex*> curr(vertices);
    vertex* ptr = get(start);
    if (ptr != nullptr) {
        ptr->color = false;
        ptr->distance = 0;
        curr.enqueue(ptr);
        int level = 0;
        stringstream out;
        while (!curr.empty()) {
            vertex* z = curr.dequeue();
            if (print) {
                if (level == 0) {
                    out << z->key;
                }
                else if (level + 1 == z->distance) {
                    level++;
                    out << endl << z->key;
                }
                else {
                    out << " " << z->key;
                }
            }
            vertex** adjList = z->adjPtr;  
            for (int i = 0; i < z->adjSize; i++) {
                if (adjList[i]->color) {
                    adjList[i]->color = false;
                    adjList[i]->distance = z->distance + 1;
                    adjList[i]->pi = z;
                    curr.enqueue(adjList[i]);
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
    return "";
}

template <class D, class K>
void Graph<D, K>::bfs_tree(K start) {
    bfs(start, true);
}