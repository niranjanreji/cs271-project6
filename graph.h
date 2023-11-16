#pragma once

#include <vector>
#include <string>

using namespace std;

template <class D, class K>
class Graph {
    private:
        struct vertex {
            D data;
            K key;
            vertex* pi;
            vertex** adj;
            bool color;
            int distance;
            int adjSize;

            vertex(D d, K k, int ad): data(d), key(k), adjSize(ad) {}
        };
        vertex** V;
        K* keys;
        int size;
    public:
        ~Graph(); 
        Graph(vector<K> key, vector<D> data, vector<vector<K>> edges);          //constructs a graph using key, data, edges vectors
        vertex* get(K key);                                                     //returns pointer to vertex with passed key
        bool reachable(K start, K end);                                         //returns if end is reachable from start
        void bfs(K start);                                                      //sets bfs attributes throughout graph
        void print_path(K start, K end);                                        //prints simple path from start to end
        string edge_class(K start, K end);                                      //returns edge class
        void bfs_tree(K start);                                                 //prints bfs tree
};