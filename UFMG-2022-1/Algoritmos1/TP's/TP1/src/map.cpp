#include <iostream>
#include <queue>
#include "map.hpp"

// Funçao construtora do mapa
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

// Adiciona um item ao mapa
void Map::addItem(char c, int x, int y) {
    if(x < rows && x >= 0 && y < columns && y >= 0) {
        int k = c;
        int idx;
        map[x][y] = c;
        
        // Adiciona as visitas e as bikes em um vetor
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

// Cria um grafo de acordo com o mapa
void Map::createGraph() {
    int node = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            // Armazena quais são os nós das visitas e das bikes
            if(map[i][j] >= 'a' && map[i][j] <= 'j') {
                nodeVisitors.push_back(node);
            }
            else if(map[i][j] >= '0' && map[i][j] <= '9') {
                nodeBikes.push_back(node);
            }
            
            // Adiciona o simbolo lido ao rotulo do nó
            graph.nodes[node].label = map[i][j];
            
            // Adiciona as arestas aos nós
            // Se o nó for uma (-) 
            // não aprensentará arestas
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

// Cria a lista de preferencias das bikes
void Map::setBikePreferences() {
    createGraph();
    vector <vector <int>> distances;
    
    distances.resize(n);
    for(int i = 0; i < n; i++) {
        distances[i].resize(n);
    }
    
    // Calcula as distancias das bikes até as visitas
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

    // Adiciona as ids na listas de preferencias
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            bikePreferences[i][j] = visitors[j].id;
        }
    }

    // Selection sort para ordenar as distancias junto com as listas de preferencias
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

    // Aplica a regra de desempate
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
}

// Cria a lista de preferencias das visitas
void Map::setVisitorPreferences(vector <vector <int>> &preferences) {
    int i, j, min_idx;
    
    // Adiciona as ids na listas de preferencias
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            visitorPreferences[i][j] = bikes[j].id;
        }
    }

    // Selection sort para ordenar os graus de preferencias junto com as listas de preferencias
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

    // Aplica a regra de desempate
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
}

// Implementação do Gale Shapley
// Funçao para preencher uma lista sequencialmente (0 -> n)
void range(list <int> &ls, int n) {
    for(int i = 0; i < n; i++) {
        ls.push_back(i);
    }
}

// Função para preencher um array com 0 ou -1
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

    // Cria a matriz com os ranks das visitas
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            rank[i][bikePreferences[i][j]] = j+1;
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
                visitorPairs[currentPair] = -1;

                nextChoice[visitor] += 1;
                unpairVisitor.pop_front();
                unpairVisitor.push_front(currentPair);
            }
            else {
                nextChoice[visitor] += 1;
            }
        }
    }
    print(visitorPairs);
}