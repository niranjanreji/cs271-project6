#include <iostream>
#include <sstream>
#include <vector>
#include "graph.h"
#include "queue.cpp"

using namespace std;

template <class D, class K>
Graph<D, K>::Graph(vector<K> key, vector<D> data, vector<vector<K>> edges) {
    size = key.size();

    std::cout << std::endl;
    for (int i = 0; i < size; i++) {
        K currKey = key[i];
        D currData = data[i];
        int adjSize = edges[i].size();
        vertex* curr = new vertex(currKey, currData, adjSize);
        V[i] = curr;
        keys[i] = curr->key;
        cout << V[i] << " and " << keys[i] << " lol " << endl;
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
    for (int i = 0; i < size; i++) {
        delete V[i];
        delete[] keys;
    }
}

template <class D, class K>
typename Graph<D, K>::vertex* Graph<D, K>::get(K key) {
    for (int i = 0; i < size; i++) {
        if (keys[i] == key) return V[i];
    }
    return nullptr;
}

template <class D, class K>
bool Graph<D, K>::reachable(K start, K end) {
    if (start == end) return true;
    bfs(start);
    vertex* temp = get(end);
    if (temp != nullptr) {
        return (temp->pi != nullptr);
    }
    return false;
}

template <class D, class K>
void Graph<D, K>::bfs(K start) {
    for (int i = 0; i < size; i++) {
        V[i]->color = true;
        V[i]->distance = -1;
        V[i]->pi = nullptr;
    }
    vertex* root = get(start);
    if (root != nullptr) {
        int level = 0;
        tree << root->key;
        root->distance = 0;
        root->color = false;
        queue<vertex*> q(size);
        q.enqueue(root);
        while (!q.empty()) {
            vertex* now = q.dequeue();

            if (now->distance = level + 1) {
                tree << endl << now->key;
                level++;
            }
            else if (root != now) {
                tree << " " << now->key;
            }

            vertex** adjs = now->adj;
            for (int i = 0; i < now->adjSize; i++) {
                if (adjs[i]->color) {
                    adjs[i]->color = false;
                    adjs[i]->distance = now->distance + 1;
                    adjs[i]->pi = now;
                }
            }
        }
    }
}

template <class D, class K>
void Graph<D, K>::print_path(K start, K end, bool first) {
    if (first) bfs(start);
    if (start == end) cout << start;
    else if (get(end)->pi != nullptr) {
        print_path(start, get(end)->pi->key, false);
        cout << " -> " << end;
    }
}

template <class D, class K>
string Graph<D, K>::edge_class(K start, K end) {
    return "";
}

template <class D, class K>
void Graph<D, K>::bfs_tree(K start) {
    bfs(start);
    cout << tree.str() << endl;
}