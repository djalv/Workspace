#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

#define SIZE 6 // Numero de nós do grafo

// Lista de adjacencias
vector <int> adj[SIZE];
vector <int> path;

// flag para marcar quais nós foram visitados
bool visited[SIZE];

// Função para inicializar a flag
void init() {
    for(int i = 0; i < SIZE; i++) {
        visited[i] = false;
    }
}

void dfs(int s, int d, int k) {
    visited[s] = true;
    for(int i = 0; i < adj[s].size(); i++) {
        if(visited[adj[s][i]] == false && k > 0) {
            k--;
            path.push_back(adj[s][i]);
            dfs(adj[s][i], d, k);
        }
        if(k == 0) {
            path.pop_back();
            k++;
        }
    }
}

void printVector(vector <int> v) {
    vector <int> :: iterator it;
    
    for(it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    int k = 3;
    int d = 6;
    int s = 0;

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

    init();
    dfs(s,d,k);
    printVector(path);

    return 0;
}