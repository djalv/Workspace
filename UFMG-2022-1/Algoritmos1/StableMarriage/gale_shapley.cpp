#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include <fstream>

using namespace std;

void range(list <int> &ls, int n) {
    for(int i = 0; i < n; i++) {
        ls.push_back(i);
    }
}

void fill(vector <int> &v, int n, bool zero = false) {
    int x = 0;
    
    if(!zero) {
        x = -1;
    }

    for(int i = 0; i < n; i++) {
        v.push_back(x);
    }
}

void print(vector <int> &v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void printList(list <int> &a) {
    list <int> :: iterator k;
    for(k = a.begin(); k != a.end(); ++k) {
        cout << *k << " ";
    }
    cout << endl;
}

void stable_matching(vector <int> *menPreferencesList, vector <int> *womenPreferenceList, int n){
    list <int> unpairMen;
    vector <int> manList, womanList, menPairs, womenPairs, nextChoice;
    int rank[n][n];
    int man, woman, nextWoman, currentPair, currentPairRank, manRank;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            rank[i][womenPreferenceList[i][j]-1] = j;
        }
    }

    range(unpairMen, n);
    fill(menPairs, n);
    fill(womenPairs, n);
    fill(nextChoice, n, true);

    while(!unpairMen.empty()) {
        man = unpairMen.front();

        manList = menPreferencesList[man];
        nextWoman = nextChoice[man];

        woman = manList[nextWoman];
        womanList = womenPreferenceList[woman];

        currentPair = womenPairs[woman];

        if(currentPair == -1) {
            womenPairs[woman] = man;
            menPairs[man] = woman;

            nextChoice[man] += 1;
            unpairMen.pop_front();
        }
        else {
            currentPairRank = rank[woman][currentPair];
            manRank = rank[woman][man];

            if(currentPairRank > manRank) {
                womenPairs[woman] = man;
                menPairs[man] = woman;

                nextChoice[man] += 1;
                unpairMen.pop_front();
                unpairMen.push_front(currentPairRank);
            }
            else {
                nextChoice[man] += 1;
            }
        }
    }
    print(menPairs);
}

int main() {
    int n, in;

    ifstream file("in.txt");
    file >> n;
    
    vector <int> h[n], s[n];

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            file >> in;
            h[i].push_back(in);
        }
    }
    
    file >> n;
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            file >> in;
            s[i].push_back(in);
        }
    }

    stable_matching(h, s, n);

    return 0;
}