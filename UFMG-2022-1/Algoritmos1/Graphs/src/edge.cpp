#include "edge.hpp"

using namespace std;

Edge::Edge(Node *u, Node *v, int w) {
        this->u = u;
        this->v = v;
        this->w = w;
}

Edge::Edge() {
        this->u = nullptr;
        this->v = nullptr;
        this->w = 0;
}