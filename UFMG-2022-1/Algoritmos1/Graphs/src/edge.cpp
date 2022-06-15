#include "edge.hpp"

using namespace std;

Edge::Edge(Node *u, Node *v, int w, int f) {
        this->u = u;
        this->v = v;
        this->w = w;
        this->f = f;
}

Edge::Edge() {
        this->u = nullptr;
        this->v = nullptr;
        this->w = 0;
        this->f = 0;
}
