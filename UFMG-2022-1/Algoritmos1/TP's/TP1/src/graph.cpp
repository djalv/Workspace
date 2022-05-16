#include <iostream>
#include "graph.hpp"

Node::Node(int node) {
    this->node = node;
    color = "White";
    dist = -1;
    parent = -1;
    iniTime = -1;
    finalTime = -1;

    label = ' ';
}

void Graph::initGraph(int n) {
    Node v(-1);
    
    for(int i = 0; i < n; i++) {
        Node v(i);
        nodes.push_back(v);
    }

    this-> n = n;
    adj.resize(n);
}

void Graph::addEdge(int u, int v) {
    Node x(v);
    adj[u].push_back(x);
}

vector <int> Graph::BFS(Node s) {
    for(int i = 0; i < nodes.size(); i++) {
        nodes[i].color = "White";
    }
    
    list <Node> q;
    list <Node> :: iterator v;
    
    vector <int> distances;
    distances.resize(n);
    
    Node u(-1);

    nodes[s.node].color = "Gray";
    nodes[s.node].dist = 0;
    nodes[s.node].parent = -1;
    distances[s.node] = nodes[s.node].dist;

    q.push_back(s);
    while(!q.empty()) {
        u = q.front();
        q.pop_front();

        for(v = adj[u.node].begin(); v != adj[u.node].end(); v++) {
            if(nodes[(*v).node].color == "White") {
                nodes[(*v).node].color = "Gray";
                nodes[(*v).node].dist = nodes[u.node].dist + 1;;
                nodes[(*v).node].parent = u.node;
                distances[(*v).node] = nodes[u.node].dist + 1;
                q.push_back(*v);
            }
        }
        nodes[u.node].color = "Black";
    }
    return distances;
}
