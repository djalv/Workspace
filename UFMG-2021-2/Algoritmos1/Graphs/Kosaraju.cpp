#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

#define SIZE 10

int V = 6, E = 12; // V = nº de nós e E = nº de arestas

vector <int> adj[SIZE];
vector <int> adj_rev[SIZE];
vector <int> components[SIZE];
stack <int> p;

bool visited[SIZE];
int numComponents = 0;
int component[SIZE];

void DFS(int s) {
    visited[s] = true;
    for(int i = 0; i < adj[s].size(); i++) {
        if(visited[adj[s][i]] == false) {
            DFS(adj[s][i]);
        }
        p.push(s);
    }
}

void rev_list() {
    vector <int> :: iterator it;
    int j = 0;
    int first, second;

    it = adj[j].begin();
    
    for(int i = 0; i < E; i++) {
        if(it == adj[j].end()){
            j++;
            it = adj[j].begin();
        }
        else{
            first = j;
            second = *it;
            adj_rev[second].push_back(first);
            it++;
        }
    }
}

void DFS_rev(int s) {
    component[s] = numComponents;
    components[numComponents].push_back(s);
    
    visited[s] = true;

    for(int i = 0; i < adj_rev[s].size(); i++) {
        if(visited[adj_rev[s][i]] == false) {
            DFS_rev(adj_rev[s][i]);
        }
        
    }
}

void kosaraju() {
    int s;

    for(int i = 0; i < V; i++) {
        if(!visited[i]) {
            DFS(i);
        }
    }

    for(int i = 0; i < V; i++) {
        visited[i] = false;
    }

    while(!p.empty()) {
        s = p.top();
        p.pop();

        if(!visited[s]) {
            //cout << "Component " << numComponents;
            DFS_rev(s);
            numComponents++;
            
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
    adj[0].push_back(2);

    adj[1].push_back(0);

    adj[2].push_back(1);

    adj[3].push_back(5);

    adj[4].push_back(3);

    adj[5].push_back(4);

    rev_list();
    kosaraju();

    for(int i = 0; i < numComponents; i++) {
        printVector(components[i]);
    }
    return 0;
}