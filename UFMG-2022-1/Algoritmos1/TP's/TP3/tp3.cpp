#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

typedef struct {
    int x;
    int y;
    int area;
}Area, Table;


vector <int> leftIndex(vector <int> &arr) { // O(n)
    vector <int> l; // Indices no qual é o elemento mais proximo a esquerda com valor menor q i
    
    stack <pair <int, int>> s; // Stack para memorizar os elementos menores anteriores em ordem crescente dos valores
                               // O primeiro é o valor e o segundo é o indice

    for(int i = 0; i < arr.size(); i++) {
        if(s.empty()) { // Se a stack estiver vazia é pq nn exite nenhum elemento a esquerda menor q i
            l.push_back(-1);
        }
        else if(!s.empty() && s.top().first < arr[i]) { // Se o valor do topo da stack for menor q o valor de i
            l.push_back(s.top().second);                // então o indice do topo da stack é o 
        }                                               // elemento mais proximo a esquerda menor q o valor de i

        else if(!s.empty() && s.top().first >= arr[i]) { // Se o valor do topo da stack for maior q o valor de i
            while(!s.empty() && s.top().first >= arr[i]) { // então desempilhamos até acharmos um valor menor q o valor de i
                s.pop();
            }
            if(s.empty()) { // Se a stack esvazia
                l.push_back(-1); // é pq não existe elemento com valor menor q o valor de i
            }
            else { // Senão o elemento do topo da stack é o elemento mais proximo a esquerda menor q o valor de i
                l.push_back(s.top().second);
            }
        }
        s.push({arr[i], i});
    }
    return l;
}

vector <int> rightIndex(vector <int> &arr) { // O(n)
    vector <int> r; // Indices no qual é o elemento mais proximo a direita com valor menor q i
    stack <pair <int, int>> s; // Stack para memorizar os elementos menores posteriores em ordem crescente dos valores

    for(int i = arr.size()-1; i >= 0; i--) {
        if(s.empty()) { // Se a stack estiver vazia é pq não existe elemento menor q i a direita
            r.push_back(arr.size());
        }
        else if(!s.empty() && s.top().first < arr[i]) { // Se o valor do topo da stack for menor q o valor de i
            r.push_back(s.top().second);                // então o indice do topo da stack é o 
        }                                               // elemento mais proximo a esquerda menor q o valor de i
        
        else if(!s.empty() && s.top().first >= arr[i]) { // Se o valor do topo da stack for maior q o valor de i
            while(!s.empty() && s.top().first >= arr[i]) { // então desempilhamos até acharmos um valor menor q o valor de i
                s.pop();
            }
            if(s.empty()) { // Se a stack esvazia
                r.push_back(arr.size()); // é pq não existe elemento com valor menor q o valor de i
            }
            else { // Senão o elemento do topo da stack é o elemento mais proximo a direita menor q o valor de i
                r.push_back(s.top().second);
            }
        }
        s.push({arr[i], i});
    }
    reverse(r.begin(), r.end());
    return r;
}

int maxAreaRectangle(vector <int> &arr, int &x, int &y) {
    int maxArea = 0, area = 0;

    vector <int> l = leftIndex(arr);
    vector <int> r = rightIndex(arr);

    vector <int> width;

    for(int i = 0; i < arr.size(); i++) { // Calcula a largura
        width.push_back(r[i] - l[i] - 1);
    }

    maxArea = width[0] * arr[0];
    x = width[0];
    y = arr[0];

    for(int i = 0; i < arr.size(); i++) { // Calcula e Acha a maior area
        area = width[i] * arr[i];
        
        if(area >= maxArea) {
            if(area == maxArea) {
                if(arr[i] >= y) {
                    x = width[i];
                    y = arr[i];
                }
            }
            else {
                x = width[i];
                y = arr[i];
            }
            maxArea = area;
        }
    }
    
    return maxArea;
}

void areaOfRectangles(vector <vector <int>> &arr, vector <Area> &areas) {
    vector <int> v(arr[0].size(), 0);
    Area a, maxArea;
    int area, x, y, spaceLength, spaceWidth;
    
    maxArea.x = -1;
    maxArea.y = -1;
    maxArea.area = -1;

    // Vamos montar o histograma
    for(int i = 0; i < arr.size(); i++) {
        for(int j = 0; j < arr[i].size(); j++) {
            if(arr[i][j] == 0) {
                v[j] = 0;
            }
            else {
                v[j] += arr[i][j];
            }
        }

        area = maxAreaRectangle(v, spaceLength, spaceWidth);
        a.area = area;
        a.x = spaceLength;
        a.y = spaceWidth;
        areas.push_back(a);

        if(a.area > maxArea.area) {
            maxArea = a;
        }
    }
}

int main() {
    int rows, columns, qtdTables, c, x, y, spaceLength, spaceWidth;
    int area, maxWidth;
    int tableX, tableY;
    char in;
    Table t, maxTableArea, s;
    
    maxTableArea.area = -1;
    maxTableArea.x = -1;
    maxTableArea.y = -1;
    
    vector <vector <int>> space;
    vector <Area> spaceAreas;
    vector <Table> tables;

    cin >> rows >> columns;
    space.resize(rows);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            cin >> in;
            if(in == '#') {
                c = 0;
            }
            else if(in == '.') {
                c = 1;
            }
            space[i].push_back(c);
        }
        in = ' ';
    }

    areaOfRectangles(space, spaceAreas);
    cin >> qtdTables;
    
    for(int i = 0; i < qtdTables; i++) {
        cin >> x >> y;
        t.x = x;
        t.y = y;
        t.area = x * y;
        tables.push_back(t);

    }

    // Calcula a maior mesa e aplica a regra de desempate
    for(int i = 0; i < tables.size(); i++) {
        for(int j = 0; j < spaceAreas.size(); j++) {
            if(tables[i].area <= spaceAreas[j].area) {
                if((tables[i].x <= spaceAreas[j].x && tables[i].y <= spaceAreas[j].y) || (tables[i].x <= spaceAreas[j].y && tables[i].y <= spaceAreas[j].x)) {
                    if(tables[i].area >= maxTableArea.area) {
                        if(tables[i].area == maxTableArea.area) {
                            if(tables[i].y > maxTableArea.y) {
                                maxTableArea = tables[i];
                                s = spaceAreas[j];
                            }
                        }
                        else {
                            maxTableArea = tables[i];
                            s = spaceAreas[j];
                        }
                    }
                }
            }
        }
    }
    
    cout << maxTableArea.x << " " << maxTableArea.y << endl;
    
    return 0;
}
