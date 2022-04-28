#include <iostream>
#include <vector>
#include <queue>

#define SIZE 13 // Numero de nós do grafo
using namespace std;

// Lista de adjacencias
vector <int> adj[SIZE];


// Camada dos nós
int level[SIZE];

// flag para marcar quais nós foram visitados
bool visited[SIZE];

void init() {
    for(int i = 0; i < SIZE; i++) {
        visited[i] = false;
    }
}

void bfs(int s) {    
    // Fila para armazenar os nós a serem processados
    queue <int> q;

    // Insere s na fila
    q.push(s);

    // Defina a camada do primeiro nó
    level[s] = 0;

    // Marca s como visitado
    visited[s] = true;
    
    // Pecorreremos toda a lista de adj
    while(!q.empty()) {
        // Pegue o primeiro nó da fila
        int p = q.front();

        // Remova o primeiro item da fila
        q.pop();

        // Pecorreremos todos os vizinhos de p
        for(int i = 0; i < adj[p].size(); i++) {
            // Se um vizinho de p não foi visitado
            if(visited[adj[p][i]] == false) {
                // Incrementa o seu level
                level[adj[p][i]] = level[p] + 1;
                // Add ele na fila para seus vizinhos sejam processados
                q.push(adj[p][i]);
                // Marque p como vistado
                visited[adj[p][i]] = true;
            }
        }
    }
}

int main() {
    adj[0].push_back(1);
    adj[0].push_back(4);

    adj[1].push_back(0);
    adj[1].push_back(2);

    adj[2].push_back(1);
    adj[2].push_back(3);
    
    adj[3].push_back(2);
    adj[3].push_back(6);

    adj[4].push_back(0);
    adj[4].push_back(5);

    adj[5].push_back(4);
    adj[5].push_back(6);

    adj[6].push_back(5);
    adj[6].push_back(3);

}