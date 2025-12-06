//Abdullah Noor
#ifndef FACILITYGRAPH_H
#define FACILITYGRAPH_H
#include "FacilityGraphNode.h"
#include <iostream>
using namespace std;
class FacilityGraph {
private:
    FacilityGraphNode** nodes;
    int nodeCount, capacity;
    int findMinDistance(int* distances, bool* visited);
    void reconstructPath(int* predecessors, int start, int end, string* path, int& pathLength);
public:
    FacilityGraph(int cap = 100);
    ~FacilityGraph();
    int addNode(string facilityID, string type, float x, float y);
    bool addEdge(int from, int to, int weight);
    void dijkstra(int start, int end, string* path, int& pathLength, int& totalDistance);
    int findNearestFacility(float x, float y, string facilityType);
    void display();
};
#endif