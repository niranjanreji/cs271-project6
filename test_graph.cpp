//
//  test_graph_example.cpp
//  CS 271 Graph Project: Example Test File
//
//  Created by Dr. Stacey Truex
//

#include <fstream>
#include <sstream>
#include "graph.cpp"

Graph<string, string> *generate_graph(string fname)
{
    string line;
    ifstream infile(fname);
    vector<string> keys = {};
    vector<string> data = {};
    vector<vector<string> > adjs = {};
    if (infile.is_open())
    {
        while (getline(infile, line))
        {
            size_t delim = line.find(":");
            string key = line.substr(0, delim);
            string adj = line.substr(delim + 1);
            keys.push_back(key);
            data.push_back(key + " data");
            delim = adj.find(",");
            vector<string> adj_lst = {};
            while (delim != string::npos)
            {
                adj_lst.push_back(adj.substr(0, delim));
                adj = adj.substr(delim + 1);
                delim = adj.find(",");
            }
            adj_lst.push_back(adj);
            adjs.push_back(adj_lst);
        }
    }
    Graph<string, string> *G = new Graph<string, string>(keys, data, adjs);
    return G;
}

void test_get(Graph<string, string> *G, Graph<string, string> *G2)
{
    try
    {
        if (G->get("S") == nullptr || G->get("S")->data != "S data")
        {
            cout << "Incorrect result getting vertex \"s\"" << endl;
        }
        if (G->get("a") != nullptr)
        {
            cout << "Incorrect result getting non-existant vertex \"a\"" << endl;
        }
        if (G2->get("M") == nullptr)
        {
            cout << "BROKEN IN GET LINE 58" << endl;
        }
        if (G2->get("P") == nullptr)
        {
            cout << "BROKEN IN GET LINE 62" << endl;
        }
        if (G2->get("M")->key != "M")
        {
            cout << "BROKEN IN GET LINE 66" << endl;
        }
        if (G2->get("P")->key != "P") 
        {
            cout << "BROKEN IN GET LINE 70" << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error getting vertex from graph : " << e.what() << endl;
    }
}

void test_reachable(Graph<string, string> *G, Graph<string, string> *G2)
{
    try
    {
        if (!G->reachable("R", "V"))
        {
            cout << "Incorrectly identified adjacent vertex \"V\" as unreachable from \"R\"" << endl;
        }
        if (!G->reachable("X", "W"))
        {
            cout << "Incorrectly identified \"W\" as unreachable from \"X\"" << endl;
        }
        if (G->reachable("S", "A"))
        {
            cout << "Incorrectly identified non-existant vertex \"A\" as reachable from \"S\"" << endl;
        }
        if (!G->reachable("R","R"))
        {
            cout << "BROKEN IN REACHABLE LINE 97" << endl;
        }
        if (G2->reachable("M","P"))
        {
            cout << "BROKEN IN REACHABLE LINE 101" << endl;
        }
        if (G2->reachable("L", "Q"))
        {
            cout << "BROKEN IN REACHABLE LINE 105" << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing reachable : " << e.what() << endl;
    }
}

void test_bfs(Graph<string, string> *G, Graph<string, string> *G2, Graph<string, string> *G3)
{
    try
    {
        G->bfs("T");
        string vertices[8] = {"V", "R", "S", "W", "T", "X", "U", "Y"};
        int distances[8] = {3, 2, 1, 1, 0, 2, 1, 2};
        for (int i = 0; i < 8; i++)
        {
            if (G->get(vertices[i]) == nullptr || G->get(vertices[i])->distance != distances[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"t\"" << endl;
            }
        }

        G2->bfs("X");
        string verticess[2] = {"M", "P"};
        int distancess[2] = {-1, -1};
        for (int i = 0; i < 2; i++) {
            if (G2->get(verticess[i]) == nullptr || G2->get(verticess[i])->distance != distancess[i] || G2->get(verticess[i])->pi != nullptr) 
            {
                cout << "BROKEN IN BFS LINE 135" << endl;
            }
        }

        G3->bfs("Z");
        string verticesss[3] = {"Z","X","Y"};
        int distancesss[3] = {0,1,1};
        for (int i = 0; i < 3; i++) {
            if (G3->get(verticesss[i]) == nullptr || G3->get(verticesss[i])->distance != distancesss[i]) 
            {
                cout << "BROKEN IN BFS LINE 135" << endl;
            }
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs : " << e.what() << endl;
    }
}

void test_print_path(Graph<string, string> *G)
{
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path("T", "V");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T -> S -> R -> V")
        {
            cout << "Incorrect path from vertex \"T\" to vertex \"V\". Expected: T -> S -> R -> V but got : " << buffer.str() << endl;
        }

        stringstream buffer2;
        streambuf *prevbuf2 = cout.rdbuf(buffer2.rdbuf());
        G->print_path("S", "T");
        cout.rdbuf(prevbuf2);
        if (buffer2.str() != "")
        {
            cout << "Incorrect path from vertex \"S\" to vertex \"T\". Expected:  but got : " << buffer.str() << endl;
        }

        stringstream buffer3;
        streambuf *prevbuf3 = cout.rdbuf(buffer3.rdbuf());
        G->print_path("R", "X");
        cout.rdbuf(prevbuf3);
        if (buffer3.str() != "")
        {
            cout << "Incorrect path from vertex \"T\" to vertex \"R\". Expected:  but got : " << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }
}

void test_edge_class(Graph<string, string> *G)
{
    try
    {
        string e_class = G->edge_class("R", "V"); // tree edge
        if (e_class != "tree edge")
        {
            cout << "Misidentified tree edge (\"R\", \"V\") as : " << e_class << endl;
        }
        e_class = G->edge_class("X", "U"); // back edge
        if (e_class != "back edge")
        {
            cout << "Misidentified back edge (\"X\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("R", "U"); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (\"R\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "W"); // forward edge
        if (e_class != "forward edge")
        {
            cout << "Misidentified forward edge (\"T\", \"W\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "S"); // cross edge
        if (e_class != "cross edge")
        {
            cout << "Misidentified cross edge (\"T\", \"S\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "R"); //  no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified cross edge (\"T\", \"R\") as : " << e_class << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing edge class : " << e.what() << endl;
    }
}

void test_bfs_tree(Graph<string, string> *G, Graph<string, string> *G2, Graph<string, string> *G3)
{
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree("T");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T\nS U W\nR Y X\nV")
        {
            cout << "Incorrect bfs tree. Expected : \nT\nS U W\nR Y X\nV \nbut got :\n"
                 << buffer.str() << endl;
        }

        stringstream buffer2;
        streambuf *prevbuf2 = cout.rdbuf(buffer2.rdbuf());
        G2->bfs_tree("M");
        cout.rdbuf(prevbuf2);
        if (buffer2.str() != "M")
        {
            cout << "Incorrect bfs tree. Expected : \nM \nbut got :\n"
                 << buffer2.str() << endl;
        }

        stringstream buffer3;
        streambuf *prevbuf3 = cout.rdbuf(buffer3.rdbuf());
        G3->bfs_tree("Z");
        cout.rdbuf(prevbuf3);
        if (buffer3.str() != "Z\nX Y")
        {
            cout << "Incorrect bfs tree. Expected : \nZ\nX Y \nbut got :\n" << buffer3.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
}

void test_disconnected_graph(Graph<string, string> *G)
{
    // Reachability in a Disconnected Graph
    if (G->reachable("A", "E"))
    {
        cout << "Error: Vertex \"E\" should not be reachable from \"A\" in a disconnected graph." << endl;
    }

    // BFS on a Disconnected Graph
    G->bfs("A");
    if (G->get("E") != nullptr && G->get("E")->distance != -1)
    {
        cout << "Error: Vertex \"E\" should have a distance of -1 from \"A\" in a disconnected graph." << endl;
    }

    // Edge Classification in a Disconnected Graph
    if (G->edge_class("A", "E") != "no edge")
    {
        cout << "Error: Edge classification between \"A\" and \"E\" should be \"no edge\" in a disconnected graph." << endl;
    }
}

void test_graph_with_self_loops(Graph<string, string> *G)
{
    // Reachability with Self-loops
    if (!G->reachable("M", "M"))
    {
        cout << "Error: Vertex \"M\" should be reachable from itself." << endl;
    }

    // BFS with Self-loops
    G->bfs("M");
    if (G->get("M")->pi != nullptr && G->get("M")->distance != 0)
    {
        cout << "Error: BFS should handle self-loops correctly." << endl;
    }

    // Edge Classification with Self-loops
    string edgeType = G->edge_class("P", "P");
    if (edgeType != "back edge")
    {
        cout << "Error: Self-loop on \"P\" should be classified correctly." << endl;
        cout << edgeType << endl;
    }
}

void test_graph_with_parallel_edges(Graph<string, string> *G)
{
    // Reachability with Parallel Edges
    if (!G->reachable("X", "Z"))
    {
        cout << "Error: Vertex \"Z\" should be reachable from \"X\" even with parallel edges." << endl;
    }

    // BFS with Parallel Edges
    G->bfs("X");
    if (G->get("Z") == nullptr || G->get("Z")->distance != 1)
    {
        cout << "Error: BFS should correctly compute distances with parallel edges." << endl;
    }

    // Edge Classification with Parallel Edges
    if (G->edge_class("Z", "Y") != "back edge")
    {
        cout << "Error: Edge classification with parallel edges needs to be consistent." << endl;
    }
}

void additional_tests(Graph<string, string> *g1, Graph<string, string> *g2, Graph<string, string> *g3)
{
    test_disconnected_graph(g1);
    test_graph_with_self_loops(g2);
    test_graph_with_parallel_edges(g3);
}

int main()
{

    Graph<string, string> *G = generate_graph("graph_description.txt");
    Graph<string, string> *g1 = generate_graph("g1.txt");
    Graph<string, string> *g2 = generate_graph("g2.txt");
    Graph<string, string> *g3 = generate_graph("g3.txt");
    test_get(G, g2);
    test_reachable(G, g2);
    test_bfs(G, g2, g3);
    test_print_path(G);
    test_edge_class(G);
    test_bfs_tree(G, g2, g3);

    delete G; // clean up

    // main function that calls additional tests
    additional_tests(g1, g2, g3);

    // Clean up
    delete g1;
    delete g2;
    delete g3;

    cout << "Testing completed" << endl;

    return 0;
}