#include "graph.hpp"

Graph::Graph(int n) {
    weight.resize(n);

    for(int i = 0; i < n; i++) {
        Node v(i);
        nodes.push_back(v);
        weight[i].resize(n);
    }

    this->m = 0;
    this-> n = n;
    adj.resize(n);
    isDAG = true;
}


void Graph::addEdge(int u, int v, int w=0) {
    Node *x = &nodes[u];
    Node *y = &nodes[v];
    
    Edge xy(x, y, w);

    edges.push_back(xy);
    adj[u].push_back(*y);
    
    weight[u][v] = w;
    m++;
}

void Graph::BFS(Node s) {
    list <Node> q;
    list <Node> :: iterator v;
    vector <int> distances;
    distances.resize(n);
    
    Node u;
    
    
    for(int i = 0; i < nodes.size(); i++) {
        nodes[i].color = "White";
    }

    nodes[s.node].color = "Gray";
    nodes[s.node].dist = 0;
    nodes[s.node].parent = -1;
    distances[s.node] = nodes[s.node].dist;

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
    vector <Node> :: iterator it;
    Node aux;
    
    DFS();
    if(isDAG) {
        // Implementar um algoritmo de ordenação mais eficiente
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j < n; j++) {
                if(nodes[j].finalTime > nodes[i].finalTime) {
                    aux = nodes[i];
                    nodes[i] = nodes[j];
                    nodes[j] = aux;
                }
            }
        }
        
        for(it = nodes.begin(); it != nodes.end(); it++) {
            cout << (*it).node << " ";
        }
    }
    cout << endl;
}

void Graph::initSingleSource(Node s) {
    for(int i = 0; i < n; i++) {
        nodes[i].d = 2147483647;
        nodes[i].p = -1;
    }
    nodes[s.node].d = 0;
}

void Graph::relax(Node &u, Node &v) {
    if(nodes[v.node].d > nodes[u.node].d + weight[u.node][v.node]) {
        nodes[v.node].d = nodes[u.node].d + weight[u.node][v.node];
        nodes[v.node].p = nodes[u.node].node;
    }
}

void Graph::printMinimunPath() {
    for(int i = 0; i < nodes.size(); i++) {
        cout << "No = " << nodes[i].node << " d = " << nodes[i].d << endl;
    }
    cout << endl;
    for(int i = 0; i < nodes.size(); i++) {
        cout << "No = " << nodes[i].node << " p = " << nodes[i].p << endl;
    }
}

bool Graph::bellmanFord(Node s) {
    list <Node> q;
    Node u, v;

    initSingleSource(s);
    for(int i = 1; i <= n-1; i++) {
        for(int j = 0; j < m; j++) {
            u = *(edges[j].u);
            v = *(edges[j].v);
            relax(u, v);
        }
    }

    for(int i = 0; i < m; i++) {
        u = *(edges[i].u);
        v = *(edges[i].v);

        if(nodes[v.node].d > nodes[u.node].d + weight[u.node][v.node]) {
            return false;
        }
    }
    return true;
}

void Graph::DAG_ShortestPath(Node s) {
    list <Node> ::iterator v;
    topological_sort();
    initSingleSource(s);

    for(int i = 0; i < n; i++) {
        Node u = nodes[i];
        for(v = adj[u.node].begin(); v != adj[u.node].end(); v++) {
            relax(u, *v);
        }
    }
}

void Graph::dijkstra(Node s) {
    list <Node> set;
    list <Node> :: iterator v;
    priority_queue <Node, vector <Node>, greater <Node> > q;
    Node u;

    initSingleSource(s);
    
    for(int i = 0; i < n; i++) {
        u = nodes[i];
        q.push(u);
    }

    while(!q.empty()) {
        u = q.top();
        q.pop();
        set.push_back(u);

        for(v = adj[u.node].begin(); v != adj[u.node].end(); v++) {
            relax(u, *v);
        }
    }
}