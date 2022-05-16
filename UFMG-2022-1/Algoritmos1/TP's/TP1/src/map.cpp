#include <iostream>
#include <queue>
#include "map.hpp"

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