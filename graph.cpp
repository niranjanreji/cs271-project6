#include <iostream>
#include <sstream>
#include <vector>
#include "graph.h"
#include "queue.cpp"

using namespace std;

// PreConditions:
// Key and Data should have same size.
// All virtices in the graph should have unique keys.

// PostConditions:
// Graph is constructed with vertices Key, and Data.
template <class D, class K>
Graph<D, K>::Graph(vector<K> key, vector<D> data, vector<vector<K>> edges)
{
    size = key.size();
    V = new vertex *[size];
    keys = new K[size];

    for (int i = 0; i < size; i++)
    {
        K currKey = key[i];
        D currData = data[i];
        int adjSize = edges[i].size();
        vertex *curr = new vertex(currData, currKey, adjSize);
        V[i] = curr;
        keys[i] = curr->key;
    }
    for (int i = 0; i < size; i++)
    {
        vertex *curr = V[i];
        int adjSize = curr->adjSize;
        vertex **adjacent = new vertex *[adjSize];
        for (int j = 0; j < adjSize; j++)
        {
            adjacent[j] = get(edges[i][j]);
        }
        curr->adj = adjacent;
    }
}

// PreCondition: Should have something to delete
// Post Condition: All dynamically allocated memory using new is freed.
template <class D, class K>
Graph<D, K>::~Graph()
{
    for (int i = 0; i < size; i++)
    {
        delete V[i];
    }
    delete[] keys;
}

// PreCondition: The graph object must be instantiated.
// PostConditions:
// If a vertex with key is found, pointer to that vertix is returned.
// returns nullptr if not found
template <class D, class K>
typename Graph<D, K>::vertex *Graph<D, K>::get(K key)
{
    for (int i = 0; i < size; i++)
    {
        if (keys[i] == key)
            return V[i];
    }
    return nullptr;
}

// PreCondition: We need a graph object to check if vertices are recheable
// PostCondition: Return true if path is found from start to end vertex, else false.
template <class D, class K>
bool Graph<D, K>::reachable(K start, K end)
{
    if (start == end)
        return true;
    bfs(start);
    vertex *temp = get(end);
    if (temp != nullptr)
    {
        return (temp->pi != nullptr);
    }
    return false;
}

// PreCondtions: The graph object must be instantiated.
// PostConditions: BFS traversal is done from start vertex
// BFS tree is stored in tree stream.
template <class D, class K>
void Graph<D, K>::bfs(K start)
{
    for (int i = 0; i < size; i++)
    {
        V[i]->color = true;
        V[i]->distance = -1;
        V[i]->pi = nullptr;
    }
    vertex *root = get(start);
    if (root != nullptr)
    {
        int level = 0;
        tree.str("");
        root->distance = 0;
        root->color = false;
        queue<vertex *> q(size);
        q.enqueue(root);
        while (!q.empty())
        {
            vertex *now = q.dequeue();
            
            if (now->distance == level + 1)
            {
                tree << endl << now->key;
                level = level + 1;
            }
            else if (now->distance == level)
            {
                if (root == now) {
                    tree << now->key;
                }
                else {
                    tree << " " << now->key;
                }
                
            }
            vertex **adjs = now->adj;
            for (int i = 0; i < now->adjSize; i++)
            {
                if (adjs[i]->color)
                {
                    adjs[i]->color = false;
                    adjs[i]->distance = now->distance + 1;
                    adjs[i]->pi = now;
                    q.enqueue(adjs[i]);
                }
            }
        }
    }
}

// PreCondition: The graph obj needs to exist
// PostCondition: Prints the path from the start vertex to the end vertex using BFS traversal.
template <class D, class K>
void Graph<D, K>::print_path(K start, K end, bool first)
{
    if (first)
        bfs(start);
    if (start == end)
        cout << start;
    else if (get(end)->pi != nullptr)
    {
        print_path(start, get(end)->pi->key, false);
        cout << " -> " << end;
    }
}

// PreConditions: The graph exists and the vertices with keys start and end also exist.
// PostConditions: Returns a string representating the classification of the edge from start to end.
template <class D, class K>
string Graph<D, K>::edge_class(K start, K end)
{
    // Perform DFS
    dfs();

    // Retrieve vertices based on keys
    vertex* u = get(start);
    vertex* v = get(end);

    if (u == nullptr || v == nullptr) return "no edge";
    if (v->pi == u) return "tree edge";
    if (reachable(u, v)) return "forward edge";
    if (u->pi != v && reachable(v, u)) return "back edge";
    for (int i = 0; i < u->adjSize; i++) {
        if (u->adj[i] == v) {
            for (int j = 0; j < v->adjSize; j++) {
                if (v->adj[j] == v) {
                    return "no edge";
                }
            }
            return "cross edge";
        }
    }
    return "no edge";
}

// PreConditions: Graph obj is insstantiated.
// PostCondition: Prints the BFS tree rep. of the graph.
template <class D, class K>
void Graph<D, K>::bfs_tree(K start)
{
    bfs(start);
    cout << tree.str();
}