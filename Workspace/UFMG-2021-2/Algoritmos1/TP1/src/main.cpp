#include  <iostream>
#include <fstream>
#include "Grid.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    
    ifstream file(argv[1]);
    int rows, columns, numStores, numClients;
    int capacity, x, y, age;
    string state, payMethod;

    file >> rows >> columns;
    file >> numStores;

    Store s[numStores];
    Grid g = Grid(rows, columns);

    for(int i = 0; i < numStores; i++) {
        file >> capacity >> x >> y;
        s[i].addStore(i, capacity, x, y);
    }
    file >> numClients;
    Client c[numClients];

    for(int i = 0; i < numClients; i++) {
        file >> age >> state >> payMethod >> x >> y;
        c[i].addClient(i, age, x, y, state, payMethod);
        state = " ";
        payMethod = " ";
    }
    g.setStorePreferences(c, numClients, numStores);
    g.calcDistances(c, s, numClients, numStores);
    g.gale_shapley(c, s, numClients, numStores);
    file.close();
    return 0;
}