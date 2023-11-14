#include <iostream>
#include <vector>
#include "graph.h"

using namespace std;

template <class D, class K>
Graph<D, K>::Graph(vector<K> key, vector<D> data, vector<vector<K>> edges) {
    int ksize = key.size();
    V = new vertex*[ksize];
    keys = new K[ksize];

    for (int i = 0; i < ksize; i++) {
        int adj = edges[i].size();
        K* arr = new K[adj];
        for (int j = 0; i < adj; j++) {
            arr[j] = edges[i][j];
        }
        vertex* curr = new vertex(data[i], key[i], arr);
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
    if (get(end) -> pi != nullptr) return true;
    return false;
} 