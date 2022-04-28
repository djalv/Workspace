#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <iterator>

using namespace std;



void bfs(list <int> *adj, list <int> *L, bool *discovered, int s) {
    int i = 0;
    list <int> :: iterator u;
    list <int> q;


    discovered[s] = true;
    L[0].push_back(s);

    while(!L[i].empty()) {
        for(u = L[i].begin(); u != L[i].end(); ++u) {
            q = adj[(*u)];
            
            while(!q.empty()) {
                int v = q.front();
                
                q.pop_front();

                if(discovered[v] == false) {
                    discovered[v] = true;
                    L[i+1].push_back(v);
                }
            }
        }
        i++; 
    }
}

int main() {
    int n = 4;
    bool discovered[n];

    for(int i = 0; i < n; i++) {
        discovered[i] = false;
    }

    list <int> adj[n], L[n];
    list <int> :: iterator j;

    adj[0].push_back(1);
    adj[0].push_back(2);

    adj[1].push_back(0);
    adj[1].push_back(2);

    adj[2].push_back(0);
    adj[2].push_back(1);
    adj[2].push_back(3);

    adj[3].push_back(2);
    adj[3].push_back(3);

    bfs(adj, L, discovered, 3);

    for(int i = 0; i < n; i++) {
        for(j = L[i].begin(); j != L[i].end(); j++) {
            cout << *j << " ";
        }
        cout << endl;
    }
    return 0;
}