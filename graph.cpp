#include <iostream>
#include <sstream>
#include <vector>
#include "graph.h"
#include "queue.cpp"

using namespace std;

// PreConditions:
// key and data should have same size
// PostConditions:
// Graph is constructed with vertices from vectors key, data
template <class D, class K>
Graph<D, K>::Graph(vector<K> key, vector<D> data, vector<vector<K>> edges)
{
    size = key.size();                                                      // tells us how many vertices we have
    V = new vertex* [size];                                                 // our graph's array of vertices
    keys = new K[size];                                                     // our graph's array of keys (in sync with vertices)
    for (int i = 0; i < size; i++)                                          // creates vertices for each key, piece of data passed
    {
        K currKey = key[i];
        D currData = data[i];
        int adjSize = edges[i].size();
        vertex* curr = new vertex(currData, currKey, adjSize);              // creates new vertex
        V[i] = curr;                                                        // adds vertex to V, keys arrays
        keys[i] = curr->key;
    }
    for (int i = 0; i < size; i++)
    {
        vertex* curr = V[i];                                                // goes through each vertex and gives them an array of adjacent vertex pointers
        int adjSize = curr->adjSize;
        vertex** adjacent = new vertex*[adjSize];
        for (int j = 0; j < adjSize; j++)
        {
            adjacent[j] = get(edges[i][j]);
        }
        curr->adj = adjacent;
    }
}

// PreCondition: called on existing graph object
// Post Condition: all dynamically allocated memory for graph is freed.
template <class D, class K>
Graph<D, K>::~Graph()
{
    for (int i = 0; i < size; i++)
    {
        delete V[i];
    }
    delete[] keys;
}

// PreCondition: called on existing graph object
// PostConditions:
// if a vertex with passed key is found, pointer to that vertexx is returned.
// returns nullptr if not found
template <class D, class K>
typename Graph<D, K>::vertex *Graph<D, K>::get(K key)
{
    for (int i = 0; i < size; i++)                                                      // searches for a vertex with the key we provided in our big vertex array
    {
        if (keys[i] == key)
            return V[i];                                                                // returns vertex ptr if found, returns nullptr if not
    }
    return nullptr;
}

// PreCondition: called on existing graph object
// PostCondition: Returns true if vertices with keys start and end exist in the graph, and there is a directed traversable path between them.
template <class D, class K>
bool Graph<D, K>::reachable(K start, K end)
{
    vertex* s = get(start);
    vertex* e = get(end);
    if (s == nullptr || e == nullptr) return false;                                      // we can't trace a path between two vertices if both are nullptrs!
    if (start == end) return true;                                                       // if both vertices have the same mem address, trivially reachable
    bfs(start);                                                                          // runs bfs on graph starting at our start vertex
    return (e->pi != nullptr);                                                           // if bfs managed to find a way from start to end, end->pi != nullptr
}

// PreCondition: called on existing graph object
// PostCondition: Returns true if vertices start and end exist in the graph, and there is a directed traversable path between them.
template <class D, class K>
bool Graph<D, K>::reachable(vertex* start, vertex* end) {
    if (start == nullptr || end == nullptr) return false;                                   //same function as earlier, but this one does its work iteratively and takes ptrs
    if (start == end) return true;                                                          //used in edge_class to not mess with the attributes dfs sets
    vertex* curr = end;
    while (curr->pi != nullptr) {                                                           //starts from the end and goes back until we run into our start node
        curr = curr->pi;                                                                    //if we run into our start node, return true
        if (curr == start) return true;
    }
    return false;                                                                           //if not, return false
}

// PreCondtions: The graph object must be instantiated.
// PostConditions: BFS traversal is done from start vertex
// BFS tree is stored in tree stringstream object.
template <class D, class K>
void Graph<D, K>::bfs(K start)
{
    for (int i = 0; i < size; i++)                                                          //sets color to true (not discovered), distance to -1 (for infty), 
    {                                                                                       //predecessor to nullptr for all graph vertices
        V[i]->color = true;
        V[i]->distance = -1;
        V[i]->pi = nullptr;
    }
    vertex *root = get(start);                                                              //gets mem address of start vertex
    if (root != nullptr)                                                                    //checks if addy is nullptr
    {
        int level = 0;
        tree.str("");                                                                       //resets BST tree sstream to empty stringstream
        root->distance = 0;                                                                 //sets root distance to 0 (0 steps from itself), color to false (discovered)
        root->color = false;
        queue<vertex *> q(size);                                                            //creates a queue for the BFS algorithm
        q.enqueue(root);                                                                    //enqueues start node (root of our BST tree)
        while (!q.empty())
        {
            vertex *now = q.dequeue();                                                      //repeatedly dequeues vertices from graph
            
            if (now->distance == level + 1)                                                 //if-else block checks if we need to go to a newline in our BST
            {                                                                               //stringstream before adding current key to it
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
            vertex **adjs = now->adj;                                                       //goes through adjacents of current vertex and if they haven't
            for (int i = 0; i < now->adjSize; i++)                                          //been discovered, sets distance, predecessor, and color then enqueues it
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

// PreCondition: The graph object needs to exist
// PostCondition: Prints the path from the start vertex to the end vertex using BFS traversal.
template <class D, class K>
void Graph<D, K>::print_path(K start, K end, bool first)
{
    if (first)                                                                              //if this is our first call to print path, bfs executes from start
        bfs(start);
    if (start == end)                                                                       //if start and end are same vertex, then path is trivial
        cout << start;
    else if (get(end)->pi != nullptr)                                                       //if there is a part, end->pi != nullptr and this while loop executes
    {                                                                                       //recursively print path from start to end
        print_path(start, get(end)->pi->key, false);
        cout << " -> " << end;
    }
}

// PreConditions: The graph exists and the vertices with keys start and end also exist.
// PostConditions: Returns a string representing the classification of the edge (start, end). Returns "no edge" if (start, end) is not an edge in the graph.
template <class D, class K>
string Graph<D, K>::edge_class(K start, K end)
{
    vertex* u = get(start);                                                                 //get ptrs to start, end vertices
    vertex* v = get(end);
    if (u == nullptr || v == nullptr) return "no edge";                                     //if either ptrs == nullptr there can be no edge

    bool exists;
    for (int i = 0; i < u->adjSize; i++) {                                                  //goes through adjacency list of start to check if an edge
        if (u->adj[i] == v) exists = true;                                                  //directly between start and end exists in graph
    }

    if (!exists) return "no edge";                                                          //if no edge exists, return false

    dfs();                                                                                  //perform DFS

    if (v->pi == u) return "tree edge";                                                     //if ends predecessor is start, dfs traversed this edge making it a tree edge
    if (reachable(v, u)) return "back edge";                                                //if end is an ancestor of start in the DFS tree, the start-end edge is a back edge
    if (reachable(u, v)) return "forward edge";                                             //if start is an ancestor of end in the DFS tree, the start-end edge is a forward edge
    return "cross edge";                                                                    //if there is an edge but no ancestor relationship, it is a cross edge
}

// PreConditions: Graph obj is instantiated.
// PostCondition: Prints the BFS tree rep. of the graph.
template <class D, class K>
void Graph<D, K>::bfs_tree(K start)
{
    bfs(start);                                                                             //prints out the bfs tree created in bfs() starting at vertex w key start
    cout << tree.str();
}

// Pre-Conditions: Called on existing Graph object
// Post-Conditions: Carries out a DFS traversal of the entire graph, sets relevant attributes of vertices
template <class D, class K>
void Graph<D, K>::dfs() {
    for (int i = 0; i < size; i++) {                                                        //resets attributes of all vertices
        V[i]->color = true;
        V[i]->pi = nullptr;
    }
    int time = 0;                                                                           //global var time set to 0
    for (int i = 0; i < size; i++) {
        if (V[i]->color) {
            time = dfs_visit(V[i], time);                                                   //if vertex hasnt been visited, visit it and pass time to it
        }                                                                                   //new time returned from dfs-visit recursion before other vertices are visited
    }
}

// Pre-Conditions: Called on an existing vertex (not nullptr) in a graph that exists
// Post-Conditions: Recursively traverses a graph using the DFS algorithm, sets relevant attributes of vertices, returns completion time
template <class D, class K>
int Graph<D, K>::dfs_visit(vertex* node, int time) {
    time = time + 1;                                                                        //increments time on every new visit
    node->distance = time;                                                                  //sets distance of current vertex to time, color to discovered (false)
    node->color = false;
    vertex** adjs = node->adj;
    for (int i = 0; i < node->adjSize; i++) {                                               //goes thru adjacency list for undiscovered vertices
        if (adjs[i]->color) {                                                               
            adjs[i]->pi = node;                                                             
            time = dfs_visit(adjs[i], time);                                                //visits undiscovered vertex after setting their predecessor to curr vertex
        }
    }
    time = time + 1;
    node->finish = time;                                                                    //increments and sets finishing time
    return time;
}