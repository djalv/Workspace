#include <iostream>
#include "Client.hpp"

int stateScoreClient(string state) { // Função que retorna o score do estado
    if(state == "MG") {
        return 0;
    }
    else if(state == "PR") {
        return 10;
    }
    else if(state == "SP") {
        return 20;
    }
    else if(state == "SC") {
        return 30;
    }
    else if(state == "RJ") {
        return 40;
    }
    else if(state == "RN") {
        return 50;
    }
    else {
        return 60;
    }
}

int payMethodScoreClient(string payMethod) { // Funçao que retorna o 
    if(payMethod == "DINHEIRO") {            // score para tipo de pagamento
        return 1;
    }
    else if(payMethod == "DEBITO") {
        return 2;
    }
    else {
        return 3;
    }
}

Client::Client() { // Construtor
    id = -1;
    age = -1;
    uf = " ";
    payMethod = " ";
    setLoc(-1, -1);
}

void Client::setId(int i) {
    id = i;
}

int Client::getId() {
    return id;
}

void Client::setAge(int a) {
    age = a;
}

int Client::getAge() {
    return age;
}

void Client::calcTicket() { // Calcula o ticket do cliente
    double payScore = payMethodScoreClient(payMethod);
    double ufScore = stateScoreClient(uf);

    ticket = (abs(60 - age) + ufScore) / payScore;
}

double Client::getTicket() {
    return ticket;
}

void Client::setUF(string state) {
    uf = state;
}

string Client::getUF() {
    return uf;
}

void Client::setPayMethod(string p) {
    payMethod = p;
}

string Client::getPayMethod() {
    return payMethod;
}

void Client::setLoc(int x, int y) {
    geoLoc.x = x;
    geoLoc.y = y;
}

Loc Client::getLoc() {
    return geoLoc;
}

void Client::addClient(int id, int age, int x, int y, string uf, string payMethod) { // Função para adicionar
    setId(id);                                                                       // os clientes
    setAge(age);
    setLoc(x, y);
    setUF(uf);
    setPayMethod(payMethod);
    calcTicket();
}