#ifndef CLIENT_DJALV
#define CLIENT_DJALV

#include <string>
#include "Loc.hpp"

class Client {
    private:
        int id;
        int age;
        double ticket;
        string uf;
        string payMethod;
        Loc geoLoc;
    public:
        Client();

        void setId(int i);
        int getId();

        void setAge(int a);
        int getAge();

        void calcTicket();
        double getTicket();

        void setUF(string state);
        string getUF();

        void setPayMethod(string p);
        string getPayMethod();

        void setLoc(int x, int y);
        Loc getLoc();

        void addClient(int id, int age, int x, int y, string uf, string payMethod);

        friend class Grid;
};
#endif