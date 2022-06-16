#include "graph.hpp"

Graph::Graph(int n) {
    weight.resize(n);
    flux.resize(n);
    matAdj.resize(n);
    tree.resize(n);

    for(int i = 0; i < n; i++) {
        Node v(i);
        nodes.push_back(v);
        weight[i].resize(n);
        flux[i].resize(n);
        matAdj[i].resize(n);
    }

    this->m = 0;
    this-> n = n;
    adj.resize(n);
    isDAG = true;
}

void Graph::clearGraph() {
    edges.clear();

    for(int i = 0; i < n; i++) {
        adj[i].clear();
        matAdj[i].clear();
        weight[i].clear();
        flux[i].clear();
    }
    m = 0;
}

void Graph::addEdge(int u, int v, int w, int f) {
    Node *x = &nodes[u];
    Node *y = &nodes[v];
    
    Edge xy(x, y, w, f);

    edges.push_back(xy);
    adj[u].push_back(*y);
    matAdj[u][v] = 1;
    flux[u][v] = f;
    weight[u][v] = w;
    m++;
}

void Graph::deleteEdge(Edge uv){
    Node *u = uv.u;
    Node *v = uv.v;

    vector <Edge> ::iterator x;
    list <Node> ::iterator it;
    
    for(x = edges.begin(); x != edges.end(); x++) {
        if((*x).u->node == u->node && (*x).v->node == v->node) {
            edges.erase(x);
        }
    }

    for(it = adj[u->node].begin(); it != adj[u->node].end(); it++){
        if((*it) == *v) {
            adj[u->node].erase(it);
            it = adj[u->node].end();
        }
    }
    matAdj[u->node][v->node] = 0;
    weight[u->node][v->node] = 0;
    flux[u->node][v->node] = 0;

    m = m - 1;
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

bool Graph::BFS(Node s, Node t) {
    list <Node> q;
    list <Node> :: iterator v;
    vector <Node> ::iterator x;

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
    tree[0] = u;

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

                tree[(*v).node] = u;

                if((*v).node == t.node) {
                    return true;
                }
                q.push_back(*v);
            }
        }
        nodes[u.node].color = "Black";
    }
    return false;
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
    Heap q(n);
    Node u;

    initSingleSource(s);
    
    for(int i = 0; i < n; i++) {
        u = nodes[i];
        q.insert(u);
    }

    while(q.size > 0) {
        u = q.extractMin();
        set.push_back(u);

        for(v = adj[u.node].begin(); v != adj[u.node].end(); v++) {
            if(nodes[(*v).node].d > nodes[u.node].d + weight[u.node][(*v).node]) {
                nodes[(*v).node].d = nodes[u.node].d + weight[u.node][(*v).node];
                nodes[(*v).node].p = nodes[u.node].node;

                q.decreaseKey(nodes[(*v).node].node, nodes[(*v).node].d);
            }
        }
    }
}

int Graph::fordFulkerson(Node s, Node t) {
    Graph rGraph(n);
    Node *u, *v;

    int c1;
    int maxFlow = 0;

    for(int i = 0; i < m; i++) {
        u = edges[i].u;
        v = edges[i].v;
        int w = edges[i].w;

        rGraph.addEdge(u->node, v->node, w);
    }

    while(rGraph.BFS(s, t)) {
        vector <Node> augPath;
        vector <Edge> edgePath;
        vector <int> capacity;
        augPath.push_back(t);

        Node k = rGraph.tree[t.node];
        while(k.node != -1) {
            augPath.push_back(k);
            k = rGraph.tree[k.node];
        }

        for(int i = 0; i < augPath.size() - 1; i++) {
            int cap = rGraph.weight[augPath[i+1].node][augPath[i].node];
            capacity.push_back(cap);
            
            Edge x(&augPath[i+1], &augPath[i], cap, 0);
            edgePath.push_back(x);
        }

        int minCap = capacity[0];
        for(int i = 0; i < capacity.size() - 1; i++) {
            if(minCap > capacity[i]) {
                minCap = capacity[i];
            }
        }

        for(int i = edgePath.size()-1; i >= 0; i--) {
            int x = edgePath[i].u->node;
            int y = edgePath[i].v->node;
            int w = rGraph.weight[x][y];

            cout << "(" << x << ", " << y << ") " << w << endl;
        }
        
        for(int i = edgePath.size()-1; i >= 0; i--) {
            int x = edgePath[i].u->node;
            int y = edgePath[i].v->node;
            int w = weight[x][y];
            int flow = 0;
            
            if(matAdj[x][y] == 1) {
                flow = w - minCap;
                rGraph.weight[x][y] = flow;
                
                rGraph.addEdge(y, x, minCap);
                if(flow == 0) {
                    rGraph.deleteEdge(edgePath[i]);
                }
            }
        }
        maxFlow += minCap;
    }

    return maxFlow;
}