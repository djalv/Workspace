#ifndef GRID_DJALV
#define GRID_DJALV

#include <cmath>
#include <list>
#include <iterator>
#include "Client.hpp"
#include "Store.hpp"


class Grid {
    private:
        int rows;
        int columns;
        double *tickets;
        list <Client> *storePreferences;
        list <Store> *clientPreferences;
    public:
        Grid(int rows, int columns);
        double* calcTickets(Client *c, int clients);
        void setStorePreferences(Client *c, int clients, int stores);
        void calcDistances(Client *c, Store *s, int clients, int stores);
        void gale_shapley(Client *c, Store *s, int clients, int stores);
};
#endif