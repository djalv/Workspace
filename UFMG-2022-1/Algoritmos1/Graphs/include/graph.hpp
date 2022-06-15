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
        vector <vector <int>> matAdj;
        vector <vector <int>> weight;
        vector <vector <int>> flux;

        vector <Node> path;
        
    public:
        Graph(int n);

        void clearGraph();

        void addEdge(int u, int v, int w=0, int f=0);
        void deleteEdge(Edge uv);

        void BFS(Node s);
        bool BFS(Node s, Node t);

        void printPath();
        
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
        
        int fordFulkerson(Node s, Node t);
};

#endif