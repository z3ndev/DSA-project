//Abdullah Noor
#ifndef AIRPORTRAILGRAPH_H
#define AIRPORTRAILGRAPH_H
#include "AirportRailGraphNode.h"
#include <iostream>
using namespace std;
class AirportRailGraph {
private:
    AirportRailGraphNode** nodes;
    int nodeCount, capacity;
    int findMinDistance(int* distances, bool* visited);
    void reconstructPath(int* predecessors, int start, int end, string* path, int& pathLength);
public:
    AirportRailGraph(int cap = 50);
    ~AirportRailGraph();
    int addNode(string name, string type, float x, float y);
    bool addEdge(int from, int to, int weight);
    void shortestRoute(int start, int end, string* path, int& pathLength, int& totalDistance);
    void display();
};
#endif