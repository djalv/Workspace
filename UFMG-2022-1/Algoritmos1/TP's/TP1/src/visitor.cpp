#include <iostream>
#include "visitor.hpp"

Visitor::Visitor() {
    id = -1;
    setLoc(-1, -1);
}

void Visitor::setId(int id) {
    this->id = id;
}

int Visitor::getId() {
    return id;
}

void Visitor::setC_id(char c_id) {
    this->c_id = c_id;
}

char Visitor::getC_id() {
    return c_id;
}

void Visitor::setLoc(int x, int y) {
    geoLoc.x = x;
    geoLoc.y = y;
}

Loc Visitor::getLoc() {
    return geoLoc;
}

void Visitor::addVisitor(char c, int x, int y) {
    int i = c - 97;
    setId(i);
    setC_id(c);
    setLoc(x, y);
}