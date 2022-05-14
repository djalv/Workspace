#include <iostream>
#include "map.hpp"

Map::Map(int n, int rows, int columns) {
    this-> n = n;

    visitors.resize(n);
    bikes.resize(n);

    map.resize(rows);
    
    for(int i = 0; i < n; i++) {
        map[i].resize(columns);
    }   
}

void Map::addItem(char c, int x, int y) {
    if(x < n && x >= 0 && y < n && y >= 0) {
        int k = c;
        int idx;
        map[x][y] = c;

        if(k >= 97 && k <= 106) {
            idx = k - 97;
            visitors[idx].addVisitor(c, x, y);
        }
        else if(k >= 48 && k <= 57) {
            idx = k - 48;
            bikes[idx].addBike(idx, x, y);
        }
    }
}

void Map::setBikePreferences() {
    
}

