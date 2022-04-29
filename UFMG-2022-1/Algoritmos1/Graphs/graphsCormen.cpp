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
    
        string color;

        Node(int node);
};

class Graph {
    private:
        int n;
        int time;
        bool isDAG;

        vector <Node> nodes;
        vector <list <Node>> adj;
    public:
        Graph(int n);

        void addEdge(int u, int v);

        void BFS(Node s);
        
        void DFS();
        void DFS_visit(Node u);

        void topological_sort();
};

Node::Node(int node) {
    this->node = node;
    color = "White";
    dist = -1;
    parent = -1;
    iniTime = -1;
    finalTime = -1;
}

Graph::Graph(int n) {
    Node v(-1);
    
    for(int i = 0; i < n; i++) {
        Node v(i);
        nodes.push_back(v);
    }

    this-> n = n;
    adj.resize(n);
    isDAG = true;
}

void Graph::addEdge(int u, int v) {
    Node x(v);
    adj[u].push_back(x);
}

void Graph::BFS(Node s) {
    list <Node> q;
    list <Node> :: iterator v;
    Node u(-1);

    nodes[s.node].color = "Gray";
    nodes[s.node].dist = 0;
    nodes[s.node].parent = -1;

    q.push_back(s);
    while(!q.empty()) {
        u = q.front();
        q.pop_front();
        
        cout << u.node << " ";

        for(v = adj[u.node].begin(); v != adj[u.node].end(); v++) {
            if(nodes[(*v).node].color == "White") {
                nodes[(*v).node].color = "Gray";
                nodes[(*v).node].dist = nodes[u.node].dist + 1;;
                nodes[(*v).node].parent = u.node;

                q.push_back(*v);
            }
        }
        nodes[u.node].color = "Black";
    }
    cout << endl;
}

void Graph::DFS() {
    vector <Node> :: iterator u;
    time = 0;
    
    for(u = nodes.begin(); u != nodes.end(); u++) {
        (*u).color = "White";
        (*u).parent = -1;
    }
    
    for(u = nodes.begin(); u != nodes.end(); u++) {
        if((*u).color == "White") {
            //cout << (*u).node << " ";
            DFS_visit(*u);
        }
        //cout << endl;
    }
}

void Graph::DFS_visit(Node u) {
    list <Node> :: iterator v;

    time++;
    nodes[u.node].iniTime = time;
    nodes[u.node].color = "Gray";

    for(v = adj[u.node].begin(); v != adj[u.node].end(); v++) {
        if(nodes[(*v).node].color == "Black") {
            if(nodes[u.node].iniTime < nodes[(*v).node].iniTime) {
                //cout << "(" << u.node << ", " << (*v).node << ") é uma aresta direta" << endl;
            }
            else {
                //cout << "(" << u.node << ", " << (*v).node << ") é uma aresta cruzada" << endl;
            }
        }
        else if(nodes[(*v).node].color == "Gray") {
            //cout << "(" << u.node << ", " << (*v).node << ") é uma aresta de retorno" << endl;
            isDAG = false;
        }
        else if(nodes[(*v).node].color == "White") {
            nodes[(*v).node].parent = u.node;
            //cout << "(" << u.node << ", " << (*v).node << ") é uma aresta de arvore" << endl;
            //cout << (*v).node << " ";
            DFS_visit(*v);
        }
    }
    nodes[u.node].color = "Black";
    time++;
    nodes[u.node].finalTime = time;
}

void Graph::topological_sort() {
    vector <Node> topOrder;
    vector <Node> :: iterator it;
    Node aux(-1);
    
    DFS();
    if(isDAG) {
        topOrder = nodes;
        
        // Implementar um algoritmo de ordenação mais eficiente
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j < n; j++) {
                if(topOrder[j].finalTime > topOrder[i].finalTime) {
                    aux = topOrder[i];
                    topOrder[i] = topOrder[j];
                    topOrder[j] = aux;
                }
            }
        }
        
        for(it = topOrder.begin(); it != topOrder.end(); it++) {
            cout << (*it).node << " ";
        }
    }
    cout << endl;
}
int main() {
    Node s(0);
    
    Graph g(7);
    g.addEdge(0,3);
    g.addEdge(0,4);
    g.addEdge(0,6);
    g.addEdge(1,2);
    g.addEdge(1,4);
    g.addEdge(1,5);
    g.addEdge(2,3);
    g.addEdge(2,4);
    g.addEdge(3,4);
    g.addEdge(4,5);
    g.addEdge(4,6);
    g.addEdge(5,6);

    
    
    //g.BFS(s);
    //g.DFS();

    g.topological_sort();
    return 0;
}