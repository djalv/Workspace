#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <iterator>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

typedef struct {
    int x;
    int y;
}Loc;

class Bike {
    private:
        int id;
        Loc geoLoc;
    public:
        Bike();

        void setId(int id);
        int getId();

        void setLoc(int x, int y);
        Loc getLoc();

        void addBike(int id, int x, int y);

        friend class Map;
};

class Visitor {
    private:
        int id;
        char c_id;
        Loc geoLoc;
    public:
        Visitor();

        void setId(int id);
        int getId();

        void setC_id(char c_id);
        char getC_id();
        
        void setLoc(int x, int y);
        Loc getLoc();

        void addVisitor(char c, int x, int y);

        friend class Map;
};

class Node {
    public:
        int node;
        int dist;
        int parent;
        int iniTime;
        int finalTime;

        char label;
    
        string color;

        Node(int node);
};

class Graph {
    private:
        int n;

        vector <Node> nodes;
        vector <list <Node>> adj;
    public:
        //Graph(int n);
        void initGraph(int n);
        void addEdge(int u, int v);

        vector <int> BFS(Node s);

        friend class Map;
};

class Map {
    private:
        int n;
        int rows;
        int columns;
        vector <vector <char>> map;
        Graph graph;

        vector <Visitor> visitors;
        vector <Bike> bikes;

        vector <int> nodeVisitors;
        vector <int> nodeBikes;

        vector <vector <Visitor>> bikePreferences;
        vector <vector <Bike>> visitorPreferences;
    public:
        Map(int n, int rows, int columns);
        void addItem(char c, int x, int y);
        void createGraph();
        void setBikePreferences();
        void setVisitorPreferences(vector <vector <int>> &preferences);
        void gale_shapley();

        void printMap();
        void printGraph();
};

Bike::Bike() {
    id = -1;
    setLoc(-1, -1);
}

void Bike::setId(int id) {
    this->id = id;
}

int Bike::getId() {
    return id;
}

void Bike::setLoc(int x, int y) {
    geoLoc.x = x;
    geoLoc.y = y;
}

Loc Bike::getLoc() {
    return geoLoc;
}

void Bike::addBike(int id, int x, int y) {
    setId(id);
    setLoc(x, y);
}

Visitor::Visitor() {
    id = -1;
    setLoc(-1, -1);
}

void Visitor::setId(int id) {
    this->id = id;
}

int Visitor::getId() {
    return id;
}

void Visitor::setC_id(char c_id) {
    this->c_id = c_id;
}

char Visitor::getC_id() {
    return c_id;
}

void Visitor::setLoc(int x, int y) {
    geoLoc.x = x;
    geoLoc.y = y;
}

Loc Visitor::getLoc() {
    return geoLoc;
}

void Visitor::addVisitor(char c, int x, int y) {
    int i = c - 97;
    setId(i);
    setC_id(c);
    setLoc(x, y);
}

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

Map::Map(int n, int rows, int columns) {
    this->n = n;
    this->rows = rows;
    this->columns = columns;

    visitors.resize(n);
    bikes.resize(n);
    
    graph.initGraph(rows*columns);
    
    visitorPreferences.resize(n);
    bikePreferences.resize(n);
    
    for(int i = 0; i < n; i++) {
        visitorPreferences[i].resize(n);
        bikePreferences[i].resize(n);
    }   

    map.resize(rows);
    for(int i = 0; i < rows; i++) {
        map[i].resize(columns);
    }   
}

void Map::addItem(char c, int x, int y) {
    if(x < rows && x >= 0 && y < columns && y >= 0) {
        int k = c;
        int idx;
        map[x][y] = c;

        if(c >= 'a' && c <= 'j') {
            idx = k - 97;
            visitors[idx].addVisitor(c, x, y);
        }
        if(c >= '0' && c <= '9') {
            idx = k - 48;
            bikes[idx].addBike(idx, x, y);
        }
    }
}

void Map::createGraph() {
    int node = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            if(map[i][j] >= 'a' && map[i][j] <= 'j') {
                nodeVisitors.push_back(node);
            }
            else if(map[i][j] >= '0' && map[i][j] <= '9') {
                nodeBikes.push_back(node);
            }
            
            graph.nodes[node].label = map[i][j];
            
            if(map[i][j] != '-') {
                if(j-1 >= 0 && map[i][j-1] != '-') {
                    graph.addEdge(node, node-1);
                }
                if(i-1 >= 0 && map[i-1][j] != '-') {
                    graph.addEdge(node, node-columns);
                }
                if(j+1 < columns && map[i][j+1] != '-') {
                    graph.addEdge(node, node+1);
                }
                if(i+1 < rows && map[i+1][j] != '-') {
                    graph.addEdge(node, node+columns);
                }
            }
            node++;
        }
    }
}

void Map::setBikePreferences() {
    createGraph();
    vector <vector <int>> distances;
    
    distances.resize(rows);
    for(int i = 0; i < rows; i++) {
        distances[i].resize(columns);
    }
    
    for(int i = 0; i < nodeBikes.size(); i++) {
        vector <int> temp;
        int bike = nodeBikes[i];
        Node s(bike);
        temp = graph.BFS(s);
        //cout << bike << endl;

        for(int i = 0; i < nodeVisitors.size(); i++) {
            int visit = nodeVisitors[i];
            cout << temp[visit] << " ";
        }
        cout << endl;
    }

    /*for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            cout << distances[i][j] << " ";
        }
        cout << endl;
    }*/
    
}

void Map::setVisitorPreferences(vector <vector <int>> &preferences) {
    int i, j, min_idx;

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            visitorPreferences[i][j] = bikes[j];
        }
    }

    for(int k = 0; k < n; k++) {
        for(i = 0; i < n-1; i++) {
            min_idx = i;
            for(j = i+1; j < n; j++) {
                if(preferences[k][j] > preferences[k][min_idx]) {
                    min_idx = j;
                }
            }
            int aux = preferences[k][i];
            preferences[k][i] = preferences[k][min_idx];
            preferences[k][min_idx] = aux;

            Bike temp = visitorPreferences[k][i];
            visitorPreferences[k][i] = visitorPreferences[k][min_idx];
            visitorPreferences[k][min_idx] = temp;
        }
    }
}

void Map::printMap() {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

void Map::printGraph() {
    list <Node> :: iterator j;
    for(int i = 0; i < rows*columns; i++) {
        cout << i << "| ";
        for(j = graph.adj[i].begin(); j != graph.adj[i].end(); j++) {
            cout << (*j).node << " ";
        }
        cout << endl;
    }
}

int main() {
    ifstream file("test.txt");
    vector <vector <int>> preferences;
    
    int n, rows, columns;
    char in;
    int number;

    file >> n;

    preferences.resize(n);
    
    for(int i = 0; i < n; i++) {
        preferences[i].resize(n);
    }   

    file >> rows >> columns;

    Map m(n, rows, columns);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            file >> in;
            m.addItem(in, i, j);
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            file >> number;
            preferences[i][j] = number;
        }
    }
    //m.createGraph();
    //m.printGraph();
    //m.setVisitorPreferences(preferences);
    m.setBikePreferences();
    file.close();
    return 0;
}