#ifndef STORE_DJALV
#define STORE_DJALV

#include "Loc.hpp"

class Store {
    private:
        int id;
        int stock;
        Loc geoLoc;
    public:
        Store();

        void setId(int i);
        int getId();
        
        void setStock(int s);
        int getStock();

        void setLoc(int x, int y);
        Loc getLoc();

        void addStore(int id, int stock, int x, int y);

        friend class Grid;
};
#endif