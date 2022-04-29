#include <iostream>
#include <list>

using namespace std;

void gTranspose(list <int> *adj, list <int> *adjT, int n) {
    list <int> q;
    int v;

    for(int i = 0; i < n; i++) {
        q = adj[i];
        
        while(!q.empty()) {
            v = q.front();
            q.pop_front();

            adjT[v].push_back(i);
        }
    }
}

int main() {
    int n = 6;
    list <int> adj[n];
    list <int> adjT[n];
    list <int> :: iterator it;

    adj[0].push_back(1);
    adj[0].push_back(3);

    adj[1].push_back(4);

    adj[2].push_back(5);
    adj[2].push_back(4);

    adj[3].push_back(1);
    
    adj[4].push_back(3);

    adj[5].push_back(5);
    
    gTranspose(adj, adjT, n);

    for(int i = 0; i < n; i++) {
        cout << i << " ";
        for(it = adjT[i].begin(); it != adjT[i].end(); it++) {
            cout << *it << " ";
        }cout << endl;
    }
    return 0;
}