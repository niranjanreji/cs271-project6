#pragma once
#include <vector>
#include <string>

template <class D, class K>
class Graph {
    private:
        struct Vertex {
            D data;
            K key;
            vector<K> adj;
        };
    public:
        Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges);
        Vertex* get(K key);
        bool reachable(K start, K end);
        void bfs(K start);
        void print_path(K start, K end);
        string edge_class(K start, K end);
        void bfs_tree(K start);
};