#include <iostream>
#include "Grid.hpp"

void printList(list <Client> &a) { // Função para imprimir uma lista
    list <Client> :: iterator k;   // do tipo Cliente
    for(k = a.begin(); k != a.end(); ++k) {
        cout << (*k).getId() << " ";
    }
    cout << endl;
}

void printList(list <Store> &a) { // Função para imprimir
    list <Store> :: iterator k;   // uma lista do tipo Store
    for(k = a.begin(); k != a.end(); ++k) {
        cout << (*k).getId() << " ";
    }
    cout << endl;
}

void printArray(double *a, int n) { // Imprime um array
    for(int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

void printMatrix(int **mat, int m, int n) { // Imprime uma matriz
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

Grid::Grid(int rows, int columns) {
    this->rows = rows;
    this->columns = columns;
}

int stateScore(string state) {
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

int payMethodScore(string payMethod) {
    if(payMethod == "DINHEIRO") {
        return 1;
    }
    else if(payMethod == "DEBITO") {
        return 2;
    }
    else {
        return 3;
    }
}

void fillIn(int *arr, int size) {   // Funçao para preencher
    for(int i = 0; i < size; i++) { // o vetor sequencialmente
        arr[i] = i;
    }
}

double* Grid::calcTickets(Client *c, int clients) { // Função que calcula o ticket
    tickets = new double[clients];                  // de todos os clients

    for(int i = 0; i < clients; i++) {
        double payScore = payMethodScore(c[i].getPayMethod());
        double ufScore = stateScore(c[i].getUF());
        tickets[i] = (abs(60 - c[i].getAge()) + ufScore) / payScore;
    }
    return tickets;
}

// Função para calcular a lista de preferencias das lojas
void Grid::setStorePreferences(Client *c, int clients, int stores) { 
    double *ticketsCopy = calcTickets(c, clients); // Copia todos os tickets
    storePreferences = new list <Client>[stores]; // Aloca uma nova lista do tipo Client

    int adj[clients]; // Cria uma matriz de adjacencia para armazenar as ids dos tickets
    fillIn(adj, clients);

    // Selection Sort para ordenar os tickets e a matriz de adjacencia em ordem decrescente
    int i, j, min_idx = 0;
    for(i = 0; i < clients-1; i++) {
        min_idx = i;
        for(j = i+1; j < clients; j++) {
            if(ticketsCopy[j] <= ticketsCopy[min_idx]) {
                min_idx = j;
            }
        }
        double aux = ticketsCopy[i];
        ticketsCopy[i] = ticketsCopy[min_idx];
        ticketsCopy[min_idx] = aux;
        

        int temp = adj[i];
        adj[i] = adj[min_idx];
        adj[min_idx] = temp;
    }

    // Aplica a regra de desempate
    for(i = 0; i < clients-1; i++) {
        for(j = i+1; j < clients; j++) {
            if(ticketsCopy[i] == ticketsCopy[j]) { // Caso há dois clientes com tickets iguais
                if(adj[i] < adj[j]) { // Verifica se a id do cliente i é menor do que a id de j
                    
                    // Faz a troca dos tickets
                    double aux = ticketsCopy[i];
                    ticketsCopy[i] = ticketsCopy[j];
                    ticketsCopy[j] = aux;
                    
                    // Faz a troca das ids
                    int temp = adj[i];
                    adj[i] = adj[j];
                    adj[j] = temp;
                }
            }
        }
    }

    // Armazena as ids ordenadas pelos tickets em uma lista
    for(i = 0; i < stores; i++) {
        for(j = 0; j < clients; j++) {
            storePreferences[i].push_front(c[adj[j]]);
        }
    }
}

// Função para calcular as distancias
void Grid::calcDistances(Client *c, Store *s, int clients, int stores) {
    int distances[clients][stores]; // Matriz para armazenar as distancias
    int adj[clients][stores]; // Matriz de adjacencia para armazenar as ids das lojas
    clientPreferences = new list <Store>[clients];
    
    // Calcula as distancias
    for(int i = 0; i < clients; i++) {
        Loc clientLoc = c[i].getLoc();
        for(int j = 0; j < stores; j++) {
            Loc storeLoc = s[j].getLoc();
            distances[i][j] = max(abs(clientLoc.x - storeLoc.x), abs(clientLoc.y - storeLoc.y)) - 1; // Distância de Chebyshev
            adj[i][j] = j; // Armazena as ids da lojas
        }
    }
    
    // Selection sort para ordenar as distancias e as ids
    int i, j, min_idx;
    for(int k = 0; k < clients; k++) {
        for(i = 0; i < stores-1; i++) {
            min_idx = i;
            for(j = i+1; j < stores; j++) {
                if(distances[k][j] < distances[k][min_idx]) {
                    min_idx = j;
                }
            }
            int aux = distances[k][i];
            distances[k][i] = distances[k][min_idx];
            distances[k][min_idx] = aux;

            aux = adj[k][i];
            adj[k][i] = adj[k][min_idx];
            adj[k][min_idx] = aux;
        }
    }

    // Aplica a regra de desempate de lojas
    for(int k = 0; k < clients; k++) {
        for(i = 0; i < stores-1; i++) {
            for(j = i+1; j < stores; j++) {
                if(distances[k][i] == distances[k][j]) {
                    if(adj[k][i] > adj[k][j]) {
                        int aux = distances[k][i];
                        distances[k][i] = distances[k][j];
                        distances[k][j] = aux;

                        aux = adj[k][i];
                        adj[k][i] = adj[k][j];
                        adj[k][j] = aux;
                    }
                }
            }
        }
    }

    // Armazena as ids das lojas
    for(i = 0; i < clients; i++) {
        for(j = 0; j < stores; j++) {
            clientPreferences[i].push_back(s[adj[i][j]]);
        }
    }
}

// Implementação do Gale Shapley
// Funçao para preencher uma lista sequencialmente (0 -> n)
void range(list <int> &ls, int size) {
    for(int i = 0; i < size; i++) {
        ls.push_back(i);
    }
}

// Função para preencher um array com 0 ou -1
void fill(int* arr, int size, bool zero) {
    if(zero) {
        for(int i = 0; i < size; i++) {
            arr[i] = -1;
        }
    }
    else {
        for(int i = 0; i < size; i++) {
            arr[i] = 0;
        }
    }
}

// Funçao para procuar um indice e retorna o elemento do indice
int search(list <Client> &ls, int index) {
    list <Client> :: iterator it;
    int i = 0;
    
    for(it = ls.begin(); it != ls.end(); ++it) {
        if(i == index) {
            break;
        }
        i++;
    }
    return (*it).getId();
}

// Funçao para deletar um indice na lista
void pop(list <Client> &ls, long unsigned int x) {
    list <Client> :: iterator it;
    long unsigned int i = 0;
    for(it = ls.begin(); it != ls.end(); it++) {
        if(i == x) {
            ls.erase(it);
            break;
        }
        i++;
    }
}

// Funçao para procurar o indice de um elemento numa lista do tipo Store
int indexOf(list <Store> &ls, int x) {
    list <Store> :: iterator it;
    int i = 0;
    for(it = ls.begin(); it != ls.end(); it++) {
        if((*it).getId() == x) {
            break;
        }
        i++;
    }
    return i;
}

// Funçao para procurar o indice de um elemento numa lista do tipo Client
int indexOf(list <Client> &ls, int x) {
    list <Client> :: iterator it;
    int i = 0;
    for(it = ls.begin(); it != ls.end(); it++) {
        if((*it).getId() == x) {
            break;
        }
        i++;
    }
    return i;
}


void Grid::gale_shapley(Client *c, Store *s, int clients, int stores) {
    list <int> withStock; // Armazena as lojas com estoque disponivel
    list <Client> schedule[stores], shopList;
    list <Store> clientList;

    int store, client, next, currentPair, currentPairRank, shopRank, index;
    int nextChoice[stores], clientPairs[clients];
    
    range(withStock, stores);
    fill(nextChoice, stores, false);
    fill(clientPairs, clients, true);
    
    // Enquanto tiver uma loja com estoque disponivel
    while(!withStock.empty()) {
        // Pega a primeira loja com estoque
        store = withStock.front();

        // Carrega a lista de prefencias da loja
        shopList = storePreferences[store];
        
        // Armazena o indice do proximo cliente
        next = nextChoice[store];

        // Procura o proximo cliente na lista de preferencias da loja
        client = search(shopList, next);

        // Carrega a lista de preferencias do cliente
        clientList = clientPreferences[client];

        // Armazena o par atual do cliente
        currentPair = clientPairs[client];
        
        // Verifica se a loja tem estoque e se o cliente não tem par
        if(s[store].getStock() > 0 && currentPair == -1) {
            // Agenda o cliente na loja
            schedule[store].push_back(c[client]);

            // Atribui o cliente o novo par
            clientPairs[client] = store;

            // Muda qual cliente a propor
            nextChoice[store]++;

            // Decrementa o estoque da loja
            s[store].stock--;
            
            // Se o estoque da loja for igual a 0
            if(s[store].stock == 0) {
                // Tira ele da lista das lojas com estoque
                withStock.pop_front();
            }
        }
        // Caso o cliente ja tenha um par
        else if(s[store].getStock() > 0){
            // Armazena o rank do par atual do cliente
            currentPairRank = indexOf(clientList, currentPair);

            // Armazena o rank da loja
            shopRank = indexOf(clientList, store);

            // Se o cliente prefere a loja do que o seu atual par
            if(currentPairRank > shopRank) {
                // Agenda o cliente na loja
                schedule[store].push_back(c[client]);
                
                // Descobre qual o indice do atual par no agendamento
                index = indexOf(schedule[currentPair], client);

                // Retira o agendamento do cliente no par atual
                pop(schedule[currentPair], index);
                
                // Client recebe um novo par
                clientPairs[client] = store;
                nextChoice[store]++;
                s[store].stock--;

                // Incrementa o estoque da antiga loja
                s[currentPair].stock++;
                
                if(s[store].stock == 0) {
                    withStock.pop_front();
                }
                // Coloca a antiga loja na lista de lojas com estoque disponivel
                withStock.push_front(currentPair);
            }
            else {
                // O cliente prefere o atual par do q a loja
                nextChoice[store]++;
            }
        }
    }
    
    for(int i = 0; i < stores; i++) {
        cout << i << endl;
        printList(schedule[i]);
    }
}