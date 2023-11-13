#pragma once
#include <vector>
#include <string>

using namespace std;

template <class D, class K>
class Graph {
    private:
        class vertex {
            private:
                D data;
                K key;
                K* adj;
                vertex* pi;
                int d; 
        };
        vertex** V;
    public:
        Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges);
        vertex* get(K key);
        bool reachable(K start, K end);
        void bfs(K start);
        void print_path(K start, K end);
        string edge_class(K start, K end);
        void bfs_tree(K start);
};