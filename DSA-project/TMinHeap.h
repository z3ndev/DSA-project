//Maaz Tahir
#pragma once
#include <string>
using namespace std;

/*
 MinHeap for Dijkstra (stores nodeID + distance)
 Implemented using arrays only.
*/

class TMinHeap {
private:
    string* ids;      // Node IDs
    double* dist;     // Distances
    int capacity;
    int size;

    // Heap helpers
    int parent(int i)
    {
        return (i - 1) / 2;
    }
    int left(int i) 
    {
        return 2 * i + 1; 
    }
    int right(int i)
    {
        return 2 * i + 2; 
    }

    void swap(int i, int j);

    void heapifyDown(int i);
    void heapifyUp(int i);

public:
    TMinHeap(int capacity = 200);
    ~TMinHeap();

    void insert(const string& id, double d);   // Push new node with distance
    bool isEmpty() const;                      // Check if heap empty
    void extractMin(string& id, double& d);    // Pop smallest distance
};
