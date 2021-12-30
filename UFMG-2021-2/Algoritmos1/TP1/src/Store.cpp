#include <iostream>
#include "Store.hpp"

Store::Store() {
    id = -1;
    stock = 0;
    setLoc(-1, -1);
}
void Store::setId(int i) {
    id = i;
}

int Store::getId() {
    return id;
}

void Store::setStock(int s) {
    stock = s;
}

int Store::getStock() {
    return stock;
}

void Store::setLoc(int x, int y) {
    geoLoc.x = x;
    geoLoc.y = y;
}

Loc Store::getLoc() {
    return geoLoc;
}

void Store::addStore(int id, int stock, int x, int y) { // Função para adicionar
    setId(id);                                          // as lojas
    setStock(stock);
    setLoc(x, y);
}