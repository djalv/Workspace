#include <iostream>
#include "graphTP.hpp"

// Função construtora classe Node
Node::Node(int node) {
    this->node = node;
    color = "White";
    dist = -1;
    parent = -1;
    iniTime = -1;
    finalTime = -1;

    label = ' ';
}

// Funçao para criar um grafo
void Graph::initGraph(int n) {
    Node v(-1);
    
    for(int i = 0; i < n; i++) {
        Node v(i);
        nodes.push_back(v);
    }

    this-> n = n;
    adj.resize(n);
}

// Funçao para adicionar uma aresta
void Graph::addEdge(int u, int v) {
    Node x(v);
    adj[u].push_back(x);
}

// Funçao BFS do livro do Cormen
vector <int> Graph::BFS(Node s) {
    
    /*Tabela de cores dos nós
    White = Nó inexplorado
    Gray = Nó explorado mas seus vizinhos não totalmente explorados
    Black = Nó e todos os seus vizinhos explorados
    */
    
    // Inicializando a cor dos nós como branco
    for(int i = 0; i < nodes.size(); i++) {
        nodes[i].color = "White";
    }
    
    // Fila para armazenar os nós a serem explorados
    list <Node> q;
    list <Node> :: iterator v;
    
    // Vetor para guardar as camadas/distancias
    vector <int> distances;
    distances.resize(n);
    
    Node u(-1);

    // Marca o nó fonte com parcialmente explorado
    nodes[s.node].color = "Gray";
    nodes[s.node].dist = 0;
    nodes[s.node].parent = -1;
    distances[s.node] = nodes[s.node].dist;

    // Enfileira s
    q.push_back(s);
    while(!q.empty()) {
        // Desenfileira o nó u
        u = q.front();
        q.pop_front();

        // Percorre todos os nós vizinhos de u
        for(v = adj[u.node].begin(); v != adj[u.node].end(); v++) {
            
            // Se um nó vizinho, v, não foi explorado
            if(nodes[(*v).node].color == "White") {
                // Marque como cinza, adicione u como pai de v e
                // calcula a distancia
                
                nodes[(*v).node].color = "Gray";
                nodes[(*v).node].dist = nodes[u.node].dist + 1;
                nodes[(*v).node].parent = u.node;
                distances[(*v).node] = nodes[u.node].dist + 1;
                q.push_back(*v);
            }
        }
        nodes[u.node].color = "Black";
    }
    return distances;
}
