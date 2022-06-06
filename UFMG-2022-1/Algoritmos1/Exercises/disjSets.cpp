#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <iterator>
#include <string>

using namespace std;

class Node {
    public:
        int node;
        int subSet;

        Node() {
            node = -1;
            subSet = -1;
        }

        friend bool operator<(Node const &l, Node const &r) {
            if(l.node < r.node) {
                return true;
            }
            return false;
        }
};

class Sets {
    private:
        vector <list <Node>> s;
        int n;
    public:
        Sets(int n);
        void makeSet(Node x);
        void unionSets(Node &x, Node &y);
        
        Node findSet(Node &x);
        
        void printSets();
};

Sets::Sets(int n) {
    this->n = n;
    s.resize(n);
}

void Sets::makeSet(Node x) {
    s[x.node].push_back(x);
    x.subSet = x.node;
}

Node Sets::findSet(Node &x) {
    return s[x.subSet].front();
}

void Sets::unionSets(Node &x, Node &y) {
    s[x.subSet].merge(s[y.subSet]);
    y.subSet = x.subSet;
}

void Sets::printSets() {
    list <Node> :: iterator it;
    for(int i = 0; i < s.size(); i++) {
        for(it = s[i].begin(); it != s[i].end(); it++) {
            cout << (*it).node << " ";
        }
        cout << endl;
    }
}

int main() {
    int n = 5;
    vector <Node> nodes;
    nodes.resize(n);

    Sets s(n);
    
    for(int i = 0; i < n; i++) {
        nodes[i].node = i;
        nodes[i].subSet = i;
    }

    for(int i = 0; i < n; i++) {
        s.makeSet(nodes[i]);
    }
    s.unionSets(nodes[0], nodes[1]);
    s.printSets();
    
    Node x = s.findSet(nodes[0]);
    Node y = s.findSet(nodes[1]);

    cout << x.subSet << " " << y.subSet << endl;

    s.unionSets(nodes[1], nodes[2]);
    s.printSets();
    
    x = s.findSet(nodes[0]);
    y = s.findSet(nodes[1]);

    cout << x.subSet << " " << y.subSet << endl;

    return 0;
}