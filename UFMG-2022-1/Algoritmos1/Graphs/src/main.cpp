#include "graph.hpp"

int main() {
    Node s(0);
    
    Graph g(6);


    bool mt = g.bellmanFord(s);

    return 0;
}
