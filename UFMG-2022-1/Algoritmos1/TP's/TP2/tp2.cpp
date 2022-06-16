#include <iostream>
#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <iterator>
#include <string>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

class Node {
    public:
        int node;
        bool visited;
        int d; // Estimativa de custo minino
        int p; // Nó parente na arvore de caminhos minimos
        
        Node(int node) {
            this->node = node;
            this->visited = false;
            this->d = -1;
            this->p = -1;
        }
        Node() {
            this->node = -1;
            this->visited = false;
            this->d = -1;
            this->p = -1;
        }
};

class Edge {
    public:
        Node *u;
        Node *v;
        int w; // weight

        Edge(Node *u, Node *v, int w) {
            this->u = u;
            this->v = v;
            this->w = w;
        }
        Edge() {
            this->u = nullptr;
            this->v = nullptr;
            this->w = 0;
        }
};

class Heap {
    public:
        int size;
        int cap;
        vector <Node> A;
        vector <int> ids;

        Heap(int n) {
            size = 0;
            cap = n;
            A.resize(n);
            ids.resize(n);
        }

        int parent(int i) {
            return floor(i/2);
        }

        int left(int i) {
            return 2 * i + 1;
        }

        int right(int i) {
            return 2 * i + 2;
        }

        Node heapMinimum() {
            return A[0];
        }
    
        void insert(Node v) {
            if(size == cap) {
                cout << "Overflow: Não consegue inserir" << endl;
                return;
            }
            size = size + 1;
            int i = size - 1;
            A[i] = v;
            ids[v.node] = i;

            while(i != 0 && A[parent(i)].d >= A[i].d){
                Node aux = A[parent(i)];
                A[parent(i)] = A[i];
                A[i] = aux;
            
                ids[A[parent(i)].node] = parent(i);
                ids[A[i].node] = i;

                i = parent(i);
            }
        }

        void decreaseKey(int &idx, int d) {
            int i = ids[idx];
            
            if(i < 0) {
                return;
            }

            A[i].d = d;

            while(i != 0 && A[parent(i)].d >= A[i].d){
                Node aux = A[parent(i)];
                A[parent(i)] = A[i];
                A[i] = aux;
            
                ids[A[parent(i)].node] = parent(i);
                ids[A[i].node] = i;

                i = parent(i);
            }
        }

        Node extractMin() {
            Node min = A[0];
        
            ids[A[0].node] = -1;
            A[0] = A[size-1];
        
            size = size - 1;
            minHeapfy(0);

            return min;
        }

        void minHeapfy(int i) {
            int l = left(i);
            int r = right(i);
        
            int min = i;

            if(l < size && A[l].d < A[i].d) {
                min = l;
            }
            else {
                min = i;
            }
            if(r < size && A[r].d < A[min].d) {
                min = r;
            }

            if(min != i) {
                Node aux = A[i];
                A[i] = A[min];
                A[min] = aux;

                ids[A[i].node] = i;
                ids[A[min].node] = min;
                minHeapfy(min);
            }
        }

        void printHeap() {
            for(int i = 0; i < size; i++) {
                cout << A[i].d << " ";
            }
            cout << endl;
        }
};

class Graph {
    public:
        int n;
        int m;

        vector <Node> nodes;
        vector <Edge> edges;
        
        vector <list <Node>> adj;
        vector <vector <int>> weight;

        vector <int> path;

        Graph(int n) {
            weight.resize(n);

            for(int i = 0; i < n; i++) {
                Node v(i);
                nodes.push_back(v);
                weight[i].resize(n);
            }
            this->m = 0;
            this-> n = n;
            adj.resize(n);
        }

        void addEdge(int u, int v, int w=0) {
            Node *x = &nodes[u];
            Node *y = &nodes[v];
            nodes[v].d = w;
            Edge xy(x, y, w);

            edges.push_back(xy);
            adj[u].push_back(*y);
            weight[u][v] = w;
            m++;
        }
        void initSingleSource(Node s) {
            path.clear();

            for(int i = 0; i < n; i++) {
                nodes[i].d = 2147483647;
                nodes[i].p = -1;
            }
            nodes[s.node].d = 0;
            nodes[s.node].visited = true;
        }

        void relax(Node &u, Node &v) {
            if(nodes[v.node].d > nodes[u.node].d + weight[u.node][v.node]) {
                nodes[v.node].d = nodes[u.node].d + weight[u.node][v.node];
                nodes[v.node].p = nodes[u.node].node;
            }
        }

        int dijkstra(Node s, Node t) {
            list <Node> :: iterator v;
            vector <int> widest(n, -2147483647);
            vector <int> path(n, 0);
            Heap pq(n);

            widest[s.node] = 2147483647;
            nodes[s.node].d = 0;

            pq.insert(nodes[s.node]);

            while(pq.size > 0) {
                Node u = nodes[pq.extractMin().node];

                for(v = adj[u.node].begin(); v != adj[u.node].end(); v++) {
                    int dstc = max(widest[(*v).node], min(widest[u.node], weight[u.node][(*v).node]));

                    if(dstc > widest[(*v).node]) {
                        widest[(*v).node] = dstc;
                        path[(*v).node] = u.node;

                        pq.insert(nodes[(*v).node]);
                    }
                }
            }
            return widest[t.node];
        }
};

int main() {
    int n, m, q;
    int u, v, w;
    int city1, city2;

    ifstream file("test1.txt");

    file >> n >> m >> q;

    Graph g(n);

    for(int i = 0; i < m; i++) {
        file >> u >> v >> w;
        g.addEdge(u-1, v-1, w);
    }

    for(int i = 0; i < q; i++) {
        file >> city1 >> city2;
        cout << g.dijkstra(city1-1, city2-1) << endl;
    }
    
    file.close();
    return 0;
}