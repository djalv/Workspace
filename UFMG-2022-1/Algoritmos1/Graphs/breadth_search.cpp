#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <iterator>

using namespace std;

void bfs(list <int> *adj, list <int> &conect, int *levels, bool *discovered, int s, int n) {
    list <int> q;
    list <int> :: iterator u;

    for(int i = 0; i < n; i++) {
        discovered[i] = false;
    }

    discovered[s] = true;
    levels[s] = 0;
    q.push_back(s);

    while(!q.empty()) {
        int v = q.front();
        q.pop_front();

        conect.push_back(v);
        
        for(u = adj[v].begin(); u != adj[v].end(); u++) {
            if(discovered[*u] == false) {
                discovered[*u] = true;
                q.push_back(*u);
                levels[*u] = levels[v] + 1;
            }
        }
    }
}

int main() {
    int n = 6;
    int levels[n];
    bool discovered[n];

    list <int> adj[n];
    list <int> comp_conect;
    list <int> :: iterator it;

    adj[0].push_back(1);
    adj[0].push_back(2);

    adj[1].push_back(0);
    adj[1].push_back(2);

    adj[2].push_back(0);
    adj[2].push_back(1);
    adj[2].push_back(3);

    adj[3].push_back(2);
    adj[3].push_back(3);
    adj[3].push_back(4);

    adj[4].push_back(3);
    adj[4].push_back(5);

    adj[5].push_back(4);
    
    bfs(adj, comp_conect, levels, discovered, 2, n);
    
    for(it = comp_conect.begin(); it != comp_conect.end(); it++) {
        cout << *it << " ";
    }cout << endl;
    
    return 0;
}