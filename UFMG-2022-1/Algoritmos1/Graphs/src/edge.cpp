#include "edge.hpp"

using namespace std;

Edge::Edge(Node *u, Node *v, int w) {
        this->u = u;
        this->v = v;
        this->w = w;
}