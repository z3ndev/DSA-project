//Abdullah Noor
#ifndef MALLGRAPH_H
#define MALLGRAPH_H
#include "MallGraphNode.h"
#include <iostream>
using namespace std;
class MallGraph {
private:
    MallGraphNode** nodes;
    int nodeCount;
    int capacity;
    int findMinDistance(int* distances, bool* visited);
    void reconstructPath(int* predecessors, int start, int end, string* path, int& pathLength);
public:
    MallGraph(int cap = 100);
    ~MallGraph();
    int addNode(string mallID, float x, float y);
    bool addEdge(int from, int to, int weight);
    void dijkstra(int start, int end, string* path, int& pathLength, int& totalDistance);
    int findNearestMall(float x, float y);
    void display();
};
#endif