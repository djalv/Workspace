#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <iterator>
#include <string>

using namespace std;

int distances[16];

class Node {
    public:
        int node;
        int dist;
        int iniTime;
        int finalTime;
        int subSet;

        int d; // Estimativa de custo minino
        Node *p; // Nó parente na arvore de caminhos minimos

        Node *parent;
        string color;

        Node(int node);

        friend bool operator<(Node const &l, Node const &r) {
            if(l.node < r.node) {
                return true;
            }
            return false;
        }
};


class Graph {
    private:
        int n;
        int time;
        bool isDAG;

        vector <Node> nodes;
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

};

class Sets {
    private:
        vector <list <Node>> s;
        int n;
    public:
        Sets(int n);
        void makeSet(Node x);
        void unionSets(Node &x, Node &y);
        
        Node findSet(Node x);
        
        void printSets();
};

Node::Node(int node) {
    this->node = node;
    color = "White";
    dist = -1;
    parent = nullptr;
    iniTime = -1;
    finalTime = -1;
    subSet = node;
}

Graph::Graph(int n) {
    Node v(-1);
    
    weight.resize(n);
    for(int i = 0; i < n; i++) {
        Node v(i);
        nodes.push_back(v);
        weight[i].resize(n);
    }

    this-> n = n;
    adj.resize(n);
    isDAG = true;
}

void Graph::addEdge(int u, int v, int w=0) {
    Node x(v);
    adj[u].push_back(x);
    weight[u][v] = w;
    weight[v][u] = w;
}

void Graph::BFS(Node s) {
    list <Node> q;
    list <Node> :: iterator v;
    Node u(-1);
    
    for(int i = 0; i < nodes.size(); i++) {
        nodes[i].color = "White";
    }

    nodes[s.node].color = "Gray";
    nodes[s.node].dist = 0;
    nodes[s.node].parent = nullptr;
    distances[s.node] = nodes[s.node].dist;

    q.push_back(s);
    while(!q.empty()) {
        u = q.front();
        q.pop_front();
        
        //cout << u.node << " ";

        for(v = adj[u.node].begin(); v != adj[u.node].end(); v++) {
            if(nodes[(*v).node].color == "White") {
                nodes[(*v).node].color = "Gray";
                nodes[(*v).node].dist = nodes[u.node].dist + 1;;
                nodes[(*v).node].parent = &u;
                distances[(*v).node] = nodes[u.node].dist + 1;
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
        (*u).parent = nullptr;
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
            nodes[(*v).node].parent = &u;
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

Sets::Sets(int n) {
    this->n = n;
    s.resize(n);
}

void Sets::makeSet(Node x) {
    s[x.node].push_back(x);
    x.subSet = x.node;
}

Node Sets::findSet(Node x) {
    return s[x.subSet].front();
}

void Sets::unionSets(Node &x, Node &y) {
    s[x.subSet].merge(s[y.subSet]);
    y.subSet = x.subSet;
}

void Sets::printSets() {
    list <Node> :: iterator it;
    for(int i = 0; i < s.size(); i++) {
        for(it = s[i].begin(); it != s[i].end(); it++) {
            cout << (*it).node << " ";
        }
        cout << endl;
    }
}

void Graph::mstKruskal() {
    Sets A(n);
    list <Node> q;
    list <Node> :: iterator v;
    Node u(-1);

    for(int i = 0; i < n; i++) {
        A.makeSet(nodes[i]);
    }
    //Ordenar as arestas de acordo com o peso com o mergesort
    
}

void Graph::initSingleSource(Node s) {
    vector <Node> ::iterator it;
    for(it = nodes.begin(); it != nodes.end(); it++) {
        (*it).d = 2147483647;
        (*it).p = nullptr;
    }
    nodes[s.node].d = 0;
}

void Graph::relax(Node &u, Node &v) {
    if(nodes[v.node].d > nodes[u.node].d + weight[u.node][v.node]) {
        nodes[v.node].d = nodes[u.node].d + weight[u.node][v.node];
        nodes[v.node].p = &u;
    }
}

void Graph::printMinimunPath() {
    for(int i = 0; i < nodes.size(); i++) {
        cout << "No = " << nodes[i].node << " d = " << nodes[i].d << endl;
    }

    /*for(int i = 0; i < nodes.size(); i++) {
        cout << "No = " << nodes[i].node << "p = " << nodes[i].p->node << endl;
    }*/
}

bool Graph::bellmanFord(Node s) {
    list <Node> q;
    list <Node> :: iterator v;
    Node u(-1);

    initSingleSource(s);
    //for(int cont = 0; cont < n-1; cont++) {
        for(int i = 0; i < n; i++) {
            u = nodes[i];
            for(v = adj[u.node].begin(); v != adj[u.node].end(); v++) {
                relax(u, *v);
            }
        }
    //}
    printMinimunPath();
    for(int i = 0; i < n; i++) {
        u = nodes[i];
        for(v = adj[u.node].begin(); v != adj[u.node].end(); v++) {
            if(nodes[(*v).node].d > nodes[u.node].d + weight[u.node][(*v).node]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    Node s(0);
    
    Graph g(5);
    g.addEdge(0,1,6);
    g.addEdge(0,3,7);
    g.addEdge(1,2,5);
    g.addEdge(1,3,8);
    g.addEdge(1,4,-4);
    g.addEdge(2,1,-2);
    g.addEdge(3,2,-3);
    g.addEdge(3,4,9);
    g.addEdge(4,2,7);
    g.addEdge(4,0,2);

    bool mt = g.bellmanFord(s);
    
    /*cout << mt;

    if(mt) {
        g.printMinimunPath();
    }*/

    return 0;
}