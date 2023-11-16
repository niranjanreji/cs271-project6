#include <iostream>
#include <sstream>
#include <vector>
#include "graph.h"
#include "queue.cpp"

using namespace std;

template <class D, class K>
Graph<D, K>::Graph(vector<K> key, vector<D> data, vector<vector<K>> edges) {
    size = key.size();
    
    for (int i = 0; i < size; i++) {
        K currKey = key[i];
        D currData = data[i];
        int adjSize = edges[i].size();
        vertex* curr = new vertex(currKey, currData, adjSize);
        V[i] = curr;
    }

    for (int i = 0; i < size; i++) {
        vertex* curr = V[i];
        int adjSize = curr->adjSize;
        vertex** adjacent = new vertex*[adjSize];
        for (int j = 0; j < adjSize; j++) {
            adjacent[j] = get(edges[i][j]);
        }
        curr->adj = adjacent;
    }
}

template <class D, class K>
Graph<D, K>::~Graph() {
    
}

template <class D, class K>
typename Graph<D, K>::vertex* Graph<D, K>::get(K key) {
}

template <class D, class K>
bool Graph<D, K>::reachable(K start, K end) {
}

template <class D, class K>
void Graph<D, K>::bfs(K start) {
}

template <class D, class K>
void Graph<D, K>::print_path(K start, K end) {
}

template <class D, class K>
string Graph<D, K>::edge_class(K start, K end) {
}

template <class D, class K>
void Graph<D, K>::bfs_tree(K start) {
}