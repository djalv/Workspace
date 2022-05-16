#ifndef BIKE_DJALV
#define BIKE_DJALV

#include "loc.hpp"

class Bike {
    private:
        int id;
        Loc geoLoc;
    public:
        Bike();

        void setId(int id);
        int getId();

        void setLoc(int x, int y);
        Loc getLoc();

        void addBike(int id, int x, int y);

        friend class Map;
};

#endif