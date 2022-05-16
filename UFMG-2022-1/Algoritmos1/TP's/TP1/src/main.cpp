#include  <iostream>
#include <fstream>
#include "map.hpp"

int main() {
    ifstream file("test.txt");
    vector <vector <int>> preferences;
    
    int n, rows, columns;
    char in;
    int number;

    file >> n;

    preferences.resize(n);
    
    for(int i = 0; i < n; i++) {
        preferences[i].resize(n);
    }   

    file >> rows >> columns;

    Map m(n, rows, columns);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            file >> in;
            m.addItem(in, i, j);
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            file >> number;
            preferences[i][j] = number;
        }
    }
    
    m.setVisitorPreferences(preferences);
    m.setBikePreferences();
    m.gale_shapley();
    file.close();
    return 0;
}