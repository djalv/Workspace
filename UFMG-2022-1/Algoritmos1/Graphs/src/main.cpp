#include "graph.hpp"

int main() {
    Node s(0);
    
    Graph g(5);


    g.addEdge(0, 1, 10);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(3, 1, 3);
    g.addEdge(3, 2, 9);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 0, 7);
    g.addEdge(4, 2, 6);

    g.dijkstra(s);

    return 0;
}
