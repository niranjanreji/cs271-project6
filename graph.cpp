#include <iostream>
#include <sstream>
#include <vector>
#include "graph.h"
#include "queue.cpp"

using namespace std;

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

template <class D, class K>
Graph<D, K>::~Graph()
{
    for (int i = 0; i < size; i++)
    {
        delete V[i];
    }
    delete[] keys;
}

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
        }
    }
}

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

template <class D, class K>
string Graph<D, K>::edge_class(K start, K end)
{
    if (get(start) == nullptr || get(end) == nullptr) {
        return "no edge";
    }

    bfs(start); // Run BFS from the start vertex

    vertex* endVertex = get(end);
    vertex* startVertex = get(start);

    if (endVertex->pi == startVertex) {
        return "tree edge"; // If end's predecessor is start, it's a tree edge
    }

    // Check if there's a path from start to end and vice versa
    bool pathFromStartToEnd = reachable(start, end);
    bool pathFromEndToStart = reachable(end, start);

    if (pathFromStartToEnd && !pathFromEndToStart) {
        return "forward edge";
    } else if (!pathFromStartToEnd && pathFromEndToStart) {
        return "back edge";
    } else if (pathFromStartToEnd && pathFromEndToStart) {
        return "cross edge";
    }

    return "no edge"; // If none of the above, there's no edge
}

template <class D, class K>
void Graph<D, K>::bfs_tree(K start)
{
    bfs(start);
    cout << tree.str();
}