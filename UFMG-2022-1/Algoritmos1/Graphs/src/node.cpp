#include "node.hpp"

using namespace std;

Node::Node(int node) {
    this->node = node;
    color = "White";
    dist = -1;
    parent = -1;
    iniTime = -1;
    finalTime = -1;
    subSet = node;
}

Node::Node() {
    this->node = -1;
    color = "White";
    dist = -1;
    parent = -1;
    iniTime = -1;
    finalTime = -1;
    subSet = -1;
}