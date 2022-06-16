#include "graph.hpp"

int main() {
    Node s(0), t(5);
    
    Graph g(6);

    g.addEdge(0,1,16,0);
    g.addEdge(0,2,13,0);

    g.addEdge(1,3,12,0);
    
    g.addEdge(2,1,4,0);
    g.addEdge(2,4,14,0);
    
    g.addEdge(3,2,9,0);
    g.addEdge(3,5,20,0);
    
    g.addEdge(4,3,7,0);
    g.addEdge(4,5,4,0);

    cout << g.fordFulkerson(s, t) << endl;
    return 0;
}
