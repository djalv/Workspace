#ifndef HEAP_DJALV0
#define HEAP_DJALV0

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <iterator>
#include <string>
#include <cmath>
#include "node.hpp"
#include "edge.hpp"

using namespace std;


class Heap {
public:
    int size;
    int cap;
    vector <Node> A;
    vector <int> ids;

    Heap(int n) {
        size = 0;
        cap = n;
        A.resize(n);
        ids.resize(n);
    }

    int parent(int i) {
        return floor(i/2);
    }

    int left(int i) {
        return 2 * i + 1;
    }

    int right(int i) {
        return 2 * i + 2;
    }

    Node heapMinimum() {
        return A[0];
    }
    
    void insert(Node v) {
        if(size == cap) {
            cout << "Overflow: Não consegue inserir" << endl;
            return;
        }
        size = size + 1;
        int i = size - 1;
        A[i] = v;
        ids[v.node] = i;

        while(i != 0 && A[parent(i)].d >= A[i].d){
            Node aux = A[parent(i)];
            A[parent(i)] = A[i];
            A[i] = aux;
            
            ids[A[parent(i)].node] = parent(i);
            ids[A[i].node] = i;

            i = parent(i);
        }
    }

    void decreaseKey(int &idx, int d) {
        int i = ids[idx];
        A[i].d = d;

        while(i != 0 && A[parent(i)].d >= A[i].d){
            Node aux = A[parent(i)];
            A[parent(i)] = A[i];
            A[i] = aux;
            
            ids[A[parent(i)].node] = parent(i);
            ids[A[i].node] = i;

            i = parent(i);
        }
    }

    Node extractMin() {
        Node min = A[0];
        
        ids[A[0].node] = -1;
        A[0] = A[size-1];
        
        size = size - 1;
        minHeapfy(0);

        return min;
    }

    void minHeapfy(int i) {
        int l = left(i);
        int r = right(i);
        
        int min = i;

        if(l < size && A[l].d < A[i].d) {
            min = l;
        }
        else {
            min = i;
        }
        if(r < size && A[r].d < A[min].d) {
            min = r;
        }

        if(min != i) {
            Node aux = A[i];
            A[i] = A[min];
            A[min] = aux;

            ids[A[i].node] = i;
            ids[A[min].node] = min;
            minHeapfy(min);
        }
    }

    void printHeap() {
        for(int i = 0; i < size; i++) {
            cout << A[i].d << " ";
        }
        cout << endl;
    }
};

#endif