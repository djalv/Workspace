#ifndef DJALV_NODE
#define DJALV_NODE

#include <iostream>

using namespace std;

class Node {
    public:
        int node;
        int dist;
        int iniTime;
        int finalTime;
        int subSet;

        int d; // Estimativa de custo minino
        int p; // Nó parente na arvore de caminhos minimos

        int parent;
        string color;

        Node(int node);
        Node();

        friend bool operator<(Node const &l, Node const &r) {
            if(l.node < r.node) {
                return true;
            }
            return false;
        }

        friend bool operator==(Node const &l, Node const &r) {
            if(l.node == r.node) {
                return true;
            }
            return false;
        }

        friend bool operator!=(Node const &l, Node const &r) {
            if(l.node != r.node) {
                return true;
            }
            return false;
        }
};

#endif