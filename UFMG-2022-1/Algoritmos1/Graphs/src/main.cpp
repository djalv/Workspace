#include "graph.hpp"

int main() {
    Node s(0), t(5);
    
    Graph g(4);
    g.addEdge(0,1,1);
    g.addEdge(0,2,2);
    g.addEdge(1,3,3);
    g.addEdge(2,3,5);

    g.dijkstra(s);
    return 0;
}
