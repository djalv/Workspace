#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Numero de nós do grafo
#define SIZE 13

// Lista de adjacencias
vector <int> adj[SIZE];

// flag para marcar quais nós foram visitados
bool visited[SIZE];

// Pilha para armazenar a ordem topoligica do DAG
stack <int> order;

// Função para inicializar a flag
void init() {
    for(int i = 0; i < SIZE; i++) {
        visited[i] = false;
    }
}

// Faz o uso do DFS
void topological_order(int s) {
    visited[s] = true;
    for(int i = 0; i < adj[s].size(); i++) {
        if(visited[adj[s][i]] == false) {
            topological_order(adj[s][i]);
        }
    }
    order.push(s);
}