#include <iostream>
#include "bike.hpp"

Bike::Bike() {
    id = -1;
    setLoc(-1, -1);
}

void Bike::setId(int id) {
    this->id = id;
}

int Bike::getId() {
    return id;
}

void Bike::setLoc(int x, int y) {
    geoLoc.x = x;
    geoLoc.y = y;
}

Loc Bike::getLoc() {
    return geoLoc;
}

void Bike::addBike(int id, int x, int y) {
    setId(id);
    setLoc(x, y);
}