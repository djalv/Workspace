#include <iostream>
#include <list>
#include <iterator>
#include <fstream>

using namespace std;

void range(list <int> &ls, int size) {
    for(int i = 0; i < size; i++) {
        ls.push_back(i);
    }
}

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

int search(list <int> &ls, int index) {
    list <int> :: iterator it;
    int i = 0;
    
    for(it = ls.begin(); it != ls.end(); ++it) {
        if(i == index) {
            break;
        }
        else {
            i++;
        }
    }
    return *it;
}

int indexOf(list <int> &v, int x, int size) {
    list <int> :: iterator it;
    int i;
    it = v.begin();

    for(i = 0; i < size; i++) {
        if(*it == x) {
            break;
        }
        it++;
    }
    return i;
}

void printList(list <int> &a) {
    list <int> :: iterator k;
    for(k = a.begin(); k != a.end(); ++k) {
        cout << *k << " ";
    }
    cout << endl;
}

void printArray(int *a, int n) {
    for(int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

void gale_shapley(list <int> *hsPreferences, list <int> *stPreferences, int n) {
    list <int> unpairsHospitals;
    list <int> listHsPreferences, listStPreferences;

    int studentPairs[n], hospitalPairs[n], nextHsChoice[n];
    int hospital, student, next, currentPair, currentPairRank, hsRank;

    range(unpairsHospitals, n);
    fill(studentPairs, n, true);
    fill(hospitalPairs, n, true);
    fill(nextHsChoice, n, false);

    while(!unpairsHospitals.empty()) {
        hospital = unpairsHospitals.front();
        
        listHsPreferences = hsPreferences[hospital];
        

        next = nextHsChoice[hospital];
        student = search(listHsPreferences, next);

        listStPreferences = stPreferences[student];

        currentPair = studentPairs[student];

        if(currentPair == -1) {
            studentPairs[student] = hospital;
            hospitalPairs[hospital] = student;

            nextHsChoice[hospital] += 1;

            unpairsHospitals.pop_front();
        }

        else{
            currentPairRank = indexOf(listStPreferences, currentPair, n);

            hsRank = indexOf(listStPreferences, hospital, n);

            if(currentPairRank > hsRank) {
                studentPairs[student] = hospital;
                hospitalPairs[hospital] = student;

                nextHsChoice[hospital] += 1;

                unpairsHospitals.pop_front();
                unpairsHospitals.push_front(currentPairRank);
            }
            else {
                nextHsChoice[hospital] += 1;
            }
        }
    }
    printArray(hospitalPairs, n);
}

int main() {
    int n, in;

    ifstream file("in.txt");
    file >> n;
    
    list <int> h[n], s[n];

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            file >> in;
            h[i].push_back(in);
        }
        cout << endl;
    }
    
    file >> n;
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            file >> in;
            s[i].push_back(in);
        }
    }

    gale_shapley(h,s,n);

    return 0;
}