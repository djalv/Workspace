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
    
    distances.resize(n);
    for(int i = 0; i < n; i++) {
        distances[i].resize(n);
    }
    
    for(int i = 0; i < nodeBikes.size(); i++) {
        vector <int> temp;
        int bike = nodeBikes[i];
        int bike_idx = graph.nodes[bike].label - 48;
        
        Node s(bike);
        temp = graph.BFS(s);

        for(int i = 0; i < nodeVisitors.size(); i++) {
            int visitor = nodeVisitors[i];
            int visitor_idx = graph.nodes[visitor].label - 97;
            distances[bike_idx][visitor_idx] = temp[visitor];
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            bikePreferences[i][j] = visitors[j].id;
        }
    }

    int i, j, min_idx;
    for(int k = 0; k < n; k++) {
        for(i = 0; i < n-1; i++) {
            min_idx = i;
            for(j = i+1; j < n; j++) {
                if(distances[k][j] < distances[k][min_idx]) {
                    min_idx = j;
                }
            }
            int aux = distances[k][i];
            distances[k][i] = distances[k][min_idx];
            distances[k][min_idx] = aux;

            int temp = bikePreferences[k][i];
            bikePreferences[k][i] = bikePreferences[k][min_idx];
            bikePreferences[k][min_idx] = temp;
        }
    }

    for(int k = 0; k < n; k++) {
        for(i = 0; i < n-1; i++) {
            for(j = i+1; j < n; j++) {
                if(distances[k][i] == distances[k][j]) {
                    if(bikePreferences[k][i] > bikePreferences[k][j]) {
                
                        int aux = distances[k][i];
                        distances[k][i] = distances[k][j];
                        distances[k][j] = aux;

                        int temp = bikePreferences[k][i];
                        bikePreferences[k][i] = bikePreferences[k][j];
                        bikePreferences[k][j] = temp;
                    }
                }
            }
        }
    }

    for(int i = 0; i < bikePreferences.size(); i++) {
        cout << i << "| ";
        for(int j = 0; j < bikePreferences[i].size(); j++) {
            cout << bikePreferences[i][j] << " ";
        }
        cout << endl;
    }
}

void Map::setVisitorPreferences(vector <vector <int>> &preferences) {
    int i, j, min_idx;

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            visitorPreferences[i][j] = bikes[j].id;
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

            int temp = visitorPreferences[k][i];
            visitorPreferences[k][i] = visitorPreferences[k][min_idx];
            visitorPreferences[k][min_idx] = temp;
        }
    }

    for(int k = 0; k < n; k++) {
        for(i = 0; i < n-1; i++) {
            for(j = i+1; j < n; j++) {
                if(preferences[k][i] == preferences[k][j]) {
                    if(visitorPreferences[k][i] > visitorPreferences[k][j]) {
                
                        int aux = preferences[k][i];
                        preferences[k][i] = preferences[k][j];
                        preferences[k][j] = aux;

                        int temp = visitorPreferences[k][i];
                        visitorPreferences[k][i] = visitorPreferences[k][j];
                        visitorPreferences[k][j] = temp;
                    }
                }
            }
        }
    }

    for(int i = 0; i < visitorPreferences.size(); i++) {
        cout << i << "| ";
        for(int j = 0; j < visitorPreferences[i].size(); j++) {
            cout << visitorPreferences[i][j] << " ";
        }
        cout << endl;
    }
}

void range(list <int> &ls, int n) {
    for(int i = 0; i < n; i++) {
        ls.push_back(i);
    }
}

void fill(vector <int> &v, int n, bool zero = false) {
    int x = 0;
    
    if(!zero) {
        x = -1;
    }

    for(int i = 0; i < n; i++) {
        v.push_back(x);
    }
}

void print(vector <int> &v) {
    for(int i = 0; i < v.size(); i++) {
        char c = 97 + i;
        cout << c << " " << v[i] << endl;
    }
}

void Map::gale_shapley(){
    list <int> unpairVisitor;
    vector <int> visitorList, bikeList, visitorPairs, bikePairs, nextChoice;
    int rank[n][n];
    int visitor, bike, nextBike, currentPair, currentPairRank, visitorRank;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            rank[i][bikePreferences[i][j]-1] = j;
        }
    }

    range(unpairVisitor, n);
    fill(visitorPairs, n);
    fill(bikePairs, n);
    fill(nextChoice, n, true);

    while(!unpairVisitor.empty()) {
        visitor = unpairVisitor.front();

        visitorList = visitorPreferences[visitor];
        nextBike = nextChoice[visitor];

        bike = visitorList[nextBike];
        bikeList = bikePreferences[bike];

        currentPair = bikePairs[bike];

        if(currentPair == -1) {
            bikePairs[bike] = visitor;
            visitorPairs[visitor] = bike;

            nextChoice[visitor] += 1;
            unpairVisitor.pop_front();
        }
        else {
            currentPairRank = rank[bike][currentPair];
            visitorRank = rank[bike][visitor];

            if(currentPairRank > visitorRank) {
                bikePairs[bike] = visitor;
                visitorPairs[visitor] = bike;

                nextChoice[visitor] += 1;
                unpairVisitor.pop_front();
                unpairVisitor.push_front(currentPairRank);
            }
            else {
                nextChoice[visitor] += 1;
            }
        }
    }
    print(visitorPairs);
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