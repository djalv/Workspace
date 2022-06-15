#ifndef DJALV_GRAPH
#define DJALV_GRAPH

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <iterator>
#include <string>
#include "node.hpp"
#include "edge.hpp"
#include "heap.hpp"

using namespace std;

class Graph {
    private:
        int n;
        int m;
        int time;
        bool isDAG;

        vector <Node> nodes;
        vector <Edge> edges;
        
        vector <list <Node>> adj;
        vector <vector <int>> weight;
        
    public:
        Graph(int n);

        void addEdge(int u, int v, int w);

        void BFS(Node s);
        
        void DFS();
        void DFS_visit(Node u);

        void topological_sort();

        void mstKruskal();

        void initSingleSource(Node s);
        void relax(Node &u, Node &v);

        void printMinimunPath();
        bool bellmanFord(Node s);

        void DAG_ShortestPath(Node s);

        void dijkstra(Node s);
};

#endif