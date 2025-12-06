#ifndef HOSPITALGRAPH_H
#define HOSPITALGRAPH_H

#include "HospitalGraphNode.h"
#include <iostream>
#include <cmath>
#include <climits>
using namespace std;

class HospitalGraph {
private:
    HospitalGraphNode** nodes;
    int nodeCount, capacity;
    int findMinDistance(int* distances, bool* visited);
    void reconstructPath(int* predecessors, int start, int end, string* path, int& pathLength);
public:
    HospitalGraph(int cap = 100);
    ~HospitalGraph();
    int addNode(string hospitalID, float x, float y);
    bool addEdge(int from, int to, int weight);
    void dijkstra(int start, int end, string* path, int& pathLength, int& totalDistance);
    int findNearestHospital(float x, float y);
    void display();
};
#endif