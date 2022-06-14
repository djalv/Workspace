#ifndef GRAPH_DJALV
#define GRAPH_DJALV

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <iterator>
#include <string>

using namespace std;

class Node {
    public:
        int node;
        int dist;
        int parent;
        int iniTime;
        int finalTime;

        char label;
    
        string color;

        Node(int node);
};

class Graph {
    private:
        int n;

        vector <Node> nodes;
        vector <list <Node>> adj;
    public:
        //Graph(int n);
        void initGraph(int n);
        void addEdge(int u, int v);

        vector <int> BFS(Node s);

        friend class Map;
};

#endif