//Abdullah Noor
#ifndef SCHOOLGRAPH_H
#define SCHOOLGRAPH_H
#include "SchoolGraphNode.h"
#include <iostream>
using namespace std;

class SchoolGraph {
private:
    SchoolGraphNode** nodes;
    int nodeCount;
    int capacity;
    int findMinDistance(int* distances, bool* visited);
    void reconstructPath(int* predecessors, int start, int end, string* path, int& pathLength);
public:
    SchoolGraph(int cap = 100);
    ~SchoolGraph();
    int addNode(string schoolID, float x, float y);
    bool addEdge(int from, int to, int weight);
    void dijkstra(int start, int end, string* path, int& pathLength, int& totalDistance);
    int findNearestSchool(float x, float y);
    void display();
};
#endif
