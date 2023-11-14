#pragma once

#include <vector>
#include <string>

using namespace std;

template <class D, class K>
class Graph {
    private:
        class vertex {
            public:
                D data;
                K key;
                K* adj;
                vertex** adjPtr;
                vertex* pi;
                int distance;
                int adjSize;
                bool color;
                vertex(D da, K ke, K* ad, int size) {
                    data = da;
                    key = ke;
                    adj = ad;
                    adjSize = size;
                    pi = nullptr;
                    distance = -1;
                    color = true;
                }
        };
        vertex** V;
        K* keys;
        int vertices;
    public:
        Graph(vector<K> key, vector<D> data, vector<vector<K>> edges);
        vertex* get(K key);
        bool reachable(K start, K end);
        void bfs(K start, bool print = false);
        void print_path(K start, K end);
        string edge_class(K start, K end);
        void bfs_tree(K start);
};