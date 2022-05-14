#ifndef MAP_DJALV
#define MAP_DJALV

#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include <iterator>
#include "visitor.hpp"
#include "bike.hpp"

class Map {
    private:
        int n;
        vector <vector <char>> map;

        vector <Visitor> visitors;
        vector <Bike> bikes;

        vector <list <Visitor>> bikePreferences;
        vector <list <Bike>> visitorPreferences;
    public:
        Map(int n, int rows, int columns);
        void addItem(char c, int x, int y);
        void setBikePreferences();
        void setVisitorPreferences();
        void gale_shapley();
};

#endif