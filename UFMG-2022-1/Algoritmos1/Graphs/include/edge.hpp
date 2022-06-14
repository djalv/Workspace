#ifndef DJALV_EDGE
#define DJALV_EDGE

#include <iostream>
#include "node.hpp"

using namespace std;

class Edge {
    public:
        Node *u;
        Node *v;
        int w; // weight

        Edge(Node *u, Node *v, int w);
};

#endif