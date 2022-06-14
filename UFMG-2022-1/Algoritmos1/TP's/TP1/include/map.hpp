#ifndef MAP_DJALV
#define MAP_DJALV

#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include <iterator>
#include "visitor.hpp"
#include "bike.hpp"
#include "graphTP.hpp"

class Map {
    private:
        int n;
        int rows;
        int columns;
        vector <vector <char>> map;
        Graph graph;

        vector <Visitor> visitors;
        vector <Bike> bikes;

        vector <int> nodeVisitors;
        vector <int> nodeBikes;

        vector <vector <int>> bikePreferences;
        vector <vector <int>> visitorPreferences;
    public:
        Map(int n, int rows, int columns);
        
        void addItem(char c, int x, int y);
        void createGraph();
        
        void setBikePreferences();
        void setVisitorPreferences(vector <vector <int>> &preferences);
        void gale_shapley();
};

#endif