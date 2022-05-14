#ifndef VISITOR_DJALV
#define VISITOR_DJALV

#include <string>
#include "loc.hpp"

class Visitor {
    private:
        int id;
        char c_id;
        Loc geoLoc;
    public:
        Visitor();

        void setId(int id);
        int getId();

        void setC_id(char c_id);
        char getC_id();
        
        void setLoc(int x, int y);
        Loc getLoc();

        void addVisitor(char c, int x, int y);

        friend class Map;
};

#endif